#include "GraphicsNodeConnectionControlBlock.h"
namespace Entity {
	GraphicsNodeConnectionControlBlock::GraphicsNodeConnectionControlBlock()
	{
	}
	GraphicsNodeConnectionControlBlock::GraphicsNodeConnectionControlBlock
	(GraphicsNodeControlBlock Block1, GraphicsNodeControlBlock Block2,
		GraphicsPort* port1, GraphicsPort* port2) :Block1(Block1),
		Block2(Block2), Block1_Port(port1), Block2_Port(port2)
	{


	}

	bool GraphicsNodeConnectionControlBlock::operator==(GraphicsNodeConnectionControlBlock& GNCCB)
	{
		if (GNCCB.Block1.GetNode() == Block1.GetNode() &&
			GNCCB.Block2.GetNode() == Block2.GetNode() &&
			GNCCB.Block1_Port == Block1_Port && GNCCB.Block2_Port == Block2_Port)
		{
			return true;
		}

		return false;
	}

}