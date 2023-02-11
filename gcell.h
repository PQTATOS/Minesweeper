#ifndef GCELL_H
#define GCELL_H
#include <QPushButton>
#include <QMouseEvent>


class GCell : public QPushButton
{
    Q_OBJECT

private:
    void flaged();
    void changeColor();

public:
    void mousePressEvent(QMouseEvent *e);
    void revealed();
    GCell();
    int cord_x;
    int cord_y;
    bool m_isMine;
    bool m_isFlaged;
    bool m_isRevealed;
    int m_minesAround;
signals:
    void cellRevealed(GCell* cell);
    void onMineClicked();
    void cellFlaged(int x);
};

#endif // GCELL_H
