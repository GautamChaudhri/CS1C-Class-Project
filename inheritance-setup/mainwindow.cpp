#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QVBoxLayout>
#include "RenderArea.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    RenderArea *customWidget = new RenderArea(this);

    customWidget->setGeometry(0, 0, width(), height());
    customWidget->raise();

    customWidget->setAttribute(Qt::WA_TransparentForMouseEvents);
    customWidget->setStyleSheet("background: transparent;");
}

MainWindow::~MainWindow()
{
    delete ui;
}

