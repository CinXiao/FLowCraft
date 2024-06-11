#ifndef TEMPLATEITEMWIDGET_H
#define TEMPLATEITEMWIDGET_H

#include <QPalette>
#include <QDialog>
#include<QEvent>
#include<QMouseEvent>
namespace Ui {
class TemplateItemWidget;
}

class TemplateItemWidget : public QDialog
{
    Q_OBJECT

public:
    explicit TemplateItemWidget(QString tempName,QString Description,QStringList tags,QWidget *parent = nullptr);
    ~TemplateItemWidget();
    void Select();
    void DisSelect();
    QString templatePath{""};
private:
    Ui::TemplateItemWidget *ui;
    bool isSelect{false};

protected:
    bool  eventFilter(QObject *obj, QEvent *event)override;
    bool isMouseOver; // 用于跟踪鼠标是否在窗口上
    QColor hoverColor{Qt::gray}; // 鼠标悬停时的背景颜色
    QColor normalColor{Qt::white}; // 正常状态的背景颜色

signals:
    void Selected();
};

#endif // TEMPLATEITEMWIDGET_H
