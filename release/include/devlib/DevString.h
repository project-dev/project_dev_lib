#if !defined(AFX_DEVSTRING_H__65AF3102_5D95_4BE6_B35A_75FE8D724E1D__INCLUDED_)
#define AFX_DEVSTRING_H__65AF3102_5D95_4BE6_B35A_75FE8D724E1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef DEVLIB_EXPORTS
	#define DEV_EXT_CLASS		 __declspec(dllexport)
#else
	#define DEV_EXT_CLASS		 __declspec(dllimport)
#endif

#include "devlib.h"

//�l�[���X�y�[�X�̗��p���������E�E�E
#if NAMESPACE_DEV
namespace devlib{
#endif

/**
 * @brief ������������N���X�ł�
 * ������������N���X�ł��B<BR>
 * MFC��CString�Ɏ��Ă��܂��B<BR>
 * @author Project D.E.V
 */
class DEV_EXT_CLASS CDevString{
public:
	CDevString();
	virtual ~CDevString();

	//�R�s�[�R���X�g���N�^
	CDevString(CDevString &strString);
	CDevString(const char* pszText);
	CDevString(char* pszText);

	//-----------------------------------------------------------------
	//�����񑀍�
	CDevString Left(int nLen) const;
	CDevString Right(int nLen) const;
	CDevString Mid(int nLen) const;
	CDevString SubString(int nStart, int nLen = -1) const;

	//�S�p�Ɣ��p���ӎ�
	CDevString LeftText(int nLen);
	CDevString RightText(int nLen);
	CDevString MidText(int nLen);
	CDevString SubStringText(int nStart, int nLen = -1);

	void Trim();
	void TrimLeft();
	void TrimRight();
	void Empty();
	bool IsEmpty();
	void SetAt(int nIndex, char ch);	
	
	//-----------------------------------------------------------------
	//����/�u��
	int Find(char* pszFind, int nStart = 0);
	int Find(const char* pszFind, int nStart = 0);
	int Find(CDevString &strFind, int nStart = 0);

	int ReverseFind(char* pszFind);
	int ReverseFind(const char* pszFind);
	int ReverseFind(CDevString &strFind);
	
	int Replace(const char* pszNew, const char* pszOld);
	int ReplaceAll(const char* pszNew, const char* pszOld);
	
	//�S�p�Ɣ��p���ӎ�
	int FindText(char* pszFind, int nStart = 0);
	int FindText(const char* pszFind, int nStart = 0);
	int FindText(CDevString &strFind, int nStart = 0);

	int ReverseFindText(char* pszFind);
	int ReverseFindText(const char* pszFind);
	int ReverseFindText(CDevString &strFind);
	
	int ReplaceText(const char* pszNew, const char* pszOld, int nPos = 0);
	int ReplaceAllText(const char* pszNew, const char* pszOld);

	//-----------------------------------------------------------------
	//��r
	int Compare(const char* pszTarget1);
	int CompareNoCase(const char* pszTarget1);
	
	//-----------------------------------------------------------------
	//�擾
	int GetLength();
	char* GetBuffer();
	void ReleaseBuffer();
	char GetAt(int nIndex);

	//�S�p�Ɣ��p���ӎ�
	int GetTextLength();
	bool GetTextAt(int nIndex, CDevString &strAt);

	//-----------------------------------------------------------------
	//�I�y���[�^
	CDevString& operator=(const char* pszText);
	CDevString& operator=(char* pszText);
	CDevString& operator=(char ch);
	CDevString& operator=(CDevString *strString);
	CDevString& operator=(CDevString &strString);
	operator const char*() const;
	char operator [](int nIndex);

	CDevString& operator+=(const char* pszText);
	CDevString& operator+=(char* pszText);
	CDevString& operator+=(char ch);
	CDevString& operator+=(CDevString *strString);
	CDevString& operator+=(CDevString &strString);

protected:
//	string *m_pString;
	void* m_pString;
	char *m_pszChar;

};
#if NAMESPACE_DEV
}
#endif
//��r�p�I�y���[�^

bool __stdcall operator==(CDevString &str1, CDevString &str2);
bool __stdcall operator==(CDevString &str1, const char* pszText);
bool __stdcall operator==(const char* pszText, CDevString &str2);
bool __stdcall operator!=(CDevString &str1, CDevString &str2);
bool __stdcall operator!=(CDevString &str1, const char* pszText);
bool __stdcall operator!=(const char* pszText, CDevString &str2);

#endif // !defined(AFX_DEVSTRING_H__65AF3102_5D95_4BE6_B35A_75FE8D724E1D__INCLUDED_)
