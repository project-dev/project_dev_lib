#include "stdafx.h"
#include "AbstractWnd.h"
#include "LogFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/**
 * @brif �w�肵���ACWnd�̃|�C���^���A�E�B���h�E�Ƃ��ėL�����𒲂ׂ�
 * @param CWnd *pWnd CWnd�̃|�C���^
 * @return �E�B���h�E�Ƃ��ėL���Ȃ�TRUE
 */
BOOL CAbstractWnd::IsWindowSafe(CWnd *pWnd){
	if(!pWnd || !::IsWindow(pWnd->m_hWnd)){
		return FALSE;
	}
	return TRUE;
}

/**
 * @brif �����X�N���[���̏����BOnHScroll����Ăяo�����ƁB
 */
void CAbstractWnd::HScrollFunc(UINT nSBCode, UINT &nPos, CScrollBar* pScrollBar){
	int minpos;
	int maxpos;
	pScrollBar->GetScrollRange(&minpos, &maxpos); 
	maxpos = pScrollBar->GetScrollLimit();

	// Get the current position of scroll box.
	int curpos = pScrollBar->GetScrollPos();

	
	switch ( nSBCode ) {
		case	SB_LINELEFT :	// ���փX�N���[��
			if (curpos > minpos)
				curpos--;
			break ;
		case	SB_LINERIGHT :	// �E�փX�N���[��
			if (curpos < maxpos)
				curpos++;
			break ;
		case	SB_PAGELEFT :	// �P�y�[�W���փX�N���[��
			{
				// Get the page size. 
				SCROLLINFO   info;
				pScrollBar->GetScrollInfo(&info, SIF_ALL);

				if (curpos > minpos)
					curpos = max(minpos, curpos - (int) info.nPage);
			}
			break ;
		case	SB_PAGERIGHT :	// �P�y�[�W�E�փX�N���[��
			{
				// Get the page size. 
				SCROLLINFO   info;
				pScrollBar->GetScrollInfo(&info, SIF_ALL);

				if (curpos < maxpos)
					curpos = min(maxpos, curpos + (int) info.nPage);
			}
			break ;
		case	SB_LEFT :	// ���[�փX�N���[��
			curpos = minpos;
			break ;
		case	SB_RIGHT :	// �E�[�փX�N���[��
			curpos = maxpos;
			break ;
		case	SB_THUMBPOSITION :	// ��Έʒu�փX�N���[���i���݈ʒu�͈��� nPos �Ŏw�肳��܂��j
			curpos = nPos;      // of the scroll box at the end of the drag operation.
			break ;
		case	SB_THUMBTRACK :	// �X�N���[���{�b�N�X���w��ʒu�փh���b�O���܂��i���݈ʒu�͈��� nPos �Ŏw�肳��܂��j
			curpos = nPos;     // position that the scroll box has been dragged to.
			break ;
		case	SB_ENDSCROLL :	// �X�N���[���I��
			break ;
		default :
			break ;
	}
	pScrollBar->SetScrollPos(curpos);
}

/**
 * @brif �����X�N���[���̏����BOnVScroll����Ăяo�����ƁB
 */
void CAbstractWnd::VScrollFunc(UINT nSBCode, UINT &nPos, CScrollBar* pScrollBar){
	int minpos;
	int maxpos;

	pScrollBar->GetScrollRange(&minpos, &maxpos); 
	maxpos = pScrollBar->GetScrollLimit();

	// Get the current position of scroll box.
	int curpos = pScrollBar->GetScrollPos();

	switch ( nSBCode ) {
		case	SB_LINEUP :	// ��փX�N���[��
			if (curpos > minpos)
				curpos--;
			break ;
		case	SB_LINEDOWN :	// ���փX�N���[��
			if (curpos < maxpos)
				curpos++;
			break ;
		case	SB_PAGEUP :	// �P�y�[�W��փX�N���[��
			{
			// Get the page size. 
				SCROLLINFO   info;
				pScrollBar->GetScrollInfo(&info, SIF_ALL);

				if (curpos > minpos)
					curpos = max(minpos, curpos - (int) info.nPage);
			}
			break ;
		case	SB_PAGEDOWN :	// �P�y�[�W���փX�N���[��
			{
			// Get the page size. 
				SCROLLINFO   info;
				pScrollBar->GetScrollInfo(&info, SIF_ALL);

				if (curpos < maxpos)
					curpos = min(maxpos, curpos + (int) info.nPage);
			}
			break ;
		case	SB_TOP :	// ��[�փX�N���[��
			curpos = minpos;
			break ;
		case	SB_BOTTOM :	// ���[�փX�N���[��
			curpos = maxpos;
			break ;
		case	SB_THUMBPOSITION :	// ��Έʒu�փX�N���[���i���݈ʒu�͈��� nPos �Ŏw�肳��܂��j
			curpos = nPos;      // of the scroll box at the end of the drag operation.
			break;
		case	SB_THUMBTRACK :		// �X�N���[���{�b�N�X���w��ʒu�փh���b�O���܂��i���݈ʒu�͈��� nPos �Ŏw�肳��܂��j
			curpos = nPos;     // position that the scroll box has been dragged to.
			break;
		case	SB_ENDSCROLL :	// �X�N���[���I��
			break ;
		default :
			break ;
	}
	pScrollBar->SetScrollPos(curpos);
}

/**
 * @brif �_�C�A���O�ŁAESC,Return�L�[���L�����Z��������B
 * @brif PreTranslateMessage����Ăяo�����ƁB
 */
BOOL CAbstractWnd::DlgKeyCancel(HWND hMyWnd, MSG *pMsg){
	if(!pMsg){
		return FALSE;
	}
	switch(pMsg->message){
	case WM_KEYDOWN:
		{
			
			if((hMyWnd == pMsg->hwnd)
			&& ((pMsg->wParam == VK_RETURN)
			||  (pMsg->wParam == VK_ESCAPE))){
				return TRUE;
			}
		}
		break;
	}
	return FALSE;
}

/**
 * @brif ���X�g�R���g���[���̃J�������𒲐�����B
 * @param CListCtrl *pList �������郊�X�g�R���g���[��
 */
void CAbstractWnd::SetColumnWidthLC(CListCtrl *pList){
	if(!pList || !::IsWindow(pList->m_hWnd)){
		return;
	}

	CHeaderCtrl *pHead = pList->GetHeaderCtrl();
	if(!pHead || !::IsWindow(pHead->m_hWnd)){
		return;
	}
	int nCnt = pHead->GetItemCount();
	for(int i = 0; i < nCnt; i++){
		if(!pList->SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER )){
			continue;
		}
		int nWidth = pList->GetColumnWidth(i);
		if(!pList->SetColumnWidth(i, LVSCW_AUTOSIZE )){
			continue;
		}
		if(nWidth > pList->GetColumnWidth(i)){
			pList->SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER );
		}
	}
}

/**
 * @brif �c�[���o�[��256�F�̃r�b�g�}�b�v��\������
 * @param CListCtrl *pList �������郊�X�g�R���g���[��
 */
BOOL CAbstractWnd::SetToolbarImg(PTBIMGINFO pTbImgInfo){
	if(!pTbImgInfo){
		return FALSE;
	}
	if(!pTbImgInfo->pToolBar){
		return FALSE;
	}
	BOOL bRet = TRUE;
	HDC ic = ::CreateIC("DISPLAY", NULL, NULL, NULL);
	CToolBar *pTBar = pTbImgInfo->pToolBar;
	CToolBarCtrl& objTbCtrl = pTBar->GetToolBarCtrl();
	if(GetDeviceCaps(ic, BITSPIXEL) > pTbImgInfo->nColorBit){
		try{
			CBitmap bmp;
			if(!bmp.LoadBitmap(pTbImgInfo->uID)){
				throw(0);
			}
			CImageList* pImgList = objTbCtrl.GetImageList();
			if(!pImgList){
				throw(0);
			}
			if(!pImgList->DeleteImageList()){
				throw(0);
			}
			BOOL bRet = pImgList->Create(pTbImgInfo->nBtnWidth, 
										 pTbImgInfo->nBtnHeight, 
										 ILC_COLOR16 | ILC_MASK, 
										 pTbImgInfo->nButtons, 
										 pTbImgInfo->nButtons);
			if(!bRet){
				throw(0);
			}
			if(pImgList->Add(&bmp, pTbImgInfo->crMask) == -1){
				throw(0);
			}
			objTbCtrl.SetImageList(pImgList);
			DeleteObject(bmp);
		}catch(int nErr){
			if(nErr){
				CLogFile::SaveAppLog("�c�[���o�[�C���[�W�̓ǂݍ��ݒ��ɃG���[����");
			}else{
				CLogFile::SaveAppLog("�c�[���o�[�C���[�W�̓ǂݍ��ݒ��ɃG���[����");
			}
			bRet = FALSE;
		}
	}
	::DeleteDC(ic);
	return bRet;
}

/**
 * @brif �ŏ�ʂ̐e�E�B���h�E���擾����
 */
CWnd* CAbstractWnd::GetTopParent(CWnd *pWnd){
	CWnd *pParent = pWnd->GetParent();
	CWnd *pOldParent = pParent;
	while(pParent){
		pOldParent = pParent;
		pParent = pOldParent->GetParent();
	}
	pParent = pOldParent;
	return pParent;
}

/**
 * @brif ���̃A�v���P�[�V�����̃t�@�C�������擾���܂��B
 */
void CAbstractWnd::GetModuleFileName(CString &strName){
	char szFileName[MAX_PATH + 1];
	memset(szFileName, 0, MAX_PATH + 1);
	::GetModuleFileName(NULL, szFileName, MAX_PATH);
	strName = szFileName;
}

/**
 * @brif ��O��ۑ����܂��BOnExceptionLog�֐����������邱�ƂŁA���b�Z�[�W��ύX�ł��܂��B
 */
void CAbstractWnd::SaveExceptLog(CException *pExcept){
	char szErr[1025];
	memset(szErr, 0, 1025);
	pExcept->GetErrorMessage(szErr, 1024);
	CString strErr = szErr;
	BOOL bOut = TRUE;
	if(pExcept->IsKindOf(RUNTIME_CLASS(CFileException))){
		bOut = OnFileExceptionLog((CFileException*)pExcept, strErr);
	}else if(pExcept->IsKindOf(RUNTIME_CLASS(CMemoryException))){
		bOut = OnMemoryExceptionLog((CMemoryException*)pExcept, strErr);
	}else{
		bOut = OnExceptionLog(pExcept, strErr);
	}
	if(bOut){
		CLogFile::SaveExceptionLog(strErr);
	}
}

BOOL CAbstractWnd::OnFileExceptionLog(CFileException *pExcept, CString& strErr){
	return TRUE;
}

BOOL CAbstractWnd::OnMemoryExceptionLog(CMemoryException *pExcept, CString& strErr){
	return TRUE;
}

BOOL CAbstractWnd::OnExceptionLog(CException *pExcept, CString& strErr){
	return TRUE;
}
BOOL CAbstractWnd::OnToolTioNotifyFunc(NMHDR *pTTTStruct, LRESULT *pResult){
    TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pTTTStruct;
    TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pTTTStruct;
    CString strTipText;
    UINT nID = pTTTStruct->idFrom;

    if( nID == 0 )      // Notification in NT from automatically
        return FALSE;       // created tooltip

	GetToolTipText(pTTTStruct, strTipText);
#ifndef _UNICODE
    if (pTTTStruct->code == TTN_NEEDTEXTA)
        lstrcpyn(pTTTA->szText, strTipText, 80);
    else
        _mbstowcsz(pTTTW->szText, strTipText, 80);
#else
    if (pTTTStruct->code == TTN_NEEDTEXTA)
        _wcstombsz(pTTTA->szText, strTipText, 80);
    else
        lstrcpyn(pTTTW->szText, strTipText, 80);
#endif
    *pResult = 0;
	return TRUE;
}
void CAbstractWnd::GetToolTipText(NMHDR *pTTTStruct, CString &strTipText){
	strTipText = "";
}

BOOL CAbstractWnd::ShowPopupMenu(POINT point, UINT uMenuID, CWnd *pParent /*= NULL*/, int nMenuIndex /*= 0*/){
	CMenu menu;
	if(!menu.LoadMenu(uMenuID)){
		return FALSE;
	}
	CMenu *pMenu = menu.GetSubMenu(nMenuIndex);

	if(!OnPopupMenuState(pMenu)){
		return FALSE;
	}
	return pMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, pParent);
}

BOOL CAbstractWnd::OnPopupMenuState(CMenu *pMenu){
	return TRUE;
}