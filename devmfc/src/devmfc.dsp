# Microsoft Developer Studio Project File - Name="devmfc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=devmfc - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "devmfc.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "devmfc.mak" CFG="devmfc - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "devmfc - Win32 Release" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE "devmfc - Win32 Debug" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "devmfc - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\lib\Release"
# PROP Intermediate_Dir "..\lib\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\release\include\devmfc" /I "..\..\release\include\devlib" /I "..\..\release\include\devstaticlib" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "DEVMFC_EXPORTS" /FAcs /Fa"..\brow\Release/" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 devlib.lib devstaticlib.lib /nologo /subsystem:windows /dll /map:"..\brow\Release/devmfc.map" /machine:I386 /out:"..\..\Release\bin\Release/devmfc.dll" /libpath:"..\include" /libpath:"..\..\release\lib\release"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=..\..\..\_common\upx.exe -9 ..\..\Release\bin\release\devmfc.dll
# End Special Build Tool

!ELSEIF  "$(CFG)" == "devmfc - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib\Debug"
# PROP Intermediate_Dir "..\lib\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\release\include\devmfc" /I "..\..\release\include\devlib" /I "..\..\release\include\devstaticlib" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "DEVMFC_EXPORTS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 devlib.lib devstaticlib.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\..\Release\bin\Debug/devmfc.dll" /pdbtype:sept /libpath:"..\include" /libpath:"..\..\release\lib\debug"

!ENDIF 

# Begin Target

# Name "devmfc - Win32 Release"
# Name "devmfc - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AbstractWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseData.cpp
# End Source File
# Begin Source File

SOURCE=.\devmfc.cpp
# End Source File
# Begin Source File

SOURCE=.\devmfc.def
# End Source File
# Begin Source File

SOURCE=.\devmfc.rc
# End Source File
# Begin Source File

SOURCE=.\EditEx.cpp
# End Source File
# Begin Source File

SOURCE=.\FileCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\FindFile.cpp
# End Source File
# Begin Source File

SOURCE=.\HwndTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\LineWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\ListCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgressStatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\RichEditCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=.\RichEditViewEx.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TabCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=.\TabDropTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\TabView.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=.\WndTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\XMLDocument.cpp
# End Source File
# Begin Source File

SOURCE=.\XMLItem.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\release\include\devmfc\AbstractWnd.h
# End Source File
# Begin Source File

SOURCE=..\..\release\include\devmfc\BaseData.h
# End Source File
# Begin Source File

SOURCE=.\devmfc.h
# End Source File
# Begin Source File

SOURCE=..\..\release\include\devmfc\EditEx.h
# End Source File
# Begin Source File

SOURCE=..\..\release\include\devmfc\FileCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\release\include\devmfc\FindFile.h
# End Source File
# Begin Source File

SOURCE=..\..\release\include\devmfc\HwndTabCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\release\include\devmfc\linewnd.h
# End Source File
# Begin Source File

SOURCE=..\..\release\include\devmfc\ListCtrlEx.h
# End Source File
# Begin Source File

SOURCE=..\..\release\include\devmfc\ProgressStatusBar.h
# End Source File
# Begin Source File

SOURCE=..\..\release\include\devmfc\richeditctrlex.h
# End Source File
# Begin Source File

SOURCE=..\..\release\include\devmfc\RichEditViewEx.h
# End Source File
# Begin Source File

SOURCE=..\..\release\include\devmfc\TabCtrlEx.h
# End Source File
# Begin Source File

SOURCE=..\..\release\include\devmfc\TabView.h
# End Source File
# Begin Source File

SOURCE=..\..\release\include\devmfc\TreeCtrlEx.h
# End Source File
# Begin Source File

SOURCE=..\..\release\include\devmfc\WndTabCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\release\include\devmfc\XMLDocument.h
# End Source File
# Begin Source File

SOURCE=..\..\release\include\devmfc\XMLItem.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\devmfc.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
