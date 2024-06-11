#include "ExpressionParser.h"
#include"functions/ChartFunction.h"
#include"functions/MathFunction.h"
#include"functions/NetWorkFunction.h"
namespace ScriptModule
{

	//��ʼ��������
	void initFunctionMap()
	{
		ExpressionParser::functionMap =
        {
            {"Clear",ChartFunction::ClearChart},
            {"clear",ChartFunction::ClearChart},
            {"InsertValue",ChartFunction::InsertChartValue},
            {"insertValue",ChartFunction::InsertChartValue},
            {"insertvalue",ChartFunction::InsertChartValue},

            {"Add",MathFunction::Add},
            {"add",MathFunction::Add},

			{"Sub",MathFunction::Sub},
			{"sub",MathFunction::Sub},


			//����
			{"SendPost",NetWorkFunction::SendPostRequest},
			{"SendPostRequest",NetWorkFunction::SendPostRequest},
			{"PostRequest",NetWorkFunction::SendPostRequest},
			{"sendpost",NetWorkFunction::SendPostRequest},
			{"sendpostrequest",NetWorkFunction::SendPostRequest},
			{"postrequest",NetWorkFunction::SendPostRequest},

		};


	};



	ExpressionParser::ExpressionParser(QString exp, GNCB* gncb)
		:gncb(gncb)
	{
		static bool isInitFunctionMap{ false };
		if (!isInitFunctionMap)
		{
			isInitFunctionMap = true;
			initFunctionMap();
		}
		//�����������Ͳ�����
		  // ������ʽ��ʹ�ò�����ֱ�ƥ�亯�����Ͳ����б�
		QRegularExpression regExp(R"((\w+)\((.*)\))");
		QRegularExpressionMatch match = regExp.match(exp);
		if (match.hasMatch()) {
			// ��ȡ������
			functionName = match.captured(1);
			// ��ȡ�����ַ�������һ���������
			QString argsStr = match.captured(2).trimmed();  // ȥ��ǰ����β��հ�
			if (!argsStr.isEmpty()) {  // ȷ���в���
				// ʹ�ö�����Ϊ�ָ����������ǵ�����������пհף�ʹ��������ʽ�ָ���Ƚ�
				QStringList args = argsStr.split(QRegularExpression("\\s*,\\s*"), Qt::SkipEmptyParts);
				argumentList = args;
			}
		}
	}

	QVariant ExpressionParser::parse()
	{
		//���ú������е�
		if (functionMap.contains(functionName))
		{
			auto function = functionMap[functionName];
            return function(argumentList, gncb);
		}
		return QVariant();
	}
}
