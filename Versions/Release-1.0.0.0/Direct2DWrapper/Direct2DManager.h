#pragma once
#include "Direct2DWrapper.h"

namespace Direct2DWrapper
{
	public ref class Direct2DManager
	{


	public:
		Direct2DManager(void);
		Graphics^ ManagedGraphics;
		void setGraphics(Graphics^ g);
		void ReleaseGraphics();
	};
}
