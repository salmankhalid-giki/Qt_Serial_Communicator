#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtCore/QDebug>
QT_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    QSerialPort *serial1;
    QSerialPort *serial2;
    const char* PORT1_String;
    const char* PORT2_String;
    ~MainWindow();
    
private slots:
    void on_PORT1_clicked();
    void on_PORT2_clicked();
    void readData_PORT1();
    void readData_PORT2();
    void on_PORT1_SEND_clicked();
    void on_PORT2_SEND_clicked();
    void on_BUAD_RATE_SELECTOR_1_currentIndexChanged(const QString &arg1);
    void on_BUAD_RATE_SELECTER_2_currentIndexChanged(const QString &arg1);
    void on_actionClose_2_triggered();

private:
     bool status_PORT1;
     bool status_PORT2;
     int buad_rate_1;
     int buad_rate_2;
     bool verifyCheckSum(QByteArray msg);
     Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
