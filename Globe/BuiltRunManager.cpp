#include "BuiltRunManager.h"

namespace Globe {
	BuiltRunManager::BuiltRunManager()
	{


	}



	void BuiltRunManager::Run()
	{
		//设置运行标致
		RuningConfig::IsOnceRuning = false;
		RuningConfig::IsRuning = true;
		QMutex mutex; // 互斥锁  
		QMutexLocker locker(&mutex); // 锁定互斥锁  
		//找到开始节点
		for (auto item : GNCCB_List)
		{
			if (item.Block1.GetNode()->Info.GraphicsItemType == Start)
			{
				StartNodeList.append(item.Block1);
			}
			else if (item.Block2.GetNode()->Info.GraphicsItemType == Start)
			{
				StartNodeList.append(item.Block2);
			}
		}

		//遍历开始节点生成执行序列
		for (auto item : StartNodeList)
		{
			StartNode_NodeStack startNodeStack;
			//设置开始节点
			startNodeStack.startNode = item;

			//构建主流程
			QList<GNCB>list;
			GenerateFlowList(startNodeStack.startNode, list);
			//生成主流各个执行程栈
			for (const auto& item : list)
			{
				GenerateFlowStack(item, startNodeStack.NodeStack);
			}
			Progress.append(startNodeStack);
		}

		for (auto progressItem : Progress)
		{
			ProgressRunThread* thread = new ProgressRunThread(progressItem, GNCCB_List);
			//线程开跑
			thread->start();
			threads.append(thread);
		}
	}

	void BuiltRunManager::RunOnce()
	{
		//设置运行标致
		RuningConfig::IsRuning = true;
		RuningConfig::IsOnceRuning = true;
		//找到开始节点
		for (auto item : GNCCB_List)
		{
			if (item.Block1.GetNode()->Info.GraphicsItemType == Start)
			{
				StartNodeList.append(item.Block1);
			}
			else if (item.Block2.GetNode()->Info.GraphicsItemType == Start)
			{
				StartNodeList.append(item.Block2);
			}
		}
		//遍历开始节点生成执行序列
		for (auto item : StartNodeList)
		{
			StartNode_NodeStack startNodeStack;
			//设置开始节点
			startNodeStack.startNode = item;
			//构建主流程
			QList<GNCB>list;
			GenerateFlowList(startNodeStack.startNode, list);
			//生成主流各个执行程栈
			for (const auto& item : list)
			{
				GenerateFlowStack(item, startNodeStack.NodeStack);
			}
			Progress.append(startNodeStack);
		}

		for (auto progressItem : Progress)
		{
			ProgressRunThread* thread = new ProgressRunThread(progressItem, GNCCB_List);
			//线程开跑
			thread->start();
			threads.append(thread);
		}
		//线程列表存在条目数，先销毁线程
		if (threads.count())
		{
			for (auto thread : threads)
			{
				thread->wait();
			}
			threads.clear();
			StartNodeList.clear();
			Progress.clear();
		}
		//重置运行标识
		RuningConfig::IsRuning = false;
		RuningConfig::IsOnceRuning = false;

	}

	void BuiltRunManager::Stop()
	{
		//设置运行标致
		RuningConfig::IsRuning = false;
		RuningConfig::IsOnceRuning = false;
		QMutex mutex; // 互斥锁  
		QMutexLocker locker(&mutex); // 锁定互斥锁  
		//线程列表存在条目数，先销毁线程
		if (threads.count())
		{
			for (auto thread : threads)
			{
				thread->wait();
			}
			threads.clear();
			StartNodeList.clear();
			Progress.clear();
			return;
		}
	}


	void BuiltRunManager::SetGNCCB(QList<GNCCB> GNCCB_List)
	{
		this->GNCCB_List = GNCCB_List;
	}

	//构建程序流
	void BuiltRunManager::GenerateFlowStack(GNCB gncb, QStack<GNCB>& stack)
	{
		//拿到与GNCB中节点控制输出端口连接的节点
		for (auto port : gncb.PortList())
		{
			//找到节点数据输入端口
			if (port->GetPortInfo().IsActive && port->GetPortInfo().IsConnection && port->GetPortInfo().portType == DataInput)
			{
				//获取与该端口连接的节点
				for (auto gnccbitem : GNCCB_List)
				{
					if (gnccbitem.Block1_Port == port)
					{
						GenerateFlowStack(gnccbitem.Block2, stack);
					}
					else if (gnccbitem.Block2_Port == port)
					{
						GenerateFlowStack(gnccbitem.Block1, stack);
					}
				}
			}
		}
		stack.append(gncb);
	}

	void BuiltRunManager::GenerateFlowList(GNCB gncb, QList<GNCB>& gncblist)
	{

		gncblist.append(gncb);
		//拿到程序控制输出端口连接的节点
		for (auto port : gncb.PortList())
		{
			if (port->GetPortInfo().IsActive &&
				port->GetPortInfo().portType == ProgramControlOutput)
			{
				for (auto gnccbitem : GNCCB_List)
				{
					if (gnccbitem.Block1_Port == port)
					{
						GenerateFlowList(gnccbitem.Block2, gncblist);
					}
					else if (gnccbitem.Block2_Port == port)
					{
						GenerateFlowList(gnccbitem.Block1, gncblist);
					}
				}
			}
		}


	}



	void BuiltRunManager::NodeRun(GNCB gncb)
	{



	}



	BuiltRunManager::~BuiltRunManager()
	{

	}
}
