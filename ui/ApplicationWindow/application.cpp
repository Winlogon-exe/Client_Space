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
}

Application::~Application()
{
    delete ui;

}
