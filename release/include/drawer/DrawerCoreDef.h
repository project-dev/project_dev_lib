#if !defined(DRAWER_CORE_DEF)
#define DRAWER_CORE_DEF

// GDI+�𗘗p���邽�߂ɕK�v�Ȑ錾
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
	eUNKNOW	= -1,	//���ݒ�
	eLINE	= 0,	//��
	eARRLINE,		//���p��
	eSQUEAR,		//�l�p
	eCIRCLE,		//�~
	eIMAGE,			//�C���[�W
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

