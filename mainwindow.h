#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <painter.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    PaintScene *scene;
    QTimer *timer;

private:
    void updateTimer();
    void resizeEvent(QResizeEvent *event);

public slots:
    void changeButtonColor(QString);
};
#endif // MAINWINDOW_H
