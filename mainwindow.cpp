#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QGridLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Game* game = new Game(16, 16);
    QWidget* widget = new QWidget(this);
    QGridLayout* layout = new QGridLayout(this);
    layout->setSpacing(0);

    for (int x = 0; x < 16; x++)
        for (int y = 0; y < 16; y++)
            layout->addWidget(&(game->m_field[y*16 + x]), x+1, y);


    auto inGameTime = setQLabel(QString('0'));
    layout->addWidget(inGameTime, 0, 1, 1, 2);

    flagCount = setQLabel(QString::number(game->m_flags));
    layout->addWidget(flagCount, 0, 13, 1, 2);

    display = new QLabel();
    layout->addWidget(display,0,5,1,6);

    connect(game->timer, &QTimer::timeout, this, [inGameTime, game]{inGameTime->setText(QString::number(game->m_inGameTime));});
    connect(game, SIGNAL(lossGame()), this, SLOT(setLossQLabel()));
    connect(game, SIGNAL(winGame()), this, SLOT(setWinQLabel()));
    connect(game, SIGNAL(flagCountChanged(int)), this, SLOT(onFlagChanged(int)));

    widget->setLayout(layout);
    this ->setCentralWidget(widget);
}

QLabel* MainWindow::setQLabel(QString text)
{
    auto label = new QLabel(text);
    label->setFixedSize(60, 30);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("color: #de1616; background: #474747; font-size: 14pt");
    return label;
}

void MainWindow::setLossQLabel()
{
    display->setText("Вы проиграли");
    display->setFixedSize(180, 30);
    display->setAlignment(Qt::AlignCenter);
    display->setStyleSheet("color: #de1616; font-size: 17pt");
}

void MainWindow::setWinQLabel()
{
    display->setText("Вы выиграли");
    display->setFixedSize(180, 30);
    display->setAlignment(Qt::AlignCenter);
    display->setStyleSheet("color: #de1616; font-size: 17pt");
}

void MainWindow::onFlagChanged(int flags)
{
    flagCount->setText(QString::number(flags));
}

MainWindow::~MainWindow()
{
}

