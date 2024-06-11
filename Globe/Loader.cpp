#include "Loader.h"

void Globe::Loader::LoadView(GraphicsView* view)
{

    QString fileName = RuningConfig::CurrentRuningPath+"\\save\\save.json";
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }
    QByteArray jsonData = file.readAll();
    file.close();

    // ����JSON�ĵ�
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "Failed to parse JSON:" << parseError.errorString();
        return;
    }

    // ��ȡJSON����
    if (!jsonDoc.isObject()) {
        qWarning() << "JSON document is not an object";
        return;
    }
    QJsonObject jsonObj = jsonDoc.object();
    //����GNCB
    if (jsonObj.contains("gncbList"))
    {
        QJsonArray gncbarr = jsonObj["gncbList"].toArray();
        //����ÿ��GNCB��ӵ�����
        for (auto item : gncbarr)
        {
            QJsonObject itemobj = item.toObject();
            GraphicsItemInfoConfig config(itemobj);
            QGraphicsItem*graphicsItem=view->ItemCreator->CreatGraphicsItem({ item.toObject()});
            view->Manager->AddItem(graphicsItem);
            int x=itemobj["x"].toInt();
            int y = itemobj["y"].toInt();
            graphicsItem->setPos(x,y);
        }
    }
    //���ӹ�ϵ,���ж˿�����
    if (jsonObj.contains("connection"))
    {
        QJsonArray connection = jsonObj["connection"].toArray();
        //����ÿ��GNCB��ӵ�����
        for (auto item : connection)
        {
            QJsonObject itemobj = item.toObject();
            int portid1 = itemobj["port1"].toInt();
            int portid2 = itemobj["port2"].toInt();
            view->Manager->ConnectPortById(portid1, portid2);
        }
    }

}
