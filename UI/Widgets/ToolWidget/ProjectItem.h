#ifndef PROJECTITEM_H
#define PROJECTITEM_H

#include <QWidget>

namespace Ui {
class ProjectItem;
}

class ProjectItem : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectItem(QString proName,QString path,QWidget *parent = nullptr);
    ~ProjectItem();
    QString ProjectPath{""};
    QString ProjectName{""};
private:
    Ui::ProjectItem *ui;

};

#endif // PROJECTITEM_H
