#pragma once
#include <Windows.h>
namespace Direct2DWrapper
{
	public ref class dwFont
	{
	private:
		

	public:
		dwFont(System::String^ FontName, float FontWidth, float Size);
		WCHAR getFontName();
		float getWidth();
		float getHeight();
		WCHAR FontName;
		float Width;
		float Height;
		

	};
}
