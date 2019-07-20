# Microsoft Developer Studio Project File - Name="DrawerCore" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=DrawerCore - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "DrawerCore.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "DrawerCore.mak" CFG="DrawerCore - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "DrawerCore - Win32 Release" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE "DrawerCore - Win32 Debug" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DrawerCore - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\lib\Release\DrawerCore"
# PROP Intermediate_Dir "..\lib\Release\DrawerCore"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\release\include\drawer" /I "..\..\release\include\devmfc" /I "..\..\..\_common\gdiplus\include" /I "..\..\release\include\devstaticlib" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "DRAWER_EXPORTS" /FAcs /Yu"stdafx.h" /FD /c
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
# ADD LINK32 Gdiplus.lib devlib.lib devmfc.lib devstaticlib.lib /nologo /subsystem:windows /dll /map:"..\brow\Release\DrawerCore/DrawerCore.map" /machine:I386 /out:"..\..\Release\bin\Release/DrawerCore.dll" /libpath:"..\..\..\_common\gdiplus" /libpath:"..\..\release\lib\release"

!ELSEIF  "$(CFG)" == "DrawerCore - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib\Debug\DrawerCore"
# PROP Intermediate_Dir "..\lib\Debug\DrawerCore"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\release\include\drawer" /I "..\..\release\include\devmfc" /I "..\..\..\_common\gdiplus\include" /I "..\..\release\include\devstaticlib" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "DRAWER_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Gdiplus.lib devlib.lib devmfc.lib devstaticlib.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\..\Release\bin\Debug/DrawerCore.dll" /pdbtype:sept /libpath:"..\..\..\_common\gdiplus" /libpath:"..\..\release\lib\debug"

!ENDIF 

# Begin Target

# Name "DrawerCore - Win32 Release"
# Name "DrawerCore - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DrawerConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawerCore.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawerCore.def
# End Source File
# Begin Source File

SOURCE=.\DrawerCore.rc
# End Source File
# Begin Source File

SOURCE=.\DrawerCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DRawerEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawerPropDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\DrawerConfig.h
# End Source File
# Begin Source File

SOURCE=.\DrawerCore.h
# End Source File
# Begin Source File

SOURCE=..\include\DrawerCoreDef.h
# End Source File
# Begin Source File

SOURCE=..\include\DrawerCtrl.h
# End Source File
# Begin Source File

SOURCE=..\include\DRawerEdit.h
# End Source File
# Begin Source File

SOURCE=.\DrawerPropDlg.h
# End Source File
# Begin Source File

SOURCE=..\include\DrawInfo.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\DrawerCore.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
