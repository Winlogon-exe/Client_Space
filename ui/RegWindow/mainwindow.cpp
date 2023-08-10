#include <QtSql> // Для работы с модулем Qt SQL
#include <QSqlDatabase> // Для создания объекта базы данных
#include <QDebug> // Для вывода отладочной информации
#include<QMessageBox>
#include <QRegularExpression>
#include<QWindow>


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"login.h"
#include"application.h"
#include"client/run_client.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // При регистрации открывается форма Application
    applicationWindow = std::make_unique<Application>();

    // Label - "Хотите войти?"
    loginWindow = std::make_unique<Login>();

}

MainWindow::~MainWindow()
{
    delete ui;

}

//click - "Хотите войти?"
void MainWindow::on_text_button_login_clicked()
{
    loginWindow->show();
    this->close();
}

//text "Продолжить"
void MainWindow::on_button_continue_reg_clicked()
{
    // Если все поля валидны ...
    if (checkFieldsValidity())
    {

        // Получаем данные, которые пользователь ввел в EditText
        QString email = ui->lineEdit_email->text();
        QString username = ui->lineEdit_username->text();
        QString password = ui->lineEdit_password->text();

        // Запускаем клиента в отдельном потоке и передаем ему данные
        std::thread client_thread([email, username, password]() {
            runClient(email, username, password);
        });


        // Показываем Application
        applicationWindow->show();
        this->close();

        // Отделяем поток, чтобы он работал независимо от главного потока
        client_thread.detach();
    }
    else
    {
        // Вывод сообщения об ошибке или предупреждения пользователю
        ui->lineEdit_empty->setText("Заполните все поля");
        ui->lineEdit_empty->setStyleSheet("color: red;");
        ui->lineEdit_empty->setVisible(true);
    }
}

//English words
bool MainWindow::isEnglish(const QString& text)
{
    QRegularExpression regex("^[A-Za-z0-9]+$");
    QRegularExpressionMatch match = regex.match(text);
    return match.hasMatch();
}

//LineEdit Email
void MainWindow::on_lineEdit_email_editingFinished()
{
    QString email = ui->lineEdit_email->text();

    // Проверка на пустое поле
    if (email.isEmpty())
    {
        // Если поле email пустое, устанавливаем флаг в false и показываем ошибку
        ui->label_emailError->setStyleSheet("color: red;");
        ui->label_emailError->setVisible(true);
        isFieldsValid = false;
        return; // Выходим из функции, чтобы не продолжать проверку
    }

    // Проверка наличия символа '@' в email
    if (!email.contains('@'))
    {
        // Если символ '@' отсутствует, устанавливаем флаг в false и показываем ошибку
        ui->label_emailError->setText("Email должен содержать символ '@'");
        ui->label_emailError->setStyleSheet("color: red;");
        ui->label_emailError->setVisible(true);
        isFieldsValid = false;
        return; // Выходим из функции, так как ошибка обнаружена
    }

    // Если все проверки пройдены успешно, сбрасываем ошибку
    ui->label_emailError->setText("");
    ui->label_emailError->setStyleSheet(""); // Сброс стиля

    // Показывать ошибку только если она есть
    ui->label_emailError->setVisible(!ui->label_emailError->text().isEmpty());
}

//LineEdit username
void MainWindow::on_lineEdit_username_editingFinished()
{
    QString username = ui->lineEdit_username->text();

    // Проверка на пустое поле
    if (username.isEmpty())
    {
        // Если поле username пустое, показываем ошибку
        ui->label_usernameError->setStyleSheet("color: red;");
        ui->label_usernameError->setVisible(true);
    }
    else
    {
        // Если поле не пустое, сбрасываем ошибку
        ui->label_usernameError->setText("");
        ui->label_usernameError->setStyleSheet(""); // Сброс стиля
    }
}

//LineEdit password
void MainWindow::on_lineEdit_password_editingFinished()
{
    QString password = ui->lineEdit_password->text();

    // Проверка длины пароля
    if (password.length() < 6)
    {
        // Если пароль слишком короткий, показываем ошибку
        ui->label_passwordError->setText("Слишком короткий пароль");
        ui->label_passwordError->setStyleSheet("color: red;");
        ui->label_passwordError->setVisible(true);
    }
    else if (!isEnglish(password))
    {
        // Если пароль содержит символы, отличные от английских, показываем ошибку
        ui->label_passwordError->setText("Только символы английского алфавита");
        ui->label_passwordError->setStyleSheet("color: red;");
        ui->label_passwordError->setVisible(true);
    }
    else
    {
        // Если длина пароля в допустимых пределах и содержит только символы английского алфавита, сбрасываем ошибку
        ui->label_passwordError->setText("");
        ui->label_passwordError->setStyleSheet(""); // Сброс стиля
    }
}

//Проверка всех полей на валидность
bool MainWindow::checkFieldsValidity()
{
    QString username = ui->lineEdit_username->text();
    QString email = ui->lineEdit_email->text();
    QString password = ui->lineEdit_password->text();

    bool isUsernameValid = !username.isEmpty();
    bool isEmailValid = !email.isEmpty() && email.contains('@'); // проверка наличия символа '@' в email
    bool isPasswordValid = password.length() >= 6 && isEnglish(password);

    // Показывать ошибки только если они есть
    ui->label_usernameError->setVisible(!isUsernameValid);
    ui->label_emailError->setVisible(!isEmailValid);
    ui->label_passwordError->setVisible(!isPasswordValid);

    return isUsernameValid && isEmailValid && isPasswordValid;
}

