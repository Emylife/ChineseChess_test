#include "Board.h"
#include<QPainter>
#include"Stone.h"
#include<iostream>

using namespace std;

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
    this->mSelectedId = -1;
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

    if(mSelectedId == i)
        painter.setBrush(Qt::yellow);
    else
        painter.setBrush(Qt::gray);

    painter.setPen(Qt::black);
    painter.drawEllipse(c, this->d/2, this->d/2);
    if(mStones[i].mIsRed)
    {
        painter.setPen(Qt::red);
    }
    painter.setFont(QFont("system", this->d/2, 700));
    painter.drawText(QRect(c.x()-this->d/2, c.y()-this->d/2, d, d), mStones[i].getText(), QTextOption(Qt::AlignCenter));
}

void Board::mouseReleaseEvent(QMouseEvent *ev)
{
    QPoint pt = ev->pos();
    int col = pt.x()/d - 1 + ((pt.x()%d) < (d/2) ? 0:1);
    int row = pt.y()/d - 1 + ((pt.y()%d) < (d/2) ? 0:1);

//    cout<<"pt.x() = "<<pt.x()<<endl;
//    cout<<"pt.y() = "<<pt.y()<<endl;
//    cout<<"pt.rx() = "<<pt.rx()<<endl;
//    cout<<"pt.ry() = "<<pt.ry()<<endl;
//    cout<<"pt.x()/d = "<<pt.x()/d<<endl;
//    cout<<"pt.y()/d = "<<pt.y()/d<<endl;
//    cout<<"pt.x()%d = "<<pt.x()%d<<endl;
//    cout<<"pt.y()%d = "<<pt.y()%d<<endl;
//    cout<<"d = "<<d<<endl;
//    cout<<"col = "<<col<<endl;
//    cout<<"row = "<<row<<endl;

    //选中棋子，判断鼠标是否点击在棋盘内
    if(0<=col && col<=8 && 0<=row && row<=9)
    {
        for(int i=0; i<32; ++i)
        {
            if(mStones[i].mColumn == col && mStones[i].mRow == row)
            {
                mSelectedId = i;
                update();
                break;
            }
        }
    }
    else
    {
        return;
    }
}
