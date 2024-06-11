#pragma once

#include"../Info/labelInfo.h"
#include "GraphicsItem.h"
namespace GraphicsModule
{
	class GraphicsLabel : public GraphicsItem
	{
	public:
		GraphicsLabel(LabelInfo info);

		QRectF boundingRect() const;
		void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)override;
		LabelInfo Info;
	};
}