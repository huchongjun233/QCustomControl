#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QListWidget>
#include <drawerwidget.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDrawerWidget *drawer = new QDrawerWidget(this);
    this->setCentralWidget(drawer);
    drawer->setLockerButtonHeight(40);

    Locker *locker = drawer->addLocker("装备模型");
    locker->addLockerItem("","无人机");
    //locker->setOPenState(true);

    locker->addLockerItem("","坦克");
    //locker->setOPenState(true);

    locker->addLockerItem("","火箭");
    //locker->setOPenState(true);

    Locker *locker2 = drawer->addLocker("地形模型");
    locker2->addLockerItem("","树木");
    //locker2->setOPenState(true);

    locker2->addLockerItem("","山地");
    //locker2->setOPenState(true);


    //drawer->setLockerButtonHeight(60);
;
}

MainWindow::~MainWindow()
{
    delete ui;
}
