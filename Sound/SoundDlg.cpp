
// SoundDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Sound.h"
#include "SoundDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSoundDlg 대화 상자



CSoundDlg::CSoundDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SOUND_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSoundDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSoundDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_BTN, &CSoundDlg::OnBnClickedStartBtn)
	ON_BN_CLICKED(IDC_STOP_BTN, &CSoundDlg::OnBnClickedStopBtn)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CSoundDlg 메시지 처리기

BOOL CSoundDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// 녹음 또는 재생에 사용할 소리 정보를 설정한다.
	// 기본 구성은 8khz, 16bit mono -> 1초당 16000 bytes (8000 * 2 * 1)
	m_wave_format.wFormatTag = WAVE_FORMAT_PCM; // PCM
	m_wave_format.nChannels = 1; // 마이크 녹음 방식: 모노
	m_wave_format.nSamplesPerSec = 8000; // 샘플링 주기 : 8khz
	m_wave_format.wBitsPerSample = 16; // 샘플링 단위 : 16 bits

	// 한개의 샘플 데이터를 몇바이트씩 읽을 것인지 정한다.
	// 샘플당 비트수/8 (샘플당 바이트수) * 채널 수
	m_wave_format.nBlockAlign = m_wave_format.nChannels * m_wave_format.wBitsPerSample / 8;
	// 1초당 데이터를 입출력하는데 필요한 바이트 수를 구한다.
	// 샘플링 * 샘플당 비트수/8 * 채널수 
	m_wave_format.nAvgBytesPerSec = m_wave_format.nSamplesPerSec * m_wave_format.nBlockAlign;
	m_wave_format.cbSize = 0; // 

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSoundDlg::OnPaint()
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
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSoundDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSoundDlg::OnBnClickedStartBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}


void CSoundDlg::OnBnClickedStopBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CSoundDlg::OnDestroy()
{
	OnBnClickedStopBtn();
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

}
