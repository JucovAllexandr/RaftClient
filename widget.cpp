#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(&node, &QRemoteObjectNode::error, this, &Widget::showError);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::showError(QRemoteObjectNode::ErrorCode errorCode)
{
    QMessageBox::warning(this, "QRemote object error code", QString::number(errorCode));
}


void Widget::on_pushButton_connect_clicked()
{
    if(!ui->lineEdit_url->text().isEmpty()){
        if(node.connectToNode(QUrl("tcp://"+ui->lineEdit_url->text()))){
            replica = node.acquire<RaftProtocolReplica>();
        }
    }
}

