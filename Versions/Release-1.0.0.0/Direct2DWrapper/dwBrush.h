#pragma once
#include <d2d1.h>

namespace Direct2DWrapper
{
	public ref class dwBrush
	{

	public:	
		dwBrush(System::Drawing::Color color);
		D2D1::ColorF getColor();
		float A;
		float R;
		float G;
		float B;
	};

}
