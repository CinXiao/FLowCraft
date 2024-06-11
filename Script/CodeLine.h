#pragma once
#include<QString>
namespace ScriptModule
{

	enum ExprssionType {
		NONE_Exp,//空语句
		Assignment_Exp,//赋值
		Jump_Exp,//跳转
		Label_Exp,//标号
		Finish_Exp,//结束
		Judge_Exp,//判断
		Handle_Exp,//默认行为
	};


	class Expression
	{
	public:
		ExprssionType type{ NONE_Exp };
		//根据代码行判断表达式类型
		Expression() {};
		Expression(QString codeline) {
			code = codeline.replace(" ", "");
			if (codeline.contains("=")&& codeline.count("=")==1)
				type = Assignment_Exp;
			else if (codeline.contains("IF"))
				type = Judge_Exp;
			else if (codeline.contains("GOTO:"))
				type = Jump_Exp;
			else if (codeline.contains("::"))
				type = Label_Exp;
			else if (codeline.contains("RETURN"))
				type = Finish_Exp;
			else
				type = Handle_Exp;
		};
		QString code;//代码
	};


}