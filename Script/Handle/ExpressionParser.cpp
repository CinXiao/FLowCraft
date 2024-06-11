#include "ExpressionParser.h"
#include"functions/ChartFunction.h"
#include"functions/MathFunction.h"
#include"functions/NetWorkFunction.h"
namespace ScriptModule
{

	//初始化函数表
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


			//网络
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
		//解析函数名和参数名
		  // 正则表达式，使用捕获组分别匹配函数名和参数列表
		QRegularExpression regExp(R"((\w+)\((.*)\))");
		QRegularExpressionMatch match = regExp.match(exp);
		if (match.hasMatch()) {
			// 提取函数名
			functionName = match.captured(1);
			// 提取参数字符串，进一步处理参数
			QString argsStr = match.captured(2).trimmed();  // 去除前导和尾随空白
			if (!argsStr.isEmpty()) {  // 确保有参数
				// 使用逗号作为分隔符，但考虑到参数间可能有空白，使用正则表达式分割更稳健
				QStringList args = argsStr.split(QRegularExpression("\\s*,\\s*"), Qt::SkipEmptyParts);
				argumentList = args;
			}
		}
	}

	QVariant ExpressionParser::parse()
	{
		//调用函数表中的
		if (functionMap.contains(functionName))
		{
			auto function = functionMap[functionName];
            return function(argumentList, gncb);
		}
		return QVariant();
	}
}
