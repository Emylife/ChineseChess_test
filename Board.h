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

private:
    Stone mStones[32];
    int d;
    int mSelectedId;

signals:

public slots:
};

#endif // BOARD_H
