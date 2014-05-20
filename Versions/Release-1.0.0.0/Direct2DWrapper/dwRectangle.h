#pragma once
#include <Windows.h>
using namespace System;
namespace Direct2DWrapper
{
	public ref class dwRectangle
	{
	public:
		float X;
		float Y;
		float Width;
		float Height;

		dwRectangle(float X, float Y, float Width, float Height);
		dwRectangle();
		~dwRectangle();
		void Initial();
	};
}
