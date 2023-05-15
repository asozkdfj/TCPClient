﻿
// mfc_test45_tcpclient1Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "mfc_test45_tcpclient1.h"
#include "mfc_test45_tcpclient1Dlg.h"
#include "afxdialogex.h"

#include "CDataSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cmfctest45tcpclient1Dlg 대화 상자



Cmfctest45tcpclient1Dlg::Cmfctest45tcpclient1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_TEST45_TCPCLIENT1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void Cmfctest45tcpclient1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipaddr);
}

BEGIN_MESSAGE_MAP(Cmfctest45tcpclient1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_CONNECT, &Cmfctest45tcpclient1Dlg::OnClickedConnect)
	ON_BN_CLICKED(IDC_DISCONNECT, &Cmfctest45tcpclient1Dlg::OnBnClickedDisconnect)
	ON_BN_CLICKED(IDC_SEND, &Cmfctest45tcpclient1Dlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_CONNECT, &Cmfctest45tcpclient1Dlg::OnBnClickedConnect)
END_MESSAGE_MAP()


// Cmfctest45tcpclient1Dlg 메시지 처리기

BOOL Cmfctest45tcpclient1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
	m_pDataSocket = NULL;
	m_ipaddr.SetWindowText(_T("127.0.0.1"));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void Cmfctest45tcpclient1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cmfctest45tcpclient1Dlg::OnPaint()
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
HCURSOR Cmfctest45tcpclient1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Cmfctest45tcpclient1Dlg::OnBnClickedDisconnect()
{
	if (m_pDataSocket == NULL) {
		MessageBox(_T("서버에 접속 안 함!"), _T("알림"), MB_ICONERROR);
	}
	else {
		m_pDataSocket->Close();
		delete m_pDataSocket;
		m_pDataSocket = NULL;
	}
}


void Cmfctest45tcpclient1Dlg::OnBnClickedSend()
{
	if (m_pDataSocket == NULL) {
		MessageBox(_T("서버에 접속 안함!"), _T("알림"), MB_ICONERROR);
	}
	else {
		CString message;
		m_edit.GetWindowText(message);
		message += _T("\r\n");
		m_pDataSocket->Send((LPCTSTR)message, (message.GetLength() + 1) * sizeof(TCHAR));
		m_edit.SetWindowText(_T(""));
		m_edit.SetFocus();
	}

}


void Cmfctest45tcpclient1Dlg::OnBnClickedConnect()
{
	if (m_pDataSocket == NULL) {
		m_pDataSocket = new CDataSocket(this);
		m_pDataSocket->Create();// 소켓 생성
		CString addr;
		m_ipaddr.GetWindowText(addr);
		if (m_pDataSocket->Connect(addr, 10000)) {
			MessageBox(_T("서버에 접속 성공!"), _T("알림"), MB_ICONINFORMATION);
			m_edit.SetFocus();
		}
		else {
			MessageBox(_T("서버에 접속 실패!"), _T("알림"), MB_ICONINFORMATION);
			delete m_pDataSocket;
			m_pDataSocket = NULL;
		}
	}
	else {
		MessageBox(_T("서버에 이미 접속됨!"), _T("알림"), MB_ICONERROR);
		m_edit.SetFocus();
	}
}