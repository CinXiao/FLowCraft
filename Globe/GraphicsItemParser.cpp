#include "GraphicsItemParser.h"

QJsonObject Globe::GraphicsItemParser::GraphicsItemToJsonObject(GraphicsItem* item)
{
    QJsonObject obj;
    obj["controlType"] = Map::GraphicsItemTypeNameMap[item->Info.GraphicsItemType];
    QJsonObject info;
    switch (item->Info.GraphicsItemType)
	{
    case Null:break;
    case Start:
    case Node:
    {
        GraphicsNode* node = dynamic_cast<GraphicsNode*>(item);
        info["nodeName"] = node->Info.nodeName;
        info["normalBorder"] = node->Info.normalBorder.color().name(QColor::HexArgb);
        info["selectBorder"] = node->Info.selectBorder.color().name(QColor::HexArgb);
        info["normalBrush"] = node->Info.normalBrush.color().name(QColor::HexArgb);
        info["selectBrush"] = node->Info.selectBrush.color().name(QColor::HexArgb);
        info["backgroundColor1"] = node->Info.backgroundColor1.name(QColor::HexArgb);
        info["backgroundColor2"] = node->Info.backgroundColor2.name(QColor::HexArgb);
        info["titleBackgroundColor1"] = node->Info.titleBackgroundColor1.name(QColor::HexArgb);
        info["titleBackgroundColor2"] = node->Info.titleBackgroundColor2.name(QColor::HexArgb);
        info["backgroundColorGradient"] = node->Info.backgroundColorGradient;
        info["titleBackgroundColorGradient"] = node->Info.titleBackgroundColorGradient;
        QString scpath= node->Info.ScriptPath.replace(RuningConfig::CurrentRuningPath, "");
        // 找到第一个斜杠的位置
        int firstSlashIndex = scpath.indexOf("/");
        if (firstSlashIndex != -1) {
            // 仅替换第一个斜杠
            scpath.replace(firstSlashIndex, 1, "");
        }
        info["scriptPath"] = scpath;
        info["radius"] = node->Info.radius;
        QJsonArray titlesize;
        titlesize.append(node->Info.titleSize.x());
        titlesize.append(node->Info.titleSize.y());
        titlesize.append(node->Info.titleSize.width());
        titlesize.append(node->Info.titleSize.height());
        info["titleSize"] = titlesize;
        QJsonArray backsize;
        backsize.append(node->Info.backgroundSize.x());
        backsize.append(node->Info.backgroundSize.y());
        backsize.append(node->Info.backgroundSize.width());
        backsize.append(node->Info.backgroundSize.height());
        info["backgroundSize"] = backsize;
    }
        break;
    case Chart:
    {
        GraphicsChart* chart = dynamic_cast<GraphicsChart*>(item);
        QJsonArray chartSize;
        chartSize.append(chart->Info.RectSize.x());
        chartSize.append(chart->Info.RectSize.y());
        chartSize.append(chart->Info.RectSize.width());
        chartSize.append(chart->Info.RectSize.height());
        info["chartSize"] = chartSize;
        info["chatyType"] = Map::ChartTypeNameMap[chart->Info.chatyType];
        info["axisColor"] = chart->Info.axisColor.name(QColor::HexArgb);
        info["lineColor"] = chart->Info.lineColor.name(QColor::HexArgb);
        info["drawPoint"] = chart->Info.drawPoint;
        info["drawLine"] = chart->Info.drawLine;
        info["pointColor"] = chart->Info.pointColor.name(QColor::HexArgb);
        info["pointSize"] = chart->Info.pointSize;
        info["chartIndex"] = chart->Info.chartIndex;
    }
    break;
    case Button:
    {
        GraphicsButton* btn = dynamic_cast<GraphicsButton*>(item);
        QJsonArray btnSize;
        btnSize.append(btn->Info.buttonSize.x());
        btnSize.append(btn->Info.buttonSize.y());
        btnSize.append(btn->Info.buttonSize.width());
        btnSize.append(btn->Info.buttonSize.height());

        info["buttonText"] = btn->Info.buttonText;
        info["buttonTextColor"] = btn->Info.buttonTextColor.name(QColor::HexArgb);
        info["buttonTextPressColor"] = btn->Info.buttonTextPressColor.name(QColor::HexArgb);
        info["buttonColor"] = btn->Info.buttonColor.name(QColor::HexArgb);
        info["buttonPressColor"] = btn->Info.buttonPressColor.name(QColor::HexArgb);
        info["buttonIndex"] = btn->Info.buttonIndex;

        
    }
        break;
    case SwitchButton: 
        {
        GraphicsSwitchButton* swbtn = dynamic_cast<GraphicsSwitchButton*>(item);
        QJsonArray switchButtonSize;
        switchButtonSize.append(swbtn->Info.switchButtonSize.x());
        switchButtonSize.append(swbtn->Info.switchButtonSize.y());
        switchButtonSize.append(swbtn->Info.switchButtonSize.width());
        switchButtonSize.append(swbtn->Info.switchButtonSize.height());
        info["switchButtonSize"] = switchButtonSize;
        info["buttonColor"] = swbtn->Info.buttonColor.name(QColor::HexArgb);
        info["buttonOpenColor"] = swbtn->Info.buttonOpenColor.name(QColor::HexArgb);
        info["switchColor"] = swbtn->Info.switchColor.name(QColor::HexArgb);
        info["index"] = swbtn->Info.buttonIndex;
        info["text"] = swbtn->Info.text;
        }
        break;
    case Text:
    {
        
        
        
    }
        break;
    case Line:
        break;
    case Group:
        break;
    case Port:
    {
        GraphicsPort* port = dynamic_cast<GraphicsPort*>(item);
        QJsonArray backsize;
        backsize.append(port->GetPortInfo().backgroundSize.x());
        backsize.append(port->GetPortInfo().backgroundSize.y());
        backsize.append(port->GetPortInfo().backgroundSize.width());
        backsize.append(port->GetPortInfo().backgroundSize.height());
        info["size"] = backsize;
        info["dataType"] =Map::PortDataTypeNameMap[port->GetPortInfo().portDataType];
        info["portType"] = Map::PortTypeNameMap[port->GetPortInfo().portType];
        info["index"] =(int) port->GetPortInfo().portIndex;
        info["portNumber"] = (int)port->GetPortInfo().portNumber;
    }
        break;
    case PictureBox:
    {
        GraphicsPictureBox* pic = dynamic_cast<GraphicsPictureBox*>(item);
        QJsonArray imageSize;
        imageSize.append(pic->info.backgroundSize.x());
        imageSize.append(pic->info.backgroundSize.y());
        imageSize.append(pic->info.imgSize.width());
        imageSize.append(pic->info.imgSize.height());
        info["imageSize"] = imageSize;
        QString path = pic->info.imgPath.replace(RuningConfig::CurrentRuningPath, "");
        info["imagePath"] = path;
    }
    break;
    case Label:
    {
        GraphicsLabel* lab = dynamic_cast<GraphicsLabel*>(item);
        QJsonArray backsize;
        backsize.append(lab->Info.backgroundSize.x());
        backsize.append(lab->Info.backgroundSize.y());
        backsize.append(lab->Info.backgroundSize.width());
        backsize.append(lab->Info.backgroundSize.height());
        info["size"] = backsize;
        info["backColor"] = lab->Info.BackgroundColor.name(QColor::HexArgb);
        info["index"] = lab->Info.index;
        info["text"] = lab->Info.Text;
        info["textColor"] = lab->Info.TextColor.name(QColor::HexArgb);
        info["bold"] = lab->Info.isbold;
        info["textSize"] =(int) lab->Info.textSize;

    }
        break;
    default:
        qDebug() << "Unknown type";
        break;
	}
    obj["info"] = info;
    return obj;
}

QJsonObject Globe::GraphicsItemParser::GraphicsItemToJsonObject(GraphicsText* text)
{
    QJsonObject obj;
    obj["controlType"] = Map::GraphicsItemTypeNameMap[text->Info->GraphicsItemType];
    QJsonObject info;
    if(text)
    {
        QJsonArray backsize;
        backsize.append(text->Info->backgroundSize.x());
        backsize.append(text->Info->backgroundSize.y());
        backsize.append(text->Info->backgroundSize.width());
        backsize.append(text->Info->backgroundSize.height());
        info["size"] = backsize;
        info["backColor"] = text->Info->BackgroundColor.name(QColor::HexArgb);
        info["text"] = text->Info->Text;
        info["index"] = text->Info->index;
    }
    obj["info"] = info;
    return obj;
}
