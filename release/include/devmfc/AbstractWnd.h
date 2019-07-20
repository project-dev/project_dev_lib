#if !defined(__ABSTRACTWND__)
#define __ABSTRACTWND__
#include "BaseData.h"
/**
 * @brif ツールバーのイメージを設定する際の情報の構造体(SetToolbarImg関数用)
 */
typedef struct tagTBIMGINFO{
	UINT		uID;		//@brif BitmapリソースのID
	int			nColorBit;	//@brif 256アイコンを適用するカラービットの最低値
	COLORREF	crMask;		//@brif マスクカラー
	CToolBar	*pToolBar;	//@brif ツールバーのポインタ
	int			nButtons;	//@brif ボタンの数
	int			nBtnWidth;	//@brif ボタンの幅
	int			nBtnHeight;	//@brif ボタンの高さ
}TBIMGINFO, *PTBIMGINFO;

#ifdef DEVMFC_EXPORTS
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_IMPORT
#endif

/**
 * @brif MFCには無いウィンドウ操作等の関数を持つクラス。(将来的に抽象クラスになる可能性有り)
 */
class DEV_EXT_MFCCLASS CAbstractWnd : public CBaseData{
public:
	static void SetColumnWidthLC(CListCtrl *pList);
	static BOOL IsWindowSafe(CWnd *pWnd);
	static void HScrollFunc(UINT nSBCode, UINT &nPos, CScrollBar* pScrollBar);
	static void VScrollFunc(UINT nSBCode, UINT &nPos, CScrollBar* pScrollBar);
	static BOOL DlgKeyCancel(HWND hMyWnd, MSG *pMsg);
	static BOOL SetToolbarImg(PTBIMGINFO pTbImgInfo);
	static CWnd* GetTopParent(CWnd *pWnd);

private:


protected:

	BOOL ShowPopupMenu(POINT point, UINT uMenuID, CWnd *pParent = NULL, int nMenuIndex = 0);
	void GetModuleFileName(CString &strName);

	void SaveExceptLog(CException *pExcept);
	virtual BOOL OnFileExceptionLog(CFileException *pExcept, CString& strErr);
	virtual BOOL OnMemoryExceptionLog(CMemoryException *pExcept, CString& strErr);
	virtual BOOL OnExceptionLog(CException *pExcept, CString& strErr);
	BOOL OnToolTioNotifyFunc(NMHDR *pTTTStruct, LRESULT *pResult);
	virtual void GetToolTipText(NMHDR *pTTTStruct, CString &strTipText);
	virtual BOOL OnPopupMenuState(CMenu *pMenu);
};
#endif