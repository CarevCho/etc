
// OpenGLwithMFCDlg.h : 헤더 파일
//

#pragma once

// including OpenGL header
//#include "freeglut.h"
//#include "freeglut_ext.h"
#include "afxwin.h"
#include <GL\glew.h>
#include <GL\wglew.h>
#include <GL\freeglut.h>

// add to be used library
//#pragma comment(lib, "OpenGL32.lib")

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")

// COpenGLwithMFCDlg 대화 상자
class COpenGLwithMFCDlg : public CDialogEx
{
// 생성입니다.
public:
	COpenGLwithMFCDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENGLWITHMFC_DIALOG };
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
protected:
	// You will add the following stuff!!!

	virtual BOOL GetOldStyleRenderingContext(void);
	virtual BOOL SetupPixelFormat(void);


private:
	//OpenGL Setup
	BOOL GetRenderingContext();
	//Rendering Context and Device Context Pointers
	HGLRC     m_hRC;
	CDC*      m_pDC;

	float m_alpha;
	float m_beta;
	float m_gamma;
	//GLuint vao;
	//void defineVAO(GLuint &vao, GLuint &shaderProgram);
	//GLuint create_program();

public:
	// control variable about IDC_PICTURE, to draw OpenGL
	CStatic m_picture;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
