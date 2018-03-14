
// ex_mfc_diag_opencv_webcamDlg.h : ��� ����
//

#pragma once
#include "opencv_3_4_1.h"
#define WEB_CAM 1000
// Cex_mfc_diag_opencv_webcamDlg ��ȭ ����
class Cex_mfc_diag_opencv_webcamDlg : public CDialogEx
{
// �����Դϴ�.
public:
	Cex_mfc_diag_opencv_webcamDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EX_MFC_DIAG_OPENCV_WEBCAM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	cv::VideoCapture m_vid;
	cv::Mat m_frame;
	int fps;
	int m_num_frame;
};
