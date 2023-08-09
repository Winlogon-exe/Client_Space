#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include <QListWidget>
#include<QTextEdit>

#include"client/client.h"


namespace Ui {
class Application;
}

class Application : public QMainWindow
{
    Q_OBJECT

public:
    explicit Application(QWidget *parent = nullptr);
    ~Application();

private slots:
    void on_channelListWidget_itemClicked(QListWidgetItem *item);

    void on_lineEditMessageInput_returnPressed();

private:
    Ui::Application *ui;
    QListWidget *channelListWidget;
    QTextEdit *messageDisplayWidget;
    QLineEdit *messageInputWidget;
    QVector<QString> channels;
    QMap<QString, QVector<QString>> messages;
    int currentChannelIndex;

    void addChannel(const QString& channelName);

    Client *client;
};
#endif // APPLICATION_H
