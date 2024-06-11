#include "GraphicsText.h"
namespace GraphicsModule
{
	GraphicsText::GraphicsText(TextInfo info, QGraphicsItem* parent)
		:QGraphicsTextItem(parent)
	{
		*Info = info;
		setDefaultTextColor(QColor(200, 200, 200)); // 设置默认文本颜色为白色 
		setPlainText(Info->Text);
		setPos(Info->backgroundSize.x(), Info->backgroundSize.y());


		//计算文本框宽度
		QFontMetrics metrics(font());
		int width = metrics.size(Qt::TextSingleLine, toPlainText()).width() + 15;// 文本的宽度
		int maxwidth = Info->MaxWidth;
		int setwidth = qMin(maxwidth, qMax((int)width, (int)Info->backgroundSize.width()));
		setTextWidth(setwidth);
	}

	void GraphicsText::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
	{
		Info->Text = this->toPlainText();
		// 首先绘制半透明的矩形框  
		painter->setPen(Qt::NoPen);
		painter->setBrush(Info->BackgroundColor); // 背景颜色
		painter->drawRoundedRect(boundingRect(), 5, 5);
		setDefaultTextColor(Info->TextColor);
		QGraphicsTextItem::paint(painter, option, widget);
	}

	void GraphicsText::focusOutEvent(QFocusEvent* event)
	{  // 取消选中所有文本
		QTextCursor cursor = textCursor();
		cursor.clearSelection();
		setTextCursor(cursor);
		// 当文本项失去焦点时，设置其不再可编辑  
		setTextInteractionFlags(Qt::NoTextInteraction);
		QGraphicsTextItem::focusOutEvent(event);

		//重新计算文本框宽度
		QFontMetrics metrics(font());
		int width = metrics.size(Qt::TextSingleLine, toPlainText()).width() + 15;// 文本的宽度
		int maxwidth = Info->MaxWidth;
		int setwidth = qMin(maxwidth, qMax((int)width, (int)Info->backgroundSize.width()));
		setTextWidth(setwidth);
	}

	void GraphicsText::mousePressEvent(QGraphicsSceneMouseEvent* event)
	{
		this->scene()->clearSelection();

		if (event->button() == Qt::LeftButton) {
			QTextCursor cursor = textCursor();
			cursor.select(QTextCursor::Document);
			setTextCursor(cursor);
		}


	}
	void GraphicsText::keyPressEvent(QKeyEvent* event)
	{
		QFontMetrics metrics(font());
		int width = metrics.size(Qt::TextSingleLine, toPlainText()).width() + 15;// 文本的宽度
		int maxwidth = Info->MaxWidth;
		int setwidth = qMin(maxwidth, qMax((int)width, (int)Info->backgroundSize.width()));
		setTextWidth(setwidth);


		QTextCursor cursor = textCursor(); // 获取当前的文本光标  
		bool cursorMoved = false;

		switch (event->key()) {
		case Qt::Key_Up:
			if (cursor.movePosition(QTextCursor::PreviousBlock)) {
				cursorMoved = true;
			}
			else if (cursor.movePosition(QTextCursor::Up)) {
				cursorMoved = true;
			}
			break;
		case Qt::Key_Down:
			if (cursor.movePosition(QTextCursor::NextBlock)) {
				cursorMoved = true;
			}
			else if (cursor.movePosition(QTextCursor::Down)) {
				cursorMoved = true;
			}
			break;
		case Qt::Key_Left:
			if (cursor.movePosition(QTextCursor::PreviousCharacter)) {
				cursorMoved = true;
			}
			break;
		case Qt::Key_Right:
			if (cursor.movePosition(QTextCursor::NextCharacter)) {
				cursorMoved = true;
			}
			break;
		default:
			// 如果不是方向键，则调用基类处理  
			QGraphicsTextItem::keyPressEvent(event);
			return;
		}

		if (cursorMoved) {
			setTextCursor(cursor); // 应用移动后的光标
		}
		else {
			// 如果光标没有移动，则调用基类处理，以允许其他按键事件得到处理  
			QGraphicsTextItem::keyPressEvent(event);
		}
	}
	QRectF GraphicsText::boundingRect() const
	{
		return QGraphicsTextItem::boundingRect(); // 扩大边界以包含半透明矩形框  
	}

}