#include "Saver.h"

void Globe::Saver::AutoSave(GraphicsView* view)
{
		QJsonObject jsonobj;

		//����GNCB�б�,����GNCB��Ϣ
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
			//�������пؼ�
			for (auto control : node->childItems())
			{
					//�ؼ�
					if(dynamic_cast<GraphicsItem*>(control))
						controls.append(GraphicsItemParser::GraphicsItemToJsonObject(dynamic_cast<GraphicsItem*>(control)));
					//�ı������,
					// TMD,��ʱ�ı���̳й�ϵд���ˣ����Զ���������Ķ������пտ��Ըĸ�
					if (dynamic_cast<GraphicsText*>(control))
						controls.append(GraphicsItemParser::GraphicsItemToJsonObject(dynamic_cast<GraphicsText*>(control)));

			}
			gncbobj["controls"]= controls;
			gncbarr.append(gncbobj);
		}
		jsonobj["gncbList"] = gncbarr;
		//�����˿����ӱ�����������Ϣ
		QJsonArray connectionInfo;
		for (auto connection : view->Manager->GetGNCCB())
		{
			QJsonObject conectionobj;
			conectionobj["port1"] = (int)connection.Block1_Port->GetPortInfo().portNumber;
			conectionobj["port2"] = (int)connection.Block2_Port->GetPortInfo().portNumber;
			connectionInfo.append(conectionobj);
		}
		jsonobj["connection"] = connectionInfo;
		//���������ļ�
		QJsonDocument savefile(jsonobj);
		JsonUtility::saveToJson(savefile, RuningConfig::CurrentRuningPath + "/save/" + "save.json");


}
