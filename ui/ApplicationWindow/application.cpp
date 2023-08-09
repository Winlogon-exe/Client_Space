#include "application.h"
#include "ui_application.h"

#include <QMainWindow>
#include <QListWidget>
#include <QInputDialog>
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

    if (!content.isEmpty() && currentChannelIndex >= 0 && currentChannelIndex < channels.size()) {
        QString channelName = channels.at(currentChannelIndex);

        messages[channelName].append(content);

        messageDisplayWidget->append(content);

        client->sendMessage(content.toStdString());
        messageInputWidget->clear();
    }
}

void Application::addChannel(const QString& channelName)
{
    if (!channels.contains(channelName)) {
        channels.append(channelName);
        messages.insert(channelName, QVector<QString>());
        channelListWidget->addItem(channelName);
    }
}


void Application::on_addChannel_clicked()
{
    QString newChannelName = QInputDialog::getText(this, "Добавить канал", "Введите имя нового канала:", QLineEdit::Normal, "");

    if (!newChannelName.isEmpty()) {
        addChannel(newChannelName);
    }
}

