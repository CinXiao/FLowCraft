#include "Interpreter.h"

namespace Utility {



	bool Interpreter::isArithmeticExpression(const QString& expr)
	{
		// 变量名模式，由字母、数字和下划线组成，并且不以数字开头  
		QString varNamePattern = "[a-zA-Z_][a-zA-Z0-9_]*";
		// 数字模式，包括整数和可选的小数点及小数部分，同时考虑负数的情况  
		QString numberPattern = "([-+]?\\d+(\\.\\d+)?)";
		// 运算符模式  
		QString operatorPattern = "[-+*/\\.]";
		// 函数调用模式
		QString functionPattern = "\\w+\\(\\s*(?:\\w+\\s*(?:,\\s*\\w+\\s*)*)?\\)";
		// 可选的空白字符模式  
		QString whitespacePattern = "\\s*";

		// 分组模式，允许变量名或数字  
		QString groupedPattern = "(" + varNamePattern + "|" + numberPattern + "|" + functionPattern + ")";

		// 表达式模式，要求至少有一个运算符和两个操作数  
		QString exprPattern = "^" + whitespacePattern +
			groupedPattern + whitespacePattern + // 第一个操作数  
			"(" + whitespacePattern + operatorPattern + whitespacePattern + groupedPattern + ")+" + // 至少一个运算符和第二个操作数  
			whitespacePattern + "$";
		QRegularExpression arithmeticExprRegExp(exprPattern);
		return arithmeticExprRegExp.match(expr).hasMatch();
	}

	bool Interpreter::isLogicalExpression(const QString& expr)
	{
		return  (expr.contains("!=") ||
			expr.contains("!") ||
			expr.contains("&&") ||
			expr.contains("||") ||
			expr.contains("==") ||
			expr.contains("<") ||
			expr.contains(">") ||
			expr.contains("!>") ||
			expr.contains("!<"));
	}

	bool Interpreter::isInteger(const QString& str)
	{
		QRegularExpression regExp("^[-+]?[1-9]\\d*$|^0$");
		return regExp.match(str).hasMatch();
	}

	bool Interpreter::isDecimal(const QString& str)
	{
		QRegularExpression regExp("^[-+]?\\d+(\\.\\d+)?$");
		return regExp.match(str).hasMatch();
	}

	bool Interpreter::isFunction(const QString& str)
	{
		QRegularExpression regExp(R"(\w+\((("[^"]*")|(\w+))(,\s*(("[^"]*")|(\w+)))*\))");

		// 使用match函数检查整个字符串是否符合该模式
		return regExp.match(str).hasMatch();
	}



	bool Interpreter::isVector(const QString& str)
	{
		// 正则表达式匹配括号括起来，逗号分隔的列表格式  
// 注意：这里假设列表中的元素不包含括号或逗号，且括号内不允许有空格  
		QString s = str;
		s = s.replace(" ", "");
		QRegularExpression re(R"(\(\s*([^(),\s]+(\s*,\s*[^(),\s]+)*)?\s*\))");
		// 使用正则表达式进行匹配  
		QRegularExpressionMatch match = re.match(s);

		// 检查是否匹配  
		return match.hasMatch();
	}

	bool Interpreter::isMatrix(const QString& str)
	{
		// 定义矩阵的正则表达式
		QString matrixRegex = R"(\{((?!"[^"]*")(?:[A-Za-z0-9_]+\s*,*\s*)+;)*((?!"[^"]*")[A-Za-z0-9_]+\s*,*\s*)*\})";

		// 使用正则表达式进行匹配
		QRegularExpression re(matrixRegex);
		QRegularExpressionMatch match = re.match(str);

		// 检查是否匹配
		return match.hasMatch();
	}


	bool Interpreter::isSubscriptAccess(const QString& str)
	{
		if (str.contains("[") && str.contains("]") && str.count("[") == str.count("]"))
			return true;
		return false;
	}

	std::pair<QString, QList<QString>> Interpreter::extractObjectNameAndIndices(const QString& input)
	{
		QString objectName;
		QList<QString> indices;
		// 找到第一个 '[' 的位置  
		int bracketIndex = input.indexOf('[');
		if (bracketIndex != -1) {
			// 截取 '[' 之前的部分作为对象名  
			objectName = input.left(bracketIndex);
			// 处理下标  
			int pos = bracketIndex + 1; // 跳过 '['  
			while (pos < input.length()) {
				// 查找 ']' 的位置  
				int endIndex = input.indexOf(']', pos);
				if (endIndex == -1) {
					// 没有找到 ']'，可能是格式错误，提前退出  
					break;
				}
				// 提取当前下标  
				bool ok;
				QString index = input.mid(pos, endIndex - pos);
				if (!index.isEmpty())
					indices.push_back(index);
				// 更新位置到下一个 '['  
				pos = input.indexOf('[', endIndex); // 查找下一个 '[' 的位置
				if (pos == -1)
					break; // 如果没有找到下一个 '['，提前退出循环
				pos++; // 跳过 '['
			}
		}
		else {
			// 没有 '['，整个输入作为对象名  
			objectName = input;
		}

		return { objectName, indices };
	}

	bool Interpreter::isHexadecimal(const QString& str)
	{
		QRegularExpression regExp("^0x[0-9A-Fa-f]+$");
		return regExp.match(str).hasMatch();
	}

	bool Interpreter::isBool(const QString& str)
	{
		return str.toLower() == "true" || str.toLower() == "false";
	}

	bool Interpreter::isString(const QString& str)
	{
		return str.contains("\"");
	}

	bool Interpreter::stringToBool(const QString& str)
	{	// 去除字符串两端的空格  
		QString trimmedStr = str.trimmed();
		// 转换为小写进行比较，不区分大小写  
		return trimmedStr.toLower() == "true";
	}

	QStringList Interpreter::splitLogicalExpression(const QString& expression)
	{
		int assignmentIndex = expression.indexOf('=');
		if (assignmentIndex == -1) {
			// 没有找到赋值运算符，可能是一个纯逻辑表达式  
			return QStringList(expression);
		}

		// 分割为两部分：赋值语句和逻辑表达式  
		QString assignment = expression.left(assignmentIndex).trimmed(); // 去除两侧空格  
		QString logic = expression.mid(assignmentIndex + 1).trimmed(); // 去除两侧空格和赋值运算符  

		// 返回结果列表，包含赋值语句和逻辑表达式  
		return QStringList() << assignment << logic;
	}

	QStringList Interpreter::splitExpression(const QString& expression)
	{
		QStringList list;
		if (expression.contains("=="))
		{
			QStringList split = expression.split("==");
			list.append(split[0]);
			list.append("==");
			list.append(split[1]);
		}
		else if (expression.contains("!="))
		{
			QStringList split = expression.split("!=");
			list.append(split[0]);
			list.append("!=");
			list.append(split[1]);
		}
		else if (expression.contains("!"))
		{
			QStringList split = expression.split("!");
			list.append(split[1]);
			list.append("!");
		}
		else if (expression.contains("||"))
		{
			QStringList split = expression.split("||");
			list.append(split[0]);
			list.append("||");
			list.append(split[1]);
		}
		else if (expression.contains("&&"))
		{
			QStringList split = expression.split("&&");
			list.append(split[0]);
			list.append("&&");
			list.append(split[1]);
		}
		else if (expression.contains("<"))
		{
			QStringList split = expression.split("<");
			list.append(split[0]);
			list.append("<");
			list.append(split[1]);
		}
		else if (expression.contains(">"))
		{
			QStringList split = expression.split(">");
			list.append(split[0]);
			list.append(">");
			list.append(split[1]);
		}
		else if (expression.contains("!<"))
		{
			QStringList split = expression.split("!<");
			list.append(split[0]);
			list.append("!<");
			list.append(split[1]);
		}
		else if (expression.contains("!>"))
		{
			QStringList split = expression.split("!>");
			list.append(split[0]);
			list.append("!>");
			list.append(split[1]);
		}


		return list;
	}

}