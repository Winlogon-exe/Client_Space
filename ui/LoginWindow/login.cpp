
#include <QtSql> // Для работы с модулем Qt SQL
#include <QSqlDatabase> // Для создания объекта базы данных
#include <QDebug> // Для вывода отладочной информации
#include<QMessageBox>
#include <QRegularExpression>

#include "ui_login.h"
#include "login.h"
#include "mainwindow.h"
#include"application.h"


Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    isFieldsValid = false; // вход
}

Login::~Login()
{
    delete ui;
}

//text "хотите войти?"
void  Login::on_pushButton_clicked()
{
    mainnwindow = std::make_unique<MainWindow>();
    mainnwindow->show();
    this->close();
}

//Login
void Login::on_button_continue_reg_clicked()
{
    if(isFieldsValid)
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("127.0.0.1");
        db.setDatabaseName("Space");
        db.setUserName("root");
        db.setPassword("winlogon991991_");

        if (!db.open())
        {
            QMessageBox::critical(NULL, QObject::tr("Ошибка"), db.lastError().text());
            return;
        }

        // Получение введенных пользователем данных
        QString username = ui->text_username_reg->text();
        QString password = ui->text_password_reg->text();

        // Создание SQL-запроса INSERT
        QSqlQuery query;
        query.prepare("INSERT INTO users (username, email, password) VALUES (:username, :email, :password)");
        query.bindValue(":username", username);
        query.bindValue(":password", password);

        if (!query.exec())
        {
            QMessageBox::critical(NULL, QObject::tr("Ошибка"), query.lastError().text());
        }
        else
        {
            application_window->show();
            db.close();
            this->close();
        }

    }
    else
    {
        // Вывод сообщения об ошибке или предупреждения пользователю
        ui->lineEdit_empty->setText("Заполните все поля");
        ui->lineEdit_empty->setStyleSheet("color: red;");
        ui->lineEdit_empty->setVisible(true);
    }
}




void Login::on_lineEdit_username_editingFinished()
{

}




void Login::on_lineEdit_password_editingFinished()
{

}

