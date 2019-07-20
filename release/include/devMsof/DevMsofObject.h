// DevMsofObject.h: CDevMsofObject �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVMSOFOBJECT_H__22686B4D_2752_4C1C_B0DC_B93237A6BB90__INCLUDED_)
#define AFX_DEVMSOFOBJECT_H__22686B4D_2752_4C1C_B0DC_B93237A6BB90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MsImport.h"
#include <AfxPriv2.h>

#ifdef DEV_EXP
	#define DEV_EXPORT __declspec( dllexport )
#else
	#define DEV_EXPORT __declspec( dllimport )
#endif

/**
 * @verify ���N���X
 */
class DEV_EXPORT CDevMsofObject{
public:
	void SetShowError(BOOL bShow);
	BOOL IsShowError();
	LPCTSTR GetLastErrorMsg();
	CDevMsofObject();
	virtual ~CDevMsofObject();
	virtual BOOL Show(BOOL bIsSHow) = 0;
	virtual BOOL Quit(LPCTSTR pszFileName, BOOL bIsSaveQuit) = 0;
	BOOL Initalize();
	BOOL Finalize();

private:
	///OLE�̏��������������Ă��邩�ǂ���
	static m_bOleInitalized;

	///�G���[���b�Z�[�W
	CString m_strErrMsg;

	///�G���[���b�Z�[�W��\�����邩�ǂ���
	BOOL m_bShowError;
protected:
	void ShowErrorMsg();
	void ShowComError(_com_error e);
	void SetLastErrorMsg(LPCTSTR pszMsg);

};

#endif // !defined(AFX_DEVMSOFOBJECT_H__22686B4D_2752_4C1C_B0DC_B93237A6BB90__INCLUDED_)
