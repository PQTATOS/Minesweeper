#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "game.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QLabel* setQLabel(QString text);
    QLabel* display;
    QLabel* flagCount;
    QTimer* timer;
private slots:
    void setLossQLabel();
    void setWinQLabel();
    void onFlagChanged(int flags);
};
#endif // MAINWINDOW_H
