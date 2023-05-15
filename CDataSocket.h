#pragma once

// CDataSocket 명령 대상
class Cmfctest45tcpclient1Dlg;

class CDataSocket : public CSocket
{
public:
	CDataSocket(Cmfctest45tcpclient1Dlg* pDlg);
	virtual ~CDataSocket();

	Cmfctest45tcpclient1Dlg* m_pDlg;
};