#include <Windows.h>
#include <tchar.h>
#include <cmath>
#define ID_TIMER1 1


LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

void Sun(HDC,int,int);
void Stars(HDC,int,int);

TCHAR WinName[] = _T("MainFrame");
bool fl1=0;
bool fl2=0;
bool fl3=0;
int  cnt=0;

int WINAPI _tWinMain(HINSTANCE This,		 // Дескриптор текущего приложения 
HINSTANCE Prev, 	// В современных системах всегда 0 
LPTSTR cmd, 		// Командная строка
int mode) 		// Режим отображения окна
{ 
HWND hWnd;		// Дескриптор главного окна программы 
MSG msg; 		// Структура для хранения сообщения 
WNDCLASS wc; 	// Класс окна
// Определение класса окна 
wc.hInstance = This; 
wc.lpszClassName = WinName; 				// Имя класса окна 
wc.lpfnWndProc = WndProc; 					// Функция окна  
wc.style = CS_HREDRAW | CS_VREDRAW; 			// Стиль окна
wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// Стандартная иконка  
wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// Стандартный курсор  
wc.lpszMenuName = NULL; 					// Нет меню  
wc.cbClsExtra = 0; 						// Нет дополнительных данных класса  
wc.cbWndExtra = 0; 						// Нет дополнительных данных окна  
wc.hbrBackground = (HBRUSH) (COLOR_GRAYTEXT+12); 	// Заполнение окна белым цветом  
 
 
// Регистрация класса окна 
if (!RegisterClass(&wc)) return 0; 	 
 
// Создание окна   
hWnd = CreateWindow(WinName,			// Имя класса окна  
_T("Лабораторная 1"), 		// Заголовок окна 
WS_OVERLAPPEDWINDOW, 		// Стиль окна 
200,				// x  
200, 				// y	 Размеры окна  
CW_USEDEFAULT, 				// width  
CW_USEDEFAULT, 				// Height  
HWND_DESKTOP, 				// Дескриптор родительского окна  
NULL, 						// Нет меню  
This, 						// Дескриптор приложения  
NULL); 					// Дополнительной информации нет  
 
ShowWindow(hWnd, mode); 				// Показать окно 

// Цикл обработки сообщений  
while(GetMessage(&msg, NULL, 0, 0))  
{ 
TranslateMessage(&msg); 		// Функция трансляции кодов нажатой клавиши 
DispatchMessage(&msg); 		// Посылает сообщение функции WndProc() 
} 
return 0;
}

void Sun(HDC hDC,int mid,int Cent)
{
HPEN RedPen=CreatePen (PS_SOLID, 7, RGB(255, 0, 0));
SelectObject(hDC,RedPen);
HBRUSH RedBrush=CreateSolidBrush(RGB(255,0,0));
SelectObject(hDC,RedBrush);

int R=100;
Chord(hDC,mid-R,Cent-R,mid+R,Cent+R,mid+R,Cent,mid-R,Cent);
ExtFloodFill(hDC,mid,Cent-(R/2),RGB(255,0,0),FLOODFILLSURFACE);

double ExX, ExY, CX, CY;
ExX=mid-2*R;ExY=Cent;
MoveToEx(hDC,ExX,ExY,NULL);
LineTo(hDC,mid,Cent);
for (int count=0;count<10;count++)
   {
   CX = mid+(ExX-mid)*cos(3.14/10)-(ExY-Cent)*sin(3.14/10);
   CY = Cent+(ExY-Cent)*cos(3.14/10)+(ExX-mid)*sin(3.14/10);
   MoveToEx(hDC,CX,CY,NULL);
   LineTo(hDC,mid,Cent);
   ExX=CX;ExY=CY;
   }
DeleteObject(RedPen);
DeleteObject(RedBrush);
}

void Stars(HDC hDC,int right,int bottom)
{
if ((fl1==1)&&(fl2==1))
	{
	HPEN BlackPen=CreatePen (PS_SOLID, 7, RGB(0,0,0));
	SelectObject(hDC,BlackPen);
	HBRUSH BlackBrush=CreateSolidBrush(RGB(0,0,0));
	SelectObject(hDC,BlackBrush);
	Rectangle(hDC,0,0,right,bottom);
	ExtFloodFill(hDC,50,50,RGB(0,0,0),FLOODFILLSURFACE);
	DeleteObject(BlackPen);
	DeleteObject(BlackBrush);
	fl2=1;
	}
if ((fl1==1)&&(fl2==1)&&(fl3==1))
	{
	HPEN WhitePen=CreatePen (PS_SOLID,3,RGB(255,255,255));
	SelectObject(hDC,WhitePen);
	int i=50;
	int j=50;
	while (i<bottom)
	{
		while (j<right)
		{
		MoveToEx(hDC,j,i,NULL);
		LineTo(hDC,j+1,i+1);
		j=j+80;
		}
	j=j-right;
	i=i+50;
	}
	DeleteObject(WhitePen);
	fl3=1;
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{ 
RECT pryam;
GetClientRect(hWnd,&pryam);
int middle=(pryam.right-pryam.left)/2;
int YCentr=pryam.bottom;

switch(message)		 // Обработчик сообщений
{

case WM_PAINT:
{
PAINTSTRUCT ps;
HDC hDC = BeginPaint(hWnd, &ps);

if (fl1==0)
	{
		FillRect(hDC, &pryam, CreateSolidBrush(RGB(0,0,255)));
        Sun(hDC,middle,YCentr+cnt);
	}
if (fl1==1)
	Stars(hDC,pryam.right,pryam.bottom);

EndPaint(hWnd, &ps);
}
break;

case WM_LBUTTONDOWN:
{
if (fl1==0)
	SetTimer(hWnd,ID_TIMER1,50,NULL);
InvalidateRect(hWnd, &pryam, FALSE);
break;
}

case WM_RBUTTONDOWN:
if (fl1==1)
	{
	if (fl2==1)
		fl3=1;
	if (fl2==0)
		fl2=1;
	}
InvalidateRect(hWnd, &pryam, FALSE);
break;

case WM_TIMER:
{
cnt=cnt+5;
Sleep(65);
InvalidateRect(hWnd, &pryam, FALSE);
if ((YCentr+cnt)>(pryam.bottom+210))
	{   
	KillTimer(hWnd,ID_TIMER1);
    fl1=1;
    }
break;
}

case WM_DESTROY: 
{
PostQuitMessage(0); 
break;
}					// Завершение программы 

default: 			// Обработка сообщения по умолчанию 
return DefWindowProc(hWnd, message, wParam, lParam); 
}
return 0;
}
