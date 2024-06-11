#include "TemplateItemWidget.h"
#include "ui_TemplateItemWidget.h"


TemplateItemWidget::TemplateItemWidget(QString tempName,QString Description,QStringList tags,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TemplateItemWidget)
{
    ui->setupUi(this);
    ui->templateName->setText(tempName);
    ui->description->setText(Description);
    ui->tag1->setVisible(false);
    QPushButton *btn{ui->tag1};
    btn->setStyleSheet(ui->tag1->styleSheet());
    for(const auto &tag:tags)
    {
        QPushButton *newbtn=new QPushButton(this);
        newbtn->resize(btn->size());
        newbtn->setEnabled(false);
        newbtn->setText(tag);
        newbtn->setStyleSheet(btn->styleSheet());
        newbtn->move(btn->x()+btn->width()+3,btn->y());
        btn=newbtn;
    }

    ui->mask->installEventFilter(this); // 安装事件过滤器
    ui->mask->raise();


}

TemplateItemWidget::~TemplateItemWidget()
{
    delete ui;
}

void TemplateItemWidget::Select()
{
    isSelect=true;
    ui->mask->setStyleSheet("background-color: rgba(0, 0, 0, 5%);"); // 设置20%的灰色背景
    update();
}

void TemplateItemWidget::DisSelect()
{
    isSelect=false;
          ui->mask->setStyleSheet("background-color: transparent;"); // 设置透明背景
    update();
}

bool TemplateItemWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->mask) { // 检查事件是否针对label

        if(!isSelect)
        {
            if (event->type() == QEvent::Enter) { // 鼠标进入事件
                ui->mask->setStyleSheet("background-color: rgba(0, 0, 0, 5%);"); // 设置20%的灰色背景
                return true; // 事件已处理
            } else if (event->type() == QEvent::Leave) { // 鼠标离开事件
                ui->mask->setStyleSheet("background-color: transparent;"); // 设置透明背景
                return true; // 事件已处理
            }

        }

        if (event->type() == QEvent::MouseButtonPress) { // 鼠标点击事件
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent->button() == Qt::LeftButton) { // 如果是左键点击
                Selected(); // 调用槽函数处理点击事件
                return true; // 事件已处理
            }
        }

    }
    // 标准事件处理
    return QDialog::eventFilter(obj, event);
}

