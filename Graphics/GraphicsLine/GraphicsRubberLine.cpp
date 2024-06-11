#include "GraphicsRubberLine.h"

namespace GraphicsModule 
{
	
	GraphicsRubberLine::GraphicsRubberLine()
	{

	}
	GraphicsRubberLine::GraphicsRubberLine(QPointF startPos, QPointF finishPos)
	{
		UpdateLine(startPos,finishPos);
	}
	GraphicsRubberLine::~GraphicsRubberLine()
	{

	}
	void GraphicsRubberLine::UpdateLine(QPointF startPos, QPointF finishPos)
	{

		Info.startPos = startPos;
		Info.FinishPos = finishPos;
		setLine(startPos.x(), startPos.y(), finishPos.x(), finishPos.y());
		
	}
	void GraphicsRubberLine::SetFinishPos(QPointF finishPos)
	{
		Info.FinishPos = finishPos;
		setLine(Info.startPos.x(), Info.startPos.y(), finishPos.x(), finishPos.y());
	}

	void GraphicsRubberLine::SetStartPos(QPointF startPos)
	{

		Info.startPos = startPos;
		setLine(startPos.x(), startPos.y(), Info.FinishPos.x(), Info.FinishPos.y());
	}


}