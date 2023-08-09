#include "application.h"
#include "ui_application.h"

#include <QMainWindow>
#include <QListWidget>

Application::Application(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Application),
    channelListWidget(nullptr),
    messageDisplayWidget(nullptr),
    messageInputWidget(nullptr),
    currentChannelIndex(-1)
{
    ui->setupUi(this);
    // Инициализация и подключение виджетов
    channelListWidget = ui->channelListWidget;
    messageDisplayWidget = ui->textEditMessageDisplay;
    messageInputWidget = ui->lineEditMessageInput;

    channelListWidget->setStyleSheet("background-color: #36393F; color: #FFFFFF;");
    messageDisplayWidget->setStyleSheet("background-color: #36393F; color: #FFFFFF;");
    messageInputWidget->setStyleSheet("background-color: #36393F; color: #FFFFFF;");

    channelListWidget->addItem("Общий");
    channelListWidget->addItem("Разработка");
    channelListWidget->addItem("Оффтоп");
}

Application::~Application()
{
    delete ui;

}

void Application::on_channelListWidget_itemClicked(QListWidgetItem *item)
{
    int index = channelListWidget->currentRow();

    if (index >= 0 && index < channels.size()) {
        currentChannelIndex = index;
        QString channelName = channels.at(currentChannelIndex);

        messageDisplayWidget->clear();
        QVector<QString> channelMessages = messages.value(channelName);
        for (const QString& message : channelMessages) {
            messageDisplayWidget->append(message);
        }
    }
}

void Application::on_lineEditMessageInput_returnPressed()
{
    QString content = messageInputWidget->text().trimmed();


        QString channelName = channels.at(currentChannelIndex);

        client->sendMessage(content.toStdString());
        messageInputWidget->clear();

}

void Application::addChannel(const QString& channelName)
{
    if (!channels.contains(channelName)) {
        channels.append(channelName);
        messages.insert(channelName, QVector<QString>());
        channelListWidget->addItem(channelName);
    }
}

