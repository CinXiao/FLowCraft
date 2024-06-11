#include "GraphicsNodeControlBlock.h"

#include"../Utility/InterpreterUtility/Interpreter.h"
#include"../Script/Handle/ExpressionParser.h"
#include"../Globe/PortAssignor.h"
namespace Entity {
	//数学运算
	QVariant GraphicsNodeControlBlock::ArithmeticExpression(QString ExpressionStr)
	{
		QVariant var;
		QRegularExpression re("([a-zA-Z0-9.]+|\\w+\\(\\s*(?:[a-zA-Z0-9.]+\\s*(?:,\\s*[a-zA-Z0-9.]+\\s*)*)?\\))\\s*(\\+|\\-|\\*|\\/|\\.)\\s*(([a-zA-Z0-9.]+)|\\w+\\(\\s*(?:[a-zA-Z0-9.]+\\s*(?:,\\s*[a-zA-Z0-9.]+\\s*)*)?\\(\\s*\\))");

		QRegularExpressionMatch match = re.match(ExpressionStr);
		if (match.hasMatch())
		{
			QString leftOperand = match.captured(1);
			QString operatorStr = match.captured(2);
			QString rightOperand = match.captured(3);

			//通过运算符拆分左右两边操作数
			QStringList dat = ExpressionStr.split(operatorStr);
			if (dat.count() == 2)
			{
				leftOperand = dat[0];
				rightOperand = dat[1];
			}


			QVariant a, b;
			a = VarTypeSolved(leftOperand);
			b = VarTypeSolved(rightOperand);
			//操作符判断
			char op = operatorStr.at(0).toLatin1();
			QVariant::Type type1 = a.type(), type2 = b.type();
			if (type1 = type2)
				switch (op)
				{
				case '+': {
					if (type1 == QVariant::Int)
					{
						var.setValue(a.toInt() + b.toInt());
					}
					if (type1 == QVariant::Double)
					{
						var.setValue(a.toDouble() + b.toDouble());
					}
					if (type1 == QVariant::String)
					{
						var.setValue(a.toString() + b.toString());
					}
					//向量加法
					if (a.canConvert<Vector_Type>())
					{
						//a向量
						Vector_Type Va = a.value<Vector_Type>();
						//b向量
						Vector_Type Vb = b.value<Vector_Type>();
						//向量相加
						var.setValue(Va + Vb);
					}
					//矩阵加法
					if (a.canConvert<Matrix_Type>())
					{	//a矩阵
						Matrix_Type Ma = a.value<Matrix_Type>();
						//b矩阵
						Matrix_Type Mb = b.value<Matrix_Type>();
						var.setValue(Ma + Mb);
					}


				}break;
				case '-': {
					if (type1 == QVariant::Int)
					{
						var.setValue(a.toInt() - b.toInt());
					}
					if (type1 == QVariant::Double)
					{
						var.setValue(a.toDouble() - b.toDouble());
					}	//向量减法
					if (a.canConvert<Vector_Type>())
					{
						Vector_Type Va = a.value<Vector_Type>();
						Vector_Type Vb = b.value<Vector_Type>();

						// 设置减法结果  
						var.setValue(Va - Vb);
					}
					//矩阵减法
					if (a.canConvert<Matrix_Type>())
					{	//a矩阵
						Matrix_Type Ma = a.value<Matrix_Type>();
						//b矩阵
						Matrix_Type Mb = b.value<Matrix_Type>();
						var.setValue(Ma - Mb);
					}
				}break;
				case '*': {
					if (type1 == QVariant::Int)
					{
						var.setValue(a.toInt() * b.toInt());
					}
					if (type1 == QVariant::Double)
					{
						var.setValue(a.toDouble() * b.toDouble());
					}
					//向量叉乘
					if (a.canConvert<Vector_Type>())
					{
						Vector_Type Va = a.value<Vector_Type>();
						Vector_Type Vb = b.value<Vector_Type>();
						// 设置叉乘(三维)结果  
						var.setValue(Va * Vb);
					}
					//矩阵乘法
					if (b.canConvert<Matrix_Type>())
					{
						if (a.canConvert<float>() || a.canConvert<int>())
						{
							float num = a.value<float>();
							Matrix_Type Mb = b.value<Matrix_Type>();
							var.setValue(Mb * num);
							break;
						}
						//a矩阵
						Matrix_Type Ma = a.value<Matrix_Type>();
						//b矩阵
						Matrix_Type Mb = b.value<Matrix_Type>();
						var.setValue(Ma * Mb);


					}

				}break;
				case '/':
				{
					if (type1 == QVariant::Int)
					{
						if (b != 0)
							var.setValue(a.toInt() / b.toInt());
					}
					if (type1 == QVariant::Double)
					{
						var.setValue(a.toDouble() / b.toDouble());
					}
				}break;
				case '.':
				{
					//向量点乘
					if (a.canConvert<Vector_Type>())
					{
						QList<float> Va = a.value<Vector_Type>().data;
						QList<float> Vb = b.value<Vector_Type>().data;
						if (Va.count() == Vb.count()) {
							float dotresult = 0.0;
							for (int i = 0; i < Va.count(); ++i) {
								dotresult += Va[i] * Vb[i];
							}
							var.setValue(dotresult);
						}
						else {
						}
					}
				}break;
				}
		}
		return var;
	}
	//逻辑运算

	bool GraphicsNodeControlBlock::LogicalExpression(QString ExpressionStr)
	{
		QStringList parts = Interpreter::splitExpression(ExpressionStr);
		//!的情况
		if (parts.size() == 2)
		{
			QString rightstr = parts[0];
			if (rightstr == "true")return false;
			else return true;
		}
		else
		{
			QString leftstr = parts[0];
			QString op = parts[1];
			QString right = parts[2];
			QVariant leftvar = VarTypeSolved(leftstr);
			QVariant rightvar = VarTypeSolved(right);
			if (op == "||")
				return leftvar.toBool() || rightvar.toBool();
			else if (op == "&&")
				return leftvar.toBool() && rightvar.toBool();
			else if (op == "!=")
				return leftvar != rightvar;
			else if (op == "==")
				return leftvar == rightvar;
			else if (op == "<")
				return leftvar.toInt() < rightvar.toInt();
			else if (op == ">")
				return leftvar.toInt() > rightvar.toInt();
			else if (op == "!<")
				return !(leftvar.toInt() < rightvar.toInt());
			else if (op == "!>")
				return !(leftvar.toInt() > rightvar.toInt());
		}
		return false;
	}
	//用于得到一个操作数的具体值
	QVariant  GraphicsNodeControlBlock::VarTypeSolved(QString VarStr)
	{
		QVariant var;
		//是函数调用
		if (Interpreter::isFunction(VarStr))
		{
			//函数解析器
			ExpressionParser parser(VarStr, this);
			//解析
			QVariant retVar = parser.parse();
			var.setValue(retVar);
		}
		//端口
		else if (VarStr.count("port") == 1 && !Interpreter::isSubscriptAccess(VarStr))
		{
			//获取端口号
			int index = VarStr.replace("port", "").toInt();
			//获取端口值
			for (auto i : (*(_portList)).keys())
			{
				if (i->GetPortInfo().portIndex == index)
				{
					//从端口数据表中取值
					var.setValue((*_portList)[i]);
					break;
				}
			}
		}//文本输入框
		else if (VarStr.count("input") == 1 && !Interpreter::isSubscriptAccess(VarStr))
		{
			//获取文本号
			int index = VarStr.replace("input", "").toInt();
			//获取文本值
			for (auto i : (*(_inputList)))
			{
				if (i->Info->index == index)
				{
					//从端口数据表中取值
					var.setValue(VarTypeSolved("\"" + i->Info->Text + "\""));
					break;
				}
			}
		}//开关
		else if (VarStr.count("switchbutton") == 1)
		{
			//获取文本号
			int index = VarStr.replace("switchbutton", "").toInt();
			//获取按钮是否点击
			for (auto i : (*(_switchbuttonList)))
			{
				if (i->Info.buttonIndex == index)
				{
					var.setValue(i->Info.IsOpen);
					break;
				}
			}
		}//按钮
		else if (VarStr.contains("button") == 1)
		{
			//获取文本号
			int index = VarStr.replace("button", "").toInt();
			//获取按钮是否点击
			for (auto i : (*(_buttonList)))
			{
				if (i->Info.buttonIndex == index)
				{
					var.setValue(i->Info.Clicked);
					if (i->Info.Clicked)
					{
						i->Info.Clicked = false;
					}
					break;
				}
			}
		}//标签
		else if (VarStr.contains("label") == 1)
		{
			//获取文本号
			int index = VarStr.replace("label", "").toInt();
			for (auto i : (*(_labelList)))
			{
				if (i->Info.index == index)
				{
					var.setValue(i->Info.Text);
					break;
				}
			}
		}
		//向量检测
		else if (Interpreter::isVector(VarStr))
		{
			//向量
			Vector_Type vector;
			//解析向量值
			QString data = VarStr.replace("(", "");
			data = data.replace(")", "");
			QStringList datas = data.split(",");
			for (auto dat : datas)
			{
				vector.data << VarTypeSolved(dat).toFloat();
			}
			var.setValue(vector);
		}
		else if (Interpreter::isString(VarStr))
		{
			QString str;
			if (VarStr.startsWith("\"") && VarStr.endsWith("\"")) {
				str = VarStr.mid(1, VarStr.length() - 2);
			}
			var.setValue(str);
		}
		//矩阵检测
		else if (Interpreter::isMatrix(VarStr))
		{
			//矩阵
			Matrix_Type matrix;
			//解析矩阵值
			QString data = VarStr.replace("{", "");
			data = data.replace("}", "");
			//得到每一个行向量
			QStringList datas = data.split(";");
			QList<Vector_Type> VecList;
			for (auto vector : datas)
			{
				Vector_Type vec;
				QStringList vecStr = vector.split(",");
				for (auto vecdat : vecStr)
				{
					float item = VarTypeSolved(vecdat).toFloat();

					vec.data << item;
				}
				VecList.append(vec);
			}

			matrix.data = VecList;

			//如果向量格式错误，进行补充

			var.setValue(matrix);

		}//下标访问
		else if (Interpreter::isSubscriptAccess(VarStr))
		{
			//取出对象和下标
			auto sResult = Interpreter::extractObjectNameAndIndices(VarStr);
			//一维访问
			if (sResult.second.size() == 1)
			{
				QVariant variant = VarTypeSolved(sResult.first);
				//如果是向量，返回元素
				if (variant.canConvert<Vector_Type>())
				{
					QList<float> Vec = variant.value<Vector_Type>().data;
					if (VarTypeSolved(sResult.second[0]).toInt() < Vec.count() && VarTypeSolved(sResult.second[0]).toInt() >= 0)
					{
						//设置向量元素值
						var.setValue(Vec[VarTypeSolved(sResult.second[0]).toInt()]);
					}
				}
				else if (variant.canConvert<Matrix_Type>())
				{
					QList<Vector_Type> data = variant.value<Matrix_Type >().data;
					int index = VarTypeSolved(sResult.second[0]).toInt();
					if (index < data.count() && index >= 0)
					{
						//设置向量元素值
						if (index < data.count() && index >= 0)
							var.setValue(data[index]);

					}
				}
			}//二维访问（矩阵）
			else if (sResult.second.size() == 2)
			{
				QVariant variant = VarTypeSolved(sResult.first);
				if (variant.canConvert<Matrix_Type>())
				{
					QList<Vector_Type> data = variant.value<Matrix_Type >().data;
					Vector_Type vec;
					if (VarTypeSolved(sResult.second[0]).toInt() < data.count() && VarTypeSolved(sResult.second[0]).toInt() < data.count() >= 0)
					{
						vec = data[VarTypeSolved(sResult.second[0]).toInt()];
						if (VarTypeSolved(sResult.second[1]).toInt() < vec.data.count() >= VarTypeSolved(sResult.second[1]).toInt() < vec.data.count())
							var.setValue(vec.data[VarTypeSolved(sResult.second[1]).toInt()]);
					}
				}

			}
		}
		else if (Interpreter::isInteger(VarStr))
		{
			var.setValue(VarStr.toInt());

		}
		else if (Interpreter::isDecimal(VarStr))
		{
			double f = VarStr.toFloat();
			var.setValue(f);
		}
		else if (Interpreter::isHexadecimal(VarStr))
		{
			bool flag{};
			var.setValue(VarStr.replace("0x", "").toInt(&flag, 16));
		}
		else if (Interpreter::isBool(VarStr))
		{
			var.setValue(Interpreter::stringToBool(VarStr));
		}
		// 表达式左值是变量
		else {
			var = VarMap[VarStr];
		}
		return var;
	}

	//获取端口数据
	QVariant  GraphicsNodeControlBlock::GetPortVar(int index)
	{
		//获取端口值
		for (auto i : _portList->keys())
		{
			if (i->GetPortInfo().portIndex == index)
			{
				//从端口数据表中取值
				return (*_portList)[i];
				break;
			}
		}
		return QVariant();
	}


	GraphicsNodeControlBlock::GraphicsNodeControlBlock()
	{
		(*_portList).insert(nullptr, 22565);
	}
	GraphicsNodeControlBlock::GraphicsNodeControlBlock(GraphicsNode* node) :_node(node)
	{
		//解析端口,添加到端口列表
		for (int i = 0; i < _node->childItems().count(); ++i)
		{
			GraphicsPort* port = dynamic_cast<GraphicsPort*>(_node->childItems()[i]);
			//确定端口值类型
			if (port)
			{
				QVariant var(QVariant::Int);
				_portList->insert(port, Map::PortDataTypeMap[port->GetPortInfo().portDataType]);
				continue;
			}
			GraphicsText* input = dynamic_cast<GraphicsText*>(_node->childItems()[i]);
			if (input)
			{
				_inputList->append(input);
				continue;
			}
			GraphicsChart* chart = dynamic_cast<GraphicsChart*>(_node->childItems()[i]);
			if (chart)
			{
				_chartList->append(chart);
				continue;
			}
			GraphicsButton* button = dynamic_cast<GraphicsButton*>(_node->childItems()[i]);
			if (button)
			{
				_buttonList->append(button);
				continue;
			}
			GraphicsSwitchButton* switchbutton = dynamic_cast<GraphicsSwitchButton*>(_node->childItems()[i]);
			if (switchbutton)
			{
				_switchbuttonList->append(switchbutton);
				continue;
			}
			GraphicsLabel* lab = dynamic_cast<GraphicsLabel*>(_node->childItems()[i]);
			if (lab)
			{
				_labelList->append(lab);
				continue;
			}
		}



		//解析脚本路径
		QFileInfo fileinfo(node->Info.ScriptPath);
		if (fileinfo.exists())
		{
			QFile file(node->Info.ScriptPath);
			file.open(QIODevice::ReadOnly);
			scriptObject.ScriptPath = node->Info.ScriptPath;
			scriptObject.Script = file.readAll();
			file.close();
		}

	}


	QList<GraphicsPort*> GraphicsNodeControlBlock::PortList()
	{
		QList<GraphicsPort*> list;
		for (auto item : _portList->keys())
		{
			list.append(item);
		}
		return list;
	}

	QList<GraphicsText*>* GraphicsNodeControlBlock::InputList()
	{
		return _inputList;
	}

	unsigned GraphicsNodeControlBlock::PortCount()
	{
		return _portList->count();
	}

	GraphicsNode* GraphicsNodeControlBlock::GetNode()
	{
		return _node;
	}

	void GraphicsNodeControlBlock::Execute()
	{
		//程序代码地址生成
		ProgramAddressGeneration();
		//重置PC
		PC = 1;
		//执行,如果正在运行
		while (PC <= CodeAddress.size() && RuningConfig::IsRuning)
		{
			//取PC对应的表达式
			ScriptModule::Expression expression = CodeAddress[PC];
			ExecuteExpression(expression);
			PC++;
		}
		//完成以后给端口设置文本
		for (auto item : _portList->keys())
		{
			QVariant var = (*_portList)[item];
			item->SetPortText(PortAssignor::PortValueParsing(item->GetPortInfo().portDataType, var));
		}
		Executed = true;
	}

	void GraphicsNodeControlBlock::SetPortValue(QVariant var, GraphicsPort* port)
	{
		for (auto item : (*_portList).keys())
		{
			if (item == port)
			{
				(*_portList)[item].setValue(var);
			}
		}
		Updata();
	}

	QVariant GraphicsNodeControlBlock::GetPortValue(GraphicsPort* port)
	{
		QVariant var = (*_portList).value(port);
		Updata();
		return var;
	}

	void GraphicsNodeControlBlock::ProgramAddressGeneration()
	{
		//执行代码控制器
		 //从脚本文件中读取每一行代码放入代码地址表中
		QRegularExpression re("\r\n|\r|\n"); // 匹配所有可能的换行符  
		QStringList lines = scriptObject.Script.split(re);
		int i = 0;
		for (auto line : lines)
		{
			i++;
			ScriptModule::Expression expression(line);
			CodeAddress.insert(i, expression);
		}
		i = 0;
		//解析标号生成虚地址
		for (auto item : CodeAddress)
		{
			i++;
			if (item.type == Label_Exp)
			{
				VirtualAddress.insert(item.code.replace("::", ""), i);
			}
		}
	}

	void GraphicsNodeControlBlock::ExecuteExpression(ScriptModule::Expression expression)
	{
		switch (expression.type)
		{
		case NONE_Exp:
		case Label_Exp:return;
		case Finish_Exp:PC = CodeAddress.size() + 1; break;
			//跳转语句
		case Jump_Exp: {
			//找到goto后面的关键字在虚地址所对应的代码地址
			QString lab = expression.code.replace("GOTO:", "").replace(" ", "");
			int index = VirtualAddress.value(lab, -1);
			//标号不存在
			if (index == -1)
				return;
			//将PC重新设置到标号地址(这个地方之所以PC=index-1是因为PC后面会+1，
			// 这样才能保证程序会从指定标号开始运行)
			PC = index - 1;
		}break;
					 //赋值语句
		case Assignment_Exp: {
			//按照=号拆分成左值和右值
			QStringList lines = Interpreter::splitLogicalExpression(expression.code);
			if (lines.size() != 2)return;
			QString left = lines[0], right = lines[1];
			QVariant rightVar;//右值
			bool flag = Interpreter::isLogicalExpression(right);
			//右值是运算
		  if (Interpreter::isArithmeticExpression(right))
			{
				rightVar = ArithmeticExpression(right);
			}
			//右值是函数调用
			else if (Interpreter::isFunction(right))
			{
			  ExpressionParser parser(expression.code, this);
			  //解析
			  rightVar = parser.parse();
			}// 右值是逻辑表达式
			else if (Interpreter::isLogicalExpression(right))
			{
				rightVar = LogicalExpression(right);
			}// 普通右值
			else
			{
				rightVar = VarTypeSolved(right);
			}
			//左值是端口直接给端口赋值
			if (left.contains("port"))
			{
				//获取端口号
				int index = left.replace("port", "").toInt();
				//设置端口值
				for (auto i : (*_portList).keys())
				{

					if (i->GetPortInfo().portIndex == index)
					{
						//类型转换，将右值转换成端口同类型值
						switch (i->GetPortInfo().portDataType)
						{
						case Int: {

							(*_portList)[i].setValue(rightVar.toInt()); 
						}; break;
						case Float: { (*_portList)[i].setValue(rightVar.toDouble()); }; break;
						case Bool: { (*_portList)[i].setValue(rightVar.toBool()); }; break;
						case String: { (*_portList)[i].setValue(rightVar.toString()); }; break;
						case Bit: { (*_portList)[i].setValue(rightVar.toInt()); }; break;
						case Vector: { (*_portList)[i].setValue(rightVar); }; break;
						case Matrix: { (*_portList)[i].setValue(rightVar); }; break;

						}
						//更新端口
						i->SetPortText(PortAssignor::PortValueParsing(i->GetPortInfo().portDataType, rightVar));
						break;
					}
				}
			}
			else if (left.contains("label"))
			{
				//获取端口号
				int index = left.replace("label", "").toInt();
				//设置端口值
				for (auto i : *_labelList)
				{
					if (i->Info.index == index)
					{
						if (Interpreter::isDecimal(rightVar.toString()))
						{
							float a = rightVar.toFloat();
							i->Info.Text = QString::number(a);
							break;
						}
						i->Info.Text = rightVar.value<QString>();
						break;
					}
				}

			}
			//左值是变量，存放数据到变量表中
			else {
				VarMap[left] = rightVar;
			}

		}break;//判断
		case Judge_Exp:
		{
			QString condition = expression.code.replace("IF", "").replace(" ", "");
			bool flag;
			//逻辑表达式
			if (Interpreter::isArithmeticExpression(condition))
			{
				flag = ArithmeticExpression(condition).toBool();
			}// 右值是逻辑表达式
			else if (Interpreter::isLogicalExpression(condition))
			{
				flag = LogicalExpression(condition);
			}
			else
			{
				flag = VarTypeSolved(condition).toBool();
			}
			//true，执行IF下面的语句，false,跳过下一行语句
			if (!flag)
			{
				PC++;
			}
		}break;
		//自定义处理柄
		case Handle_Exp:
		{
			//判断是不是函数形式function(,,,)
			if (Interpreter::isFunction(expression.code))
			{
				ExpressionParser parser(expression.code, this);
				//解析
				parser.parse();
			}
		}break;
		default:return;
			break;
		}
	}


}
