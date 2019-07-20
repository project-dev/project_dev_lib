# Microsoft Developer Studio Project File - Name="devlib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=devlib - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "devlib.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "devlib.mak" CFG="devlib - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "devlib - Win32 Release" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE "devlib - Win32 Debug" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "devlib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\lib\Release"
# PROP Intermediate_Dir "..\lib\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DEVLIB_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\release\include\devlib" /I "..\..\release\include\devjava" /I "..\..\release\include\devstaticlib" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DEVLIB_EXPORTS" /FAcs /Fa"..\brow\Release/" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib Version.lib devjava.lib devstaticlib.lib /nologo /dll /map:"..\brow\Release/devlib.map" /machine:I386 /out:"..\..\Release\bin\Release/devlib.dll" /libpath:"..\..\release\lib\release"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=..\..\..\_common\upx.exe -9 ..\..\Release\bin\release\devlib.dll
# End Special Build Tool

!ELSEIF  "$(CFG)" == "devlib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib\Debug"
# PROP Intermediate_Dir "..\lib\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DEVLIB_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\release\include\devlib" /I "..\..\release\include\devjava" /I "..\..\release\include\devstaticlib" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DEVLIB_EXPORTS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib Version.lib devjava.lib devstaticlib.lib /nologo /dll /debug /machine:I386 /out:"..\..\Release\bin\Debug/devlib.dll" /pdbtype:sept /libpath:"..\..\release\lib\debug"

!ENDIF 

# Begin Target

# Name "devlib - Win32 Release"
# Name "devlib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Cryptography.cpp
# End Source File
# Begin Source File

SOURCE=.\DebugSupport.cpp
# End Source File
# Begin Source File

SOURCE=.\devlib.cpp
# End Source File
# Begin Source File

SOURCE=.\devlib.rc
# End Source File
# Begin Source File

SOURCE=.\devlib_debug.cpp
# End Source File
# Begin Source File

SOURCE=.\devlib_file.cpp
# End Source File
# Begin Source File

SOURCE=.\devlib_main.cpp
# End Source File
# Begin Source File

SOURCE=.\DevString.cpp
# End Source File
# Begin Source File

SOURCE=.\EnvInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\FileDialogEx.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageObject.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StringEncode.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\release\include\devlib\Cryptography.h
# End Source File
# Begin Source File

SOURCE=..\..\release\include\devlib\DebugSupport.h
# End Source File
# Begin Source File

SOURCE=..\..\release\include\devlib\devlib.h
# End Source File
# Begin Source File

SOURCE=..\..\release\include\devlib\DevString.h
# End Source File
# Begin Source File

SOURCE=..\..\release\include\devlib\devstructs.h
# End Source File
# Begin Source File

SOURCE=..\..\release\include\devlib\devtypedef.h
# End Source File
# Begin Source File

SOURCE=..\..\release\include\devlib\EnvInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\release\include\devlib\FileDialogEx.h
# End Source File
# Begin Source File

SOURCE=..\..\release\include\devlib\FolderDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\release\include\devlib\ImageObject.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\..\release\include\devlib\StringEncode.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
