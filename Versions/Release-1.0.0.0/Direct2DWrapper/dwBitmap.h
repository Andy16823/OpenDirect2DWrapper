#pragma once
#include <d2d1.h>
#include <wincodec.h>
#include <wincodec.h>
#include <Windows.h>

namespace Direct2DWrapper
{
	public ref class dwBitmap
	{
	private:
		IWICFormatConverter* bmpsource;
		
	public:
		dwBitmap(void);
		~dwBitmap(void);
		dwBitmap(System::String^ Path);
		IWICFormatConverter* getBitmap();
		
	};
}
