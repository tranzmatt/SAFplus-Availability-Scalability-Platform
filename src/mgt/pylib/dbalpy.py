"""
@namespace DBAL 

This module provides interfaces to access the DBAL provided by SAFplus library.
"""
import pdb
import os, sys, os.path
import re
import pyDbal
import microdom
from common import *

from xml.etree import ElementPath
from xml.etree import ElementTree as ET
from xml.dom import minidom

cfgpath = os.environ.get("SAFPLUS_CONFIG",os.environ.get("SAFPLUS_BINDIR","."))

SAFplusError = {
    0x00:"CL_OK",
    0x02:"CL_ERR_INVALID_PARAMETER",
    0x03:"CL_ERR_NULL_POINTER",
    0x04:"CL_ERR_DOESNT_EXIST",
    0x05:"CL_ERR_INVALID_HANDLE",
    0x08:"CL_ERR_DUPLICATE",
    0x0e:"CL_ERR_NOT_INITIALIZED",
    0x10:"CL_ERR_ALREADY_EXIST",
    0x11:"CL_ERR_UNSPECIFIED",
    0x12:"CL_ERR_INVALID_STATE",
    0x13:"CL_ERR_DOESNT_EXIST",
    0x100:"CL_DBAL_ERR_DB_ERROR",
    0x101:"CL_DBAL_ERR_COMMIT_FAILED",
    0x102:"CL_DBAL_ERR_ABORT_FAILED"
}

PREDICATE_KEY_START = '['
PREDICATE_KEY_END = ']'

def key_to_xml(s):
  s = s.replace("_",":")
  #tag without array index
  #/c[1] => /c
  s = s.split("[")[0]
  return s

def getErrorString(errCode):
    if type(errCode) == str:
        return errCode
    try:
        retStr = SAFplusError[errCode[0]]
    except KeyError:
        retStr = "UNKNOWN_ERROR_CODE"
   
    return retStr

def prettify(elem):
    """Return a pretty-printed XML string for the Element.
    """
    rough_string = ET.tostring(elem, 'utf-8')
    reparsed = minidom.parseString(rough_string)
    return reparsed.toprettyxml(indent="  ")

class PyDBAL():
    """
    @param fileName: 
        This parameter specifies the file name (without suffix) along with its path,
        where the database is to be created.
    @param maxKeySize:
        Maximum size of the key (in bytes) to be stored in the database.
    @param maxRecordSize:
        Maximum size of the record (in bytes) to be stored in the database.
    @param docRoot:
        Decode cfg file and set doc root tree
    """
    def __init__(self, fileName, maxKeySize = 4, maxRecordSize = 8, docRoot=None):
        self.cfgfile = "%s" % fileName
        self.suppliedData = None
        self.dbName = os.path.splitext(fileName)[0]
        self.docRoot = docRoot
        pyDbal.initializeDbal(self.dbName, maxKeySize, maxRecordSize)

    """ Load cfg xml and save to binary database """
    def LoadXML(self, xmlFile = None):
        if xmlFile is None: xmlFile = self.cfgfile
        try:
            self.suppliedData = microdom.LoadFile(xmlFile)
            if self.docRoot:
                self.suppliedData = self.suppliedData.get(self.docRoot)

        except IOError, e: # If the supplied data file does not exist just print a warning
            raise Exception("Supplied data file %s does not exist.  You may need to export SAFPLUS_CONFIG enviroment variable" % self.cfgfile)

        except Exception, e: # If the supplied data file does not exist just print a warning
            raise Exception("Invalid format XML file!")

        self.xpathDB = {}
        self.xpathParentDB = {}

        #Process first phrase to retrieve xpath
        self._load(self.suppliedData)

        #Convert list container or list-leaf to array list
        map_change_xpath = {}

        #Done customize xpath
        #Unit test http://xmltoolbox.appspot.com/xpath_generator.html
        for (key, value) in sorted(self.xpathDB.items()):
            try:
                self.Write(key, value)
            except Exception, e:
                #Duplicate key
                pass

    """ Load cfg xml and save to binary database """
    def _load(self, element, xpath = ''):
        if isInstanceOf(element, microdom.MicroDom):
            xpath = "%s/%s" %(xpath, microdom.keyify(element.tag_))

            if len(element.attributes_) > 1:
                # Format attribute string with 'and' expression for each attribute
                attrs = [(microdom.keyify(k),v) for (k,v) in filter(lambda i: i[0] != 'tag_', element.attributes_.items())]
                xpath = xpath + "[%s]" %" and ".join(["@%s=\"%s\"" %(k,v) for (k,v) in attrs])
                for el in attrs:
                    attrKey = "%s/@%s" %(xpath, el[0])
                    self.xpathDB[attrKey] = el[1]
                    self.xpathParentDB[attrKey] = 1

            #Add index key into list container, also modify old one with index [1]
            if self.xpathParentDB.has_key(xpath):
                if self.xpathParentDB[xpath] == 1:
                    # Lookup on xpathDB and replace with extra index [1]
                    for key in filter(lambda key: key.rfind(xpath) != -1, self.xpathDB.keys()):
                        key_prefix = xpath + "[1]"
                        key_new = key.replace(xpath, key_prefix)
                        self.xpathDB[key_new] = self.xpathDB.pop(key)

                #Now, all having [index], just increase
                self.xpathParentDB[xpath] +=1
                xpath = xpath + "[%d]" %self.xpathParentDB[xpath]
            else:
                self.xpathParentDB[xpath] = 1

            if len(element.children()) > 0:
                for elchild in element.children():
                    self._load(elchild, xpath)
            else:
                self.xpathDB[xpath] = str(element.data_)

        elif len(str(element).strip()) > 0:
            self.xpathDB[xpath] = str(element).strip()

    """ Build element attribute """
    def _transformAttr(self, next, token):
        predicate = []
        attributes = {}

        #This is [list] attribute value of a node element
        #Ex: /a/b/c[@name="foo" and @id="bar"] => attributes {name=foo, id=bar}
        if token[0] == "[":
            while 1:
                token = next()
                if token[0] == "]":
                    break
                if token[0] and token[0][:1] in "'\"":
                    token = "'", token[0][1:-1]
                predicate.append(token[1])

            #This is array index [1] ... [2] ...(already combine with @attributes)
            if not re.match("\d+$", predicate[0]):
                while len(predicate)>3:
                    #Ignore 'and' expression token
                    if predicate[0] == 'and':
                        predicate = predicate[2:]
                    key = predicate[1]
                    value = predicate[3]
                    # shift left
                    predicate = predicate[5:]
                    attributes[key_to_xml(key)] = value

        return attributes

    def _buildNode(self, current_xpath):
        current_elemment = None
        p_parent_xpath = None
        try:
            current_elemment = self.mapparentelem[current_xpath]
        except:
            try:
                p_parent_xpath = current_xpath[:current_xpath.rfind("/")]
                token = current_xpath[current_xpath.rfind("/") + 1:]

                # TODO: This token is attributes value
                if token[0] == '@':
                    token = token[1:]

                #Get current element with xpath:current_xpath if exists
                parent_elemment = self.mapparentelem[p_parent_xpath]

                current_elemment = ET.Element(key_to_xml(token))
                self.mapparentelem[current_xpath] = current_elemment
                parent_elemment.append(current_elemment)

            except:
                """ Backward up level of parent xpath """
                current_elemment = self._buildNode(p_parent_xpath)
        return current_elemment

    """ Export to cfg xml from binary database """
    def ExportXML(self, filename = None):
        """ Build element tree from xpaths """

        # Tree root node
        root = None

        #Map to store xpath and ElementXpath
        self.mapparentelem = {}
        for xpath in self.Iterators():
            #Is attribute xpath? /a/b/c@name => attr name
            attr_xpath = False 

            value = str(self.Read(xpath))
            next = iter(ElementPath.xpath_tokenizer(xpath)).next

            #For each leaf node on xpath
            current_elemment = root

            #parent xpath
            parent_xpath = None

            #current xpath token
            current_xpath = None

            while 1:
                try:
                    token = next()
                    if token[0] == "/":
                        token = next()

                        #Ignore attribue element (xpath=//sg/@name)
                        if token[0] == "@":
                            attr_xpath = True
                            continue

                        index = xpath.rfind("/%s" %token[1])
                        if index >= 0:
                            parent_xpath = "%s" %(xpath[:index])

                            #Get xpath assume suffix is leaf
                            next_index = xpath.find("/", len(parent_xpath) + 1)
                            if next_index>0:
                                current_xpath = xpath[0:next_index]
                            else:
                                #Last leaf
                                current_xpath = xpath

                            if root is None:
                                root = ET.Element(key_to_xml(token[1]))
                                current_elemment = root
                                self.mapparentelem["/%s" %token[1]] = current_elemment
                            else:
                                current_elemment = self._buildNode(current_xpath)
                    elif token[0] == "[":
                        attributes = self._transformAttr(next, token)
                        if len(attributes) > 0:
                            current_elemment.attrib = attributes

                except StopIteration:
                    break

            if attr_xpath == False:
                current_elemment.text = value

        #Write to xml or stdout
        if filename is None:
            filename = "%s.xml" %self.dbName

        file = open(filename, "wb")
        file.write(prettify(root))
        file.close()

    def Finalize(self):
        pyDbal.finalizeDbal()

    def Iterators(self, xpath=None):
        if xpath:
            try:
                keys = [key for key in pyDbal.iterators() if key.startswith(xpath)]
                return keys
            except:
                return []
        else:
            return pyDbal.iterators()

    def Write(self, key, data):
        print "Writing %s -> %s" % (str(key), str(data))
        return pyDbal.write(key, data)
    
    def Read(self, key):
        return pyDbal.read(key)

    def Replace(self, key, data):
        if key in self.Iterators():
            try:
                return pyDbal.replace(key, data)
            except Exception, e:
                return e
        raise ValueError(0x13)


def main(argv):
  if len(argv) < 3:
    print "Usage:\n '%s -x <xml file> [output file]': Encode xml file to database file\n" % argv[0]
    print " '%s -d <database file (no extension)> [output file]': Write database file into xml file of the same name\n" % argv[0]
    print "If [output file] is not specified, a file is created with the same name as the input file.\n"
    return -1

  inFile = argv[2]

  outFile = None
  if len(argv) > 3:
    outFile = argv[3]
  else:
    outFile = os.path.splitext(os.path.split(inFile)[1])[0]  # remove both the directory and the extension from the input file to form the output file

  print "Writing to: %s" % outFile

  # Store into binary database
  if argv[1] == '-x':
    try:
      print "Reading from %s" %inFile
      data = PyDBAL(outFile)
      data.LoadXML(inFile);
      data.Finalize()
    except Exception, e:
      print e
      return

  # Export to XML from binary database
  if argv[1] == '-d':
    try:
      data = PyDBAL(argv[2])
      data.ExportXML(outFile + ".xml");
      data.Finalize()
    except Exception, e:
      print e
      return


def Test():
    test = PyDBAL("SAFplusAmf.xml") # Root of Log service start from /log ->  docRoot= "version.log_BootConfig.log"
    test.StoreDB();

    # Iterators
    for key in test.Iterators():
       try:
           data = test.Read(key)
           print "[%s] -> [%s]" %(key, data)
       except Exception, e:
           print getErrorString(e)

    #Replace data with a key
    try:
        key="/SAFplusLog/ServerConfig/maximumSharedMemoryPages"
        test.Replace(key, "100")
    except Exception, e:
        print getErrorString(e)

    try:
        key="/SAFplusLog/ServerConfig/maximumRecordsInPacket"
        test.Replace(key,"150")
    except Exception, e:
        print getErrorString(e)

    #Export to XML
    test.ExportXML("SAFplusLog_New.xml")

    test.Finalize()

if __name__ == '__main__':
  main(sys.argv)
