#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include <QListWidget>


namespace Ui {
class Application;
}

class Application : public QMainWindow
{
    Q_OBJECT

public:
    explicit Application(QWidget *parent = nullptr);
    ~Application();

private:
    Ui::Application *ui;
    QListWidget *channelListWidget; // Виджет для списка каналов
};

#endif // APPLICATION_H
