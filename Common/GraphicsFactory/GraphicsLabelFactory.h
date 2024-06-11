#pragma once
#include<QGraphicsitem>
#include"GraphicsFactory.h"
#include"../../Graphics/GraphicsItem/GraphicsLable.h"
#include"../../Graphics/Info/LabelInfo.h"

namespace Common {
	class GraphicsLabelFactory :public GraphicsFactory
	{
	public:
		GraphicsLabelFactory(LabelInfo info);
		// 通过 GraphicsFactory 继承
		QGraphicsItem* CreatSelfGraphicsItem() override;
		LabelInfo Info;
	};
}