#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include <QListWidget>
#include<QTextEdit>


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

private:
    Ui::Application *ui;
    QListWidget *channelListWidget;
    QTextEdit *messageDisplayWidget;
    QLineEdit *messageInputWidget;
    QVector<QString> channels;
    QMap<QString, QVector<QString>> messages;
    int currentChannelIndex;

    void addChannel(const QString& channelName);
};
#endif // APPLICATION_H
