
// ex_mfc_diag_opencv_webcamDlg.h : 헤더 파일
//

#pragma once
#include "opencv_3_4_1.h"
#define WEB_CAM 1000
// Cex_mfc_diag_opencv_webcamDlg 대화 상자
class Cex_mfc_diag_opencv_webcamDlg : public CDialogEx
{
// 생성입니다.
public:
	Cex_mfc_diag_opencv_webcamDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EX_MFC_DIAG_OPENCV_WEBCAM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
