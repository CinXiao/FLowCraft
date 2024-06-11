#pragma once

#include <QPainter>
#include <QGraphicsObject>
#include"../Info/NodeInfo.h"
#include "GraphicsItem.h"

namespace GraphicsModule {


	class GraphicsNode : public GraphicsItem
	{

	public:
		GraphicsNode(NodeInfo nodeInfo = NodeInfo());

		void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)override;


		NodeInfo Info;



	};


}
