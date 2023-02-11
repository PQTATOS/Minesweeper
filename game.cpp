#include "game.h"

Game::Game(int height, int width)
{
    m_height = height;
    m_width = width;

    m_mineCount = (height * width) * 0.12;
    m_flags = m_mineCount;
    m_cellsToReveal = m_width*m_height - m_mineCount - 1;

    m_field = new GCell[height * width];

    connectCells();
    placeMines();
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, [this] {this->m_inGameTime++;});
    timer->start();
}

void Game::startGame()
{

}

void Game::placeMines()
{
    int i = 0;
    std::srand(std::time(nullptr));

    while (i <= m_mineCount)
    {
        int x = std::rand() % m_width;
        int y = std::rand() % m_height;

        if (m_field[y*m_width + x].m_isMine == true)
            continue;
        m_field[y*m_width + x].m_isMine = true;
        i++;
    }
}

void Game::connectCells()
{
    for (int x = 0; x < m_width; x++)
        for (int y = 0; y < m_height; y++)
        {
            connect(&m_field[y*m_width + x], SIGNAL(cellRevealed(GCell*)), this, SLOT(cellReveal(GCell*)));
            connect(&m_field[y*m_width + x], SIGNAL(onMineClicked()), this, SLOT(gameLoss()));
            connect(&m_field[y*m_width + x], SIGNAL(cellFlaged(int)), this, SLOT(cellFlaged(int)));
            m_field[y*m_width + x].cord_x = x;
            m_field[y*m_width + x].cord_y = y;
        }
}

void Game::cellReveal(GCell* cell)
{
    revealCellsAround(cell->cord_x,cell->cord_y);
}
void Game::cellFlaged(int i)
{
    m_flags -= i;
    emit flagCountChanged(m_flags);
}


void Game::gameLoss()
{
    timer->stop();
    emit lossGame();
}


int Game::minesAround(int x, int y)
{
    int mineCount = 0;
    for (int xOffset = -1; xOffset <= 1; xOffset++)
        for (int yOffset = -1; yOffset <= 1; yOffset++)
        {
            if (outBounds(x+xOffset, y+yOffset))
                continue;
            else if (m_field[(y+yOffset)*m_width + (x+xOffset)].m_isMine)
                mineCount++;
        }

    m_field[y*m_width + x].m_minesAround = mineCount;
    return mineCount;
}

void Game::revealCellsAround(int x, int y)
{
    if (m_field[y*m_width + x].m_isRevealed || m_field[y*m_width + x].m_isFlaged) return;
    if (outBounds(x,y)) return;

    m_field[y*m_width + x].m_isRevealed = true;
    int mines = minesAround(x,y);
    m_field[y*m_width + x].revealed();
    checkForWin();

    if (mines != 0) return;

    revealCellsAround(x-1,y-1);
    revealCellsAround(x,y-1);
    revealCellsAround(x+1,y-1);
    revealCellsAround(x-1,y);
    revealCellsAround(x+1,y);
    revealCellsAround(x-1,y+1);
    revealCellsAround(x,y+1);
    revealCellsAround(x+1,y+1);
}


bool Game::outBounds(int x, int y)
{
    return x<0 || y<0 || x>=m_width || y>=m_height;
}


bool Game::checkForWin()
{
    m_cellRevealed++;
    if (m_cellRevealed == m_cellsToReveal)
        emit winGame();
    return false;
}
