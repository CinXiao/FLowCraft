#ifndef CREATNEWPROJECT_H
#define CREATNEWPROJECT_H

#include <QDialog>
#include<QPushButton>
#include"../Widgets/ToolWidget/TemplateItemWidget.h"
namespace Ui {
class CreatNewProject;
}

class CreatNewProject : public QDialog
{
    Q_OBJECT

public:
    explicit CreatNewProject(QWidget *parent = nullptr);
    ~CreatNewProject();


private slots:
    void on_selectPath_clicked();

    void on_pushButton_3_clicked();
signals:
    void stringReturned(const QString &str);

private:
    Ui::CreatNewProject *ui;
    QList< TemplateItemWidget *> QListWidgetItemList;
    TemplateItemWidget*selectTemplate{nullptr};

};

#endif // CREATNEWPROJECT_H
