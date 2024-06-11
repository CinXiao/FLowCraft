#pragma once
#include<QPainter>
#include<QGraphicsitem>
#include<QGraphicsSceneMouseEvent>
#include<QFont>
#include<QMutex>
#include<QKeyEvent>
#include<QTextCursor>
#include<QGraphicsScene>
#include"../Info/TextInfo.h"
namespace GraphicsModule
{
	class GraphicsText :public QGraphicsTextItem
	{
	public:
		GraphicsText(TextInfo info, QGraphicsItem* parent = nullptr);
		void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)override;

		void focusOutEvent(QFocusEvent* event);
		void mousePressEvent(QGraphicsSceneMouseEvent* event)override;
		void keyPressEvent(QKeyEvent* event)override;
		QRectF boundingRect() const;
		TextInfo* Info{ new TextInfo{} };
	};
}