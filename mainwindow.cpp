#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->PORT1->setDisabled(1);
    //ui->PORT2->setDisabled(1);
    ui->PORT1_TEXTEDIT->setDisabled(1);
    ui->PORT2_TEXTEDIT->setDisabled(1);
    ui->PORT1_SENDTEXT_LINEEDIT->setDisabled(1);
    ui->PORT2_SENDTEXT_LINEEDIT->setDisabled(1);
    ui->PORT1_SEND->setDisabled(1);
    ui->PORT2_SEND->setDisabled(1);
    status_PORT1 = false;
    status_PORT2 = false;
    buad_rate_1 = 9600;
    buad_rate_2 = 9600;
}

MainWindow::~MainWindow()
{
    delete PORT1_String;
    delete PORT2_String;
    serial1->~QSerialPort();
    serial2->~QSerialPort();
    delete serial1;
    delete serial2;
    delete ui;
}

void MainWindow::on_PORT1_clicked()
{
    if(!status_PORT1){
    bool status = false;
    if(ui->PORT1__DEIVICENUM_LINEEDIT->text() == ""){
    ui->PORT1_TEXTEDIT->append("Error No Device Entered");
    }
    else{
        QString devname = "/dev/"+ui->PORT1__DEIVICENUM_LINEEDIT->text();
        serial1 = new QSerialPort(this);
        serial1->setPortName(devname);
        status = serial1->open(QIODevice::ReadWrite);
        if(status){
           ui->PORT1_TEXTEDIT->clear();
           ui->PORT1_TEXTEDIT->append("PORT OPEN SUCCESFUL\n");
           ui->PORT1->setText("Close");
           serial1->setBaudRate(buad_rate_1,QSerialPort::AllDirections);
           serial1->setDataBits(QSerialPort::Data8);
           serial1->setStopBits(QSerialPort::OneStop);
           serial1->setFlowControl(QSerialPort::NoFlowControl);
           serial1->setParity(QSerialPort::NoParity);
           QObject::connect(serial1, SIGNAL(readyRead()), this, SLOT(readData_PORT1()));
           ui->PORT1_TEXTEDIT->setDisabled(0);
           ui->PORT1_SENDTEXT_LINEEDIT->setDisabled(0);
           ui->PORT1_SEND->setDisabled(0);
           status_PORT1 = true;
           devname.~QString();

        }
        else{
            ui->PORT1_TEXTEDIT->append("ERROR DEVICE NOT OPENED");
        }
    }

    }
   else{

        serial1->close();
        status_PORT1 = false;
        ui->PORT1->setText("Open Port 1");
        ui->PORT1_TEXTEDIT->append("PORT CLOSE SUCCESFUL");
        ui->PORT1_TEXTEDIT->setDisabled(1);
        ui->PORT1_SENDTEXT_LINEEDIT->setDisabled(1);
        ui->PORT1_SEND->setDisabled(1);
    }



}

void MainWindow::readData_PORT1()
{
      QByteArray data = serial1->readAll();
    serial1->flush();
    serial1->clear();
    ui->PORT1_TEXTEDIT->insertPlainText(data);
   //ui->PORT1_TEXTEDIT->append(data);
   data.clear();

}

void MainWindow::on_PORT1_SEND_clicked()
{
    QString str1 = ui->PORT1_SENDTEXT_LINEEDIT->text();
    QByteArray byteArray = str1.toUtf8();
    PORT1_String = byteArray.constData();
    serial1->write(PORT1_String);

}


void MainWindow::on_PORT2_clicked()
{

    if(!status_PORT2){
    bool status = false;
    if(ui->PORT2__DEIVICENUM_LINEEDIT->text() == ""){
    ui->PORT2_TEXTEDIT->append("Error No Device Entered");
    }
    else{
        QString devname = "/dev/"+ui->PORT2__DEIVICENUM_LINEEDIT->text();
        serial2 = new QSerialPort(this);
        serial2->setPortName(devname);
        status = serial2->open(QIODevice::ReadWrite);
        if(status){
           ui->PORT2_TEXTEDIT->clear();
           ui->PORT2_TEXTEDIT->append("PORT OPEN SUCCESFUL\n");
           ui->PORT2->setText("Close");
           serial2->setBaudRate(buad_rate_2,QSerialPort::AllDirections);
           serial2->setDataBits(QSerialPort::Data8);
           serial2->setStopBits(QSerialPort::OneStop);
           serial2->setFlowControl(QSerialPort::NoFlowControl);
           serial2->setParity(QSerialPort::NoParity);
           QObject::connect(serial2, SIGNAL(readyRead()), this, SLOT(readData_PORT2()));
           ui->PORT2_TEXTEDIT->setDisabled(0);
           ui->PORT2_SENDTEXT_LINEEDIT->setDisabled(0);
           ui->PORT2_SEND->setDisabled(0);
           status_PORT2 = true;
           devname.~QString();

        }
        else{
            ui->PORT2_TEXTEDIT->append("ERROR DEVICE NOT OPENED");
        }
    }

    }
   else{

        serial2->close();
        status_PORT2 = false;
        ui->PORT2->setText("Open Port 2");
        ui->PORT2_TEXTEDIT->append("PORT CLOSE SUCCESFUL");
        ui->PORT2_TEXTEDIT->setDisabled(1);
        ui->PORT2_SENDTEXT_LINEEDIT->setDisabled(1);
        ui->PORT2_SEND->setDisabled(1);

    }



}

void MainWindow::readData_PORT2()
{
    QByteArray data = serial2->readAll();
    serial2->flush();
    serial2->clear();
    ui->PORT2_TEXTEDIT->insertPlainText(data);
    //ui->PORT2_TEXTEDIT->append(data);
    data.clear();
}


void MainWindow::on_PORT2_SEND_clicked()
{
    QString str1 = ui->PORT2_SENDTEXT_LINEEDIT->text();
    QByteArray byteArray = str1.toUtf8();
    PORT2_String = byteArray.constData();
    serial2->write(PORT2_String);

}

void MainWindow::on_BUAD_RATE_SELECTOR_1_currentIndexChanged(const QString &arg1)
{
    volatile int buad_rate;
    bool ok;
    buad_rate = arg1.toInt(&ok);
    if(ok == false){
       ui->COMMAND_EDIT->append("PORT1 Error Wrong Buad Rate");
    }
    else{

        buad_rate_1 = buad_rate;
        ui->COMMAND_EDIT->append("PORT1 Buad Rate ="+arg1);
    }

}

void MainWindow::on_BUAD_RATE_SELECTER_2_currentIndexChanged(const QString &arg1)
{

    volatile int buad_rate;
    bool ok;
    buad_rate = arg1.toInt(&ok);
    if(ok == false){
       ui->COMMAND_EDIT->append("PORT1 Error Wrong Buad Rate");
    }
    else{

        buad_rate_2 = buad_rate;
        ui->COMMAND_EDIT->append("PORT2 Buad Rate ="+arg1);
    }

}

void MainWindow::on_actionClose_2_triggered()
{
    serial1->close();
    serial2->close();
    QApplication::quit();

}
