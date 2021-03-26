#include "Board.h"
#include<QPainter>

Board::Board(QWidget *parent) : QWidget(parent)
{

}

Board::~Board()
{

}

void Board::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int d = 40;

    for(int i=1; i<=10; i++)
    {
        //划10条横线
        painter.drawLine(QPoint(d, i*d), QPoint(9*d, i*d));
    }
    for(int i=1; i<=9; i++)
    {
        //划9条竖线
        if(i == 1 || i == 9)
        {
            painter.drawLine(QPoint(i*d, d), QPoint(i*d, 10*d));
        }
        else
        {
            painter.drawLine(QPoint(i*d, d), QPoint(i*d, 5*d));
            painter.drawLine(QPoint(i*d, 6*d), QPoint(i*d, 10*d));
        }
    }

    //划九宫格
    painter.drawLine(QPoint(4*d, d), QPoint(6*d, 3*d));
    painter.drawLine(QPoint(6*d, d), QPoint(4*d, 3*d));
    painter.drawLine(QPoint(4*d, 8*d), QPoint(6*d, 10*d));
    painter.drawLine(QPoint(6*d, 8*d), QPoint(4*d, 10*d));
}