#pragma once
#include"ItemInfo.h"
#include<QRectF>
#include<QColor>
#include<QString>
namespace GraphicsModule
{
	class SwitchButtonInfo :ItemInfo
	{
	public:
		SwitchButtonInfo();
		QRectF switchButtonSize;
		QColor  buttonColor{ Qt::black };
		QColor	buttonOpenColor{ Qt::darkGray };
		QColor	switchColor{ Qt::white };
		QString	text{ "SwitchButton" };

		bool IsOpen{ false };
		int buttonIndex{ -1 };
	};
}