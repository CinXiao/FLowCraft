#ifndef NODEEDITORWIDGET_H
#define NODEEDITORWIDGET_H

#include <QWidget>
#include <QDir>
#include <QTreeWidgetItem>
#include<QFileinfo>
#include"../NodeTreeWidget.h"
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include"../../../Graphics/GraphicsItem/GraphicsNode.h"
namespace Ui {
	class NodeEditorWidget;
}

class NodeEditorWidget : public QWidget
{
	Q_OBJECT

public:
	explicit NodeEditorWidget(QWidget* parent = nullptr);
	~NodeEditorWidget();

	QGraphicsItem* PreItem{ nullptr };
	QString NodePath{};
	QString ScriptPath{};
    QGraphicsScene* scene{nullptr};
private slots:
    void on_Refresh_clicked();

protected:
    void keyPressEvent(QKeyEvent *event) override;


private:
	Ui::NodeEditorWidget* ui;
};

#endif // NODEEDITORWIDGET_H
