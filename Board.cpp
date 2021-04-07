#include "Board.h"
#include<QPainter>
#include"Stone.h"

Board::Board(QWidget *parent) : QWidget(parent)
{
    Init();
}

Board::~Board()
{

}

QPoint Board::center(int col, int row)
{
    return QPoint((col+1)*this->d,(row+1)*this->d);
}

void Board::Init()
{
    for(int i=0; i<32; ++i)
    {
       this->mStones[i].Init(i);
    }
    this->d = 2*mStones[0].mRadius;
}

void Board::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    for(int i=1; i<=10; i++)
    {
        //画10条横线
        painter.drawLine(QPoint(this->d, i*this->d), QPoint(9*this->d, i*this->d));
    }
    for(int i=1; i<=9; i++)
    {
        //画9条竖线
        if(i == 1 || i == 9)
        {
            painter.drawLine(QPoint(i*this->d, this->d), QPoint(i*this->d, 10*this->d));
        }
        else
        {
            painter.drawLine(QPoint(i*this->d, this->d), QPoint(i*this->d, 5*this->d));
            painter.drawLine(QPoint(i*this->d, 6*this->d), QPoint(i*this->d, 10*this->d));
        }
    }

    //画九宫格
    painter.drawLine(QPoint(4*this->d, this->d), QPoint(6*this->d, 3*this->d));
    painter.drawLine(QPoint(6*this->d, this->d), QPoint(4*this->d, 3*this->d));
    painter.drawLine(QPoint(4*this->d, 8*this->d), QPoint(6*this->d, 10*this->d));
    painter.drawLine(QPoint(6*this->d, 8*this->d), QPoint(4*this->d, 10*this->d));

    //画棋子
    for(int i=0; i<32; ++i)
    {
        drawStones(painter, i);
    }
}

void Board::drawStones(QPainter &painter, int i)
{
    QPoint c = center(mStones[i].mColumn, mStones[i].mRow);
    painter.setBrush(Qt::yellow);
    painter.setPen(Qt::black);
    painter.drawEllipse(c, this->d/2, this->d/2);
    if(mStones[i].mIsRed)
    {
        painter.setPen(Qt::red);
    }
    painter.setFont(QFont("system", this->d/2, 700));
    painter.drawText(QRect(c.x()-this->d/2, c.y()-this->d/2, d, d), mStones[i].getText(), QTextOption(Qt::AlignCenter));
}
