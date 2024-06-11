#pragma once

#include <QMutex>
#include <QObject>
#include<QMutexLocker>
#include<QColor>
#include"ItemInfo.h"
namespace GraphicsModule {
	class LabelInfo :public ItemInfo
	{
	public:
		LabelInfo();
		QColor  BackgroundColor{ Qt::black };
		QColor  TextColor{ Qt::white };
		int index{ -1 };
		QString Text{ "label" };
		bool isbold{ false };
		unsigned textSize{ 12 };
		unsigned radius{ 5 };
	};
}