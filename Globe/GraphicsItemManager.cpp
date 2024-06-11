#include "GraphicsItemManager.h"

namespace Globe {
	GraphicsItemManager::GraphicsItemManager(QGraphicsView* view) :
		View(view)
	{
		Scene = View->scene();

	}

	GraphicsItemManager::~GraphicsItemManager()
	{}
	void GraphicsItemManager::AddItem(QGraphicsItem* item)
	{

		Scene->addItem(item);

		GraphicsItem* graphicsItem = dynamic_cast<GraphicsItem*>(item);
		if (graphicsItem != nullptr)
		{
			//判断是不是节点
			if (graphicsItem->Info.GraphicsItemType == GraphicsItemType::Node ||
				graphicsItem->Info.GraphicsItemType == GraphicsItemType::Start ||
				graphicsItem->Info.GraphicsItemType == GraphicsItemType::Chart)
			{
				GraphicsNode* ndoe = dynamic_cast<GraphicsNode*>(item);
				//构建GNCB
				GNCB GNCB_Item(ndoe);
				//添加到GNCB集合
				GNCB_List.push_back(GNCB_Item);
			}
		}

	}

	void GraphicsItemManager::Remove(QGraphicsItem* Item)
	{
		if (Item == nullptr)
			return;
		Scene->removeItem(Item);
		delete Item;
		Item = nullptr;
	}

	void GraphicsItemManager::RemoveNode(QGraphicsItem* Item)
	{
		//是节点
		GraphicsNode* node{ nullptr };
		if (Item->parentItem() == nullptr)
		{

			for (auto GNCB : GNCB_List)
			{
				if (GNCB.GetNode() == Item)
				{
					node = GNCB.GetNode();
					//找到以后先删除节点各个端口的连接关系
					QList<GraphicsPort*> portlist = GNCB.PortList();
					for (auto port : portlist)
					{
						//如果连接，则需要断开连接
						if (port->GetPortInfo().IsConnection)
						{
							DisConnectPort(port);
						}
					}

				}

			}
		}
		if (node)
		{
			Scene->removeItem(Item);
			GNCB_List.removeIf([=](GNCB gncb) {
				return gncb.GetNode() == node;
				});
			delete Item;
			Item = nullptr;
		}

	}

	void GraphicsItemManager::RemoveLine(QGraphicsLineItem* Line)
	{
		//寻找
		for (auto line : GNCCB_ConnectLineList)
		{
			if (line.line == Line)
			{
				DisConnectPort(line.GNCCB.Block1_Port);

				return;
			}
		}
	}



	void GraphicsItemManager::ConnectPort(GraphicsPort* port1, GraphicsPort* port2)
	{

		bool porttypeflag = ConnectPortTypeCheck(port1, port2);
		bool portdatatypeflag = ConnectPortDataTypeCheck(port1, port2);
		bool portMonotonicityflag = ConnectPortMonotonicityCheck(port1, port2);

		//端口类型不匹配
		if (!porttypeflag)return;

		//数据类型不匹配
		if (!portdatatypeflag)
		{
			//尝试创建数据转换节点


			return;
		}
		//单调性检查不匹配(输入端口已连接)
		else if (!portMonotonicityflag)
		{
			//端口已连接输入端口，尝试先断开重新连接
			if (port1->GetPortInfo().IsConnection)
			{
				DisConnectPort(port1);
			}
			if (port2->GetPortInfo().IsConnection)
			{
				DisConnectPort(port2);
			}
			//重新连接
			ConnectPort(port1, port2);
			return;
		}
		//正常情况，检查全部通过
		else if (portMonotonicityflag && portdatatypeflag)
		{
			//设置端口信息
			port1->GetPortInfo().IsConnection = true;
			port2->GetPortInfo().IsConnection = true;

			//得到端口的父对象（节点）
			QGraphicsItem* node1 = port1->parentItem();
			QGraphicsItem* node2 = port2->parentItem();
			GNCB gncb1 = GetGNCB(node1);
			GNCB gncb2 = GetGNCB(node2);
			//构建逻辑连接关系
			GNCCB GNCCBItem(gncb1, gncb2, port1, port2);
			GNCCB_List.push_back(GNCCBItem);

			//构建连接线
			GraphicsLineItemBeziercurveitem* connectionline
				= new GraphicsLineItemBeziercurveitem
				(
					port1->mapToScene(port1->boundingRect().center()),
					port2->mapToScene(port2->boundingRect().center())
				);
			QPen pen = port1->GetPortInfo().normalBorder;
			pen.setWidth(8);
			connectionline->SetPen(pen);
			Scene->addItem(connectionline);
			CGNNCB_LINE item{ GNCCBItem ,connectionline };
			//添加到物理连接列表中
			GNCCB_ConnectLineList.append(item);

		}
	}

	void GraphicsItemManager::ConnectPortById(int portId1, int portId2)
	{
		GraphicsPort* port1, * port2;
		int count = 0;
		for (auto gncb : GNCB_List)
		{
			for (auto port : gncb.PortList())
			{
				if (port->GetPortInfo().portNumber == portId1)
				{
					count++;
					port1 = port;
				}else
				if (port->GetPortInfo().portNumber == portId2)
				{
					count++;
					port2 = port;
				}
				//两个端口都找到了，退出循环
				if (count == 2)
				{
					//连接端口
					ConnectPort(port1, port2);
					break;
				}
			}
		}
	}

	void GraphicsItemManager::DisConnectPort(GraphicsPort* port1, GraphicsPort* port2)
	{


	}

	void GraphicsItemManager::DisConnectPort(GraphicsPort* port1)
	{
		//两个list的下标；
		int i = -1, j = -1;
		bool flag{ false };
		for (auto item : GNCCB_List)
		{
			i++;
			if (item.Block1_Port == port1 || item.Block2_Port == port1)
			{
				for (auto linkitem : GNCCB_ConnectLineList)
				{
					j++;
					if (linkitem.GNCCB == item)
					{
						flag = true;
						break;
					}
				}
				break;
			}
		}

		if (flag)
		{

			//设置端口1标识
			int port1count = 0, port2count = 0;
			for (auto item : GNCCB_List)
			{
				if (GNCCB_List[i].Block1_Port == item.Block1_Port || GNCCB_List[i].Block1_Port == item.Block2_Port)
				{
					port1count++;
				}

			}
			for (auto item : GNCCB_List)
			{
				if (GNCCB_List[i].Block2_Port == item.Block1_Port || GNCCB_List[i].Block2_Port == item.Block2_Port)
				{
					port2count++;
				}

			}
			//设置端口2标识
			if (port1count == 1)
				GNCCB_List[i].Block1_Port->GetPortInfo().IsConnection = false;
			if (port2count == 1)
				GNCCB_List[i].Block2_Port->GetPortInfo().IsConnection = false;

			//移除逻辑连接
			GNCCB_List.remove(i);
			//移除物理连接
			delete GNCCB_ConnectLineList[j].line;
			GNCCB_ConnectLineList[j].line = nullptr;
			GNCCB_ConnectLineList.remove(j);
		}

	}

	void GraphicsItemManager::UpdateNode(QGraphicsItem* item)
	{
		//检查是不是节点
		if (dynamic_cast<GraphicsNode*>(item) == nullptr)
			return;
		//更新节点
		//得到连接线
		GNCB gncb = GetGNCB(item);
		//找到物理连接关系列表
		QList<CGNNCB_LINE>ConnectLineList;
		for (auto item : GNCCB_ConnectLineList)
		{
			if (gncb.GetNode() == item.GNCCB.Block1.GetNode() ||
				gncb.GetNode() == item.GNCCB.Block2.GetNode());
			ConnectLineList.push_back(item);
		}
		//调整物理连接线
		for (auto item : ConnectLineList)
		{
			item.line->UpdateLine
			(
				item.GNCCB.Block1_Port->mapToScene(item.GNCCB.Block1_Port->boundingRect().center()),
				item.GNCCB.Block2_Port->mapToScene(item.GNCCB.Block2_Port->boundingRect().center()
				)
			);

		}
	}

	QList<GNCCB> GraphicsItemManager::GetGNCCB()
	{
		return GNCCB_List;
	}

	QList<GNCB> GraphicsItemManager::GetGNCBList()
	{
		return GNCB_List;
	}

	bool GraphicsItemManager::ConnectPortTypeCheck(GraphicsPort* port1, GraphicsPort* port2)
	{
		PortInfo type1 = port1->GetPortInfo(), type2 = port2->GetPortInfo();
		//不能自己连接自己
		if (port1->parentItem() == port2->parentItem())
			return false;
		//端口输入输出端口类型检测，确保输入只能连接输出
		if (type1.portType == type2.portType)
			return false;
		if (type1.portType == PortType::DataInput && type2.portType != PortType::DataOutput)
			return false;
		if (type2.portType == PortType::DataInput && type1.portType != PortType::DataOutput)
			return false;

		if (type1.portType == PortType::ProgramControlInput && type2.portType != PortType::ProgramControlOutput)
			return false;
		if (type2.portType == PortType::ProgramControlInput && type1.portType != PortType::ProgramControlOutput)
			return false;

		if (type1.portType == PortType::TriggerInput && type2.portType != PortType::TriggerOutput)
			return false;
		if (type2.portType == PortType::TriggerInput && type1.portType != PortType::TriggerOutput)
			return false;
		return true;
	}

	bool GraphicsItemManager::ConnectPortDataTypeCheck(GraphicsPort* port1, GraphicsPort* port2)
	{

		//端口数据类型检查
		PortInfo type1 = port1->GetPortInfo(), type2 = port2->GetPortInfo();
		return type1.portDataType == type2.portDataType;
	}

	bool GraphicsItemManager::ConnectPortMonotonicityCheck(GraphicsPort* port1, GraphicsPort* port2)
	{

		PortInfo type1 = port1->GetPortInfo(), type2 = port2->GetPortInfo();

		//端口类型单调性检测   一个数据输出可以连多个数据输入，但是一个数据输入只能连一个数据输出 程序控制和触发器则只能输入输出都只能连一个
		if (type1.IsConnection && type1.portType == PortType::DataInput)
			return false;
		if (type2.IsConnection && type2.portType == PortType::DataInput)
			return false;

		if (type1.IsConnection && type1.portType == PortType::ProgramControlInput)
			return false;
		if (type2.IsConnection && type2.portType == PortType::ProgramControlInput)
			return false;
		if (type1.IsConnection && type1.portType == PortType::ProgramControlOutput)
			return false;
		if (type2.IsConnection && type2.portType == PortType::ProgramControlOutput)
			return false;

		if (type1.IsConnection && type1.portType == PortType::TriggerInput)
			return false;
		if (type2.IsConnection && type2.portType == PortType::TriggerInput)
			return false;
		if (type1.IsConnection && type1.portType == PortType::TriggerOutput)
			return false;
		if (type2.IsConnection && type2.portType == PortType::TriggerOutput)
			return false;
		return true;
	}

	GNCB GraphicsItemManager::GetGNCB(QGraphicsItem* target)
	{
		auto gncb = std::find_if(GNCB_List.begin(), GNCB_List.end(), [target](GNCB& gncb)
			{
				return gncb.GetNode() == target;
			});
		return *gncb;
	}
}