#include "stdafx.h"
#include "Direct2DManager.h"
#include "Direct2DWrapper.h"

namespace Direct2DWrapper
{
	
	Direct2DManager::Direct2DManager(void)
	{
	}

	void Direct2DManager::setGraphics(Graphics^ g)
	{
		this->ManagedGraphics = g;
	}

	void Direct2DManager::ReleaseGraphics()
	{
		delete this->ManagedGraphics;
	}

}
