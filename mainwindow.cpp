#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "painter.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new PaintScene();
    ui->graphicsView->setScene(scene);

    timer = new QTimer();
    timer->start(100);

    ui->colorButton->setStyleSheet("background-color: black");

    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimer);
    connect(ui->colorButton, &QPushButton::clicked, scene, &PaintScene::changeColor);
    connect(scene, &PaintScene::colorChanged, this, &MainWindow::changeButtonColor);
    connect(ui->brushSizeValue, &QSpinBox::valueChanged, scene, &PaintScene::changeBrushSize);
    connect(ui->clearAllBtn, &QPushButton::clicked, scene, &PaintScene::clear);
    connect(ui->back, &QPushButton::clicked, scene, &PaintScene::undo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTimer()
{
    timer->stop();
    scene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    timer->start(100);
    QWidget::resizeEvent(event);
}

void MainWindow::changeButtonColor(QString colorName)
{
    ui->colorButton->setStyleSheet("background-color: " + colorName);
}
