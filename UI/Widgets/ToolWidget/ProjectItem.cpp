#include "ProjectItem.h"
#include "ui_ProjectItem.h"

#include <QMouseEvent>

ProjectItem::ProjectItem(QString proName,QString path,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectItem)
{
    ui->setupUi(this);
    ProjectPath=path;
    ProjectName=proName;
    ui->ProjectName->setText(ProjectName);
    ui->projectPath->setText(ProjectPath);
}

ProjectItem::~ProjectItem()
{
    delete ui;
}
