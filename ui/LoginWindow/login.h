#pragma once

#include <QMainWindow>
#include <memory>

#include"application.h"

class MainWindow;

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pushButton_clicked();
    void on_button_continue_reg_clicked();
    void on_lineEdit_username_editingFinished();
    void on_lineEdit_password_editingFinished();

private:
    Ui::Login *ui;
    std::unique_ptr<Application> application_window; // главная форма приложения
    std::unique_ptr<Login> loginwindow; // форма входа в систему
    std::unique_ptr<MainWindow> mainnwindow; // форма регистрации
    bool isFieldsValid;
};
