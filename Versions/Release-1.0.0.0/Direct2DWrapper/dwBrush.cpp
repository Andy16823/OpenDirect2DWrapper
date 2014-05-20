#include "stdafx.h"
#include "dwBrush.h"

namespace Direct2DWrapper
{

	dwBrush::dwBrush(System::Drawing::Color Color)
	{
		this->A = Color.A;
		this->R = Color.R;
		this->G = Color.G;
		this->B = Color.B;
	}

	D2D1::ColorF dwBrush::getColor()
	{
		D2D1::ColorF Col = NULL;
		Col.a = this->A;
		Col.r = this->R;
		Col.g = this->G;
		Col.b = this->B;
		return Col;
	}
}
