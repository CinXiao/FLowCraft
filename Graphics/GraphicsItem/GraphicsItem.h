#pragma once
#include <QGraphicsItem>
#include<QPainter>
#include<QStyleOptionGraphicsItem>
#include"../Info/ItemInfo.h"
namespace GraphicsModule
{
	class GraphicsItem : public QGraphicsItem
	{
	public:
		GraphicsItem(ItemInfo info = ItemInfo(), QGraphicsItem* parent = nullptr);
		~GraphicsItem();
		QRectF boundingRect() const;
		void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)override;;
		ItemInfo Info;
	};
}
