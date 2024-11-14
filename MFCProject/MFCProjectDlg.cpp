
// MFCProjectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCProject.h"
#include "MFCProjectDlg.h"
#include "afxdialogex.h"
#include "iostream"
#include "Windows.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

void OpenConsole()
{
	AllocConsole();
	FILE* fp;

	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);
	freopen_s(&fp, "CONIN$", "r", stdin);

}

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:

	CBrush m_brush;
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMFCProjectDlg 대화 상자



CMFCProjectDlg::CMFCProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCPROJECT_DIALOG, pParent)
	, StartPointX(55)
	, StartPointY(200)
	, EndPointX(200)
	, EndPointY(200)
	, radius(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	OpenConsole();
	m_brush.CreateSolidBrush(RGB(200, 200, 200));


}

void CMFCProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_StartXPoint, StartPointX);
	DDX_Text(pDX, IDC_StartYPoint, StartPointY);
	DDX_Text(pDX, IDC_EndXPoint, EndPointX);
	DDX_Text(pDX, IDC_EndYPoint, EndPointY);
	DDX_Text(pDX, IDC_Radius, radius);
}

BEGIN_MESSAGE_MAP(CMFCProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BTN_Draw, &CMFCProjectDlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BTN_Dice, &CMFCProjectDlg::OnBnClickedBtnDice)
	ON_BN_CLICKED(IDC_Action, &CMFCProjectDlg::OnBnClickedAction)
	ON_BN_CLICKED(IDC_Open, &CMFCProjectDlg::OnBnClickedOpen)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCProjectDlg 메시지 처리기

BOOL CMFCProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	srand(static_cast<unsigned int>(time(NULL)));

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	// 이미지
	InitDialog();

	srand(static_cast<unsigned int>(time(nullptr)));


	// 그리기 이미지
	CRect drawRect(0, 0, 0, 0);
	GetDlgItem(IDC_BTN_Draw)->GetWindowRect(&drawRect);
	ScreenToClient(&drawRect);

	m_pBtnDraw = new CBitmapButton;
	m_pBtnDraw->Create(NULL, WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, drawRect, this, IDC_BTN_Draw);
	m_pBtnDraw->LoadBitmaps(IDB_On, IDB_OFF);
	m_pBtnDraw->SizeToContent();


	// 랜덤 좌표값 이미지
	CRect diceRect(0, 0, 0, 0);
	GetDlgItem(IDC_BTN_Dice)->GetWindowRect(&diceRect);
	ScreenToClient(&diceRect);

	m_pBtnDice = new CBitmapButton;
	m_pBtnDice->Create(NULL, WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, diceRect, this, IDC_BTN_Dice);
	m_pBtnDice->LoadBitmaps(IDB_DiceOn, IDB_DiceOff);
	m_pBtnDice->SizeToContent();


	int nBpp = 24;
	m_image.Create(WindowsSizeX, WindowsSizeY, nBpp);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

		CDialogEx::OnPaint();


		// 배경
		CClientDC dc(this);
		//m_image.Draw(dc, 0, 100);
				// 랜덤크기의 원
		CBrush brush(RGB(rand() % 255, rand() % 255, rand() % 255));
		CBrush* pOldBrush = dc.SelectObject(&brush);
		dc.Ellipse(int(StartPointX) - radius, int(StartPointY) - radius, int(StartPointX) + radius, int(StartPointY) + radius);
		dc.SelectObject(pOldBrush);
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCProjectDlg::OnBnClickedBtnDraw()
{
	UpdateData(TRUE);

	radius = rand() % 40 + 15;
	if (m_pDlgImage)
		m_pDlgImage->ShowWindow(SW_HIDE);

	if (m_pDlgParameter)
		m_pDlgParameter->ShowWindow(SW_HIDE);

	UpdateData(FALSE);
	Invalidate();
}


void CMFCProjectDlg::OnBnClickedBtnDice()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	//radius = rand() % 40 + 15;

	StartPointX = float(rand() % (WindowsSizeX - 110) + 55);
	StartPointY = float(rand() % (WindowsSizeY - 200) + 200);
	EndPointX = float(rand() % (WindowsSizeX - 110) + 55);
	EndPointY = float(rand() % (WindowsSizeX - 400) + 200);


	//cout << StartPointX << endl;

	UpdateData(FALSE);
}


void CMFCProjectDlg::OnBnClickedAction()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	float speed = 10;
	float tolerance = 5;  // 목표 지점에 도달했다고 간주할 거리 오차
	float StartPX = StartPointX;
	float StartPY = StartPointY;


	while (abs(StartPointX - EndPointX) > tolerance || abs(StartPointY - EndPointY) > tolerance)
	{

		// 캡처할 영역을 수동으로 설정
		CRect rect(0, 100, WindowsSizeX, WindowsSizeY + 100);  // 원하는 캡처 영역

		// 클라이언트 DC 가져오기
		CDC* pDC = GetDC();
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);

		// 메모리 비트맵 생성
		CBitmap bitmap;
		bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
		CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);

		// 지정된 크기만큼 memDC에 화면을 복사
		memDC.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, rect.left, rect.top, SRCCOPY);

		// CImage에 비트맵 복사
		CImage image;
		image.Create(rect.Width(), rect.Height(), 32);
		HDC hDC = image.GetDC();
		BitBlt(hDC, 0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);
		image.ReleaseDC();

		// 날짜와 시간을 기반으로 파일명 생성
		time_t now = time(0);
		struct tm t;
		localtime_s(&t, &now);
		CString fileName;
		fileName.Format(_T("ScreenCapture_%04d%02d%02d_%02d%02d%02d.bmp"),
			t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
			t.tm_hour, t.tm_min, t.tm_sec);

		// 이미지 저장 경로 설정
		CString savePath = _T("C:\\Users\\서재승\\source\\repos\\MFCProject\\MFCProject\\res\\SaveFile\\") + fileName;
		HRESULT hr = image.Save(savePath, Gdiplus::ImageFormatBMP);

		// 리소스 해제
		memDC.SelectObject(pOldBitmap);
		ReleaseDC(pDC);

		if (StartPointX > EndPointX) StartPointX -=  (StartPX - EndPointX) / speed;
		else if (StartPointX < EndPointX) StartPointX +=  (EndPointX - StartPX) / speed;

		if (StartPointY > EndPointY) StartPointY -=  (StartPY - EndPointY) / speed;
		else if (StartPointY < EndPointY) StartPointY += (EndPointY - StartPY) / speed;

		UpdateData(FALSE);  // UI에 갱신된 좌표를 반영
		Invalidate();       // 화면 갱신
		UpdateWindow();     // 즉각적으로 갱신 적용

		

		Sleep(1500);
	}

	// 마지막 위치를 정확히 맞추기
	StartPointX = EndPointX;
	StartPointY = EndPointY;


	UpdateData(FALSE);
	Invalidate();
}


void CMFCProjectDlg::OnBnClickedOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	char strFilter[] = "BMP ONLY (*.BMP) | *.BMP;*.bmp | All Files(*.*)|*.*||";
	CFileDialog FileDlg(TRUE, CString(".BMP"),NULL,0,CString(strFilter));

	if (FileDlg.DoModal() == IDOK)
	{
		m_pDlgImage->m_imgFile.Destroy();
		HRESULT hr = m_pDlgImage->m_imgFile.Load(FileDlg.GetPathName());

		if (SUCCEEDED(hr))
		{
			// 이미지 출력
			m_pDlgImage->centroid();
			//m_pDlgParameter->ShowWindow(SW_HIDE);
			m_pDlgImage->ShowWindow(SW_HIDE);
			m_pDlgImage->ShowWindow(SW_SHOW);

		}
	}


	
}

void CMFCProjectDlg::InitDialog()
{
	m_pDlgImage = new CDlgImage();
	m_pDlgImage->Create(IDD_CDlgImage);
	m_pDlgImage->MoveWindow(20, 100, WindowsSizeX, WindowsSizeY);

	//m_pDlgParameter = new CDlgParameter();
	//m_pDlgParameter->Create(IDD_CDlgParameter);
	//m_pDlgParameter->MoveWindow(20, 100, 200, 200);

	//SetDlgView(DLG_VIEW_IMAGE);
	//SetDlgView(DLG_VIEW_PARAMETER);


}

void CMFCProjectDlg::SetDlgView(int nMode)
{
	if (nMode & DLG_VIEW_IMAGE) m_pDlgImage->ShowWindow(SW_SHOW);
	else m_pDlgImage->ShowWindow(SW_HIDE);

	//if (nMode & DLG_VIEW_PARAMETER) m_pDlgParameter->ShowWindow(SW_SHOW);
	//else m_pDlgParameter->ShowWindow(SW_HIDE);
}




void CMFCProjectDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	delete m_pDlgImage;
	//delete m_pDlgParameter;

}


