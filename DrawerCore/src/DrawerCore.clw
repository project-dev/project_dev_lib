; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDrawerPropDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "drawercore.h"
LastPage=0

ClassCount=4
Class1=CDrawerCoreApp
Class2=CDrawerCtrl
Class3=CDRawerEdit

ResourceCount=2
Resource1=IDD_PROP_DLG
Class4=CDrawerPropDlg
Resource2=IDM_DR_POPUP

[CLS:CDrawerCoreApp]
Type=0
BaseClass=CWinApp
HeaderFile=DrawerCore.h
ImplementationFile=DrawerCore.cpp
LastObject=CDrawerCoreApp

[CLS:CDrawerCtrl]
Type=0
BaseClass=CWnd
HeaderFile=\Other\Drawer\include\DrawerCtrl.h
ImplementationFile=DrawerCtrl.cpp
Filter=W
VirtualFilter=WC

[CLS:CDRawerEdit]
Type=0
BaseClass=CEdit
HeaderFile=\Other\Drawer\include\DRawerEdit.h
ImplementationFile=DRawerEdit.cpp

[MNU:IDM_DR_POPUP]
Type=1
Class=?
Command1=IDM_INP_TEXT
Command2=IDM_DR_COPY
Command3=IDM_DR_DELETE
Command4=IDM_PROPERTY
CommandCount=4

[DLG:IDD_PROP_DLG]
Type=1
Class=CDrawerPropDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_PROP_TAB,SysTabControl32,1342177280

[CLS:CDrawerPropDlg]
Type=0
HeaderFile=DrawerPropDlg.h
ImplementationFile=DrawerPropDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDrawerPropDlg

