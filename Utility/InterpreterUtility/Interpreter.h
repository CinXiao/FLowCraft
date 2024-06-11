#pragma once
#include<QVariant>
#include<QRegularExpression>
#include<QString>
namespace Utility {

	class Interpreter {
	public:
		//算数表达式类型判断
		static bool  isArithmeticExpression(const QString& expr);
		//逻辑表达式
		static bool  isLogicalExpression(const QString& expr);
		//值类型判断
		static bool  isInteger(const QString& str);
		//
		static bool  isDecimal(const QString& str);
		//函数调用判断
		static bool  isFunction(const QString& str);

		//向量检测
		static bool  isVector(const QString& str);

		//矩阵检测
		static bool  isMatrix(const QString& str);
		//下标访问检测
		static bool  isSubscriptAccess(const QString& str);

		//取出对象和下标
		static std::pair<QString, QList<QString>> extractObjectNameAndIndices(const QString& input);

		static bool  isHexadecimal(const QString& str);
		static bool  isBool(const QString& str);
		static bool  isString(const QString& str);
		static bool  stringToBool(const QString& str);
		//拆分逻辑表达式
		static QStringList splitLogicalExpression(const QString& expression);
		//拆分表达式
		static QStringList splitExpression(const QString& expression);
	};
}