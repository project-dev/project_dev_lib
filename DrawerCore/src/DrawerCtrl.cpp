// Drawer1.cpp: CDrawerCtrl クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawerCtrl.h"
#include <comdef.h> 
#include "resource.h"
#include "DrawerPropDlg.h"
#include <AfxPriv2.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//--------------------------------------------------------------
// static宣言用
int CDrawerCtrl::m_nClCnt = 0;
BOOL CDrawerCtrl::m_bComInit = FALSE;
const char* CDrawerCtrl::imgBMP = "image/bmp";
const char* CDrawerCtrl::imgGIF = "image/gif";
const char* CDrawerCtrl::imgJPG = "image/jpeg";
const char* CDrawerCtrl::imgPNG = "image/png";

//--------------------------------------------------------------

IMPLEMENT_DYNCREATE(CDrawerCtrl, CWnd)

BEGIN_MESSAGE_MAP(CDrawerCtrl, CWnd)
	//{{AFX_MSG_MAP(CDrawerCtrl)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_COPYDATA()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_KEYDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(IDM_DR_COPY, OnDrCopy)
	ON_COMMAND(IDM_DR_DELETE, OnDrDelete)
	ON_COMMAND(IDM_INP_TEXT, OnInpText)
	ON_COMMAND(IDM_PROPERTY, OnProperty)
	ON_UPDATE_COMMAND_UI(IDM_DR_COPY, OnUpdateDrCopy)
	ON_UPDATE_COMMAND_UI(IDM_DR_DELETE, OnUpdateDrDelete)
	ON_UPDATE_COMMAND_UI(IDM_INP_TEXT, OnUpdateInpText)
	ON_UPDATE_COMMAND_UI(IDM_PROPERTY, OnUpdateProperty)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/**
 * @brif エンコードしたCLSIDの取得
 * @param format
 * @param pClsid
 * @return
 */
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
    using namespace Gdiplus;//必要あれば
    UINT num  = 0; // number of image encoders
    UINT size = 0; // size of the image encoder array in bytes

    ImageCodecInfo* pImageCodecInfo = NULL;

    GetImageEncodersSize(&num, &size);
    if(size == 0)
        return -1; // Failure

    pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
    if(pImageCodecInfo == NULL)
        return -1; // Failure

    GetImageEncoders(num, size, pImageCodecInfo);

    for(UINT j = 0; j < num; ++j)
    {
        if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
        {
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return j; // Success
        } 
    }

    free(pImageCodecInfo);
    return -1; // Failure
}

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

/**
 * @brif コンストラクタ
 */
CDrawerCtrl::CDrawerCtrl(){
	m_pBackDC		= NULL;
	m_pBackBmp		= NULL;
	m_crBack		= RGB(0xff, 0xff, 0xff);
	m_pHeightRight	= NULL;
	m_eDrawType		= eLINE;
	m_eMode			= edFreeCursor;
	m_pParentWnd	= NULL;
	m_pGridDC		= NULL;
	m_pGridBmp		= NULL;
	m_pTxtInfo		= NULL;
	m_pActive		= NULL;
	m_nPasteShiftV	= 0;
	m_nPasteShiftH	= 0;

	//GDI+の開始
	GdiplusStartup(&m_gdiToken, &m_gdiSI, NULL);

}

/**
 * @brif デストラクタ
 */
CDrawerCtrl::~CDrawerCtrl(){
	m_objCfg.Save();

	if(m_pBackDC){
		m_pBackDC->SelectObject((CBitmap*)NULL);
		delete m_pBackDC;
		m_pBackDC = NULL;
	}
	if(m_pBackBmp){
		m_pBackBmp->DeleteObject();
		delete m_pBackBmp;
		m_pBackBmp = NULL;
	}
	if(m_pGridDC){
		m_pGridDC->SelectObject((CBitmap*)NULL);
		delete m_pGridDC;
		m_pGridDC = NULL;
	}
	if(m_pGridBmp){
		m_pGridBmp->DeleteObject();
		delete m_pGridBmp;
		m_pGridBmp = NULL;
	}
	CDrawInfo* pInfo = NULL;
	int nSize = m_arrDrawinfo.GetSize();
	for(int i = 0; i < nSize; i++){
		pInfo = m_arrDrawinfo.GetAt(i);
		delete pInfo;
	}
	m_arrDrawinfo.RemoveAll();

	ClearCopyBuff();

	//GDI+の終了
	GdiplusShutdown(m_gdiToken);

	if(m_bComInit){
		::CoUninitialize();
		m_bComInit = FALSE;
	}
}

/**
 * @brif CDrawCtrl生成
 * @param pParent 親ウィンドウ
 * @param nWidth 幅
 * @param nHeight 高さ
 * @param crBack 背景色
 * @return 成功した場合はTRUE、失敗した場合はFALSE
 * @attention CDrawerCtrlを利用する場合は必ず本関数を呼び出してから利用してください。
 */
BOOL CDrawerCtrl::Create(CWnd *pParent, int nWidth, int nHeight, COLORREF crBack /* = RGB(0xFF, 0xFF, 0xFF)*/){
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
	//COMの開始
	if(!m_bComInit){
		HRESULT hRes = ::CoInitialize(NULL);
		if(FAILED(hRes)){
			return FALSE;
		}
		m_bComInit = TRUE;
	}

	char szPath[MAX_PATH];
	::GetModuleFileName(NULL, szPath, MAX_PATH);
	CString strPath = szPath;
	strPath.Replace(".exe", ".ini");
	m_objCfg.SetIniFileName(strPath);
	m_objCfg.Load();

	CString strWndName;
	strWndName.Format("CDrawerCtrl%06d", m_nClCnt);
	BOOL bRet = CWnd::Create(NULL, strWndName, 
							 WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_TABSTOP, 
							 CRect(0, 0, m_nWidth, m_nHeight), pParent, 1);
#if !defined(USE_SCROLLBAR_OBJ)
	ModifyStyle(0, WS_HSCROLL | WS_VSCROLL);
#endif
	if(!bRet){
		DWORD dwEr = ::GetLastError();
		return FALSE;
	}
	m_pParentWnd = pParent;
	m_crBack = crBack;
	if(!CreateImage(nWidth, nHeight)){
		return FALSE;
	}
#if defined(USE_SCROLLBAR_OBJ)
	CRect vRect(m_nWidth - 16, 0, m_nWidth, m_nHeight);
	CRect hRect(0, m_nHeight - 16, m_nWidth, m_nHeight);
	m_objVScrBar.Create(WS_CHILD | WS_VISIBLE | SBS_VERT | SBS_RIGHTALIGN, vRect, this, 2);
	m_objHScrBar.Create(WS_CHILD | WS_VISIBLE | SBS_HORZ | SBS_BOTTOMALIGN, hRect, this, 3);
#endif
	m_nClCnt++;

	CalcScrollRange();
	m_objEdit.Create(WS_BORDER | ES_MULTILINE, CRect(0, 0, 0, 0), this, 1);
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////
// メッセージハンドラ
//////////////////////////////////////////////////////////////////////////////////
/**
 * @brif WM_CREATEのハンドラ関数
 */
int CDrawerCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: この位置に固有の作成用コードを追加してください
	
	return 0;
}

/**
 * @brif WM_LBUTTONDBCLICKのハンドラ関数
 */
void CDrawerCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) {
	if(m_pActive && (m_pActive->eType == eARRLINE) && m_pActive->IsDrawing()){
		DrawEnd(m_pActive, point.x, point.y);
		m_pActive = NULL;
	}else{
		CDrawInfo* pInfo = (CDrawInfo*)GetDrawInfo(point.x, point.y, TRUE);
		EditText(pInfo);
	}
	CWnd::OnLButtonDblClk(nFlags, point);
}

/**
 * @brif WM_SIZEのハンドラ関数
 */
void CDrawerCtrl::OnSize(UINT nType, int cx, int cy){
	CWnd::OnSize(nType, cx, cy);
	CalcScrollRange();
}

/**
 * @brif WM_LBUTTONDOWNのハンドラ関数
 */
void CDrawerCtrl::OnLButtonDown(UINT nFlags, CPoint point){
	SetFocus();
	if(m_objEdit.IsWindowVisible()){
		SetFocus();
	}else if((m_eMode == edFreeCursor) || (m_eMode == edSelect)){
		SHORT sCtrl = ::GetKeyState(VK_CONTROL) & 0x80;
		int nSize = m_arrDrawinfo.GetSize();
		if(m_pActive && !sCtrl){
			m_pActive->Select(FALSE);
			m_pActive = NULL;
		}
		for(int i = nSize - 1; i >= 0; i--){
			CDrawInfo *pInfo = m_arrDrawinfo.GetAt(i);
			if(pInfo->judgeRect.PtInRect(point)){
				m_eMode = edSelect;
				m_pActive = pInfo;
				m_pActive->Select(TRUE);
				break;
			}else if(pInfo->IsSelect()){
				pInfo->Select(FALSE);
			}
		}
		if((!m_pActive) || (m_pActive && !m_pActive->IsSelect())){
			m_eMode = edFreeCursor;
			m_selRect.left = point.x;
			m_selRect.top = point.y;
			m_selRect.right = point.x;
			m_selRect.bottom = point.y;
		}
	}else{
		if(m_pActive && m_pActive->IsDrawing()){
			//描画中
			if(m_pActive->eType == eARRLINE){
				//描画継続
				DrawStart(RGB(0xff, 0xff, 0xff), point.x, point.y);
			}else{
				m_pActive = (CDrawInfo*)DrawStart(RGB(0xff, 0xff, 0xff), point.x, point.y);
				if(m_pActive){
					m_pActive->cfFront = RGB(0x00, 0x00, 0xff);
				}
			}
		}else{
			//選択を解除しておく
			int nSize = m_arrDrawinfo.GetSize();
			for(int i = nSize - 1; i >= 0; i--){
				CDrawInfo *pInfo = m_arrDrawinfo.GetAt(i);
				pInfo->Select(FALSE);
			}
			m_pActive = (CDrawInfo*)DrawStart(RGB(0xff, 0xff, 0xff), point.x, point.y);
			if(m_pActive){
				m_pActive->cfFront = RGB(0x00, 0x00, 0xff);
			}
		}
	}

	m_nOldCurX = point.x;
	m_nOldCurY = point.y;

	CWnd::OnLButtonDown(nFlags, point);
	InvalidateRect(NULL);
}

/**
 * @brif WM_LBUTTONUPのハンドラ関数
 */
void CDrawerCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{

	if(m_pActive && (m_pActive->eType == eARRLINE)){
	}else if(m_pActive && m_pActive->IsDrawing()){
		DrawEnd(m_pActive, point.x, point.y);
		m_pActive = NULL;
	}
	m_nOldCurX = point.x;
	m_nOldCurY = point.y;
	m_selRect.left = 0;
	m_selRect.right = 0;
	m_selRect.top = 0;
	m_selRect.bottom = 0;
	CWnd::OnLButtonUp(nFlags, point);
	InvalidateRect(NULL);
}

/**
 * @brif WM_MOUSEMOVEのハンドラ関数
 */
void CDrawerCtrl::OnMouseMove(UINT nFlags, CPoint point){
	GetDrawInfo(point.x, point.y, TRUE);
	if(m_pActive){
		if(m_pActive->eType == eARRLINE){
			DrawMove(m_pActive, point.x, point.y);
		}else if((nFlags & MK_LBUTTON) == MK_LBUTTON){
			DrawMove(m_pActive, point.x, point.y);
		}
	}else if(((nFlags & MK_LBUTTON) == MK_LBUTTON) && (m_eMode == edFreeCursor)){
		//範囲選択モード
		m_selRect.right = point.x;
		m_selRect.bottom = point.y;
		//選択範囲の部品を選択状態にする
		int nCnt = m_arrDrawinfo.GetSize();
		for(int i = 0; i < nCnt; i++){
			CDrawInfo *pInfo = m_arrDrawinfo.GetAt(i);
			CPoint pt1(pInfo->judgeRect.left, pInfo->judgeRect.top);
			CPoint pt2(pInfo->judgeRect.right, pInfo->judgeRect.bottom);
			if(m_selRect.PtInRect(pt1) && m_selRect.PtInRect(pt2)){
				pInfo->Select(TRUE);
			}else{
				pInfo->Select(FALSE);
			}
		}
	}
	m_nOldCurX = point.x;
	m_nOldCurY = point.y;
	CWnd::OnMouseMove(nFlags, point);
	InvalidateRect(NULL);
}

/**
 * @brif WM_ERASEBKGROUNDのハンドラ関数
 */
BOOL CDrawerCtrl::OnEraseBkgnd(CDC* pDC) {
	//必要な部分だけ、背景を塗りつぶす
	CRect rect;
	GetClientRect(rect);
	int nSx = rect.Width() - m_nWidth;
	int nSy = rect.Height() - m_nHeight;
	
	CBrush brush;
	if(brush.CreateSolidBrush(RGB(0x00, 0x88, 0x88))){
		if(nSx > 0){
			pDC->FillRect(CRect(rect.right - nSx, 0, rect.right, rect.bottom), &brush);
		}
		if(nSy > 0){
			pDC->FillRect(CRect(0, rect.bottom - nSy, rect.right, rect.bottom), &brush);
		}
	}
	return TRUE;	
}

/**
 * @brif WM_PAINTのハンドラ関数
 */
void CDrawerCtrl::OnPaint() {
	CPaintDC dc(this); // 描画用のデバイス コンテキスト

	CRect rect;
	GetClientRect(rect);
	int nXoffset = GetScrollPos(SB_HORZ) * -1;
	int nYoffset = GetScrollPos(SB_VERT) * -1;
	DrawImage(&dc, nXoffset, nYoffset, 0, 0, rect.Width(), rect.Height());
}

/**
 * @brif WM_COPYDATAのハンドラ関数
 */
BOOL CDrawerCtrl::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct){
	switch(pCopyDataStruct->dwData){
	case CDS_EDITEND:
		if(pCopyDataStruct->lpData && m_pTxtInfo){
			//テキスト設定
			m_pTxtInfo->SetString("");
			CString strText;
			m_objEdit.GetWindowText(strText);
			SetText(m_pTxtInfo, strText);
		}
		break;
	}
	return CWnd::OnCopyData(pWnd, pCopyDataStruct);
}

void CDrawerCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
#if !defined(USE_SCROLLBAR_OBJ)
#endif
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CDrawerCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar){
#if !defined(USE_SCROLLBAR_OBJ)
#endif
	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDrawerCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){
	int nStep = m_objCfg.m_bPosGrid ? m_objCfg.m_nGridSize : 1;
	int nCnt = m_arrDrawinfo.GetSize();

	BOOL bUpdate = FALSE;
	for(int i = 0; i < nCnt; i++){
		CDrawInfo *pInfo = m_arrDrawinfo.GetAt(i);
		if(!pInfo || !pInfo->IsSelect()){
			continue;
		}
		bUpdate = TRUE;
		for(int j = 0; j < pInfo->nRectCnt; j++){
			switch(nChar){
			case VK_UP:
				pInfo->GetRect(j)->top		-= nStep;
				pInfo->GetRect(j)->bottom	-= nStep;
				break;
			case VK_DOWN:
				pInfo->GetRect(j)->top		+= nStep;
				pInfo->GetRect(j)->bottom	+= nStep;
				break;
			case VK_LEFT:
				pInfo->GetRect(j)->left		-= nStep;
				pInfo->GetRect(j)->right	-= nStep;
				break;
			case VK_RIGHT:
				pInfo->GetRect(j)->left		+= nStep;
				pInfo->GetRect(j)->right	+= nStep;
				break;
			}
		}
		SetJudgeRect(pInfo);
	}
	if(bUpdate){
		InvalidateRect(NULL);
	}
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CDrawerCtrl::OnRButtonDown(UINT nFlags, CPoint point){
	CWnd::OnRButtonDown(nFlags, point);
}

void CDrawerCtrl::OnContextMenu(CWnd* pWnd, CPoint point){
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
//	ClientToScreen( &point);

    CMenu *p_menu;
    CMenu menu;

    //メニューの読み込み
	if(!menu.LoadMenu(IDM_DR_POPUP)){
		return;
	}

    //サブメニューの関連づけ
    p_menu = menu.GetSubMenu(0);
	if(!p_menu){
		return;
	}

	if(m_pActive && m_pActive->IsSelect()){
		p_menu->EnableMenuItem(IDM_INP_TEXT,	MF_BYCOMMAND | MF_ENABLED);
		p_menu->EnableMenuItem(IDM_DR_COPY,		MF_BYCOMMAND | MF_ENABLED);
		p_menu->EnableMenuItem(IDM_DR_DELETE,	MF_BYCOMMAND | MF_ENABLED);
		p_menu->EnableMenuItem(IDM_PROPERTY,	MF_BYCOMMAND | MF_ENABLED);
	}else{
		p_menu->EnableMenuItem(IDM_INP_TEXT,	MF_BYCOMMAND | MF_GRAYED);
		p_menu->EnableMenuItem(IDM_DR_COPY,		MF_BYCOMMAND | MF_GRAYED);
		p_menu->EnableMenuItem(IDM_DR_DELETE,	MF_BYCOMMAND | MF_GRAYED);
		p_menu->EnableMenuItem(IDM_PROPERTY,	MF_BYCOMMAND | MF_GRAYED);
	}

    //ポップアップメニュー表示
    p_menu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

//////////////////////////////////////////////////////////////////////////////////
// イメージ
//////////////////////////////////////////////////////////////////////////////////
BOOL CDrawerCtrl::CreateImage(int cx, int cy, BOOL bNew){
	if(!m_pParentWnd){
		return FALSE;
	}
	BOOL bRet;
	if(m_pBackDC && m_pBackBmp){
		m_pBackDC->SelectObject((CBitmap*)NULL);

		m_pBackBmp->DeleteObject();
		delete m_pBackBmp;
		m_pBackBmp = NULL;
	}
	CDC *pDC = m_pParentWnd->GetDC();
	if(!m_pBackDC){
		m_pBackDC = new CDC();
		if(!m_pBackDC->CreateCompatibleDC(pDC)){
			return FALSE;
		}
	}

	if(!m_pBackBmp){
		m_pBackBmp = new CBitmap();
	}
	if(!m_pBackBmp->CreateCompatibleBitmap(pDC, cx, cy)){
		delete m_pBackBmp;
		m_pBackBmp = NULL;
		bRet = FALSE;
	}else{
		m_nWidth = cx;
		m_nHeight = cy;
		m_pBackDC->SelectObject(m_pBackBmp);
		MakeGridBmp();
	}
	CalcScrollRange();
	return bRet;
}

/**
 * @brif 指定デバイスコンテキストにバックバッファの内容を描画する
 * @param pDc 対象となるCDCオブジェクトのポインタ
 * @param dx 転送先X座標
 * @param dy 転送先Y座標
 * @param sx 転送元X座標
 * @param sy 転送元Y座標
 * @param nWidth 転送幅
 * @param nHeight 転送高さ
 * @return 描画に成功した場合はTRUE、失敗した場合はFALSE
 */
BOOL CDrawerCtrl::DrawImage(CDC *pDc, int dx, int dy, int sx, int sy, int nWidth, int nHeight){
	if(!pDc || !m_pBackDC || !m_pBackBmp){
		return FALSE;
	}
	CBrush objBack;
	objBack.CreateSolidBrush(m_crBack);
	CRect rect(0, 0, m_nWidth, m_nHeight);
	m_pBackDC->FillRect(rect, &objBack);

	//グリッド描画
	if(m_pGridDC && m_objCfg.m_bShowGrid){
		m_pBackDC->BitBlt(0, 0, m_nWidth, m_nHeight, m_pGridDC, 0, 0, SRCCOPY);
	}

	//部品描画
	int nSize = m_arrDrawinfo.GetSize();
	CDrawInfo* pInfo;
	m_pBackDC->SetBkMode(TRANSPARENT);
	for(int i = 0; i < nSize; i++){
		pInfo = m_arrDrawinfo.GetAt(i);
		CPen objPen(PS_SOLID, 1, pInfo->cfFront);
		CBrush objBrush;
		objBrush.CreateSolidBrush(pInfo->cfFront);
		CPen *pOldPen = m_pBackDC->SelectObject(&objPen);
		CBrush *pOldBrush = m_pBackDC->SelectObject(&objBrush);

		//部品描画
		switch(pInfo->eType){
		case eLINE:			//線
			m_pBackDC->MoveTo(pInfo->GetRect(0)->left,  pInfo->GetRect(0)->top);
			m_pBackDC->LineTo(pInfo->GetRect(0)->right, pInfo->GetRect(0)->bottom);
			break;
		case eARRLINE:		//多角線
			{
				for(int j = 0; j < pInfo->nRectCnt; j++){
					m_pBackDC->MoveTo(pInfo->GetRect(j)->left,  pInfo->GetRect(j)->top);
					m_pBackDC->LineTo(pInfo->GetRect(j)->right, pInfo->GetRect(j)->bottom);
				}
			}
			break;

		case eSQUEAR:		//四角
			if(pInfo->IsPaint()){
				m_pBackDC->Rectangle(pInfo->GetRect(0));
			}else{
				m_pBackDC->MoveTo(pInfo->GetRect(0)->left,  pInfo->GetRect(0)->top);
				m_pBackDC->LineTo(pInfo->GetRect(0)->right, pInfo->GetRect(0)->top);
				m_pBackDC->LineTo(pInfo->GetRect(0)->right, pInfo->GetRect(0)->bottom);
				m_pBackDC->LineTo(pInfo->GetRect(0)->left,  pInfo->GetRect(0)->bottom);
				m_pBackDC->LineTo(pInfo->GetRect(0)->left,  pInfo->GetRect(0)->top);
			}
			break;

		case eCIRCLE:		//円
			if(pInfo->IsPaint()){
				m_pBackDC->Ellipse(pInfo->GetRect(0));
			}else{
				m_pBackDC->Arc(pInfo->GetRect(0), CPoint(pInfo->GetRect(0)->left, pInfo->GetRect(0)->top), CPoint(pInfo->GetRect(0)->left, pInfo->GetRect(0)->top));
			}
			break;
		}

		//文字列描画
		CString strText;
		pInfo->GetString(strText);
		CRect txtRect(pInfo->GetRect(0)->left + 1, pInfo->GetRect(0)->top + 1,pInfo->GetRect(0)->right - 1, pInfo->GetRect(0)->bottom - 1);
		CSize size = m_pBackDC->GetTextExtent(strText);
		UINT txtOpt = DT_END_ELLIPSIS | DT_EXPANDTABS | DT_NOCLIP;
		int nPosAdd = 0;
		switch(pInfo->vAlign){
		case alvTOP:
			txtOpt |= DT_TOP;
			break;
		case alvCENTER:
			txtOpt |= DT_VCENTER;
			nPosAdd = (txtRect.Height() - size.cy) / 2;
			break;
		case alvBOTTOM:
			txtOpt |= DT_BOTTOM;
			nPosAdd = (txtRect.Height() - size.cy);
			break;
		}
		txtRect.top += nPosAdd;

		switch(pInfo->hAlign){
		case alhLEFT:
			txtOpt |= DT_LEFT;
			break;
		case alhCENTER:
			txtOpt |= DT_CENTER;
			break;
		case alhRIGHT:
			txtOpt |= DT_RIGHT;
			break;
		}
		m_pBackDC->DrawText(strText, &txtRect, txtOpt);
/*
		if(m_pHeightRight == pInfo){
			//ハイライト表示
			CPen objPen(PS_SOLID, 1, RGB(0xFF, 0xFF, 0x00));
			m_pBackDC->SelectObject(&objPen);
			switch(pInfo->eType){
			case eLINE:			//線
			case eSQUEAR:		//四角
			case eCIRCLE:		//円
				m_pBackDC->MoveTo(pInfo->GetRect(0)->left - 1,  pInfo->GetRect(0)->top - 1);
				m_pBackDC->LineTo(pInfo->GetRect(0)->right + 1, pInfo->GetRect(0)->top - 1);
				m_pBackDC->LineTo(pInfo->GetRect(0)->right + 1, pInfo->GetRect(0)->bottom + 1);
				m_pBackDC->LineTo(pInfo->GetRect(0)->left - 1,  pInfo->GetRect(0)->bottom + 1);
				m_pBackDC->LineTo(pInfo->GetRect(0)->left - 1,  pInfo->GetRect(0)->top - 1);
				break;
			case eARRLINE:		//多角線
				m_pBackDC->MoveTo(pInfo->judgeRect.left - 1,  pInfo->judgeRect.top - 1);
				m_pBackDC->LineTo(pInfo->judgeRect.right + 1, pInfo->judgeRect.top - 1);
				m_pBackDC->LineTo(pInfo->judgeRect.right + 1, pInfo->judgeRect.bottom + 1);
				m_pBackDC->LineTo(pInfo->judgeRect.left - 1,  pInfo->judgeRect.bottom + 1);
				m_pBackDC->LineTo(pInfo->judgeRect.left - 1,  pInfo->judgeRect.top - 1);
				break;
			}
		}
*/
		//選択
		if(pInfo->IsSelect()){
			CPen objSelPen(PS_SOLID, 1, RGB(0xFF, 0xFF, 0x00));
			CBrush objSelBrnsh;
			objSelBrnsh.CreateSolidBrush(RGB(0xFF, 0xFF, 0x00));
			m_pBackDC->SelectObject(&objSelPen);
			m_pBackDC->SelectObject(&objSelBrnsh);
			CRect selRect(pInfo->judgeRect.left  - 1, pInfo->judgeRect.top    - 1, 
						  pInfo->judgeRect.right + 1, pInfo->judgeRect.bottom + 1);

			//強調枠
			m_pBackDC->MoveTo(selRect.left  , selRect.top    );
			m_pBackDC->LineTo(selRect.right , selRect.top    );
			m_pBackDC->LineTo(selRect.right , selRect.bottom );
			m_pBackDC->LineTo(selRect.left  , selRect.bottom );
			m_pBackDC->LineTo(selRect.left  , selRect.top    );

			//サイズ変更ポイント
			int nSelSize = 3;
			switch(pInfo->eType){
			case eLINE:			//線
			case eARRLINE:		//多角線
				//始点と中間点と終点に配置
				{
					for(int nLn = 0; nLn < pInfo->nRectCnt; nLn++){
						CRect rect = pInfo->GetRect(nLn);
						CRect rSq1(rect.left  - nSelSize, rect.top    - nSelSize, rect.left  + nSelSize, rect.top    + nSelSize);
						CRect rSq2(rect.right - nSelSize, rect.bottom - nSelSize, rect.right + nSelSize, rect.bottom + nSelSize);
						m_pBackDC->Rectangle(rSq1);
						m_pBackDC->Rectangle(rSq2);
					}
				}
				break;
			case eSQUEAR:		//四角
			case eCIRCLE:		//円
				{
				//上下左右等に配置
					CRect rect = pInfo->GetRect(0);
					int nWhalf = rect.Width() / 2;
					int nHhalf = rect.Height() / 2;
					CRect rSq1_1(rect.left  - nSelSize,          rect.top    - nSelSize,          rect.left  + nSelSize,          rect.top    + nSelSize);
					CRect rSq1_2(rect.left  - nSelSize + nWhalf, rect.top    - nSelSize,          rect.left  + nSelSize + nWhalf, rect.top    + nSelSize);
					CRect rSq1_3(rect.right - nSelSize,          rect.top    - nSelSize,          rect.right + nSelSize,          rect.top    + nSelSize);

					CRect rSq2_1(rect.left  - nSelSize,          rect.top    - nSelSize + nHhalf, rect.left  + nSelSize,          rect.top    + nSelSize + nHhalf);
					CRect rSq2_3(rect.right - nSelSize,          rect.top    - nSelSize + nHhalf, rect.right + nSelSize,          rect.top    + nSelSize + nHhalf);

					CRect rSq3_1(rect.left  - nSelSize,          rect.bottom - nSelSize,          rect.left  + nSelSize,          rect.bottom + nSelSize);
					CRect rSq3_2(rect.left  - nSelSize + nWhalf, rect.bottom - nSelSize,          rect.left  + nSelSize + nWhalf, rect.bottom + nSelSize);
					CRect rSq3_3(rect.right - nSelSize,          rect.bottom - nSelSize,          rect.right + nSelSize,          rect.bottom + nSelSize);

					m_pBackDC->Rectangle(rSq1_1);
					m_pBackDC->Rectangle(rSq1_2);
					m_pBackDC->Rectangle(rSq1_3);

					m_pBackDC->Rectangle(rSq2_1);
					m_pBackDC->Rectangle(rSq2_3);

					m_pBackDC->Rectangle(rSq3_1);
					m_pBackDC->Rectangle(rSq3_2);
					m_pBackDC->Rectangle(rSq3_3);
				}
				break;
			}
		}

		//範囲選択の線を描画
		if((m_selRect.left - m_selRect.right) || (m_selRect.top - m_selRect.bottom)){
			CPen objSelPen(PS_DASH, 1, RGB(0x88, 0x88, 0x88));
			m_pBackDC->SelectObject(&objSelPen);
			m_pBackDC->MoveTo(m_selRect.left  , m_selRect.top    );
			m_pBackDC->LineTo(m_selRect.right , m_selRect.top    );
			m_pBackDC->LineTo(m_selRect.right , m_selRect.bottom );
			m_pBackDC->LineTo(m_selRect.left  , m_selRect.bottom );
			m_pBackDC->LineTo(m_selRect.left  , m_selRect.top    );

			CPen objSelPen2(PS_DOT, 1, RGB(0xff, 0xff, 0xff));
			m_pBackDC->SelectObject(&objSelPen2);
			m_pBackDC->MoveTo(m_selRect.left - 1  , m_selRect.top - 1   );
			m_pBackDC->LineTo(m_selRect.right + 1 , m_selRect.top - 1   );
			m_pBackDC->LineTo(m_selRect.right + 1 , m_selRect.bottom + 1);
			m_pBackDC->LineTo(m_selRect.left - 1  , m_selRect.bottom + 1);
			m_pBackDC->LineTo(m_selRect.left - 1  , m_selRect.top - 1   );

			m_pBackDC->MoveTo(m_selRect.left + 1  , m_selRect.top + 1   );
			m_pBackDC->LineTo(m_selRect.right - 1 , m_selRect.top + 1   );
			m_pBackDC->LineTo(m_selRect.right - 1 , m_selRect.bottom - 1);
			m_pBackDC->LineTo(m_selRect.left + 1  , m_selRect.bottom - 1);
			m_pBackDC->LineTo(m_selRect.left + 1  , m_selRect.top + 1   );
		}		
		m_pBackDC->SelectObject(pOldPen);
		m_pBackDC->SelectObject(pOldBrush);
		objPen.DeleteObject();
		objBrush.DeleteObject();

	}

	//フロントバッファへ描画
	pDc->BitBlt(dx, dy, nWidth, nHeight, m_pBackDC, sx, sy, SRCCOPY);
	return TRUE;
}

/**
 * @brif グリッドのビットマップ生成
 */
void CDrawerCtrl::MakeGridBmp(){
	CDC *pDc = m_pParentWnd->GetDC();
	if(m_pGridDC){
		m_pGridDC->SelectObject((CBitmap*)NULL);
	}else{
		m_pGridDC = new CDC();
		if(!m_pGridDC->CreateCompatibleDC(pDc)){
			delete m_pGridDC;
			m_pGridDC = NULL;
			return;
		}
	}

	if(m_pGridBmp){
		m_pGridBmp->DeleteObject();
		delete m_pGridBmp;
		m_pGridBmp = NULL;
	}
	
	m_pGridBmp = new CBitmap();
	if(!m_pGridBmp->CreateCompatibleBitmap(pDc, m_nWidth, m_nHeight)){
		delete m_pGridBmp;
		m_pGridBmp = NULL;
		return;
	}
	m_pGridDC->SelectObject(m_pGridBmp);

	//グリッド描画
	CBrush objBack;
	objBack.CreateSolidBrush(m_crBack);
	CRect rect(0, 0, m_nWidth, m_nHeight);
	m_pGridDC->FillRect(rect, &objBack);

	int nXCnt = m_nWidth  / m_objCfg.m_nGridSize + 1;
	int nYCnt = m_nHeight / m_objCfg.m_nGridSize + 1;
	LOGPEN logPen1;
	CPen objGridPen1;
	logPen1.lopnColor = RGB(0xDD, 0xDD, 0xDD);
//	logPen1.lopnStyle = PS_DOT;
	logPen1.lopnStyle = PS_SOLID;
	logPen1.lopnWidth.x = 1;
	logPen1.lopnWidth.y = 1;
	objGridPen1.CreatePenIndirect(&logPen1);
	CPen* pOldPen = m_pGridDC->SelectObject(&objGridPen1);

	for(int i = 0; i < nXCnt; i++){
		m_pGridDC->MoveTo(i * m_objCfg.m_nGridSize, 0);
		m_pGridDC->LineTo(i * m_objCfg.m_nGridSize, m_nHeight);
	}
	for(i = 0; i < nYCnt; i++){
		m_pGridDC->MoveTo(0,        i * m_objCfg.m_nGridSize);
		m_pGridDC->LineTo(m_nWidth, i * m_objCfg.m_nGridSize);
	}
	m_pGridDC->SelectObject(pOldPen);
	
	return;
}

/**
 * @brif 画像保存
 * @brif pszSaveFile 保存ファイル名
 * @brif pszType 保存種別。CDrawerCtrl::imgBMP等を指定する
 * @return 保存に成功するとTRUE、失敗するとFALSE
 */
BOOL CDrawerCtrl::SaveImage(LPCTSTR pszSaveFile, LPCTSTR pszType){
	CPalette plt;
	HBITMAP hBmp = *m_pBackBmp;
	plt.CreateHalftonePalette(m_pBackDC);
	Bitmap bmpSrc(hBmp, plt);

	_bstr_t fname( pszSaveFile );
	_bstr_t type( pszType );

	CLSID pngClsid;
	GetEncoderClsid( type, &pngClsid );
	bmpSrc.Save( fname, &pngClsid, NULL );
	return TRUE;
}

/**
 * @brif ビットマップ保存
 * @brif pszSaveFile 保存ファイル名
 * @return 保存に成功するとTRUE、失敗するとFALSE
 */
BOOL CDrawerCtrl::SaveBitmap(LPCTSTR pszSaveFile){
	return SaveImage(pszSaveFile, imgBMP);
}

/**
 * @brif GIF保存
 * @brif pszSaveFile 保存ファイル名
 * @return 保存に成功するとTRUE、失敗するとFALSE
 */
BOOL CDrawerCtrl::SaveGif(LPCTSTR pszSaveFile){
	return SaveImage(pszSaveFile, imgGIF);
}

/**
 * @brif JPEG保存
 * @brif pszSaveFile 保存ファイル名
 * @return 保存に成功するとTRUE、失敗するとFALSE
 */
BOOL CDrawerCtrl::SaveJpeg(LPCTSTR pszSaveFile){
	return SaveImage(pszSaveFile, imgJPG);
}

/**
 * @brif PNG保存
 * @brif pszSaveFile 保存ファイル名
 * @return 保存に成功するとTRUE、失敗するとFALSE
 */
BOOL CDrawerCtrl::SavePng(LPCTSTR pszSaveFile){
	return SaveImage(pszSaveFile, imgPNG);
}

/**
 * @brif 背景色設定
 */
void CDrawerCtrl::SetBkColor(COLORREF crBack){
	m_crBack = crBack;
	MakeGridBmp();
	InvalidateRect(NULL);
}


//////////////////////////////////////////////////////////////////////////////////
// マウス操作(描画処理)
//////////////////////////////////////////////////////////////////////////////////

/**
 * @brif 描画開始
 * @param crDraw 描画色
 * @param x X座標
 * @param y Y座標
 * @return 描画開始に成功すると、CDrawInfoオブジェクトのポインタを返却する
 */
const CDrawInfo* CDrawerCtrl::DrawStart(COLORREF crDraw, int x, int y){
	if(::IsWindowVisible(m_objEdit.m_hWnd)){
		return NULL;
	}
	CDrawInfo* pInfo = NULL;
	if(m_objCfg.m_bPosGrid){
		//グリッドにあわせる
		x = (int)(x / m_objCfg.m_nGridSize) * m_objCfg.m_nGridSize;
		y = (int)(y / m_objCfg.m_nGridSize) * m_objCfg.m_nGridSize;
	}
	switch(m_eMode){
	case edDraw:
		{
			if(m_pActive && m_pActive->IsDrawing() && (m_pActive->eType == eARRLINE)){
				int nCnt = m_pActive->nRectCnt - 1;
				m_pActive->GetRect(nCnt)->right = x;
				m_pActive->GetRect(nCnt)->bottom = y;

				m_pActive->nRectCnt++;
				nCnt = m_pActive->nRectCnt - 1;
				m_pActive->GetRect(nCnt)->left = x;
				m_pActive->GetRect(nCnt)->top = y;
				m_pActive->GetRect(nCnt)->right = x;
				m_pActive->GetRect(nCnt)->bottom = y;
				m_pActive->judgeRect = m_pActive->GetRect(nCnt);
			}else{
				pInfo = new CDrawInfo();
				pInfo->GetRect(0)->left = x;
				pInfo->GetRect(0)->top = y;
				pInfo->GetRect(0)->right = x;
				pInfo->GetRect(0)->bottom = y;
				pInfo->judgeRect = pInfo->GetRect(0);
				pInfo->cfFront = crDraw;
				pInfo->nRectCnt = 1;
				pInfo->eType = m_eDrawType;
				pInfo->vAlign = alvCENTER;
				pInfo->hAlign = alhCENTER;
				pInfo->SetDrawing(TRUE);
				m_arrDrawinfo.Add(pInfo);
			}
		}
		break;
	case edselMove:
		{
			pInfo = (CDrawInfo *)GetDrawInfo(x, y, TRUE);
		}
		break;
	}
	return pInfo;
}

/**
 * @brif マウス移動時処理
 * @param pInfo 捜査対象
 * @param x X座標
 * @param y Y座標
 */
void CDrawerCtrl::DrawMove(CDrawInfo* pInfo, int x, int y){
	if(::IsWindowVisible(m_objEdit.m_hWnd)){
		return;
	}

	int nOldX = m_nOldCurX;
	int nOldY = m_nOldCurY;
	if(m_objCfg.m_bPosGrid){
		//グリッドにあわせる
		x = (int)(x / m_objCfg.m_nGridSize) * m_objCfg.m_nGridSize;
		y = (int)(y / m_objCfg.m_nGridSize) * m_objCfg.m_nGridSize;
		nOldX = (int)(nOldX / m_objCfg.m_nGridSize) * m_objCfg.m_nGridSize;
		nOldY = (int)(nOldY / m_objCfg.m_nGridSize) * m_objCfg.m_nGridSize;
	}
	switch(m_eMode){
	case edDraw:
		{
			int nCnt = pInfo->nRectCnt - 1;
			pInfo->GetRect(nCnt)->right = x;
			pInfo->GetRect(nCnt)->bottom = y;
			SetJudgeRect(pInfo);
		}
		break;
	case edSelect:
		{
			int nState = ::GetKeyState(VK_LBUTTON) & 0x80;
			if(pInfo->IsSelect() && nState){
				int nMoveX = x - nOldX;
				int nMoveY = y - nOldY;
				int nSize = m_arrDrawinfo.GetSize();
				for(int j = 0; j < nSize; j++){
					pInfo = m_arrDrawinfo.GetAt(j);
					if(!pInfo){
						continue;
					}
					for(int i = 0; i < pInfo->nRectCnt; i++){
						BOOL bResize = FALSE;
						int nSelSize = 3;
						switch(pInfo->eType){
						case eLINE:			//線
						case eARRLINE:		//多角線
							//始点と中間点と終点に配置
							{
								for(int nLn = 0; nLn < pInfo->nRectCnt; nLn++){
									CRect rect = pInfo->GetRect(nLn);
									CRect rSq1(rect.left  - nSelSize, rect.top    - nSelSize, rect.left  + nSelSize, rect.top    + nSelSize);
									CRect rSq2(rect.right - nSelSize, rect.bottom - nSelSize, rect.right + nSelSize, rect.bottom + nSelSize);
								}
							}
							break;
						case eSQUEAR:		//四角
						case eCIRCLE:		//円
							{
							//上下左右等に配置
								CRect rect = pInfo->GetRect(0);
								int nWhalf = rect.Width() / 2;
								int nHhalf = rect.Height() / 2;
								CRect rSq1_1(rect.left  - nSelSize,          rect.top    - nSelSize,          rect.left  + nSelSize,          rect.top    + nSelSize);
								CRect rSq1_2(rect.left  - nSelSize + nWhalf, rect.top    - nSelSize,          rect.left  + nSelSize + nWhalf, rect.top    + nSelSize);
								CRect rSq1_3(rect.right - nSelSize,          rect.top    - nSelSize,          rect.right + nSelSize,          rect.top    + nSelSize);

								CRect rSq2_1(rect.left  - nSelSize,          rect.top    - nSelSize + nHhalf, rect.left  + nSelSize,          rect.top    + nSelSize + nHhalf);
								CRect rSq2_3(rect.right - nSelSize,          rect.top    - nSelSize + nHhalf, rect.right + nSelSize,          rect.top    + nSelSize + nHhalf);

								CRect rSq3_1(rect.left  - nSelSize,          rect.bottom - nSelSize,          rect.left  + nSelSize,          rect.bottom + nSelSize);
								CRect rSq3_2(rect.left  - nSelSize + nWhalf, rect.bottom - nSelSize,          rect.left  + nSelSize + nWhalf, rect.bottom + nSelSize);
								CRect rSq3_3(rect.right - nSelSize,          rect.bottom - nSelSize,          rect.right + nSelSize,          rect.bottom + nSelSize);
							}
							break;
						}
						if(pInfo->nRectCnt && pInfo->IsSelect()){
							CRect * pRect = pInfo->GetRect(i);
							pRect->left		+= nMoveX;
							pRect->top		+= nMoveY;
							pRect->right	+= nMoveX;
							pRect->bottom	+= nMoveY;
						}
					}
					SetJudgeRect(pInfo);
				}
				InvalidateRect(NULL);
			}
		}
		break;
	}
}

/**
 * @brif 描画終了処理
 * @param pInfo 捜査対象
 * @param x X座標
 * @param y Y座標
 */
void CDrawerCtrl::DrawEnd(CDrawInfo* pInfo, int x, int y){
	if(::IsWindowVisible(m_objEdit.m_hWnd) || !pInfo){
		return;
	}
	if(m_objCfg.m_bPosGrid){
		//グリッドにあわせる
		x = (int)(x / m_objCfg.m_nGridSize) * m_objCfg.m_nGridSize;
		y = (int)(y / m_objCfg.m_nGridSize) * m_objCfg.m_nGridSize;
	}
	if(m_eMode == edDraw){
		int nCnt = pInfo->nRectCnt - 1;
		pInfo->GetRect(nCnt)->right = x;
		pInfo->GetRect(nCnt)->bottom = y;
		SetJudgeRect(pInfo);
		pInfo->SetDrawing(FALSE);
		if((nCnt == 1)
		&& !(pInfo->GetRect(nCnt)->left - pInfo->GetRect(nCnt)->right)
		&& !(pInfo->GetRect(nCnt)->top  - pInfo->GetRect(nCnt)->bottom)){
			//この描画は無効
			DeleteItem(pInfo, FALSE);
		}
	}
}


/**
 * @brif 描画情報設定
 * @param x X座標
 * @param y Y座標
 * @param bHeightLight TRUE:ハイライトにする FALSE:ハイライトにしない
 */
const CDrawInfo* CDrawerCtrl::GetDrawInfo(int x, int y, BOOL bHeightLight){
	int nSize = m_arrDrawinfo.GetSize();
	CDrawInfo* pInfo = NULL;
	for(int i = 0; i < nSize; i++){
		pInfo = m_arrDrawinfo.GetAt(i);
		CRect rect( pInfo->judgeRect.left - 1
				   ,pInfo->judgeRect.top - 1
				   ,pInfo->judgeRect.right + 1
				   ,pInfo->judgeRect.bottom + 1);
		if(rect.PtInRect(CPoint(x, y))){
			if(bHeightLight){
				m_pHeightRight = pInfo;
			}
			return pInfo;
		}
		pInfo = NULL;
	}
	m_pHeightRight = NULL;
	return pInfo;	
}

//////////////////////////////////////////////////////////////////////////////////
// 設定
//////////////////////////////////////////////////////////////////////////////////
/**
 * @brif 編集モード切替
 * @param eMode 描画モード
 */
void CDrawerCtrl::SetEditMode(eEditMode eMode){
	if(m_pActive && m_pActive->IsDrawing()){
		//編集中
	}
	m_eMode = eMode;
}

/**
 * @brif 描画モード取得
 * @return 現在の描画モード
 */
eEditMode CDrawerCtrl::GetEditMode(){
	return m_eMode;
}

/**
 * @brif 描画種別の設定
 * @param eDraw 描画種別
 */
void CDrawerCtrl::SetDrawType(eDrawType eDraw){
	m_eDrawType = eDraw;
}

/**
 * @brif 描画種別の取得
 * @return 描画種別
 */
eDrawType CDrawerCtrl::GetDrawType(){
	return m_eDrawType;
}

/**
 * @brif グリッドサイズの設定
 * @param nSize グリッドのサイズ
 * @return 設定に成功すればTRUE
 */
BOOL CDrawerCtrl::SetGridSize(int nSize){
	if(nSize < 0){
		return FALSE;
	}
	m_objCfg.m_nGridSize = nSize;
	MakeGridBmp();
	InvalidateRect(NULL);
	return TRUE;
}

/**
 * @brif グリッドサイズの取得
 * @return グリッドサイズ
 */
int CDrawerCtrl::GetGridSize(){
	return m_objCfg.m_nGridSize;
}

/**
 * @brif グリッド使用/未使用状態設定
 * @param bUse TRUE : 使用 / FALSE :未使用
 */
void CDrawerCtrl::SetUsePosGrid(BOOL bUse){
	m_objCfg.m_bPosGrid = bUse;
}

/**
 * @brif グリッド使用/未使用状態取得
 * @return bUse TRUE : 使用 / FALSE :未使用
 */
BOOL CDrawerCtrl::GetUsePosGrid(){
	return m_objCfg.m_bPosGrid;
}

/**
 * @brif イメージのサイズ設定
 */
BOOL CDrawerCtrl::SetSize(int nWidth, int nHeight){
	return CreateImage(nWidth, nHeight);
}

//////////////////////////////////////////////////////////////////////////////////
// テキスト
//////////////////////////////////////////////////////////////////////////////////
/**
 * @brif テキストの設定
 * @param pInfo 設定対象
 * @param pszText 設定するテキスト
 */
void CDrawerCtrl::SetText(CDrawInfo* pInfo, LPCTSTR pszText){
	if(!pInfo){
		return;
	}

	if(!pszText){
		return;
	}
	pInfo->SetString(pszText);
}

/**
 * @brif テキスト編集中のCDrawInfoオブジェクトのポインタ取得
 * @return 編集中のCDrawInfoオブジェクトのポインタ
 */
CDrawInfo* CDrawerCtrl::GetTextEditInfo(){
	return m_pTxtInfo;
}

/**
 * @brif テキスト編集
 * @param pInfo 編集対象
 */
BOOL CDrawerCtrl::EditText(CDrawInfo* pInfo){
	if(!pInfo){
		return FALSE;
	}

	if(!::IsWindow(m_objEdit.m_hWnd)){
		return FALSE;
	}
	m_pTxtInfo = pInfo;
	CString strText;
	pInfo->GetString(strText);
	m_objEdit.SetWindowText(strText);
	m_objEdit.ShowWindow(SW_SHOW);
	m_objEdit.SetWindowPos(&CWnd::wndTop, 
						   pInfo->judgeRect.left, 
						   pInfo->judgeRect.top,
						   pInfo->judgeRect.right - pInfo->judgeRect.left,
						   pInfo->judgeRect.bottom - pInfo->judgeRect.top,
						   SWP_SHOWWINDOW);
	m_objEdit.SetFocus();

	return TRUE;

}

//////////////////////////////////////////////////////////////////////////////////
// セーブ・ロード
//////////////////////////////////////////////////////////////////////////////////
/**
 * @brif 画像情報の保存
 */
BOOL CDrawerCtrl::SaveItemData(LPCTSTR pszFileName, LPCTSTR pszVersion){
	CStdioFile file;
	BOOL bOpen = FALSE;
	TRY{
		int nSize = m_arrDrawinfo.GetSize();
		CString strItemXML;
		bOpen = file.Open(pszFileName, CFile::modeCreate | CFile::modeWrite);
		if(bOpen){

			strItemXML.Format("<?xml version=\"1.0\" encoding=\"Shift-JIS\" ?>\n<DRAWER-ROOT version=\"%s\">\n", pszVersion);
			file.WriteString(strItemXML);
			for(int i = 0; i < nSize; i++){
				CDrawInfo *pInfo = (CDrawInfo*)m_arrDrawinfo.GetAt(i);
				if(pInfo){
					pInfo->GetXMLData(strItemXML);
					file.WriteString(strItemXML);
				}
			}
			file.WriteString("</DRAWER-ROOT>\r\n");
		}
	}CATCH_ALL(e){
		if(e){
			char szErr[1025];
			memset(szErr, 0, 1025);
			e->GetErrorMessage(szErr, 1024);
			AfxMessageBox(szErr, MB_OK);
		}
	}END_CATCH_ALL
	if(bOpen){
		file.Close();
	}
	return TRUE;
}

/**
 * @brif 画像情報読み込み
 */
BOOL CDrawerCtrl::LoadItemData(LPCTSTR pszFilename){
	//XMLドキュメントの生成
	IXMLDOMDocumentPtr pXMLDoc;
	BOOL bRet = TRUE;
	try{
		//MSXMLの作成
		HRESULT hRes = pXMLDoc.CreateInstance(CLSID_DOMDocument);
		if(hRes != S_OK){
			throw 1;
		}
		pXMLDoc->put_async(VARIANT_FALSE); // load メソッドがロードを完了するまで待つようにする	
		VARIANT_BOOL f;
		hRes = pXMLDoc->load(_variant_t(pszFilename), &f);
		if((hRes != S_OK) || !f){
			// エラー処理
			throw 1;
		}

		IXMLDOMElementPtr pRoot;
		pXMLDoc->get_documentElement(&pRoot);
		if(pRoot == NULL){
			throw 1;
		}
/*
		IXMLDOMNodePtr pNode;
		pXMLDoc->get_firstChild(&pNode);
		if(NULL == pNode){
			// エラー処理
			throw 1;
		}
*/
		BSTR bstrText;
		CString strText;
		pRoot->get_nodeName(&bstrText);
		AfxBSTR2CString(&strText, bstrText);
		if(strText.Compare("DRAWER-ROOT")){
			throw 1;
		}

		//バージョン取得

	}catch(...){
		bRet = FALSE;
	}
	pXMLDoc = NULL;
	return bRet;
}

//////////////////////////////////////////////////////////////////////////////////
// 他
//////////////////////////////////////////////////////////////////////////////////
/**
 * @brif 範囲判定用矩形登録
 * @param pInfo 登録対象
 */
void CDrawerCtrl::SetJudgeRect(CDrawInfo* pInfo){
	for(int i = 0; i < pInfo->nRectCnt; i++){
		if(i == 0){
			if(pInfo->GetRect(i)->left > pInfo->GetRect(i)->right){
				pInfo->judgeRect.left	= pInfo->GetRect(i)->right;
				pInfo->judgeRect.right	= pInfo->GetRect(i)->left;
			}else{
				pInfo->judgeRect.left	= pInfo->GetRect(i)->left;
				pInfo->judgeRect.right	= pInfo->GetRect(i)->right;
			}
			if(pInfo->GetRect(i)->top > pInfo->GetRect(i)->bottom){
				pInfo->judgeRect.top	= pInfo->GetRect(i)->bottom;
				pInfo->judgeRect.bottom	= pInfo->GetRect(i)->top;
			}else{
				pInfo->judgeRect.top	= pInfo->GetRect(i)->top;
				pInfo->judgeRect.bottom	= pInfo->GetRect(i)->bottom;
			}
		}else{
			if(pInfo->GetRect(i)->left > pInfo->GetRect(i)->right){
				if(pInfo->judgeRect.left >  pInfo->GetRect(i)->right){
					pInfo->judgeRect.left	= pInfo->GetRect(i)->right;
				}
				if(pInfo->judgeRect.right <  pInfo->GetRect(i)->left){
					pInfo->judgeRect.right	= pInfo->GetRect(i)->left;
				}
			}else{
				if(pInfo->judgeRect.left >=  pInfo->GetRect(i)->left){
					pInfo->judgeRect.left	= pInfo->GetRect(i)->left;
				}
				if(pInfo->judgeRect.right <=  pInfo->GetRect(i)->right){
					pInfo->judgeRect.right	= pInfo->GetRect(i)->right;
				}
			}
			if(pInfo->GetRect(i)->top > pInfo->GetRect(i)->bottom){
				if(pInfo->judgeRect.top >  pInfo->GetRect(i)->bottom){
					pInfo->judgeRect.top	= pInfo->GetRect(i)->bottom;
				}
				if(pInfo->judgeRect.bottom <  pInfo->GetRect(i)->top){
					pInfo->judgeRect.bottom	= pInfo->GetRect(i)->top;
				}
			}else{
				if(pInfo->judgeRect.top >= pInfo->GetRect(i)->top){
					pInfo->judgeRect.top	= pInfo->GetRect(i)->top;
				}
				if(pInfo->judgeRect.bottom <=  pInfo->GetRect(i)->bottom){
					pInfo->judgeRect.bottom	= pInfo->GetRect(i)->bottom;
				}
			}
		}
	}
	if(pInfo->judgeRect.left == pInfo->judgeRect.right){
		pInfo->judgeRect.left -= 2;
		pInfo->judgeRect.right += 2;
	}
	if(pInfo->judgeRect.top == pInfo->judgeRect.bottom){
		pInfo->judgeRect.top -= 2;
		pInfo->judgeRect.bottom += 2;
	}
}

/**
 * @brif アイテム削除
 * @param pInfo 削除対象
 * @return 削除に成功すればTRUE
 */
BOOL CDrawerCtrl::DeleteItem(CDrawInfo* pItem /* = NULL*/, BOOL bSelOnly /* = TRUE*/){
	int nSize = m_arrDrawinfo.GetSize();
		//選択アイテム全て削除
	
	for(int i = nSize - 1; i >= 0; i--){
		CDrawInfo* pTargetItem = m_arrDrawinfo[i];
		if(pItem == NULL){
			if(pTargetItem && pTargetItem->IsSelect()){
				if(pTargetItem == m_pActive){
					m_pActive = NULL;
				}
				if(pTargetItem == m_pHeightRight){
					m_pHeightRight = NULL;
				}
				if(pTargetItem == m_pTxtInfo){
					m_pTxtInfo = NULL;
				}
				m_arrDrawinfo.RemoveAt(i);
				delete pTargetItem;
			}
		}else if(pTargetItem == pItem){
			if(pTargetItem == m_pActive){
				m_pActive = NULL;
			}
			if(pTargetItem == m_pHeightRight){
				m_pHeightRight = NULL;
			}
			if(pTargetItem == m_pTxtInfo){
				m_pTxtInfo = NULL;
			}
			m_arrDrawinfo.RemoveAt(i);
			delete pTargetItem;
			return TRUE;
		}
	}
	return FALSE;
}

/**
 * @brif スクロール情報の設定
 */
void CDrawerCtrl::CalcScrollRange(){
#if defined(USE_SCROLLBAR_OBJ)
	if(!GetScrollBarCtrl(SB_VERT) && !GetScrollBarCtrl(SB_HORZ) ){
		return;
	}
#endif
	
	CRect clRect;
	GetClientRect(clRect);

	SCROLLINFO scInfo;
	memset(&scInfo, 0, sizeof(SCROLLINFO));
	scInfo.cbSize = sizeof(SCROLLINFO);
	scInfo.fMask = SIF_PAGE	| SIF_RANGE;
	scInfo.nPage = clRect.Height();
//	scInfo.nMax = m_nHeight - clRect.Height();
	scInfo.nMax = m_nHeight;
	if(scInfo.nMax < 0){
		scInfo.nMax = 0;
	}
	SetScrollInfo(SB_VERT, &scInfo);
#if defined(USE_SCROLLBAR_OBJ)
	if(GetScrollBarCtrl(SB_VERT)){
		if(scInfo.nMax <= 0){
			m_objVScrBar.ShowScrollBar(FALSE);
		}else{
			m_objVScrBar.ShowScrollBar(TRUE);
		}
	}
#else
//	if(scInfo.nMax <= 0){
//		ShowScrollBar(SB_VERT, FALSE);
//	}else{
//		ShowScrollBar(SB_VERT, TRUE);
//	}
#endif
	memset(&scInfo, 0, sizeof(SCROLLINFO));
	scInfo.cbSize = sizeof(SCROLLINFO);
	scInfo.fMask = SIF_PAGE	| SIF_RANGE;
	scInfo.nPage = clRect.Width();
//	scInfo.nMax = m_nWidth - clRect.Width();
	scInfo.nMax = m_nWidth;
	if(scInfo.nMax < 0){
		scInfo.nMax = 0;
	}
	SetScrollInfo(SB_HORZ, &scInfo);
#if defined(USE_SCROLLBAR_OBJ)
	if(GetScrollBarCtrl(SB_HORZ)){
		if(scInfo.nMax <= 0){
			ShowScrollBar(FALSE);
		}else{
			ShowScrollBar(TRUE);
		}
	}
#else
//	if(scInfo.nMax <= 0){
//		ShowScrollBar(SB_HORZ, FALSE);
//	}else{
//		ShowScrollBar(SB_HORZ, TRUE);
//	}
#endif
}

#if defined(USE_SCROLLBAR_OBJ)
/**
 * @brif GetScrollBarCtrlのオーバーライド
 */
CScrollBar* CDrawerCtrl::GetScrollBarCtrl( int nBar ) const{
	const CScrollBar* pBar = NULL;
	if((nBar == SB_HORZ) && ::IsWindow(m_objHScrBar.m_hWnd)){
		pBar = &m_objHScrBar;
	}else if((nBar == SB_VERT) && ::IsWindow(m_objVScrBar.m_hWnd)){
		pBar = &m_objVScrBar;
	}
	return (CScrollBar*)pBar;
}
#endif

int CDrawerCtrl::IsSelected(){
	int nCnt = m_arrDrawinfo.GetSize();
	for(int i = 0; i < nCnt; i++){
		CDrawInfo *pInfo = m_arrDrawinfo.GetAt(i);
		if(pInfo && pInfo->IsSelect()){
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CDrawerCtrl::CopyItem(CDrawInfo *pFrom){
	ClearCopyBuff();
	m_nPasteShiftV = 16;
	m_nPasteShiftH = 16;
	if(pFrom){
		CDrawInfo *pCopyInfo = new CDrawInfo();
		if(pCopyInfo->Copy(pFrom)){
			m_arrCopyinfo.Add(pCopyInfo);
		}else{
			delete pCopyInfo;
		}
	}else{
		//選択を全部コピー
		int nSize = m_arrDrawinfo.GetSize();
		for(int i = 0; i < nSize; i++){
			CDrawInfo *pInfo = m_arrDrawinfo.GetAt(i);
			if(pInfo && pInfo->IsSelect()){
				CDrawInfo *pCopyInfo = new CDrawInfo();
				if(pCopyInfo->Copy(pInfo)){
					m_arrCopyinfo.Add(pCopyInfo);
				}else{
					delete pCopyInfo;
				}
			}
		}
	}
	return TRUE;
}

void CDrawerCtrl::ClearCopyBuff(){
	int nSize = m_arrCopyinfo.GetSize();
	//コピーバッファをクリア
	for(int i = 0; i < nSize; i++){
		CDrawInfo *pInfo = m_arrCopyinfo.GetAt(i);
		if(pInfo){
			delete pInfo;
		}
	}
	m_arrCopyinfo.RemoveAll();
}

BOOL CDrawerCtrl::CutItem(CDrawInfo *pItem){

	return TRUE;
}

BOOL CDrawerCtrl::UnDo(){
	return TRUE;
}


void CDrawerCtrl::Paste(){
	int nSize = m_arrCopyinfo.GetSize();
	SelectAll(FALSE);
	for(int i = 0; i < nSize; i++){
		CDrawInfo *pFrom = m_arrCopyinfo.GetAt(i);
		if(pFrom){
			CDrawInfo *pNew = new CDrawInfo();
			pNew->Copy(pFrom);
			if(pNew->judgeRect.bottom + m_nPasteShiftV > m_nHeight){
				m_nPasteShiftV = 0;
			}
			if(pNew->judgeRect.right + m_nPasteShiftH > m_nWidth){
				m_nPasteShiftH = 0;
			}
			for(int j = 0; j < pNew->nRectCnt; j++){
				pNew->GetRect(j)->left		+= m_nPasteShiftH;
				pNew->GetRect(j)->top		+= m_nPasteShiftV;
				pNew->GetRect(j)->right		+= m_nPasteShiftH;
				pNew->GetRect(j)->bottom	+= m_nPasteShiftV;
			}
			pNew->Select(TRUE);
			m_arrDrawinfo.Add(pNew);

		}
	}
	m_nPasteShiftH += 16;
	m_nPasteShiftV += 16;
	InvalidateRect(NULL);
}

void CDrawerCtrl::SelectAll(BOOL bSel){
	int nSize = m_arrDrawinfo.GetSize();
	for(int i = 0; i < nSize; i++){
		CDrawInfo *pInfo = m_arrDrawinfo.GetAt(i);
		pInfo->Select(bSel);
	}
}

void CDrawerCtrl::OnDrCopy(){
	CopyItem();
}

void CDrawerCtrl::OnDrDelete(){
	DeleteItem();
}

void CDrawerCtrl::OnInpText(){
	CPoint point;
	::GetCursorPos(&point);
	ScreenToClient(&point);
	CDrawInfo* pInfo = (CDrawInfo*)GetDrawInfo(point.x, point.y, TRUE);
	EditText(pInfo);
}

void CDrawerCtrl::OnProperty(){
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
	CDrawerPropDlg dlg;
	dlg.m_pCtrl = this;
	dlg.DoModal();
}

void CDrawerCtrl::OnUpdateDrCopy(CCmdUI* pCmdUI){
	if(m_pActive){
		pCmdUI->Enable(m_pActive->IsSelect());
	}else{
		pCmdUI->Enable(FALSE);
	}
}

void CDrawerCtrl::OnUpdateDrDelete(CCmdUI* pCmdUI){
	if(m_pActive){
		pCmdUI->Enable(m_pActive->IsSelect());
	}else{
		pCmdUI->Enable(FALSE);
	}
}

void CDrawerCtrl::OnUpdateInpText(CCmdUI* pCmdUI){
	if(m_pActive){
		pCmdUI->Enable(m_pActive->IsSelect());
	}else{
		pCmdUI->Enable(FALSE);
	}
}

void CDrawerCtrl::OnUpdateProperty(CCmdUI* pCmdUI){
	if(m_pActive){
		pCmdUI->Enable(m_pActive->IsSelect());
	}else{
		pCmdUI->Enable(FALSE);
	}
}



void CDrawerCtrl::ShowGrid(BOOL bShow){
	m_objCfg.m_bShowGrid = bShow;
}

BOOL CDrawerCtrl::IsShowGrid(){
	return m_objCfg.m_bShowGrid;
}
