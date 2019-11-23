#include <Windows.h>
#include <gl/GL.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment(lib, "winmm.lib")

#define WINDOW_TITLE "Practical 3"

float xValue = 0;
float yValue = 0;

int questionNo = 1;
float speed = 0.11;
float degree = 0.0;
int rotateDirection = 0;
boolean music = false;

void soundOn() {
	PlaySound(TEXT("fan2.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
}

void soundOff() {
	PlaySound(NULL, NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
}

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		else if (wParam == 0x31)
			questionNo = 1;
		else if (wParam == 0x32)
			questionNo = 2;
		else if (wParam == 0x25 || wParam == 0x27)
			xValue = xValue + 0.005;
		else if (wParam == VK_UP || wParam == VK_DOWN)
			yValue = yValue + 0.005;
		else if (wParam == 0x20) {
			xValue = 0;
			yValue = 0;
		}
		else if (wParam == 0x41)
			rotateDirection = 0;
		else if (wParam == 0x44)
			rotateDirection = 1;
		else if (wParam == 'C')
			soundOff();
		else if (wParam == 'O')
			soundOn();

		break;


	case WM_MOUSEWHEEL:
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
			//mouse wheel scrolled up
			speed += 0.1;
		else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0 && speed > 0.1)
			//mouse wheel scrolled down
			speed -= 0.1;
		break;

	case WM_LBUTTONUP:
		speed = 0;
		PlaySound(NULL, NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
		break;

	case WM_RBUTTONUP:
		speed = 0.11;
		PlaySound(TEXT("C:\\Users\\TARUC\\Documents\\Visual Studio 2017\\Projects\\Practical 4\\fan2.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);


	glLoadIdentity();
	glScalef(0.5, 0.5, 1.0);
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glPushMatrix();

	glTranslatef(0.5, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.5, 0.0);
	glVertex2f(0.0, 0.5);
	glVertex2f(0.5, 0.0);
	glEnd();
	//glPopMatrix();


	glTranslatef(0.0, 0.5, 0.0);
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex2f(-0.5, 0.0);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, 0.0);
	glEnd();
	glPopMatrix();
	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}

void display1(float x, float y)
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef((0.0 - x), (0.0 - y), 0.0);
	//Left Quads
	glBegin(GL_QUADS);
	glVertex2f(-0.3, 0.1);
	glVertex2f(0.0, 0.1);
	glVertex2f(0.0, -0.1);
	glVertex2f(-0.3, -0.1);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef((0.0 + x), (0.0 + y), 0.0);
	//Right Quads
	glBegin(GL_QUADS);
	glVertex2f(0.0, 0.1);
	glVertex2f(0.3, 0.1);
	glVertex2f(0.3, -0.1);
	glVertex2f(0.0, -0.1);
	glEnd();
	glPopMatrix();

	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}

//--------------------------------------------------------------------


void rotor() {

	//First Rotor
	glBegin(GL_QUADS);
	glColor3f(0.55, 0.27, 0.07);
	glVertex2f(0.05f, 0.31f);
	glVertex2f(0.55f, 0.31f);
	glVertex2f(0.55f, 0.29f);
	glVertex2f(0.05f, 0.29f);
	glEnd();

	//Second Rotor
	glBegin(GL_QUADS);
	glColor3f(0.55, 0.27, 0.07);
	glVertex2f(-0.01f, 0.85f);
	glVertex2f(0.01f, 0.85f);
	glVertex2f(0.01f, 0.35f);
	glVertex2f(-0.01f, 0.35f);
	glEnd();

	//Third Rotor
	glBegin(GL_QUADS);
	glColor3f(0.55, 0.27, 0.07);
	glVertex2f(-0.55f, 0.31f);
	glVertex2f(-0.05f, 0.31f);
	glVertex2f(-0.05f, 0.29f);
	glVertex2f(-0.55f, 0.29f);
	glEnd();

	//Fourth Rotor
	glBegin(GL_QUADS);
	glColor3f(0.55, 0.27, 0.07);
	glVertex2f(-0.01f, -0.25f);
	glVertex2f(0.01f, -0.25f);
	glVertex2f(0.01f, 0.35f);
	glVertex2f(-0.01f, 0.35f);
	glEnd();
}

void wings() {
	//First Flag
	glBegin(GL_POLYGON);
	glColor3f(0.82, 0.71, 0.55);
	glVertex2f(0.1, 0.29);
	glVertex2f(0.2, 0.15);
	glVertex2f(0.55, 0.15);
	glVertex2f(0.55, 0.29);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.55, 0.27, 0.07);
	glVertex2f(0.15, 0.23);
	glVertex2f(0.55, 0.23);
	glVertex2f(0.55, 0.29);
	glVertex2f(0.5, 0.29);
	glVertex2f(0.5, 0.15);
	glVertex2f(0.4, 0.15);
	glVertex2f(0.4, 0.29);
	glVertex2f(0.3, 0.29);
	glVertex2f(0.3, 0.15);
	glEnd();

	//Second Flag
	glBegin(GL_POLYGON);
	glColor3f(0.82, 0.71, 0.55);
	glVertex2f(0.01f, 0.4f);
	glVertex2f(0.15f, 0.5f);
	glVertex2f(0.15f, 0.85f);
	glVertex2f(0.01f, 0.85f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.55, 0.27, 0.07);
	glVertex2f(0.08, 0.45);
	glVertex2f(0.08, 0.85);
	glVertex2f(0.15, 0.85);
	glVertex2f(0.15, 0.8);
	glVertex2f(0.01, 0.8);
	glVertex2f(0.01, 0.7);
	glVertex2f(0.15, 0.7);
	glVertex2f(0.15, 0.6);
	glVertex2f(0.01, 0.6);
	glEnd();

	//Third Flag
	glBegin(GL_POLYGON);
	glColor3f(0.82, 0.71, 0.55);
	glVertex2f(-0.1, 0.31);
	glVertex2f(-0.2, 0.45);
	glVertex2f(-0.55, 0.45);
	glVertex2f(-0.55, 0.31);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.55, 0.27, 0.07);
	glVertex2f(-0.15, 0.38);
	glVertex2f(-0.55, 0.38);
	glVertex2f(-0.55, 0.45);
	glVertex2f(-0.5, 0.45);
	glVertex2f(-0.5, 0.31);
	glVertex2f(-0.4, 0.31);
	glVertex2f(-0.4, 0.45);
	glVertex2f(-0.3, 0.45);
	glVertex2f(-0.3, 0.31);
	glEnd();

	//Fourth Wings
	glBegin(GL_POLYGON);
	glColor3f(0.82, 0.71, 0.55);
	glVertex2f(-0.01f, 0.2f);
	glVertex2f(-0.15f, 0.1f);
	glVertex2f(-0.15f, -0.25f);
	glVertex2f(-0.01f, -0.25f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.55, 0.27, 0.07);
	glVertex2f(-0.08, 0.15);
	glVertex2f(-0.08, -0.25);
	glVertex2f(-0.15, -0.25);
	glVertex2f(-0.15, -0.2);
	glVertex2f(-0.01, -0.2);
	glVertex2f(-0.01, -0.1);
	glVertex2f(-0.15, -0.1);
	glVertex2f(-0.15, 0.0);
	glVertex2f(-0.01, 0.0);
	glEnd();
}

void building() {

	//Top Part
	glBegin(GL_TRIANGLES);
	glColor3f(0.25, 0.16, 0.08);
	glVertex2f(0.0, 0.15);
	glVertex2f(-0.2, -0.1);
	glVertex2f(0.2, -0.1);
	glEnd();

	//Second Part
	glLineWidth(4.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.25, 0.16, 0.08);
	glVertex2f(-0.2, -0.1);
	glVertex2f(0.2, -0.1);
	glVertex2f(0.2, -0.4);
	glVertex2f(-0.2, -0.4);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.5, 0.51, 0.499);
	glVertex2f(-0.2, -0.1);
	glVertex2f(0.2, -0.1);
	glVertex2f(0.2, -0.4);
	glVertex2f(-0.2, -0.4);
	glEnd();

	//Second Top Windows
	glBegin(GL_QUADS);
	glColor3f(0.25, 0.16, 0.08);
	glVertex2f(-0.09, -0.16);
	glVertex2f(0.09, -0.16);
	glVertex2f(0.09, -0.35);
	glVertex2f(-0.09, -0.35);
	glEnd();

	glLineWidth(2.0);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.0, -0.16);
	glVertex2f(0.0, -0.35);
	glEnd();

	//Third Part
	glLineWidth(4.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.25, 0.16, 0.08);
	glVertex2f(-0.2, -0.4);
	glVertex2f(0.2, -0.4);
	glVertex2f(0.2, -0.7);
	glVertex2f(-0.2, -0.7);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.5, 0.51, 0.499);
	glVertex2f(-0.2, -0.4);
	glVertex2f(0.2, -0.4);
	glVertex2f(0.2, -0.7);
	glVertex2f(-0.2, -0.7);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.25, 0.16, 0.08);
	glVertex2f(-0.2, -0.6);
	glVertex2f(-0.1, -0.7);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.25, 0.16, 0.08);
	glVertex2f(0.2, -0.6);
	glVertex2f(0.1, -0.7);
	glEnd();

	//Third Part Windows
	glBegin(GL_QUADS);
	glColor3f(0.25, 0.16, 0.08);
	glVertex2f(-0.09, -0.45);
	glVertex2f(0.09, -0.45);
	glVertex2f(0.09, -0.6);
	glVertex2f(-0.09, -0.6);
	glEnd();

	glLineWidth(2.0);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.0, -0.45);
	glVertex2f(0.0, -0.6);
	glEnd();

	//Bottom Part
	glBegin(GL_QUADS);
	glColor3f(0.5, 0.51, 0.499);
	glVertex2f(-0.2, -0.7);
	glVertex2f(0.2, -0.7);
	glVertex2f(0.2, -1.0);
	glVertex2f(-0.2, -1.0);
	glEnd();

	glLineWidth(2.5);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.25, 0.16, 0.08);
	glVertex2f(-0.2, -0.7);
	glVertex2f(0.2, -0.7);
	glVertex2f(0.2, -1.0);
	glVertex2f(-0.2, -1.0);
	glEnd();

	//Door
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.25, 0.16, 0.08);
	glVertex2f(-0.1, -0.8);
	glVertex2f(0.1, -0.8);
	glVertex2f(0.1, -1.0);
	glVertex2f(-0.1, -1.0);
	glEnd();

	//Door Handle
	const float radius = 0.01;
	const float DEG2RAD = 3.14159 / 180;
	glBegin(GL_POLYGON);
	glColor3f(0.00, 0.00, 0.00);
	for (int i = 0; i <= 360; i++)
	{
		float degInRad = i * DEG2RAD;
		glVertex2f((cos(degInRad)*radius) - 0.07, (sin(degInRad)*radius) - 0.9);

	}
	glEnd();


}

void background() {
	//Sky
	glBegin(GL_QUADS);
	glColor3f(0.09, 0.93, 0.93);
	glVertex2f(-1, 1.0);
	glVertex2f(1, 1.0);
	glVertex2f(1, -0.75);
	glVertex2f(-1, -0.75);
	glEnd();

	//Ground
	glBegin(GL_QUADS);
	glColor3f(0.55, 0.55, 0.48);
	glVertex2f(-1, -0.75);
	glVertex2f(1, -0.75);
	glVertex2f(1, -1.3);
	glVertex2f(-1, -1.3);
	glEnd();


}

void RotorAndPivot() {


	//Set Rotor
	rotor();

	//Set Wings
	wings();

	//Pivot
	const float radius = 0.05;
	const float DEG2RAD = 3.14159 / 180;
	glBegin(GL_POLYGON);
	glColor3f(0.55, 0.27, 0.07);
	for (int i = 0; i <= 360; i++)
	{
		float degInRad = i * DEG2RAD;
		glVertex2f(cos(degInRad)*radius, 0.3 + sin(degInRad)*radius);

	}
	glEnd();
}



void windmill(float degree)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	background();
	building();

	glRotatef(degree, 0.0, 0.0, 1.0);

	glPushMatrix();
	glTranslatef(0.0, -0.3, 0.0);
	RotorAndPivot();
	glPopMatrix();

	glLoadIdentity();
	glTranslatef(0.0, 0.3, 1.0);

}


//--------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);



	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}


		if (questionNo == 1) {
			display1(xValue, yValue);
		}
		else if (questionNo == 2) {
			if (rotateDirection == 0) {
				windmill(degree);
			}
			else {
				windmill(-(degree));
			}

			degree += speed;
		}


		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------
