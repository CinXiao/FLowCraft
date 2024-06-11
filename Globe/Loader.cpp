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

    // 解析JSON文档
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "Failed to parse JSON:" << parseError.errorString();
        return;
    }

    // 获取JSON对象
    if (!jsonDoc.isObject()) {
        qWarning() << "JSON document is not an object";
        return;
    }
    QJsonObject jsonObj = jsonDoc.object();
    //构建GNCB
    if (jsonObj.contains("gncbList"))
    {
        QJsonArray gncbarr = jsonObj["gncbList"].toArray();
        //遍历每个GNCB添加到场景
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
    //连接关系,进行端口连接
    if (jsonObj.contains("connection"))
    {
        QJsonArray connection = jsonObj["connection"].toArray();
        //遍历每个GNCB添加到场景
        for (auto item : connection)
        {
            QJsonObject itemobj = item.toObject();
            int portid1 = itemobj["port1"].toInt();
            int portid2 = itemobj["port2"].toInt();
            view->Manager->ConnectPortById(portid1, portid2);
        }
    }

}
