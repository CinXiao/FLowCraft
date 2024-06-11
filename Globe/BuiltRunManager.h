#pragma once
#include<qdebug.h>
#include<QStack>
#include<qdebug.h>
#include<qthread.h>
#include"../Entity/GraphicsNodeControlBlock.h"
#include"../Entity/GraphicsNodeConnectionControlBlock.h"
#include <qmutex.h>
#include"../Globe/RuningConfig.h"
using namespace Entity;
using namespace GraphicsModule;
using namespace Globe;
typedef GraphicsNodeControlBlock GNCB;
typedef GraphicsNodeConnectionControlBlock GNCCB;
using namespace Entity;
namespace Globe {
	//控制块和执行栈结构
	struct StartNode_NodeStack
	{
		//图元元对象进程控制块
		GNCB startNode;
		//进程控制块 执行栈
		QStack<GNCB> NodeStack;
	};


	//程序执行流多线程调动进程调度线程
	class ProgressRunThread :public QThread {
		Q_OBJECT
	public:
		ProgressRunThread(StartNode_NodeStack progress, QList<GNCCB>GNCCB_List) :
			progress(progress), GNCCB_List(GNCCB_List) {};
		void run()override
		{
			do
			{
				for (auto& gncb : progress.NodeStack)
				{
					//GNCB开始执行
					if (!gncb.Executed)
						gncb.Execute();
					//执行完成以后给gncb输入端口连接的输入端口赋值
					for (auto item : gncb.PortList())
					{
						if (item->GetPortInfo().IsConnection)
						{
							//遍历连接关系给相连的端口赋值
							for (auto gnccb : GNCCB_List)
							{
								if (gnccb.Block1_Port == item && gnccb.Block1_Port->GetPortInfo().portType == DataOutput)
								{
									gnccb.Block2.SetPortValue(gnccb.Block1.GetPortValue(gnccb.Block1_Port), gnccb.Block2_Port);
								}
								else
									if (gnccb.Block2_Port == item && gnccb.Block2_Port->GetPortInfo().portType == DataOutput)
									{
										gnccb.Block1.SetPortValue(gnccb.Block2.GetPortValue(gnccb.Block2_Port), gnccb.Block1_Port);
									}
							}
						}
					}
					gncb.GetNode()->update();
				}
				QThread::msleep(RuningConfig::UnitStepDelay);
				for (auto& gncb : progress.NodeStack)
				{
					gncb.Executed = false;

				}
			} while (RuningConfig::IsRuning && !RuningConfig::IsOnceRuning);
		}
	private:
		QList<GNCCB> GNCCB_List;
		StartNode_NodeStack progress;
	};


	class BuiltRunManager
	{
	public:
		BuiltRunManager();

		~BuiltRunManager();
		void Run();
		void RunOnce();
		void Stop();
		void SetGNCCB(QList<GNCCB> GNCCB_List);

	private:
		void NodeRun(GNCB gncb);

		//用于获取单个节点的输入端口与其连接的节点，生成一个节点队列
		void GenerateFlowStack(GNCB gncb, QStack<GNCB>& stack);
		//获取与开始节点连接的程序流程节点列表
		void GenerateFlowList(GNCB gncb, QList<GNCB>& gncblist);


		//节点连接控制块(逻辑连接) 后期用于生成程序流程树
		QList<GNCCB> GNCCB_List;

		//开始节点列表
		QList<GNCB> StartNodeList;


		//程序列表，每条程序应该放在不同的线程
		QList<StartNode_NodeStack> Progress;

		//多线程序列执行
		QList<ProgressRunThread*> threads;
	};
}
