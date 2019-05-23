#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QTcpSocket>
#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrent>
#include <QHostAddress>
#include "scanresult.h"

ScanResult asyncScanDevice(const QString &ip, int port)
{
    QTcpSocket *socket=new QTcpSocket;
    socket->connectToHost(ip, port);
    socket->waitForConnected(2000);
    bool connected=false;
    if(socket->state()==QTcpSocket::ConnectedState)
    {
        connected=true;
    }
    socket->close();
    socket->deleteLater();
    ScanResult scanResult;
    scanResult.setIp(ip);
    scanResult.setFound(connected);
    return scanResult;
}

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_buttonScan_clicked()
{
    quint32 ip1=QHostAddress(ui->lineIP1->text()).toIPv4Address();
    quint32 ip2=QHostAddress(ui->lineIP2->text()).toIPv4Address();
    if((ip2-ip1)<0 || (ip2-ip1)>300)
    {
        ui->textLog->append(tr("The IP2 should be larger than IP1, the total number of ip addresses should be smaller than 300！"));
        return;
    }
    ui->buttonScan->setEnabled(false);
    m_finishedNumber=0;
    m_totalNumber=(ip2-ip1+1);
    ui->textLog->append(tr("Total: %1").arg(m_totalNumber));
    for(quint32 ip=ip1; ip<=ip2; ip++)
    {
        qDebug()<<QHostAddress(ip).toString();
        QFutureWatcher<ScanResult> *watcher=new QFutureWatcher<ScanResult>;
        connect(watcher, SIGNAL(finished()), this, SLOT(doScanFinished()));
        QFuture<ScanResult> future=QtConcurrent::run(asyncScanDevice, QHostAddress(ip).toString(), ui->linePort->text().toInt());
        watcher->setFuture(future);
    }
}

void MainWidget::doScanFinished()
{
    m_finishedNumber++;
    QFutureWatcher<ScanResult> *watcher=static_cast<QFutureWatcher<ScanResult>*>(sender());
    ScanResult result=watcher->result();
    ui->textLog->append(QString("%1/%2, %3").arg(m_finishedNumber).arg(m_totalNumber).arg(result.ip()));
    if(result.found())
    {
        ui->textDevice->append(result.ip());
    }
    watcher->deleteLater();
    if(m_finishedNumber>=m_totalNumber)
    {
        ui->buttonScan->setEnabled(true);
    }
}

void MainWidget::on_buttonClear_clicked()
{
    ui->textDevice->clear();
    ui->textLog->clear();
}
