import pdb

import wx
#from wx.py import shell,
#from wx.py import  version
import math
import svg
try:
    import wx.lib.wxcairo
    import cairo
    import rsvg
    haveCairo = True
except ImportError:
    haveCairo = False

import module
import share
from model import *
from entity import *
import wx.lib.scrolledpanel as scrolled
import instanceEditor

LOCK_BUTTON_ID = 3482
HELP_BUTTON_ID = 4523
TEXT_ENTRY_ID = 7598

SU_TYPE_MENU_ID_START = 0
SI_TYPE_MENU_ID_START = 20
COMP_TYPE_MENU_ID_START = 40
CSI_TYPE_MENU_ID_START = 60


class EntityTool():
  def __init__(self, treeItem, parent, entity):
    self.entity = entity
    self.treeItem = treeItem
    self.parent = parent #parent entity instance

  def OnEditEvent(self, event):
    #return share.instancePanel.CreateNewInstance(self.entity, (0,0), (10,10))
    #TODO : Building instance + build containmentArrows with parent
    pass

class Panel(scrolled.ScrolledPanel):
    def __init__(self, parent,menubar,toolbar,statusbar,model):
        global thePanel
        scrolled.ScrolledPanel.__init__(self, parent, style = wx.TAB_TRAVERSAL|wx.SUNKEN_BORDER)
        self.SetupScrolling(True, True)
        self.SetScrollRate(10, 10)

        self.model = model
        self.lockedSvg = svg.SvgFile("locked.svg") 
        self.unlockedSvg = svg.SvgFile("unlocked.svg") 
        self.helpSvg = svg.SvgFile("help.svg") 
        self.lockedBmp = self.lockedSvg.bmp((24,24))
        self.unlockedBmp = self.unlockedSvg.bmp((24,24))
        self.helpBmp = self.helpSvg.bmp((12,12))
        self.entity=None
        self.sizer =None
        self.lookup = {}  # find the object from its windowing ID
        self.numElements = 0
        # Event handlers
        #self.Bind(wx.EVT_PAINT, self.OnPaint)
        self.Bind(wx.EVT_BUTTON, self.OnButtonClick)
  
        # for the data entry
        #self.Bind(wx.EVT_TEXT, self.EvtText)

        if not share.instanceDetailsPanel:
          share.instanceDetailsPanel = self

        #e = model.entities["MyServiceGroup"]
        #self.showEntity(e)
        #self.SetSashPosition(10)
        self.entityNode = None
        self.entitySg = None
        self.hsplitter = parent

        self.treeInstance = None
        self.item = None
        self.eventDictTree = {wx.EVT_TREE_SEL_CHANGED: self.OnSelChanged, wx.EVT_TREE_ITEM_RIGHT_CLICK: self.OnRightDown, wx.EVT_RIGHT_DOWN: self.OnRightDown, wx.EVT_RIGHT_UP:self.OnRightUp}
        self.lookupEntity = {}
        self.childDict = {'Node': {'ServiceUnit' : 'Component'}, 'ServiceGroup':{'ServiceInstance': 'ComponentServiceInstance' } } 


    def partialDataValidate(self, proposedPartialValue, fieldData):
      """Return True if the passed data could be part of a valid entry for this field -- that is, user might enter more text"""
      # TODO: fieldData contains information about the expected type of this field.
      return True

    def dataValidate(self, proposedValue, fieldData):
      """Return True if the passed data is a valid entry for this field"""
      # TODO: fieldData contains information about the expected type of this field.
      return True

    def EvtText(self,event):
      id = event.GetId()
      if id>=TEXT_ENTRY_ID and id < TEXT_ENTRY_ID+self.numElements:
        idx = id - TEXT_ENTRY_ID
        obj = self.lookup[idx]
        query = obj[2]

        if not isinstance(query, wx._core._wxPyDeadObject):
          proposedValue = query.GetValue()
          # print "evt text ", obj
          if not self.partialDataValidate(proposedValue, obj[0]):          
            # TODO: Print a big red warning in the error area
            pass
    
          # TODO: handle only dirty (actually value changed) entity
          #share.instancePanel.notifyValueChange(self.entity, obj[0][0], proposedValue)
      else:
        # Notify name change to instancePanel to validate and render
        #share.instancePanel.notifyNameValueChange(self.entity, event.GetEventObject().GetValue())
        pass

    def OnUnfocus(self,event):
      id = event.GetId()
      if id>=TEXT_ENTRY_ID and id < TEXT_ENTRY_ID+self.numElements:
        idx = id - TEXT_ENTRY_ID
        obj = self.lookup[idx]
        name = obj[0][0]
        query = obj[2]

        if not isinstance(query, wx._core._wxPyDeadObject):
          proposedValue = query.GetValue()
          if not self.dataValidate(proposedValue, obj[0]):
            # TODO: Print a big red warning in the error area
            pass
          # TODO: model consistency check -- test the validity of the whole model given this change
          else:
            # TODO: handle only dirty (actually value changed) entity
            #share.instancePanel.notifyValueChange(self.entity, obj[0][0], proposedValue)
            pass

      else:
        # Notify name change to instancePanel to validate and render
        #share.instancePanel.notifyNameValueChange(self.entity, event.GetEventObject().GetValue())
        pass

    def OnButtonClick(self,event):
      id = event.GetId()
      if id>=LOCK_BUTTON_ID and id < HELP_BUTTON_ID:
        idx = id - LOCK_BUTTON_ID
      obj = self.lookup[idx]
      lockButton = obj[3]
      # Toggle the locked state, create it unlocked (then instantly lock it) if it is not already set
      self.entity.instanceLocked[obj[0][0]] = not self.entity.instanceLocked.get(obj[0][0],False)
      # set the button appropriately
      if self.entity.instanceLocked[obj[0][0]]:
        lockButton.SetBitmap(self.lockedBmp);
        lockButton.SetBitmapSelected(self.unlockedBmp)
      else:
        lockButton.SetBitmap(self.unlockedBmp);
        lockButton.SetBitmapSelected(self.lockedBmp)

    def createControl(self,id,item, value):
      """Create the best GUI control for this type of data"""
      # pdb.set_trace()
      typeData = item[1]
      if typeData.has_key("type"):
        if typeData["type"] == "boolean":
          query = wx.CheckBox(self,id,"")
        elif typeData["type"] == "uint32":
          v = 0
          try:
            v = int(value)
          except:
            pass
          query = wx.Slider(self,id,v,0,100,style = wx.SL_HORIZONTAL | wx.SL_AUTOTICKS | wx.SL_LABELS)
          query.SetTickFreq(5)
          # TODO create a control that contains both a slider and a small text box
          # TODO size the slider properly using min an max hints 
        elif self.model.dataTypes.has_key(typeData["type"]):
          typ = self.model.dataTypes[typeData["type"]]
          if typ["type"] == "enumeration":
            vals = typ["values"].items()
            vals = sorted(vals, module.DataTypeSortOrder)
            choices = [x[0] for x in vals]
            if not value in choices:  # OOPS!  Either initial case or the datatype was changed
              value = choices[0]  # so set the value to the first one TODO: set to default one
            query = wx.ComboBox(self,id,value=value,choices=[x[0] for x in vals])
          else:
            # TODO other datatypes 
            query  = wx.TextCtrl(self, id, value,style = wx.BORDER_SIMPLE)
            query.Bind(wx.EVT_KILL_FOCUS, self.OnUnfocus)
        else:  # Default control is a text box
          query  = wx.TextCtrl(self, id, str(value),style = wx.BORDER_SIMPLE)
          # Works: query.SetToolTipString("test")
          query.Bind(wx.EVT_KILL_FOCUS, self.OnUnfocus)
        
        # Bind to handle event on change
        self.BuildChangeEvent(query)
        
      else:
        # TODO do any of these need to be displayed?
        query = None
      return query


    def showEntity(self,ent):
      if self.entity == ent: return  # Its already being shown
      if self.sizer:
        self.sizer.Clear(True)
        created = False
      else:
        self.sizer = wx.GridBagSizer(2,1)
        self.sizer.SetFlexibleDirection(wx.HORIZONTAL | wx.VERTICAL)
        created = True

      sizer = self.sizer   

      self.entity = ent
      items = ent.et.data.items()
      items = sorted(items,EntityTypeSortOrder)
      font = wx.Font(10, wx.MODERN, wx.NORMAL, wx.BOLD)

      # Put the name at the top
      row=0
      prompt = wx.StaticText(self,-1,"Name:",style =wx.ALIGN_RIGHT)
      query  = wx.TextCtrl(self, -1, "")
      query.ChangeValue(ent.data["name"])
      query.Bind(wx.EVT_KILL_FOCUS, self.OnUnfocus)
      
      # Binding name wx control
      self.BuildChangeEvent(query)

      prompt.SetFont(font)
      sizer.Add(prompt,(row,0),(1,1),wx.ALIGN_CENTER)
      sizer.Add(query,(row,2),flag=wx.EXPAND)
      bmp = wx.StaticBitmap(self, -1, self.unlockedBmp)
      sizer.Add(bmp,(row,3),(1,1),wx.ALIGN_CENTER | wx.ALL)
      row += 1
      for item in items:
        name = item[0]
        if type(item[1]) is DictType: # Its a datatype; not a "canned" field from parsing the yang

          # Create the data entry field
          query = self.createControl(row + TEXT_ENTRY_ID,item,ent.data[name])
          if not query: continue  # If this piece of data has not control, it is not user editable

          # figure out the prompt; its either the name of the item or the prompt override
          s = item[1].get("prompt",name)
          if not s: s = name
          prompt = wx.StaticText(self,-1,s,style=wx.ALIGN_RIGHT)
          prompt.SetFont(font)  # BUG: Note, setting the font can mess up the layout; resize the window to recalc
          prompt.Fit()

          # Now create the lock/unlock button
          b = wx.BitmapButton(self, row + LOCK_BUTTON_ID, self.unlockedBmp,style = wx.NO_BORDER )
          b.SetToolTipString("If unlocked, instances can change this field")
          if self.entity.instanceLocked.get(name, False):  # Set its initial state
            b.SetBitmap(self.lockedBmp);
            b.SetBitmapSelected(self.unlockedBmp)

            # Not allow to change this value from instance
            query.Enable(False)
          else:
            b.SetBitmap(self.unlockedBmp);
            b.SetBitmapSelected(self.lockedBmp)

          b.SetBitmapSelected(self.lockedBmp)
          # Devide from entity type, not allow to 'Lock' this from instance
          b.Enable(False)

          # Next add the extended help button
          h = None
          if item[1].has_key("help") and item[1]["help"]:
            h = wx.BitmapButton(self, row + HELP_BUTTON_ID, self.helpBmp,style = wx.NO_BORDER )
            h.SetToolTipString(item[1]["help"])
          #else: 
          #  h = wx.StaticText(self,-1,"")  # Need a placeholder or gridbag sizer screws up

          # OK fill up the sizer
          sizer.Add(prompt,(row,0),(1,1),wx.ALIGN_CENTER)
          if h: sizer.Add(h,(row,1),(1,1),wx.ALIGN_CENTER)
          sizer.Add(query,(row,2),flag=wx.EXPAND)
          sizer.Add(b,(row,3))

          # Update the lookup dictionary so when an action occurs we can get the objects from the window ID
          self.lookup[row] = [item,prompt,query,b,h]
          row +=1
      self.numElements = row
      if created:
        sizer.AddGrowableCol(2)
      elif self.sizer.IsColGrowable(0):
        self.sizer.RemoveGrowableCol(0)
        self.sizer.RemoveGrowableRow(0)
        self.sizer.AddGrowableCol(2)

      self.SetSizer(sizer)
      sizer.Layout()
      self.Refresh()
      self.SetSashPosition(self.GetParent().GetClientSize().y)

    def showEntities(self, *entities):
      self.entity = None
      self.entityNode = filter(lambda x: x.et.name == "Node", entities)[0]
      self.entitySg = filter(lambda x: x.et.name == "ServiceGroup", entities)[0]

      if self.sizer:
        self.sizer.Clear(True)
        created = False
      else:
        self.sizer = wx.GridBagSizer(2,1)
        self.sizer.SetFlexibleDirection(wx.HORIZONTAL | wx.VERTICAL)
        created = True

      if self.treeInstance:
        self.treeInstance.DeleteAllItems()
      else:
        self.treeInstance = wx.TreeCtrl(self)
        #Bind events for tree
        for (evt, func) in self.eventDictTree.items():
          self.treeInstance.Bind(evt, func)

      tree = self.treeInstance

      # Building tree and item data which relate to entity and entity type. So we can create or modify
      root = tree.AddRoot("%s - %s" %(self.entityNode.data["name"], self.entitySg.data["name"]))
      sus = tree.AppendItem(root, "ServiceUnit Instance List",  data=wx.TreeItemData(self.model.entityTypes.get(self.childDict[self.entityNode.et.name].keys()[0], None)))
      sis = tree.AppendItem(root, "Service Instance List", data=wx.TreeItemData(self.model.entityTypes.get(self.childDict[self.entitySg.et.name].keys()[0], None)))

      #TODO: Get SU and create control
      for child in filter(lambda x: x.contained.et.name in self.childDict[self.entityNode.et.name].keys(), self.entityNode.containmentArrows):
        su = tree.AppendItem(sus, child.contained.data["name"], -1,-1, data=wx.TreeItemData(child.contained))
        #TODO: Get COMP and create control
        comps = tree.AppendItem(su, "Component Instance List", data=wx.TreeItemData(self.model.entityTypes.get(self.childDict[self.entityNode.et.name][child.contained.et.name], None)))
        for child2 in filter(lambda x: x.contained.et.name == self.childDict[self.entityNode.et.name][child.contained.et.name], child.contained.containmentArrows):
          compitem = tree.AppendItem(comps, child2.contained.data["name"], -1,-1, data=wx.TreeItemData(child2.contained))

      #TODO: Get SI and create control
      for child in  filter(lambda x: x.contained.et.name in self.childDict[self.entitySg.et.name].keys(), self.entitySg.containmentArrows):
        si = tree.AppendItem(sis, child.contained.data["name"], -1,-1, data=wx.TreeItemData(child.contained))
        #TODO: Get CSI and create control
        csi = tree.AppendItem(si, "Component Service Instance List", data=wx.TreeItemData(self.model.entityTypes.get(self.childDict[self.entitySg.et.name][child.contained.et.name], None)))
        for child2 in filter(lambda x: x.contained.et.name == self.childDict[self.entitySg.et.name][child.contained.et.name], child.contained.containmentArrows):
          csiitem = tree.AppendItem(csi, child2.contained.data["name"], -1,-1, data=wx.TreeItemData(child2.contained))

      sizer = self.sizer
      sizer.Add(tree, (0,0), (1,1), wx.ALL|wx.EXPAND, 5)
      if created:
        sizer.AddGrowableCol(0)
        sizer.AddGrowableRow(0)
      elif self.sizer.IsColGrowable(2):
        self.sizer.RemoveGrowableCol(2)
        self.sizer.AddGrowableCol(0)
        self.sizer.AddGrowableRow(0)

      tree.ExpandAll()
      self.SetSizer(sizer)
      sizer.Layout()
      self.Refresh()
      self.SetSashPosition(self.GetParent().GetClientSize().y)

    def OnSelChanged(self, event):
      itemData = self.treeInstance.GetPyData(event.GetItem())
      if itemData and isinstance(itemData, entity.Instance):
        #View detail su/si/comp/csi
        self.hsplitter.GetParent().GetParent().detailsItems.showEntity(itemData)
        self.SetSashPosition(self.GetParent().GetClientSize().y/2)
        self.item = None
      else:
        # Default editor
        self.item = event.GetItem()
        self.SetSashPosition(self.GetParent().GetClientSize().y)

      event.Skip()

    def OnRightDown(self, event):
        pt = event.GetPosition()
        item, flags = self.treeInstance.HitTest(pt)

        if item:
            self.item = item
            self.treeInstance.SelectItem(item)

    def OnRightUp(self, event):
        item = self.item
        if not item:
            event.Skip()
            return

        # Only show popup menu if item is entity type
        menu = self.BuildMenu(item)
        if menu:
          self.treeInstance.PopupMenu(menu)
          menu.Destroy()

    def BuildMenu(self, item):
      itemData = self.treeInstance.GetPyData(item)
      if isinstance(itemData, entity.EntityType):
        building = {'ServiceUnit' : self.BuildMenuServiceUnit, 'Component' : self.BuildMenuComponent, 'ServiceInstance': self.BuildMenuSeviceInstance, 'ComponentServiceInstance': self.BuildMenuComponentServiceInstance}
        return building[itemData.name](item)
      return None

    def BuildMenuServiceUnit(self, item):
      # TODO: Filter SU belongs to self.node
      menu = wx.Menu()
      idx = SU_TYPE_MENU_ID_START
      for child in  filter(lambda x: x.contained.et.name in self.childDict[self.entityNode.entity.et.name].keys(), self.entityNode.entity.containmentArrows):
        mntItem = menu.Append(idx, "Created %s instance" %child.contained.data["name"])
        self.Bind(wx.EVT_MENU, self.OnCreateServiceUnit, mntItem)
        self.lookupEntity[idx] = EntityTool(item, self.entityNode, child.contained)
        idx+=1
      return menu

    def BuildMenuComponent(self, item):
      # TODO: Filter Comps belongs to parent SU
      parentSUItemData = self.treeInstance.GetPyData(self.treeInstance.GetItemParent(item))
      menu = wx.Menu()
      idx = COMP_TYPE_MENU_ID_START
      for child in  filter(lambda x: x.contained.et.name in self.childDict[self.entityNode.entity.et.name][parentSUItemData.entity.et.name], parentSUItemData.entity.containmentArrows):
        mntItem = menu.Append(idx, "Created %s instance" %child.contained.data["name"])
        self.Bind(wx.EVT_MENU, self.OnCreateComponent, mntItem)
        self.lookupEntity[idx] = EntityTool(item, parentSUItemData, child.contained)
        idx+=1
      return menu

    def BuildMenuSeviceInstance(self, item):
      # TODO: Filter SIs belongs to self.entitySg
      menu = wx.Menu()
      idx = SI_TYPE_MENU_ID_START
      for child in  filter(lambda x: x.contained.et.name in self.childDict[self.entitySg.entity.et.name].keys(), self.entitySg.entity.containmentArrows):
        mntItem = menu.Append(idx, "Created %s instance" %child.contained.data["name"])
        self.Bind(wx.EVT_MENU, self.OnCreateServiceInstance, mntItem)
        self.lookupEntity[idx] = EntityTool(item, self.entitySg, child.contained)
        idx+=1
      return menu

    def BuildMenuComponentServiceInstance(self, item):
      # TODO: Filter CSIs belongs to parent SI
      parentSIItemData = self.treeInstance.GetPyData(self.treeInstance.GetItemParent(item))
      menu = wx.Menu()
      idx = CSI_TYPE_MENU_ID_START
      for child in  filter(lambda x: x.contained.et.name in self.childDict[self.entitySg.entity.et.name][parentSIItemData.entity.et.name], parentSIItemData.entity.containmentArrows):
        mntItem = menu.Append(idx, "Created %s instance" %child.contained.data["name"])
        self.Bind(wx.EVT_MENU, self.OnCreateComponentServiceInstance, mntItem)
        self.lookupEntity[idx] = EntityTool(item, parentSIItemData, child.contained)
        idx+=1
      return menu

    def OnCreateServiceUnit(self, event):
      id = event.GetId()
      entityTool = self.lookupEntity[id]

      #TODO: Create an SU instance
      entityTool.OnEditEvent(event)
      self.treeInstance.AppendItem(entityTool.treeItem, entityTool.entity.data["name"])

    def OnCreateComponent(self, event):
      id = event.GetId()
      entityTool = self.lookupEntity[id]

      #TODO: Create an Component instance
      entityTool.OnEditEvent(event)
      self.treeInstance.AppendItem(entityTool.treeItem, entityTool.entity.data["name"])

    def OnCreateServiceInstance(self, event):
      id = event.GetId()
      entityTool = self.lookupEntity[id]

      #TODO: Create an SI instance
      entityTool.OnEditEvent(event)
      self.treeInstance.AppendItem(entityTool.treeItem, entityTool.entity.data["name"])

    def OnCreateComponentServiceInstance(self, event):
      id = event.GetId()
      entityTool = self.lookupEntity[id]

      #TODO: Create an Component instance
      entityTool.OnEditEvent(event)
      self.treeInstance.AppendItem(entityTool.treeItem, entityTool.entity.data["name"])

    def OnPaint(self, evt):
        if self.IsDoubleBuffered():
            dc = wx.PaintDC(self)
        else:
            dc = wx.BufferedPaintDC(self)
        dc.SetBackground(wx.Brush('blue'))
        dc.Clear()
        
        #self.Render(dc)

    def SetSashPosition(self, position = -1):
      #Workaround to show scrollbar
      if isinstance(self.GetParent(), wx.SplitterWindow):
        self.GetParent().SetSashPosition(-1)
        self.GetParent().SetSashPosition(position)
        self.GetParent().UpdateSize()

    def BuildChangeEvent(self, ctrl):
        mapEvents = {
            'text': [wx.EVT_TEXT, wx.EVT_TEXT_ENTER],
            'check': [wx.EVT_CHECKBOX],
            'slider': [wx.EVT_SCROLL, wx.EVT_SLIDER, wx.EVT_SCROLL_CHANGED, ],
            'comboBox': [wx.EVT_COMBOBOX, wx.EVT_TEXT, wx.EVT_TEXT_ENTER, wx.EVT_COMBOBOX_DROPDOWN, wx.EVT_COMBOBOX_CLOSEUP],
            # TBD 
        }

        for t in mapEvents[ctrl.GetName()]:
          ctrl.Bind(t, self.EvtText)

def Test():
  import time
  import pyGuiWrapper as gui

  mdl = Model()
  mdl.load("testModel.xml")

  sgt = mdl.entityTypes["ServiceGroup"]
  sg = mdl.entities["MyServiceGroup"] = Entity(sgt,(0,0),(100,20))

  gui.go(lambda parent,menu,tool,status,m=mdl: Panel(parent,menu,tool,status, m))
  #time.sleep(2)
  #thePanel.showEntity(sg)