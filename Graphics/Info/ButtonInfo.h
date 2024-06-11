#pragma once
#include"ItemInfo.h"
#include<QRectF>
#include<QColor>
#include<QString>
namespace GraphicsModule
{

	class ButtonInfo :ItemInfo
	{
	public:
		ButtonInfo();
		QRectF buttonSize;
		QString	buttonText{ "button" };
		QColor	buttonTextColor{ Qt::white };
		QColor	buttonTextPressColor{ Qt::gray };
		QColor  buttonColor{ Qt::black };
		QColor	buttonPressColor{ Qt::darkGray };
		bool Clicked{ false };
		int buttonIndex{ -1 };
	};
}