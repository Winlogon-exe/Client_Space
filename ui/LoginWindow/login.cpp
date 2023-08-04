
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
    
}




void Login::on_lineEdit_username_editingFinished()
{

}




void Login::on_lineEdit_password_editingFinished()
{

}

