#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void on_buttonScan_clicked();
    void doScanFinished();

    void on_buttonClear_clicked();

private:
    Ui::MainWidget *ui;
    int m_finishedNumber;
    int m_totalNumber;
};

#endif // MAINWIDGET_H
