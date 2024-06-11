#include "Saver.h"

void Globe::Saver::AutoSave(GraphicsView* view)
{
		QJsonObject jsonobj;

		//遍历GNCB列表,保存GNCB信息
		QJsonArray gncbarr;
		for (auto gncb : view->Manager->GetGNCBList())
		{

			QJsonObject gncbobj;
			GraphicsNode* node = gncb.GetNode();
			gncbobj["x"] = node->pos().x();
			gncbobj["y"] = node->pos().y();
			QJsonObject maincontrol;
			maincontrol["type"] = "";
			maincontrol["info"] = "";
			gncbobj["mainControl"]= GraphicsItemParser::GraphicsItemToJsonObject(node);
			QJsonArray controls;
			//遍历所有控件
			for (auto control : node->childItems())
			{
					//控件
					if(dynamic_cast<GraphicsItem*>(control))
						controls.append(GraphicsItemParser::GraphicsItemToJsonObject(dynamic_cast<GraphicsItem*>(control)));
					//文本输入框,
					// TMD,当时文本框继承关系写错了，所以多出来这样的东西，有空可以改改
					if (dynamic_cast<GraphicsText*>(control))
						controls.append(GraphicsItemParser::GraphicsItemToJsonObject(dynamic_cast<GraphicsText*>(control)));

			}
			gncbobj["controls"]= controls;
			gncbarr.append(gncbobj);
		}
		jsonobj["gncbList"] = gncbarr;
		//遍历端口连接表，保存连接信息
		QJsonArray connectionInfo;
		for (auto connection : view->Manager->GetGNCCB())
		{
			QJsonObject conectionobj;
			conectionobj["port1"] = (int)connection.Block1_Port->GetPortInfo().portNumber;
			conectionobj["port2"] = (int)connection.Block2_Port->GetPortInfo().portNumber;
			connectionInfo.append(conectionobj);
		}
		jsonobj["connection"] = connectionInfo;
		//创建保存文件
		QJsonDocument savefile(jsonobj);
		JsonUtility::saveToJson(savefile, RuningConfig::CurrentRuningPath + "/save/" + "save.json");


}
