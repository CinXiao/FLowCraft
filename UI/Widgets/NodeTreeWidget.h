#pragma once

#include <QTreeWidget>  
#include <QTreeWidgetItem>  
#include <QMimeData>  
#include <QDrag>  
#include <QMouseEvent>  
#include <QDir>  
#include <QFileInfo> 
#include<QMenu>
#include<QHeaderView>
#include<qdebug.h>
#include<QLineEdit>
#include"../../Globe/RuningConfig.h"
using namespace Globe;
class NodeTreeWidget :public QTreeWidget
{
public:
	NodeTreeWidget(QWidget* parent = nullptr);
	void populateTree(const QDir& dir);



private:
	void populateTree(const QDir& dir, QTreeWidgetItem* parentItem);
	QIcon folderIcon{ ":/NodeData/icon/folder.png" }; // 文件夹图标  
	QIcon fileIcon{ ":/NodeData/icon/nodes.png" };   // 文件图标
	QIcon scriptIcon{ ":/NodeData/icon/code.png" };   // 脚本图标
	QIcon pictureIcon{ ":/NodeData/icon/picture.png" };   // 图片图标
	QIcon jsonIcon{ ":/NodeData/icon/json.png" };   // json图标

	QIcon renameIcon{ ":/NodeData/icon/rename.png" };
	QIcon copyIcon{ ":/NodeData/icon/copy.png" };
	QIcon pasteIcon{ ":/NodeData/icon/paste.png" };
	QIcon deleteIcon{ ":/NodeData/icon/delete.png" };

	void mousePressEvent(QMouseEvent* event);


protected:
	bool dropMimeData(QTreeWidgetItem* parent, int index, const QMimeData* data, Qt::DropAction action) override;
	QMimeData* mimeData(const QList<QTreeWidgetItem*>& items) const override;
	QDir targetDir{};
	QString clipboard{ "" };//剪贴盘，用于存放复制的文件或者路径



};
