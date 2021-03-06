
// OpenGLwithMFCDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "OpenGLwithMFC.h"
#include "OpenGLwithMFCDlg.h"
#include "afxdialogex.h"

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


// COpenGLwithMFCDlg 대화 상자



COpenGLwithMFCDlg::COpenGLwithMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OPENGLWITHMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpenGLwithMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE, m_picture);
}

BEGIN_MESSAGE_MAP(COpenGLwithMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// COpenGLwithMFCDlg 메시지 처리기

BOOL COpenGLwithMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	//OpenGL context 생성
	if (!GetRenderingContext())
	{
		AfxMessageBox(CString("OpenGL 초기화중 에러가 발생하여 프로그램을 실행할 수 없습니다."));
		return -1;
	}
	
	/*
	// OpenGL 3.x
	GLuint shaderProgram;
	defineVAO(vao, shaderProgram);

	glUseProgram(shaderProgram);
	glBindVertexArray(vao);
	*/

	//angle = 0;
	m_alpha = m_beta = m_gamma = 0;
	SetTimer(1000, 30, NULL);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void COpenGLwithMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void COpenGLwithMFCDlg::OnPaint()
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
HCURSOR COpenGLwithMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void COpenGLwithMFCDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	//z축을 중심으로 설정된 angle로 회전한다.
	glRotatef(m_alpha, 0.0f, 0.0f, 1.0f);
	glRotatef(m_beta, 0.f, 1.f, 0.f);
	glRotatef(m_gamma, 1.f, 0.f, 0.f);

	/*
	//중앙이 원점에 오도록 삼각형을 그린다. 
	glBegin(GL_TRIANGLES); //3점이 하나의 삼각형을 구성한다. 반시계 방향으로 3점의 vertex를 지정해줘야 한다.
	glColor3f(1.0f, 0.0f, 0.0f); //빨간색 지정
	glVertex3f(-0.5f, -0.5f, 0.0f);    // 왼쪽 아래 vertex
	glColor3f(0.0f, 1.0f, 0.0f); //녹색 지정
	glVertex3f(0.5f, -0.5f, 0.0f);    // 오른쪽 아래 vertex
	glColor3f(0.0f, 0.0f, 1.0f); //파란색 지정
	glVertex3f(0.0f, 0.5f, 0.0f);    // 위쪽 vertex
	glEnd();
	*/

	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(-0.5,0,  0);
	glVertex3f(0.5,0,  0);
	glColor3f(0, 1, 0);
	glVertex3f(0, -0.5, 0);
	glVertex3f(0, 0.5, 0);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, -0.5);
	glVertex3f(0, 0, 0.5);
	glEnd();

	
	
	//삼각형 회전각 증가
	//m_alpha += 0.5f;

	//화면 업데이트
	SwapBuffers(m_pDC->GetSafeHdc());

	CDialogEx::OnTimer(nIDEvent);
	

	/*
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	glDrawArrays(GL_TRIANGLES, 0, 3);

	//화면 업데이트
	SwapBuffers(m_pDC->GetSafeHdc());

	CDialogEx::OnTimer(nIDEvent);
	*/
}


void COpenGLwithMFCDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//glDeleteVertexArrays(1, &vao);

	if (FALSE == ::wglDeleteContext(m_hRC))
	{
		AfxMessageBox(CString("wglDeleteContext failed"));
	}

}
BOOL COpenGLwithMFCDlg::GetRenderingContext()
{
	//픽처 컨트롤에만 그리도록 DC 생성
	//참고 https://goo.gl/CK36zE
	CWnd* pImage = GetDlgItem(IDC_PICTURE);
	CRect rc;
	pImage->GetWindowRect(rc);
	m_pDC = pImage->GetDC();


	if (NULL == m_pDC)
	{
		AfxMessageBox(CString("Unable to get a DC"));
		return FALSE;
	}


	if (!GetOldStyleRenderingContext())
	{
		return TRUE;
	}
	
	/*
	//Get access to modern OpenGL functionality from this old style context.
	glewExperimental = GL_TRUE;
	*/
	if (GLEW_OK != glewInit())
	{
		AfxMessageBox(CString("GLEW could not be initialized!"));
		return FALSE;
	}
	/*
	//Get a new style pixel format
	if (!SetupPixelFormat())
	{
		return FALSE;
	}
	*/


	//참고 http://gamedev.stackexchange.com/a/30443
	GLint attribs[] =
	{
		// Here we ask for OpenGL 2.1
		WGL_CONTEXT_MAJOR_VERSION_ARB, 2,
		WGL_CONTEXT_MINOR_VERSION_ARB, 1,
		/*
		// Here we ask for OpenGL 3.3
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 3,
		*/
		// Uncomment this for forward compatibility mode
		//WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		// Uncomment this for Compatibility profile
		//WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
		// We are using Core profile here
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};


	HGLRC CompHRC = wglCreateContextAttribsARB(m_pDC->GetSafeHdc(), 0, attribs);
	if (CompHRC && wglMakeCurrent(m_pDC->GetSafeHdc(), CompHRC))
		m_hRC = CompHRC;

	return TRUE;
}

BOOL COpenGLwithMFCDlg::GetOldStyleRenderingContext()
{
	//A generic pixel format descriptor. This will be replaced with a more
	//specific and modern one later, so don't worry about it too much.
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |            // support window
		PFD_SUPPORT_OPENGL |            // support OpenGL
		PFD_DOUBLEBUFFER,               // double buffered
		PFD_TYPE_RGBA,                  // RGBA type
		32,                             // 32-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		24,                        // 24-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};

	// Get the id number for the best match supported by the hardware device context
	// to what is described in pfd
	int pixelFormat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);

	//If there's no match, report an error
	if (0 == pixelFormat)
	{
		AfxMessageBox(CString("ChoosePixelFormat failed"));
		return FALSE;
	}

	//If there is an acceptable match, set it as the current 
	if (FALSE == SetPixelFormat(m_pDC->GetSafeHdc(), pixelFormat, &pfd))
	{
		AfxMessageBox(CString("SetPixelFormat failed"));
		return FALSE;
	}

	//Create a context with this pixel format
	if (0 == (m_hRC = wglCreateContext(m_pDC->GetSafeHdc())))
	{
		AfxMessageBox(CString("wglCreateContext failed"));
		return FALSE;
	}

	//Make it current. 
	if (FALSE == wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC))
	{
		AfxMessageBox(CString("wglMakeCurrent failed"));
		return FALSE;
	}
	return TRUE;
}

/*
void COpenGLwithMFCDlg::defineVAO(GLuint &vao, GLuint &shaderProgram)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	float position[] = {
		0.0f,  0.5f, 0.0f, //vertex 1
		0.5f, -0.5f, 0.0f, //vertex 2
		-0.5f, -0.5f, 0.0f //vertex 3
	};

	float color[] = {
		1.0f, 0.0f, 0.0f, //vertex 1 : RED (1,0,0)
		0.0f, 1.0f, 0.0f, //vertex 2 : GREEN (0,1,0) 
		0.0f, 0.0f, 1.0f  //vertex 3 : BLUE (0,0,1)
	};



	GLuint position_vbo, color_vbo;

	glGenBuffers(1, &position_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);

	glGenBuffers(1, &color_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);


	shaderProgram = create_program();

	GLint position_attribute = glGetAttribLocation(shaderProgram, "position");
	glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
	glVertexAttribPointer(position_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(position_attribute);

	GLint color_attribute = glGetAttribLocation(shaderProgram, "color");
	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	glVertexAttribPointer(color_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(color_attribute);

	glBindVertexArray(0);
}



GLuint COpenGLwithMFCDlg::create_program() {

	const GLchar* vertexShaderSource =
		"#version 330 core\n"
		"in vec3 position;"
		"in vec3 color;"
		"out vec3 color_from_vshader;"
		"void main()"
		"{"
		"gl_Position = vec4(position, 1.0);"
		"color_from_vshader = color;"
		"}";

	const GLchar* fragmentShaderSource =
		"#version 330 core\n"
		"in vec3 color_from_vshader;"
		"out vec4 out_color;"
		"void main()"
		"{"
		"out_color = vec4(color_from_vshader, 1.0);"
		"}";


	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLint success;
	GLchar infoLog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		TRACE(CString("ERROR: vertex shader 컴파일 실패 ") + CString(infoLog) + CString("\n"));
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		TRACE(CString("ERROR: fragment shader 컴파일 실패 ") + CString(infoLog) + CString("\n"));
	}


	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glLinkProgram(shaderProgram);


	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);

		TRACE(CString("ERROR: shader program 연결 실패 ") + CString(infoLog) + CString("\n"));
	}

	return shaderProgram;
}*/


BOOL COpenGLwithMFCDlg::SetupPixelFormat()
{
	//This is a modern pixel format attribute list.
	//It has an extensible structure. Just add in more argument pairs 
	//befroe the null to request more features.
	const int attribList[] =
	{
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
		WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
		WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB,     32,
		WGL_DEPTH_BITS_ARB,     24,
		WGL_STENCIL_BITS_ARB,   8,
		0, 0  //End
	};


	unsigned int numFormats;
	int pixelFormat;
	PIXELFORMATDESCRIPTOR pfd;

	//Select a pixel format number
	wglChoosePixelFormatARB(m_pDC->GetSafeHdc(), attribList, NULL, 1, &pixelFormat, &numFormats);

	//Optional: Get the pixel format's description. We must provide a 
	//description to SetPixelFormat(), but its contents mean little.
	//According to MSDN: 
	//  The system's metafile component uses this structure to record the logical
	//  pixel format specification. The structure has no other effect upon the
	//  behavior of the SetPixelFormat function.
	//DescribePixelFormat(m_pDC->GetSafeHdc(), pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	//Set it as the current 
	if (FALSE == SetPixelFormat(m_pDC->GetSafeHdc(), pixelFormat, &pfd))
	{
		AfxMessageBox(CString("SelectPixelFormat failed"));
		return FALSE;
	}

	return TRUE;
}


BOOL COpenGLwithMFCDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam)
		{
		case 65:
			m_alpha += 0.5;
			break;
		case 66:
			m_beta += 0.5;
			break;
		case 67:
			m_gamma += 0.5;
			break;
		default:
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
