#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include"Stone.h"
#include<QMouseEvent>

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);
    ~Board();

    void Init();
    void paintEvent(QPaintEvent *);
    void drawStones(QPainter &painter, int i);
    QPoint center(int col, int row);
    void mouseReleaseEvent(QMouseEvent *ev);
    bool canMove(int moveId, int row, int col, int killId);
    bool jiangCanMove(int moveId, int row, int col, int killId);
    bool shiCanMove(int moveId, int row, int col, int killId);
    bool xiangCanMove(int moveId, int row, int col, int killId);
    bool maCanMove(int moveId, int row, int col, int killId);
    bool cheCanMove(int moveId, int row, int col, int killId);
    bool paoCanMove(int moveId, int row, int col, int killId);
    bool bingCanMove(int moveId, int row, int col, int killId);
    bool exitStoneOnthePosition(int row, int col);
    bool cheCanMoveInLine(int moveId, int row, int col, int killId);
    bool paoCanMoveInLine(int moveId, int row, int col, int killId);
private:
    Stone mStones[32];
    int d;
    int mSelectedId;
    bool mIsRedTurn;

signals:

public slots:
};

#endif // BOARD_H
