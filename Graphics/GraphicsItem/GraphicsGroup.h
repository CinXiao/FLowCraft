#ifndef QGRAPHICSITEMGROUP_H
#define QGRAPHICSITEMGROUP_H
#include<QGraphicsItemGroup>
#include <QStyleOptionGraphicsItem> 
#include<QPainter>
#include"../Info/GroupInfo.h"
#include"GraphicsItem.h"
namespace GraphicsModule 
{
    class GraphicsGroup :public QGraphicsItemGroup
	{
	public:
        GraphicsGroup(GroupInfo info=GroupInfo(),QGraphicsItem* parent = nullptr);
		void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

        GroupInfo Info;
	};
}

#endif // QGRAPHICSITEMGROUP_H
