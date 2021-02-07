#include "mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include "ui_mainwindow.h"
#include <windows.h>

int clicked;
int i = 10;
QTimer *timer;
QTimer *why_there_are_two_timer_here;
int why_there_are_two_i_here = 5;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮
    setFixedSize(this->width(),this->height());                     // 禁止拖动窗口大小
    setWindowTitle("CPS测试");

    ui->label_2->setAttribute(Qt::WA_TransparentForMouseEvents,true);

    ui->label_2->setWindowFlags(Qt::FramelessWindowHint);
    ui->label_2->setAttribute(Qt::WA_TranslucentBackground);

    timer = new QTimer(this);
    why_there_are_two_timer_here = new QTimer(this);


    connect(why_there_are_two_timer_here, &QTimer::timeout, [=](){
        why_there_are_two_i_here--;
        if (why_there_are_two_i_here == 0)
        {
            why_there_are_two_timer_here->stop();
            ui->Button->setEnabled(true);
            ui->Button->setText("在10秒内你点击了" + QString::number(clicked)  + "次" + "\n你的CPS为" + QString::number(clicked / 10.0));
            clicked = 0;
            i = 10;
            why_there_are_two_i_here = 5;
            ui->label->setText("10");
        }
        else
        {
            ui->Button->setText("在10秒内你点击了" + QString::number(clicked)  + "次" + "\n你的CPS为" + QString::number(clicked / 10.0) + "\n按钮在" + QString::number(why_there_are_two_i_here) + "秒后启用");
        }
    });
    connect(timer, &QTimer::timeout, [=](){
        i--;
        if (i == 0) // 处理到时
        {
            timer->stop();
            ui->Button->setEnabled(false);
            why_there_are_two_timer_here->start(1000);
        }
        ui->label->setText(QString::number(i));
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Button_clicked()
{
    if (!timer->isActive())
        timer->start(1000);
    clicked++;
    ui->Button->setText(QString::number(clicked));
}
