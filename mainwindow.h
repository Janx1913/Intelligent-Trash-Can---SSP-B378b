#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void readSerial();
    void updateLCD(const QString);
    void updateLCD2(const int);

    void on_stopButton_clicked();

    void on_startButton_clicked();


private:
    Ui::MainWindow *ui;

    QSerialPort *arduino;
    static const quint16 arduino_uno_vendor_id = 10755;
    static const quint16 arduino_uno_product_id = 67;
    QString arduino_port_name;
    bool arduino_is_available;

    QByteArray serialData;
    QString serialBuffer;
    QStringList bufferSplit;

    int data;
    int uses=0;
    int counter=0;


};

#endif // MAINWINDOW_H
