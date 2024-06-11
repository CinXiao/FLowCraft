#pragma once
#include "../../../Entity/GraphicsNodeControlBlock.h"
#include"../../../Utility/InterpreterUtility/Interpreter.h"
typedef Entity::GraphicsNodeControlBlock GNCB;
namespace ScriptModule
{	/// <summary>
	/// ͼ���
	/// </summary>
	class ChartFunction
	{

	public:
		 
		//���ͼ������
        inline static QVariant ClearChart(const QStringList& arg, GNCB* gncb)
		{
			//���ͼ������
			if (arg.count() >= 1)
			{
				//��ȡ���ͼ���±��б�
				QList<int> indexlist;
				for (auto index : arg)
				{
					indexlist.append(index.replace("chart", "").toInt());
				}
				//�ҵ�ָ��ͼ��,���ͼ������
				for (auto index : indexlist)
					for (auto chart : *(gncb->_chartList))
					{
						//�������
						if (chart->Info.chartIndex == index)
						{
							chart->Info.DataList.clear();
						}
					}
			}
			return QVariant();
		}
		//����ͼ������
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
					//�߼����ʽ
					if (Interpreter::isArithmeticExpression(item))
					{
						Var = gncb->ArithmeticExpression(item);
					}// ��ֵ���߼����ʽ
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
				//�ҵ�ָ��ͼ��
				if (index != -1)
					for (auto chart : *(gncb->_chartList))
					{
						//��������
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
