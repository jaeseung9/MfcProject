// CDlgParameter.cpp: 구현 파일
//

#include "pch.h"
#include "MFCProject.h"
#include "afxdialogex.h"
#include "CDlgParameter.h"


// CDlgParameter 대화 상자

IMPLEMENT_DYNAMIC(CDlgParameter, CDialog)

CDlgParameter::CDlgParameter(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CDlgParameter, pParent)
{

}

CDlgParameter::~CDlgParameter()
{
}

void CDlgParameter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgParameter, CDialog)
END_MESSAGE_MAP()


// CDlgParameter 메시지 처리기
