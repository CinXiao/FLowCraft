#pragma once
#include<QGraphicsLineItem>
#include"../Info/LineInfo.h"
#include"../GraphicsLine/GraphicsLineItem.h"
namespace GraphicsModule {
	class GraphicsRubberLine :public GraphicsLineItem
	{
	public:
		GraphicsRubberLine();
		GraphicsRubberLine(QPointF startPos, QPointF finishPos);

		~GraphicsRubberLine();
		void UpdateLine(QPointF startPos,QPointF finishPos);
		void SetFinishPos(QPointF finishPos);
		void SetStartPos(QPointF startPos);

	};
}
