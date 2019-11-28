#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include "rep_RaftProtocol_merged.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    RaftProtocolReplica *replica;
    QRemoteObjectNode *node;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void showError(QRemoteObjectNode::ErrorCode errorCode);
    void on_pushButton_connect_clicked();
    void isLeader(bool val);
    void on_pushButton_send_clicked();
    void stateChanged(QRemoteObjectReplica::State state, QRemoteObjectReplica::State oldState);

    void on_pushButton_disconnect_clicked();

private:
    Ui::Widget *ui;
};


#endif // WIDGET_H
