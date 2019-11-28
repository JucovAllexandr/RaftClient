#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    replica = nullptr;
    node = nullptr;

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
        if(!node){
            node = new QRemoteObjectNode(this);
            connect(node, &QRemoteObjectNode::error, this, &Widget::showError);
        }

        if(node->connectToNode(QUrl("tcp://"+ui->lineEdit_url->text()))){
            replica = node->acquire<RaftProtocolReplica>();
            connect(replica, &RaftProtocolReplica::stateChanged, this, &Widget::stateChanged);
            connect(replica, &RaftProtocolReplica::isLeader, this, &Widget::isLeader);

        }
    }
}

void Widget::isLeader(bool val)
{
    if(!val){
        QMessageBox::warning(this, "Warning!", "This server is not a leader");
    }
}


void Widget::on_pushButton_send_clicked()
{
    if(replica){
        if(!ui->lineEdit_data->text().isEmpty()){
            qDebug()<<"Emit AppendString";
            emit replica->AppendString(ui->lineEdit_data->text());
        }
    }
}

void Widget::stateChanged(QRemoteObjectReplica::State state, QRemoteObjectReplica::State oldState)
{
    if(state == QRemoteObjectReplica::State::Valid){
        replica->checkLeader();
    }
}

void Widget::on_pushButton_disconnect_clicked()
{
    if(node){
    disconnect(node, &QRemoteObjectNode::error, this, &Widget::showError);
    disconnect(replica, &RaftProtocolReplica::stateChanged, this, &Widget::stateChanged);
    disconnect(replica, &RaftProtocolReplica::isLeader, this, &Widget::isLeader);

    delete node;
    node = nullptr;
    }
}
