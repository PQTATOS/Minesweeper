#include "gcell.h"

GCell::GCell()
{
    m_isFlaged = false;
    m_isMine = false;
    m_isRevealed = false;
    setFixedSize(QSize(30,30));
}


void GCell::mousePressEvent(QMouseEvent *e)
{
    if (e->button()==Qt::RightButton && !m_isRevealed)
    {
        flaged();
    }
    else if (e->button()==Qt::LeftButton)
    {
        emit cellRevealed(this);
    }
}


void GCell::flaged()
{
    m_isFlaged = !m_isFlaged;

    if (m_isFlaged)
    {
        setText("P");
        emit cellFlaged(1);
    }
    else
    {
        setText("");
        emit cellFlaged(-1);
    }
    setStyleSheet("color: red;");
}


void GCell::revealed()
{
    if (m_isMine)
    {
        setStyleSheet("background-color: red");
        emit onMineClicked();
    }
    else
        changeColor();
}


void GCell::changeColor()
{
    switch (m_minesAround)
    {
        case 0:
            setText("");
            setStyleSheet("background-color: #c8c8c8; font-size: 12pt;");
            break;
        case 1:
            setText("1");
            setStyleSheet("background-color: #c8c8c8; color: blue; font-size: 12pt;");
            break;
        case 2:
            setText("2");
            setStyleSheet("background-color: #c8c8c8; color: green; font-size: 12pt;");
            break;
        case 3:
            setText("3");
            setStyleSheet("background-color: #c8c8c8; color: red; font-size: 12pt;");
            break;
        case 4:
            setText("4");
            setStyleSheet("background-color: #c8c8c8; color: navy; font-size: 12pt;");
            break;
        case 5:
            setText("5");
            setStyleSheet("background-color: #c8c8c8; color: #ff4e0d; font-size: 12pt;");
            break;
        case 6:
            setText("6");
            setStyleSheet("background-color: #c8c8c8; color: teal; font-size: 12pt;");
            break;
        case 7:
            setText("7");
            setStyleSheet("background-color: #c8c8c8; color: black; font-size: 12pt;");
            break;
        case 8:
            setText("8");
            setStyleSheet("background-color: #c8c8c8; color: white; font-size: 12pt;");
            break;
    }
}
