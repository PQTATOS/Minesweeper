#ifndef GAME_H
#define GAME_H
#include <QObject>
#include <QTimer>
#include "gcell.h"


class Game : public QObject
{
    Q_OBJECT

private:

    int m_mineCount;
    int m_cellsToReveal;

    int m_cellRevealed = 0;

    int m_height;
    int m_width;

    bool m_firstClick = true;

    int minesAround(int x, int y);
    void revealCellsAround(int x, int y);
    void placeMines();
    void startGame();
    void connectCells();

    bool outBounds(int x, int y);
    bool checkForWin();

public:
    int m_flags;
    int m_inGameTime = 0;
    QTimer* timer;
    GCell* m_field;
    Game(int height, int width);

private slots:
    void gameLoss();
    void cellReveal(GCell* cell);
    void cellFlaged(int i);

signals:
    void lossGame();
    void winGame();
    void flagCountChanged(int flags);

};

#endif // GAME_H
