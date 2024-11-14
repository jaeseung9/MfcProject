#pragma once
#include "afxdialogex.h"


// CDlgParameter 대화 상자

class CDlgParameter : public CDialog
{
	DECLARE_DYNAMIC(CDlgParameter)

public:
	CDlgParameter(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgParameter();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDlgParameter };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
