#if !defined(DRAWER_CORE_DEF)
#define DRAWER_CORE_DEF

// GDI+を利用するために必要な宣言
#define ULONG_PTR DWORD 

#include "./gdiplus/gdiplus.h"
using namespace Gdiplus;

// MS XML
#import "msxml.dll" named_guids raw_interfaces_only
using namespace MSXML;


#ifdef DRAWER_EXPORTS
	#define DRAWER_EXT_CLASS		 AFX_CLASS_EXPORT
#else
	#define DRAWER_EXT_CLASS		 AFX_CLASS_IMPORT
#endif

#define CDS_EDITEND 0x10000000

typedef enum eDrawType{
	eUNKNOW	= -1,	//未設定
	eLINE	= 0,	//線
	eARRLINE,		//多角線
	eSQUEAR,		//四角
	eCIRCLE,		//円
	eIMAGE,			//イメージ
};

typedef enum eEditMode{
	edDraw = 0,
	edFreeCursor,
	edselMove,
	edResize,
	edSelect,
};
typedef enum HTEXT_ALIGN{
	alhLEFT,
	alhCENTER,
	alhRIGHT,
};
typedef enum VTEXT_ALIGN{
	alvTOP,
	alvCENTER,
	alvBOTTOM,
};
#endif

