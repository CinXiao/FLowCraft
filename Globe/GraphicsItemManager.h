#pragma once
#include<QgraphicsView>
#include<QGraphicsScene>
#include"../Entity/GraphicsNodeControlBlock.h"
#include"../Entity/GraphicsNodeConnectionControlBlock.h"
#include"../Graphics/GraphicsItem/GraphicsItem.h"
#include"../Graphics/GraphicsLine/GraphicsLineItemBeziercurveitem.h"
#include"../Graphics/GraphicsItem/GraphicsPort.h"
#include"Enum.h"
#include<QSet.h>
using namespace Entity;
using namespace GraphicsModule;
typedef GraphicsNodeControlBlock GNCB;
typedef GraphicsNodeConnectionControlBlock GNCCB;
namespace Globe {
	class GraphicsItemManager
	{
	public:
		GraphicsItemManager(QGraphicsView *view);
		~GraphicsItemManager();
		void AddItem(QGraphicsItem*item);
		void Remove(QGraphicsItem*Item);
		void RemoveNode(QGraphicsItem* Item);
		void RemoveLine(QGraphicsLineItem* Line);

		void ConnectPort(GraphicsPort*port1, GraphicsPort*port2);
		void ConnectPortById(int portId1, int portId2);

		//断掉两个端口之间的连接
		void DisConnectPort(GraphicsPort* port1, GraphicsPort* port2);
		//断掉端口之间的连接
		void DisConnectPort(GraphicsPort* port1);
		void UpdateNode(QGraphicsItem*item);

		//逻辑连接和物理线结构
		struct  CGNNCB_LINE {
			GNCCB GNCCB;
			GraphicsLineItemBeziercurveitem* line;
		};
		QList<GNCCB> GetGNCCB();
		QList<GNCB> GetGNCBList();
	private:
		//端口连接检查
		bool ConnectPortTypeCheck(GraphicsPort* port1, GraphicsPort* port2);
		bool ConnectPortDataTypeCheck(GraphicsPort* port1, GraphicsPort* port2);
		bool ConnectPortMonotonicityCheck(GraphicsPort* port1, GraphicsPort* port2);


		//从节点控制块列表中获取节点控制块
		GNCB GetGNCB(QGraphicsItem*target);

		//视图和场景
		QGraphicsView* View;
		QGraphicsScene* Scene;


		//节点控制块
		QList<GNCB> GNCB_List;
		//节点连接控制块(逻辑连接) 后期用于生成程序流程树
		QList<GNCCB> GNCCB_List;
	
		//连接关系和连接线(物理连接)
		QList<CGNNCB_LINE>GNCCB_ConnectLineList;
	};
}