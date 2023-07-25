#include "application.h"
#include "ui_application.h"

#include <QMainWindow>
#include <QListWidget>

Application::Application(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Application)
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
