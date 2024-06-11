#pragma once

#include<QList>
#include<QVariant>
#include<qgraphicsscene.h>
#include<qgraphicsview.h>

#include"../Graphics/GraphicsItem/GraphicsNode.h"
#include"../Graphics/GraphicsItem/GraphicsPort.h"
#include"../Graphics/GraphicsItem/GraphicsText.h"
#include"../Graphics/GraphicsItem/GraphicsChart.h"
#include"../Graphics/GraphicsItem/GraphicsSwitchButton.h"
#include"../Graphics/GraphicsItem/GraphicsLable.h"
#include "../Graphics/GraphicsItem/GraphicsButton.h"

#include"../Script/ScriptObject.h"
#include"../Script/CodeLine.h"

#include<QMutex>
#include<QThread>
#include<qfileinfo.h>

using namespace GraphicsModule;
using namespace ScriptModule;
using namespace Utility;

namespace Entity {


	class GraphicsNodeControlBlock
	{
	public:
		GraphicsNodeControlBlock();
		GraphicsNodeControlBlock(GraphicsNode* node);
		QList<GraphicsPort*>PortList();
		QList<GraphicsText*>* InputList();
		unsigned PortCount();

		GraphicsNode* GetNode();

		void Execute();//执行节点
		void SetPortValue(QVariant var, GraphicsPort* port);
		QVariant GetPortValue(GraphicsPort* port);
		void Updata() { if (_node)_node->update(); };//刷新节点

		bool Executed{ false };//执行标识符

		//脚本对象
		ScriptObject scriptObject{};
		//代码地址表
		QMap<int, Expression>CodeAddress{};

		//各种控件列表
		QMap<GraphicsPort*, QVariant>* _portList{ new QMap<GraphicsPort*, QVariant>() };
		QList<GraphicsText*>* _inputList{ new QList<GraphicsText*>() };
		QList<GraphicsChart*>* _chartList{ new QList<GraphicsChart*>() };
		QList<GraphicsButton*>* _buttonList{ new QList<GraphicsButton*>() };
		QList<GraphicsSwitchButton*>* _switchbuttonList{ new QList<GraphicsSwitchButton*>() };
		QList<GraphicsLabel*>* _labelList{ new QList<GraphicsLabel*>() };
		QVariant VarTypeSolved(QString VarStr);//获取变量的值
		QVariant ArithmeticExpression(QString ExpressionStr);//数学运算
		bool LogicalExpression(QString ExpressionStr);//逻辑运算
	private:
		void ProgramAddressGeneration();//生成程序地址
		void ExecuteExpression(Expression expression);//执行表达式

		GraphicsNode* _node{ nullptr };
		//标签名和地址映射表(虚地址表)
		QMap<QString, int>VirtualAddress{};
		//变量名和数据表
		QMap<QString, QVariant>VarMap{};
		//程序计数器PC
		int PC{ 0 };
		//获取端口数据
		QVariant  GetPortVar(int inex);

	};


}
