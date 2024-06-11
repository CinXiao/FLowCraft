#include "GraphicsPort.h"
namespace GraphicsModule {

	GraphicsPort::GraphicsPort(PortInfo info) :m_PortInfo(info)
	{
		setFlag(QGraphicsItem::ItemIsSelectable, false);
		GraphicsItem::Info.GraphicsItemType = Port;
		m_PortInfo.GraphicsItemType = Port;
	}

	GraphicsPort::~GraphicsPort()
	{}

	QRectF GraphicsPort::boundingRect() const
	{
		return m_PortInfo.backgroundSize;
	}

	void GraphicsPort::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
	{

		//数据端口绘制
		if (m_PortInfo.portType == PortType::DataInput || m_PortInfo.portType == PortType::DataOutput)
		{
			painter->setPen(m_PortInfo.normalBorder);
			if (m_PortInfo.IsConnection)
			{
				painter->setBrush(painter->pen().color());
			}
			painter->drawEllipse(m_PortInfo.backgroundSize);

			//端口提示文字
			QRectF rect = m_PortInfo.backgroundSize;
			QTextOption opt;
			if (m_PortInfo.portType == PortType::DataInput)
			{
				rect.setRect
				(m_PortInfo.backgroundSize.x() + m_PortInfo.backgroundSize.width() + 10
					, m_PortInfo.backgroundSize.y()
					, m_PortInfo.backgroundSize.width() * 3
					, m_PortInfo.backgroundSize.height()
				);
				opt.setAlignment(Qt::AlignLeft);
			}
			else if (m_PortInfo.portType == PortType::DataOutput)
			{
				rect.setRect
				(m_PortInfo.backgroundSize.x() - m_PortInfo.backgroundSize.width() * 3 - 10
					, m_PortInfo.backgroundSize.y()
					, m_PortInfo.backgroundSize.width() * 3
					, m_PortInfo.backgroundSize.height()
				);
				opt.setAlignment(Qt::AlignRight);
			}

			painter->drawText(rect, PortText, opt);
		}//程序控制端口绘制
		else if (m_PortInfo.portType == PortType::ProgramControlInput || m_PortInfo.portType == PortType::ProgramControlOutput)
		{

			painter->setPen(m_PortInfo.normalBorder);
			if (m_PortInfo.IsConnection)
			{
				painter->setBrush(painter->pen().color());
			}
			QPolygonF triangle;
			triangle << QPointF(m_PortInfo.backgroundSize.right(), m_PortInfo.backgroundSize.center().y())
				<< QPointF(m_PortInfo.backgroundSize.left(), m_PortInfo.backgroundSize.top())
				<< QPointF(m_PortInfo.backgroundSize.left(), m_PortInfo.backgroundSize.bottom());
			painter->drawPolygon(triangle);

		}//触发端口绘制
		else if (m_PortInfo.portType == PortType::ProgramControlInput || m_PortInfo.portType == PortType::ProgramControlOutput)
		{


		}


	}
	PortInfo& GraphicsPort::GetPortInfo()
	{
		return m_PortInfo;
	}
	void GraphicsPort::SetPortText(const QString& text)
	{
		PortText = text;                      // 安全地设置PortText 
	}
	QString GraphicsPort::GetPortText() const
	{
		return PortText;                      // 安全地获取PortText 
	}
}