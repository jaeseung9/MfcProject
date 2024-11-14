// CDlgImage.cpp: 구현 파일
//

#include "pch.h"
#include "MFCProject.h"
#include "afxdialogex.h"
#include "CDlgImage.h"

// CDlgImage 대화 상자

IMPLEMENT_DYNAMIC(CDlgImage, CDialog)

CDlgImage::CDlgImage(CWnd* pParent /*=nullptr*/)
    : CDialog(IDD_CDlgImage, pParent)
{
    // 생성자 초기화
}

CDlgImage::~CDlgImage()
{
    // 소멸자
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
    // 데이터 교환 처리
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlgImage, CDialog)
    ON_WM_PAINT()
END_MESSAGE_MAP()

// CDlgImage 메시지 처리기

void CDlgImage::OnPaint()
{
    // 그리기 메시지 처리기
    CPaintDC dc(this); // 페인팅을 위한 DC 컨텍스트 설정

    // 이미지 그리기 함수 호출
    drawImage();

    // 부모 대화 상자 가져오기
    CWnd* pParentDlg = GetParent();
    CRect imageRect;
    GetWindowRect(&imageRect); // 현재 창의 사각형 좌표 얻기
    pParentDlg->ScreenToClient(&imageRect); // 부모 대화 상자 기준으로 좌표 변환

    // y 좌표 보정: 이미지 높이 기준으로 반전
    int displayCenterX = centerX + imageRect.left;
    int displayCenterY = (imageRect.bottom - centerY);  // y 좌표 반전 보정

    // 현재 좌표 출력
    CString message;
    message.Format(_T("좌표: (%d, %d)"), displayCenterX - 19, displayCenterY);
    dc.TextOut(25, 25, message); // 좌표 텍스트 출력
}

void CDlgImage::drawImage()
{
    // 이미지가 표시될 CStatic 컨트롤 가져오기
    CStatic* staticsize = (CStatic*)GetDlgItem(IDC_STATIC_IMAGE);
    CClientDC dc(staticsize); // 이미지 그리기를 위한 DC 컨텍스트 설정

    CRect rect;
    staticsize->GetClientRect(rect); // 이미지 컨트롤의 크기 얻기

    // 이미지가 로드되어 있을 경우 그리기
    if (m_imgFile != NULL)
    {
        int w = m_imgFile.GetWidth();
        int h = m_imgFile.GetWidth();

        // 이미지 비트맵 그리기
        m_imgFile.BitBlt(dc.m_hDC, 0, 0, w, h, 0, 0);
    }
}

void CDlgImage::centroid()
{
    // 이미지가 로드되어 있는지 확인
    if (m_imgFile != NULL)
    {
        int w = m_imgFile.GetWidth();
        int h = m_imgFile.GetHeight();

        // 이미지의 시작 주소 가져오기
        unsigned char* fm = (unsigned char*)m_imgFile.GetPixelAddress(0, h - 1);

        int xsum = 0; // x 좌표의 합
        int ysum = 0; // y 좌표의 합
        int count = 0; // 검은색 픽셀의 개수

        // 픽셀을 반복하며 검은색(0) 픽셀의 x, y 좌표의 합계를 구함
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                unsigned char* fmTmp = fm + (i * w + j) * 4; // 픽셀은 4바이트(BGRA)로 구성됨
                if (fmTmp[0] == 0 && fmTmp[1] == 0 && fmTmp[2] == 0) // 검은색 픽셀 확인
                {
                    xsum += j;
                    ysum += i;
                    count++;
                }
            }
        }

        // 검은색 픽셀의 개수가 0보다 크면 중앙 좌표 계산
        if (count > 0)
        {
            centerX = xsum / count; // x 좌표의 평균
            centerY = ysum / count; // y 좌표의 평균

            // 중앙에 X 모양 그리기 (-5 ~ +5 범위)
            for (int i = -5; i <= 5; i++)
            {
                // 왼쪽 위에서 오른쪽 아래로 내려가는 대각선
                if (centerX + i >= 0 && centerX + i < w && centerY + i >= 0 && centerY + i < h)
                {
                    unsigned char* fmTmp = (unsigned char*)m_imgFile.GetPixelAddress(centerX + i, h - 1 - (centerY + i));
                    fmTmp[0] = 0; // Blue
                    fmTmp[1] = 0; // Green
                    fmTmp[2] = 0; // Red
                }

                // 왼쪽 아래에서 오른쪽 위로 올라가는 대각선
                if (centerX + i >= 0 && centerX + i < w && centerY - i >= 0 && centerY - i < h)
                {
                    unsigned char* fmTmp = (unsigned char*)m_imgFile.GetPixelAddress(centerX + i, h - 1 - (centerY - i));
                    fmTmp[0] = 0; // Blue
                    fmTmp[1] = 0; // Green
                    fmTmp[2] = 0; // Red
                }
            }
        }
    }
}
