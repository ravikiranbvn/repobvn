#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    double xaxis[2], yaxis[2];
    int i;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int clicked;
    QTimer timer;


private slots:

    void on_Start_clicked();

    void on_clear_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void update();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
