#if !defined(__MSIMPORT__)
#define __MSIMPORT__

#define USE_OFFICE9
//#define USE_OFFICE10
//#define USE_OFFICE11

// MSO.DLLのインポート
#if defined(USE_OFFICE9)
	#import "C:\Program Files\Microsoft Office\Office\MSO9.DLL"
#elif defined(USE_OFFICE10)
	#import "C:\Program Files\Common Files\Microsoft Shared\OFFICE10\MSO.DLL"
#elif defined(USE_OFFICE11)
	#import "C:\Program Files\Common Files\Microsoft Shared\OFFICE11\MSO.DLL"
	#import "C:\Program Files\Common Files\Microsoft Shared\VBA\VBA6\VBE6EXT.OLB"
#endif

//MS WORD
#if defined(USE_OFFICE9)
	#import "C:\Program Files\Microsoft Office\Office\Mso9.dll"\
	no_namespace rename("DocumentProperties", "DocumentPropertiesACC")
	#import "C:\Program Files\Common Files\Microsoft Shared\VBA\VBA6\Vbe6ext.olb" no_namespace
	#import "C:\Program Files\Microsoft Office\Office\MSWORD9.OLB"\
	rename("ExitWindows", "ExitWindowsForWord")
#elif defined(USE_OFFICE10)

#elif defined(USE_OFFICE11)
	#import "C:\Program Files\Microsoft Office\OFFICE11\MSWORD.OLB"\
	rename("ExitWindows", "ExitWindowsForWord")
#endif


//MS EXCEL
#if defined(USE_OFFICE9)
	#import "C:\Program Files\Microsoft Office\Office\EXCEL9.OLB" \
	rename("DialogBox", "DialogBoxForExcel") rename( "RGB", "RGBForExcel")
#elif defined(USE_OFFICE10)
#elif defined(USE_OFFICE11)
	#import "C:\Program Files\Microsoft Office\OFFICE11\XL5JP32.OLB"\
	rename("DialogBox", "DialogBoxForExcel") rename( "RGB", "RGBForExcel")
#endif



#endif