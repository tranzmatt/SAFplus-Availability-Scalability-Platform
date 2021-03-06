"""<module>
This module generates an html page based on some class
"""
import pdb
import shutil
import types

from constants import *

from PyHtmlGen.gen import *
from PyHtmlGen.document import *
from PyHtmlGen.htmldoc import *
from PyHtmlGen.bar import *
# from layoutstyle import *
from PyHtmlGen.layouttable import *
from PyHtmlGen.table import *
from PyHtmlGen.imagehtml import *
from PyHtmlGen.menu import *
from PyHtmlGen.layouthtml import *
from PyHtmlGen.form import *
from PyHtmlGen.attribute import *
from PyHtmlGen.json import *
from PyHtmlGen.cssclass import *
from PyHtmlGen.module import *


#? The json module is defined
yadogJsModule = Module("yadogJs",jsm,[("head",["<script language='JavaScript' src='yadogjs.js'>1;</script>\n"]) ])


myDir = os.path.dirname(__file__) + os.sep

def generate(obj,cfg,args,tagdict=None):
  ret = (None,None)
  try:
    ret = main(obj,cfg,tagdict)
    print "Home page generation completed."
  except Exception, e:
    print e
    raise
#    pdb.set_trace()
  return ret



def main(obj,cfg,tagdict):

  helpContent = Chunk("",myId='center')

  # SetImagePathPrefix("./")
  mediaDir = cfg["html"]["skin"]

  hlst = []
  for (name,page) in cfg["html"]["sectionIndexImplementers"].items():
    c = anchor(name + ".html",name).setClass(cleanAnchor)
    action(c,"onClick",actionDynGetScript(helpContent,name + ".html",name + ".js"))
    
    hlst.append(c)
  
  idxbar = VerticalList(activeStyleItems(hlst, "color:%s;" % "Blue", ""),None, "  |  ")

  hlst = []
  for nav in cfg["html"]["nav"]:
    if type(nav) is types.DictType:
      name = nav["name"]
      filename = nav["file"]
      pi = nav["gen"]
    else:
      name = nav[0]
      pi = nav[1]
      if len(nav) > 2:
        args = nav[2]
      else:
        args = None
      filename = name

    c = anchor(name + ".html",name).setClass(cleanAnchor)
    action(c,"onClick",actionDynGetScript(helpContent,filename + ".html",filename + ".js"))    
    hlst.append(c)

  navbar = VerticalList(activeStyleItems(hlst, "color:%s;" % "Blue", ""),None, "  |  ")

  if cfg["html"].has_key("quicklists"):
    quicklst = []
    loading = []
    for (name,page) in cfg["html"]["quicklists"].items():
      c = anchor(page + ".html",page).setClass(cleanAnchor)
      action(c,"onClick",actionDynGet(page,page + ".html"))    
      quicklst.append(c)
      tmp = ChunkTable(1,1,border="2px").setAttrs({"class":"hidden","oclass":"quicktable"})
      tmp.id = "qt" + name
      tmp.forceId = True
      tmp.idx[0][0].set(Chunk("loading...",myId=page))
      loading.append(tmp)

    quicklst = activeStyleItems(quicklst, "color:%s;" % "Blue", "")  #,loading)
    interleaved = []
    for x,y in zip(quicklst,loading):
      interleaved.append(x)
      interleaved.append(y)
    quickbar = ["Quick List",HSplit(interleaved)]
  else:
    quickbar = []
    
  if (1):
    shutil.copy(myDir+"json.js","html/")
    shutil.copy(myDir+"jsonreq.js","html/")
    shutil.copy(myDir+"yadogjs.js","html/")
    shutil.copy(mediaDir+"/medlogo.svg","html/")
    shutil.copy(mediaDir+"/thelook.css","html/")
    shutil.copy(mediaDir+"/thinbar.png","html/")


    prj = cfg["project"]
    
    hdr = HSplit([Chunk(prj["name"],myId="projectName"),VSplit([Span(["Version: ",prj['version']],myId="projectVersion"),Span([" Released: ",prj['date']],myId="projectReleaseDate").setAttrs("align","right") ]),ImageHtml("thinbar.png",localFileName=mediaDir+"/thinbar.png")]).setAttrs("align","top")

    startContents = '<script language="JavaScript">\n' + """
onHashChange();
</script>
"""

    content = HeaderFooter(hdr, startContents,helpContent)

    sidebarContent=HSplit([ImageHtml("medlogo.svg",localFileName=mediaDir+"/medlogo.svg"), navbar,idxbar, BR,quickbar, Chunk("",myId='sidebar')])
    page = Sidebar(length(15,"%"), sidebarContent, content)
    page.cell(1,0).setStyles("vertical-align","top")
    page.cell(0,0).setStyles("vertical-align","top")

    fname = "index.html"
    doc = HtmlSkel()
    doc.Insert("""<script language='JavaScript'>
window.onhashchange = function() { onHashChange(); };
</script>""",doc.head);

    doc.AddModule(jsModule,LocationBoth)  
    doc.AddModule(jsonModule,LocationBoth)
    doc.AddStyleSheet("thelook.css")
    doc.AddModule(yadogJsModule,LocationBoth)

    WriteFile("html"+os.sep+fname,page,doc)
    return (fname,page)
    


def Test():
    main(None,None)

# </module>
