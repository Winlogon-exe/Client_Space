#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include <QListWidget>
#include<QTextEdit>

#include"client/client.h"
#include"client/run_client.h"


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

    void on_addChannel_clicked();

private:
    Ui::Application *ui;
    QListWidget *channelListWidget;
    QTextEdit *messageDisplayWidget;
    QLineEdit *messageInputWidget;
    QVector<QString> channels;
    QMap<QString, QVector<QString>> messages;
    int currentChannelIndex;

    void addChannel(const QString& channelName);
    std::shared_ptr<Client> client;  // Поле для хранения клиента
};
#endif // APPLICATION_H
