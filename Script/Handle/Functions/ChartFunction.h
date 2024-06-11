#pragma once
#include "../../../Entity/GraphicsNodeControlBlock.h"
#include"../../../Utility/InterpreterUtility/Interpreter.h"
typedef Entity::GraphicsNodeControlBlock GNCB;
namespace ScriptModule
{	/// <summary>
	/// 图表库
	/// </summary>
	class ChartFunction
	{

	public:
		 
		//清除图表数据
        inline static QVariant ClearChart(const QStringList& arg, GNCB* gncb)
		{
			//清除图表数据
			if (arg.count() >= 1)
			{
				//获取清除图表下标列表
				QList<int> indexlist;
				for (auto index : arg)
				{
					indexlist.append(index.replace("chart", "").toInt());
				}
				//找到指定图表,清除图表数据
				for (auto index : indexlist)
					for (auto chart : *(gncb->_chartList))
					{
						//清除数据
						if (chart->Info.chartIndex == index)
						{
							chart->Info.DataList.clear();
						}
					}
			}
			return QVariant();
		}
		//插入图表数据
		inline static QVariant InsertChartValue(const QStringList& arg, GNCB* gncb)
		{
			QList<QVariant>VarList{};
			QString chartName{ "" };
			int index{ -1 };
			if (arg.count() >= 2)
			{
				QString chartName = arg[0];
				QString indexstr = arg[0];
				index = indexstr.replace("chart", "").toInt();
				for (auto item : arg)
				{
					if (item == chartName)continue;
					QVariant Var;
					//逻辑表达式
					if (Interpreter::isArithmeticExpression(item))
					{
						Var = gncb->ArithmeticExpression(item);
					}// 右值是逻辑表达式
					else if (Interpreter::isLogicalExpression(item))
					{
						Var = gncb->LogicalExpression(item);
					}
					else
					{
						Var = gncb->VarTypeSolved(item);
					}
					VarList.append(Var.toFloat());
				}
				//找到指定图表
				if (index != -1)
					for (auto chart : *(gncb->_chartList))
					{
						//插入数据
						if (chart->Info.chartIndex == index)
						{
							chart->Info.InsertValueList(VarList);
						}
					}
			}

			return QVariant();
		}



	};
}
