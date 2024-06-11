#pragma once
#include <QPainter>
#include <QGraphicsObject>
#include<QPainter>
#include"GraphicsItem.h"
#include"../Info/PictureBoxInfo.h"
#include<QRectF>
#include<QGraphicsSceneMouseEvent>
#include"../../Globe/RuningConfig.h"

using namespace Globe;
namespace GraphicsModule {
	class GraphicsPictureBox : public GraphicsItem
	{
	public:
		GraphicsPictureBox(PictureBoxInfo info = PictureBoxInfo{});
		QRectF boundingRect() const;
		void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)override;

		PictureBoxInfo info;
		QPixmap image;

	};
}