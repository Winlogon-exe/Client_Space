#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "application.h"
#include "login.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    bool isEnglish(const QString& text);//проверка текста на англ
    bool checkFieldsValidity();//проверка всех полей на валидность
    ~MainWindow();

private slots:
    void on_text_button_login_clicked();//Label - "Хотите войти?"
    void on_button_continue_reg_clicked();//Button Reg Form- "Продолжить"
    void on_lineEdit_email_editingFinished();//LineEdit - Email
    void on_lineEdit_username_editingFinished();//LineEdit - username
    void on_lineEdit_password_editingFinished();//LineEdit - password

private:
    Ui::MainWindow *ui;  // Reg Window
    std::unique_ptr<Application> application_window;  // Smart pointer to application window
    std::unique_ptr<Login> loginwindow;  // Smart pointer to login window
    bool isFieldsValid;//проверка полей
};
#endif // MAINWINDOW_H
