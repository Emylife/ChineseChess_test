#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include"Stone.h"

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

private:
    Stone mStones[32];
    int d;

signals:

public slots:
};

#endif // BOARD_H
