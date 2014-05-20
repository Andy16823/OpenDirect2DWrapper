#define _WIN32_WINNT 0x0601
#include "stdafx.h"
#include "dwBitmap.h"


namespace Direct2DWrapper
{

	dwBitmap::~dwBitmap(void)
	{
		this->bmpsource->Release();
	}

	dwBitmap::dwBitmap(void)
	{
	}

	dwBitmap::dwBitmap(System::String^ path)
	{
		
		System::IntPtr strptr = System::Runtime::InteropServices::Marshal::StringToHGlobalUni(path);
		LPCWSTR Path2 = (LPCWSTR) strptr.ToPointer();
		IWICImagingFactory* Factory;
		IWICBitmapDecoder* decoder = NULL;
		IWICBitmapFrameDecode* source = NULL;

		IWICStream* stream = NULL;
		IWICFormatConverter* converter = NULL;

		// Image Factory erstellen
		HRESULT result = CoCreateInstance( CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,	 IID_IWICImagingFactory, (LPVOID*)&Factory);


		if(SUCCEEDED(result))
		{
			// Image Decoder
			result = Factory->CreateDecoderFromFilename(Path2, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder);
		}

		// Get Frame
		if(SUCCEEDED(result))
		{
			result = decoder->GetFrame(0, &source);
		}

		// Format Converter
		if(SUCCEEDED(result))
		{
			result = Factory->CreateFormatConverter(&converter);
		}

		// Konvert
		if(SUCCEEDED(result))
		{
			result = converter->Initialize(source, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut);
		}

		this->bmpsource = converter;
	}

	IWICFormatConverter* dwBitmap::getBitmap()
	{
		return this->bmpsource;
	}


}
