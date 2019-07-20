#if !defined(__ABSTRACTWND__)
#define __ABSTRACTWND__
#include "BaseData.h"
/**
 * @brif �c�[���o�[�̃C���[�W��ݒ肷��ۂ̏��̍\����(SetToolbarImg�֐��p)
 */
typedef struct tagTBIMGINFO{
	UINT		uID;		//@brif Bitmap���\�[�X��ID
	int			nColorBit;	//@brif 256�A�C�R����K�p����J���[�r�b�g�̍Œ�l
	COLORREF	crMask;		//@brif �}�X�N�J���[
	CToolBar	*pToolBar;	//@brif �c�[���o�[�̃|�C���^
	int			nButtons;	//@brif �{�^���̐�
	int			nBtnWidth;	//@brif �{�^���̕�
	int			nBtnHeight;	//@brif �{�^���̍���
}TBIMGINFO, *PTBIMGINFO;

#ifdef DEVMFC_EXPORTS
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_IMPORT
#endif

/**
 * @brif MFC�ɂ͖����E�B���h�E���쓙�̊֐������N���X�B(�����I�ɒ��ۃN���X�ɂȂ�\���L��)
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