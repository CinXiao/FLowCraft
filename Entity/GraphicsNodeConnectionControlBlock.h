#pragma once
#include"GraphicsNodeControlBlock.h"
#include"../Graphics/GraphicsItem/GraphicsPort.h"
using namespace GraphicsModule;
namespace Entity {
	class GraphicsNodeConnectionControlBlock
	{
	public:
		GraphicsNodeConnectionControlBlock();
		GraphicsNodeConnectionControlBlock(GraphicsNodeControlBlock Block1, 
		GraphicsNodeControlBlock Block2, GraphicsPort*port1, GraphicsPort*port2);



		GraphicsNodeControlBlock Block1{};
		GraphicsNodeControlBlock Block2{};
		
		GraphicsPort* Block1_Port{};
		GraphicsPort* Block2_Port{};
		bool operator==(GraphicsNodeConnectionControlBlock& GNCCB);
	

	};
}