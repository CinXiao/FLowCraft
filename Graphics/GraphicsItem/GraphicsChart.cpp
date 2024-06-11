#include "GraphicsChart.h"
namespace GraphicsModule {


	GraphicsChart::GraphicsChart(ChartInfo info) :Info(info)
	{

		GraphicsItem::Info.GraphicsItemType = Chart;
	}

	QRectF GraphicsChart::boundingRect() const
	{


		return Info.RectSize;
	}

	void GraphicsChart::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
	{

		painter->setPen(Info.axisColor); // 设置画笔颜色坐标颜色  
		// 折线画坐标系  
		if (Info.chatyType == Straight)
		{
			// 获取获取图表的大小
			QRectF chartRect = Info.RectSize;
			// 绘制X轴  
			painter->drawLine(chartRect.left(), chartRect.center().y(), chartRect.right(), chartRect.center().y());
			//绘制Y轴
			painter->drawLine(chartRect.center().x(), chartRect.top(), chartRect.center().x(), chartRect.bottom());

			//计算膨胀系数
			//遍历数据队列找到绝对值最大值（离远点最远的点）
			QPointF abspoint{ 0,0 };
			qreal maxDistance = qSqrt(abspoint.x() * abspoint.x() + abspoint.y() * abspoint.y());
			for (auto i : Info.DataList)
			{
				qreal distance = qSqrt(i.x() * i.x() + i.y() * i.y());
				if (distance > maxDistance) {
					abspoint = i;
					maxDistance = distance;
				}
			}
			//计算膨胀系数
			QPointF targetpos;
			targetpos = { chartRect.center().x() + abspoint.x() * Info.stepDistance,chartRect.center().y() - abspoint.y() * Info.stepDistance };
			while (!Info.RectSize.contains(targetpos))
			{
				targetpos = { chartRect.center().x() + abspoint.x() * Info.stepDistance,chartRect.center().y() - abspoint.y() * Info.stepDistance };
				Info.stepDistance /= 2;
			}


			//起始点
			QPointF derive{ 0,0 };
			if (Info.DataList.count() > 0)
			{
				//起始点
				derive = { chartRect.center().x() + Info.DataList[0].x() * Info.stepDistance,chartRect.center().y() - Info.DataList[0].y() * Info.stepDistance };
			}
			QList<QPoint> points;
			for (auto data : Info.DataList)
			{
				QPointF pos1{ derive.x(),derive.y() };
				QPointF pos2{ chartRect.center().x() + data.x() * Info.stepDistance,chartRect.center().y() - data.y() * Info.stepDistance };
				if (!Info.RectSize.contains(derive) || points.contains(derive.toPoint()))
				{
					derive = pos2;
					continue;
				}
				//画点、画线
				if (Info.drawPoint)
				{
					painter->setPen(Info.pointColor);
					painter->drawEllipse(derive, 2, 2);
				}
				if (Info.drawLine)
				{
					painter->setPen(Info.lineColor);
					painter->drawLine(pos1, pos2);
				}
				//插入到已画集合
				points.append(derive.toPoint());
				derive = pos2;
			}

		}//方波图
		else if (Info.chatyType == SquareWave)
		{
			//步进值为20
			Info.stepDistance = 20;
			// 获取获取图表的大小
			QRectF chartRect = Info.RectSize;

			QPointF derive{ chartRect.left(),chartRect.bottom() };
			// 绘制Y轴 (左下角)
			painter->drawLine(chartRect.left(), chartRect.top(), derive.x(), derive.y());
			//绘制X轴 (左下角)
			painter->drawLine(derive.x(), derive.y(), chartRect.right(), chartRect.bottom());
			int count = 0;
			//方波图只画线
			for (auto data : Info.DataList)
			{
				float value = data.y();
				QPointF pos1, pos2;
				float y{ 0 };
				//Y为1
				if (value == 1)
				{
					y = derive.y() - Info.RectSize.height() / 2;
				}
				//Y为0
				if (value == 0)
				{
					y = derive.y() - 3;
				}
				//计算pos1,pos2
				pos1 = { derive.x() + count * Info.stepDistance,y };
				pos2 = { pos1.x() + Info.stepDistance,pos1.y() };

				//先画横线
				//获取后一个数据
				if (count < Info.DataList.count() - 1)
				{
					//获取后一个数据
					if (Info.DataList[count + 1].y() != data.y())
					{
						if (data.y() == 0)
						{
							//向上画线
							QPointF uppos{ pos2.x(),pos2.y() + 3 - Info.RectSize.height() / 2 };
							painter->drawLine(pos2, uppos);
						}
						if (data.y() == 1)
						{
							//向下画线
							QPointF downpos{ pos2.x(),pos2.y() - 3 + Info.RectSize.height() / 2 };
							painter->drawLine(pos2, downpos);
						}
					}
				}
				//画线
				painter->setPen(Info.lineColor);
				painter->drawLine(pos1, pos2);

				count++;
			}
		}



	}

	GraphicsChart::~GraphicsChart()
	{}
}