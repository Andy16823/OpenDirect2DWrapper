// Direct2DWrapper.h
#pragma once
#define _WIN32_WINNT 0x0601
#include <d2d1.h>
#include "dwBrush.h"
#include "dwRectangle.h"
#include "dwBitmap.h"
#include "dwPoint.h"
#include "dwFont.h"

using namespace System;

namespace Direct2DWrapper {

	public ref class Graphics
	{
	
	private: 
		ID2D1Factory* d2dfact;
		HWND Container;
		ID2D1HwndRenderTarget* GraphicsTarget;


	public:
		Graphics();
		~Graphics();
		void CreateGraphics(IntPtr hWndl);
		void dwDispose();
		void CreateRectangle(float X, float Y, float Width, float Height, dwRectangle Source);
		void dwDrawRectangle(dwRectangle^ rect, float width, dwBrush^ Brush);
		void dwDrawEllipse(dwPoint^ Point, float xRadius, float yRadius, float Width, dwBrush^ Brush);
		void dwDrawBitmap(dwBitmap^ bmp, dwRectangle^ rect);
		void dwDrawLine(dwPoint^ PointA, dwPoint^ PointB, float Width, dwBrush^ Brush);
		void dwFillRectangle(dwRectangle^ rect, dwBrush^ Brush);
		void dwFillEllipse(dwPoint^ Point, float xRadius, float yRadius, dwBrush^ Brush);
		void dwDrawString(System::String^ String, int TextLength, dwFont^ Font, dwRectangle^ Rect, dwBrush^ Brush);

	};
}
