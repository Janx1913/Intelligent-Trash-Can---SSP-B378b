#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QLabel>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <iostream>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serialBuffer = "";
    MainWindow::updateLCD("------");

    arduino_is_available = false;
    arduino_port_name = "";
    arduino = new QSerialPort;

    //Finds the vendor and product ID of the arduino
    /*
    qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length();
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        qDebug() << "Has vendor ID: " << serialPortInfo.hasVendorIdentifier();
        if(serialPortInfo.hasVendorIdentifier()){
            qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier();
        }
        qDebug() << "Has product ID: " << serialPortInfo.hasProductIdentifier();
        if(serialPortInfo.hasProductIdentifier()){
            qDebug() << "Product ID: " << serialPortInfo.productIdentifier();
        }
    }
    */

}

MainWindow::~MainWindow()
{
    if(arduino->isOpen())
        arduino->close();

    delete ui;
}

void MainWindow::readSerial(){

    //qDebug() << serialBuffer;
    QStringList bufferSplit = serialBuffer.split(",");

    if(bufferSplit.length() < 3){
        QByteArray serialData = arduino->readAll();
        serialBuffer += QString::fromStdString(serialData.toStdString());
    }else{
        //buffersplit[1] is a good value
        qDebug() << bufferSplit;
        MainWindow::updateLCD(bufferSplit[1]);
        int data = bufferSplit[1].toInt();
        qDebug() << data;
        serialBuffer = "";

        if(data<20 && counter==1){
            counter = 0;
            uses++;
        }
        if(data>=20)
            counter = 1;
    }

    //qDebug() << counter;

    MainWindow::updateLCD2(uses);

}

void MainWindow::updateLCD(const QString sensor_reading){
    ui->lcdNumber->display(sensor_reading);
}

void MainWindow::updateLCD2(const int number_uses){
    QString uses = QString::number(number_uses);
    ui->lcdNumber_2->display(uses);
}

void MainWindow::on_stopButton_clicked()
{
    arduino->close();
    MainWindow::updateLCD("------");
    arduino_is_available = false;
}

void MainWindow::on_startButton_clicked()
{
    // Checks every port for the Arduino Uno, and makes a QString with the port name
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            if(serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id){
                if(serialPortInfo.productIdentifier() == arduino_uno_product_id){
                    arduino_port_name = serialPortInfo.portName();
                    arduino_is_available = true;
                }
            }
        }
    }

    if(arduino_is_available){
        // open and configure port
        arduino->setPortName(arduino_port_name);
        arduino->open(QSerialPort::ReadOnly);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);

        QMessageBox::information(this, "Connection", "Connected to Arduino");
    }else{
        // give error message
        QMessageBox::warning(this, "Port error", "Couldn't find the Arduino!");
    }
    QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
}
