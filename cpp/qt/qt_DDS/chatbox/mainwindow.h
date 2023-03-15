#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "publisher.h"
#include "subscriber.h"
#include <QString>
#include <string>

extern string username;
extern unsigned long password;
extern int disp;

namespace Ui {
class MainWindow;
}

class CB_Publisher;
class CB_Subscriber;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow  *ui;
    CB_Publisher    *pb;
    QMessageBox     info;
    CB_Subscriber   *sb;

private slots:
    void on_type_returnPressed();

    void on_password_returnPressed();

    void on_logout_clicked();
};

#endif // MAINWINDOW_H
