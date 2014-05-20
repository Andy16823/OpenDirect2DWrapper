
#include "stdafx.h"
#include "Direct2DWrapper.h"
#include <wincodec.h>
#include <wincodec.h>
#include <Windows.h>
#include <dwrite.h>
#include <string>
#include <Vcclr.h>

namespace Direct2DWrapper
{

	Direct2DWrapper::Graphics::~Graphics()
	{
		this->d2dfact->Release();
		this->d2dfact = NULL;
		this->GraphicsTarget->Release();
		this->GraphicsTarget = NULL;
		this->Container = NULL;
		delete this->d2dfact;
		delete this->GraphicsTarget;
		delete this->Container;
	}

	Direct2DWrapper::Graphics::Graphics()
	{

	}

	void Direct2DWrapper::Graphics::CreateRectangle(float X, float Y, float Width, float Height, dwRectangle Source)
	{
		Source.X = X;
		Source.Y = Y;
		Source.Width = Width;
		Source.Height = Height;
	}

	void Direct2DWrapper::Graphics::CreateGraphics(IntPtr hWndl)
	{
		this->Container = (HWND) hWndl.ToPointer();

		// Factory Erstellen
		ID2D1Factory* d2dfact;
		HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2dfact);

		// Factory an Variable Übegeben
		this->d2dfact = d2dfact;

		// Rect des HWNDL
		RECT cr;
		GetClientRect(this->Container, &cr);
		
		// Renderer Erstellen
		ID2D1HwndRenderTarget* rt = NULL;
		HRESULT hr2 = d2dfact->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),D2D1::HwndRenderTargetProperties(this->Container, D2D1::SizeU(cr.right - cr.left,cr.bottom - cr.top)), &rt);

		// Renderer Übergeben an Variable
		this->GraphicsTarget = rt;
	}

	void Direct2DWrapper::Graphics::dwDispose()
	{
		delete this;

	}

	void Direct2DWrapper::Graphics::dwDrawRectangle(dwRectangle^ rect, float width, dwBrush^ Brush)
	{
		// Rect des HWNDL
		RECT cr;
		GetClientRect(this->Container, &cr);

		// Positionen Bestimmen
		float left = cr.left + rect->X;
		float top = cr.top + rect->Y;
		float right = cr.left + rect->X + rect->Width;
		float bottom = cr.top + rect->Y + rect->Height;


		// Brush Erstellen
		ID2D1SolidColorBrush* brush;
		this->GraphicsTarget->CreateSolidColorBrush(D2D1::ColorF(Brush->getColor()), &brush);

		// Render Sagen, das wir mit dem Zeichnen Beginnen
		this->GraphicsTarget->BeginDraw();

		// Zeichnen des Rectangle
		this->GraphicsTarget->DrawRectangle(D2D1::RectF(left, top, right, bottom), brush, width);
		
		// Renderer Sagen, dass das zeichnen Beendet ist
		this->GraphicsTarget->EndDraw();


		// Freigeben
		brush->Release();
	}

	void Direct2DWrapper::Graphics::dwDrawEllipse(dwPoint^ Point, float xRadius, float yRadius, float Width, dwBrush^ Brush)
	{
		// RECT des HWND
		RECT cr;
		GetClientRect(this->Container, &cr);

		// Brush Erstellen
		ID2D1SolidColorBrush *brush;
		this->GraphicsTarget->CreateSolidColorBrush(D2D1::ColorF(Brush->getColor()), &brush);

		// Render Startem
		this->GraphicsTarget->BeginDraw();

		// Zeichnen
		this->GraphicsTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(cr.left + Point->X, cr.top + Point->Y), xRadius, yRadius), brush, Width);

		// Renderer Beenden
		this->GraphicsTarget->EndDraw();

		// Freigeben
		brush->Release();
	}

	void Direct2DWrapper::Graphics::dwDrawBitmap(dwBitmap^ bmp, dwRectangle^ rect)
	{
		
		// Bitmap erstellen
		ID2D1Bitmap* d2bmp = NULL;
		this->GraphicsTarget->CreateBitmapFromWicBitmap(bmp->getBitmap(), NULL, &d2bmp);

		// Client Rechteck
		RECT cr;
		GetClientRect(this->Container, &cr);

		// Breiche Definieren
		float left = cr.left + rect->X;
		float top = cr.top + rect->Y;
		float right = cr.left + rect->X + rect->Width;
		float bottom = cr.top + rect->Y + rect->Height;

		// Zeichnen

		this->GraphicsTarget->BeginDraw();
		this->GraphicsTarget->DrawBitmap(d2bmp, D2D1::RectF(left,top,right,bottom));
		this->GraphicsTarget->EndDraw();

		// Freigeben
		d2bmp->Release();
		d2bmp = NULL;
	}
	
	void Direct2DWrapper::Graphics::dwFillRectangle(dwRectangle^ rect, dwBrush^ Brush)
	{
		// Client Bereich Erstellen
		RECT cr;
		GetClientRect(this->Container, &cr);

		// Berechnen der Position
		float left = cr.left + rect->X;
		float top = cr.top + rect->Y;
		float right = cr.left + rect->X + rect->Width;
		float bottom = cr.top + rect->Y + rect->Height;

		// Brush Erstellen
		ID2D1SolidColorBrush *brush;
		this->GraphicsTarget->CreateSolidColorBrush(D2D1::ColorF(Brush->getColor()), &brush);

		// Zeichnen
		this->GraphicsTarget->BeginDraw();
		this->GraphicsTarget->FillRectangle(D2D1::RectF(left, top, right, bottom), brush);
		this->GraphicsTarget->EndDraw();

		// Freigeben
		brush->Release();
	}

	void Direct2DWrapper::Graphics::dwDrawLine(dwPoint^ PointA, dwPoint^ PointB, float Width, dwBrush^ Brush)
	{
		// Client Bereich
		RECT cr;
		GetClientRect(this->Container, &cr);

		// Brush erstellen
		ID2D1SolidColorBrush* brush = NULL;
		this->GraphicsTarget->CreateSolidColorBrush(D2D1::ColorF(Brush->getColor()), &brush);

		// Zeichnen der Linie
		this->GraphicsTarget->BeginDraw();
		this->GraphicsTarget->DrawLine(D2D1::Point2F(cr.left + PointA->X, cr.top + PointA->Y), D2D1::Point2F(cr.left + PointB->X, cr.top + PointB->Y), brush,Width);
		this->GraphicsTarget->EndDraw();

		// Freigen
		brush->Release();
	}

	void Direct2DWrapper::Graphics::dwFillEllipse(dwPoint^ Point, float xRadius, float yRadius, dwBrush^ Brush)
	{
		// Client Rect
		RECT cr;
		GetClientRect(this->Container, &cr);

		// Brush erstellen
		ID2D1SolidColorBrush* brush = NULL;
		this->GraphicsTarget->CreateSolidColorBrush(D2D1::ColorF(Brush->getColor()), &brush);

		// Zeichnen
		this->GraphicsTarget->BeginDraw();
		this->GraphicsTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(cr.left + Point->X, cr.top + Point->Y), xRadius, yRadius), brush);
		this->GraphicsTarget->EndDraw();

		// Freigeben
		brush->Release();
	}

	void Direct2DWrapper::Graphics::dwDrawString(System::String^ String, int TextLength, dwFont^ Font, dwRectangle^ Rect, dwBrush^ Brush)
	{
		IntPtr StrPtr =  System::Runtime::InteropServices::Marshal::StringToHGlobalUni(String);
		PCWSTR Str = (PCWSTR) StrPtr.ToPointer();
		pin_ptr<const WCHAR> wch = PtrToStringChars(String);
		UINT32 StrLength = (UINT32) TextLength;
		IDWriteFactory* wFactory = NULL;
		IDWriteTextFormat* tFormat = NULL;
		ID2D1SolidColorBrush* brush = NULL;

		// Font Eigenschaften
		WCHAR FontName = Font->FontName;
		float FontSize = Font->Height;

		// Client Rect
		RECT cr;
		GetClientRect(this->Container, &cr);

		float left = cr.left + Rect->X;
		float top = cr.top + Rect->Y;
		float right = cr.left + Rect->X + Rect->Width;
		float bottom = cr.top + Rect->Y + Rect->Height;

		// Write Factory Erstellen
		HRESULT result = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,  __uuidof(wFactory), reinterpret_cast<IUnknown**>(&wFactory));
		if(SUCCEEDED(result))
		{
			result = wFactory->CreateTextFormat(&FontName, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, FontSize, L"", &tFormat);	
		}

		// Solidbrush Erstellen
		if(SUCCEEDED(result))
		{
			tFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
			tFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
			result = this->GraphicsTarget->CreateSolidColorBrush(D2D1::ColorF(Brush->getColor()), &brush);
		}

		// Zeichnen
		if(SUCCEEDED(result))
		{
			this->GraphicsTarget->BeginDraw();
			this->GraphicsTarget->DrawText(wch, StrLength, tFormat, D2D1::RectF(left, top, right, bottom), brush);
			this->GraphicsTarget->EndDraw();
		}

		// Freigeben
		wFactory->Release();
		tFormat->Release();
		brush->Release();

	}
}
