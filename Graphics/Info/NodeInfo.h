#ifndef NODEINFO_H
#define NODEINFO_H

#include<QSize>
#include <QObject>
#include<QString>
#include<QColor>
#include<QQueue>
#include"ItemInfo.h"
namespace GraphicsModule
{


	class NodeInfo :public ItemInfo
	{

	public:
		NodeInfo();


		//背景颜色
		QColor backgroundColor1{ QColor(0,0,0,255) };
		QColor backgroundColor2{ QColor(0,0,0,255) };
		//标题栏颜色
		QColor titleBackgroundColor1{ QColor(0,0,0,255) };
		QColor titleBackgroundColor2{ QColor(0,0,0,255) };

		//背景颜色是否渐变
		bool backgroundColorGradient = true;
		//标题栏颜色是否渐变
		bool titleBackgroundColorGradient = true;

		//标题栏大小
		QRectF titleSize{ 0,0,backgroundSize.width(),30 };

		//节点名称
		QString nodeName;

		//脚本路径或地址
		QString ScriptPath{ "" };
	public:



	};


}
#endif // NODEINFO_H
