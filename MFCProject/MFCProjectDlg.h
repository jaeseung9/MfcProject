// MFCProjectDlg.h: 헤더 파일
//

#pragma once
#include "CDlgImage.h"
#include "CDlgParameter.h"


// CMFCProjectDlg 대화 상자
class CMFCProjectDlg : public CDialogEx
{
private:

	CImage m_image; // 이미지 객체

	// 생성자입니다.
public:
	CMFCProjectDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCPROJECT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


	CBitmapButton* m_pBtnDraw; // 그리기 버튼
	CBitmapButton* m_pBtnDice; // 랜덤 버튼

	// 구현입니다.
protected:
	HICON m_hIcon; // 아이콘 핸들

	// 메시지 맵 함수
	virtual BOOL OnInitDialog(); // 대화 상자 초기화
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam); // 시스템 명령 처리
	afx_msg void OnPaint(); // 그리기 처리
	afx_msg HCURSOR OnQueryDragIcon(); // 드래그 아이콘 설정
	DECLARE_MESSAGE_MAP()

public:
	CBrush m_brush; // 브러시 객체
	CImage m_imgFile; // 파일 이미지 객체

	float StartPointX; // 시작점 X 좌표
	float StartPointY; // 시작점 Y 좌표
	float EndPointX;   // 끝점 X 좌표
	float EndPointY;   // 끝점 Y 좌표
	int radius;        // 반지름


	afx_msg void OnBnClickedBtnDraw(); // 그리기 버튼 클릭 처리
	afx_msg void OnBnClickedBtnDice(); // 랜덤값 버튼 클릭 처리
	afx_msg void OnBnClickedAction(); // 이동 버튼 클릭 처리
	afx_msg void OnBnClickedOpen(); // 탐색기 열기 버튼 클릭 처리

	CDlgImage* m_pDlgImage; // 이미지 대화 상자 포인터
	CDlgParameter* m_pDlgParameter; // 파라미터 대화 상자 포인터

	void InitDialog(); // 대화 상자 초기화 함수
	void SetDlgView(int nMode); // 대화 상자 보기 설정
	afx_msg void OnDestroy(); // 대화 상자 소멸 시 처리

};
