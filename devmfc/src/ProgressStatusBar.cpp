// ProgressStatusBar.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "ProgressStatusBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressStatusBar
/**
 * コンストラクタ
 */
CProgressStatusBar::CProgressStatusBar(){
	m_nIndex = -1;
}

/**
 *デストラクタ
 */
CProgressStatusBar::~CProgressStatusBar(){
}


BEGIN_MESSAGE_MAP(CProgressStatusBar, CStatusBar)
	//{{AFX_MSG_MAP(CProgressStatusBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressStatusBar メッセージ ハンドラ

// 
// 関数名 : GetProgressBar
// 概  要 : CProgressCtrlの取得
// 引  数 : なし
// 戻り値 : なし
// 備  考 : なし
//
CProgressCtrl* CProgressStatusBar::GetProgressBar(){
	
	return &m_objProgress;
}

// 
// 関数名 : OnCreate
// 概  要 : ウィンドウ生成時のハンドラ関数
// 引  数 : なし
// 戻り値 : なし
// 備  考 : なし
//
int CProgressStatusBar::OnCreate(LPCREATESTRUCT lpCreateStruct){
	if (CStatusBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect;
    m_objProgress.Create(WS_CHILD, rect, this, 0);
	
	return 0;
}

// 
// 関数名 : ShowProgressBar
// 概  要 : プログレスバーの表示
// 引  数 : nIndex 表示位置
// 戻り値 : なし
// 備  考 : なし
//
UINT CProgressStatusBar::ShowProgressBar(int nIndex){
	CRect rect;
    int nOldIndex = m_nIndex;
    m_nIndex = nIndex;
    GetItemRect(nIndex, rect);
    m_objProgress.MoveWindow(rect);
    m_objProgress.ShowWindow((nIndex == -1) ? SW_HIDE : SW_SHOWNA);
    return nOldIndex;

}

// 
// 関数名 : OnSize
// 概  要 : サイズ変更時のハンドラ関数
// 引  数 : なし
// 戻り値 : なし
// 備  考 : なし
//
void CProgressStatusBar::OnSize(UINT nType, int cx, int cy){
	CStatusBar::OnSize(nType, cx, cy);
    if (!::IsWindow(m_objProgress.m_hWnd) || m_nIndex == -1)
        return;

    // 位置を修正
    CRect rect;
    GetItemRect(m_nIndex, rect);
    m_objProgress.MoveWindow(rect, FALSE);
}

// 
// 関数名 : SetRange32
// 概  要 : 最大、最小の設定
// 引  数 : なし
// 戻り値 : なし
// 備  考 : なし
//
void CProgressStatusBar::SetRange32(int nLower, int nUpper){
	m_objProgress.SetRange32(nLower, nUpper);
}

// 
// 関数名 : SetRange
// 概  要 : 最大、最小の設定
// 引  数 : なし
// 戻り値 : なし
// 備  考 : なし
//
void CProgressStatusBar::SetRange(short nLower, short nUpper){
	m_objProgress.SetRange(nLower, nUpper);
}

// 
// 関数名 : GetRange
// 概  要 : 最大、最小の取得
// 引  数 : なし
// 戻り値 : なし
// 備  考 : なし
//
void CProgressStatusBar::GetRange(int &nLower, int &nUpper){
	m_objProgress.GetRange(nLower, nUpper);
}

/**
 * 目盛りの現在位置の取得
 * @return 目盛りの現在の位置
 */
int CProgressStatusBar::GetPos(){
	return m_objProgress.GetPos();
}

/**
 * 目盛りの位置を設定
 * @param nPos 位置
 * @return 直前の位置
 */
int CProgressStatusBar::SetPos(int nPos){
	return m_objProgress.SetPos(nPos);
}

/**
 * オフセット位置を指定
 * @param nPos 位置を進める量を指定します
 * @return 直前の位置
 */
int CProgressStatusBar::OffsetPos(int nPos){
	return m_objProgress.OffsetPos(nPos);
}

/**
 * 増分値を指定
 * @return 直前の増分値を返します。
 */
int CProgressStatusBar::SetStep(int nStep){
	return m_objProgress.SetStep(nStep);
}


/**
 * 目盛りを進めます
 * @return 直前の位置を返します。
 */
int CProgressStatusBar::StepIt(){
	return m_objProgress.StepIt();
}
