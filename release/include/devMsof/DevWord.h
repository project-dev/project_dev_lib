// DevWord.h: CDevWord クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVWORD_H__927DDBCA_F6FA_4D92_9072_59EE8C6F2821__INCLUDED_)
#define AFX_DEVWORD_H__927DDBCA_F6FA_4D92_9072_59EE8C6F2821__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DevMsofObject.h"
#include "MsImport.h"
/**
 * @verify MS-WORDのCOMオブジェクトのラップクラス
 */
class DEV_EXPORT CDevWord : public CDevMsofObject{
public:
	CDevWord();
	virtual ~CDevWord();

	virtual BOOL Initalize();
	virtual BOOL Finalize();
	virtual BOOL Show(BOOL bIsSHow);
	virtual BOOL Quit(LPCTSTR pszFileName, BOOL bIsSaveQuit);
	virtual BOOL Load(LPCTSTR pszFileName); 
	virtual BOOL Save(LPCTSTR pszFileName, BOOL isOverWrite);
private:
	Word::_ApplicationPtr m_pWord;

};

#endif // !defined(AFX_DEVWORD_H__927DDBCA_F6FA_4D92_9072_59EE8C6F2821__INCLUDED_)
