#include "Board.h"
#include<QPainter>
#include"Stone.h"
#include<iostream>
#include<math.h>

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
    this->mIsRedTurn = true;
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
    if(mStones[i].mIsDead)
    {
        return;
    }

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
//    cout<<"mSelectedId = "<<mSelectedId<<endl;

    //判断鼠标是否点击在棋盘内
//    if(0<=col && col<=8 && 0<=row && row<=9)
//    {
//        int i=0;
//        for(; i<32; ++i)
//        {
//            if(mStones[i].mColumn == col && mStones[i].mRow == row && !mStones[i].mIsDead)  //正好点击到了棋盘内的一颗棋子
//            {
//                if(mSelectedId == -1) //未选中棋子，那么选中该棋子
//                {
//                    mSelectedId = i;
//                }
//                else //之前就已选中棋子，那么吃掉现在点击位置的棋子
//                {
//                    mStones[i].mIsDead = true;
//                    mStones[mSelectedId].mColumn = col;
//                    mStones[mSelectedId].mRow = row;
//                    mSelectedId = -1;
//                }
//                update();
//                break;
//            }
//        }
//        if(i == 32) //点击的位置没有棋子
//        {
//            if(mSelectedId == -1)  //之前没有选中棋子，现在又点击空白位置，那么直接返回
//            {
//                return;
//            }
//            else   //之前已经选中了棋子，现在又点击了空白位置，那么把选中的棋子走到现在点击的位置上
//            {
//                mStones[mSelectedId].mColumn = col;
//                mStones[mSelectedId].mRow = row;
//                mSelectedId = -1;
//                update();
//            }
//        }
//    }
//    else
//    {
//        return;
//    }
    if(!(0<=col && col<=8 && 0<=row && row<=9))
    {
        return;
    }
    int i=0;
    for(; i<32; ++i)
    {
        if(mStones[i].mColumn == col && mStones[i].mRow == row && !mStones[i].mIsDead)  //正好点击到了棋盘内的一颗棋子
        {
            break;
        }
    }
    if(mSelectedId == -1)  //之前未选中棋子
    {
        if(i < 32)
        {
            if(mIsRedTurn == mStones[i].mIsRed)
            {
                mSelectedId = i; //之前未选中棋子,选中棋子
                update();
            }
        }
    }
    else  //之前就已经选中棋子，那么走棋
    {
        if(canMove(mSelectedId, row, col, i))
        {
            if(i < 32) //之前就已经选中棋子,现在点击的位置正好有一颗棋子,那么吃掉该棋子
            {
                mStones[i].mIsDead = true;
            }
            //之前已经选中了棋子，现在又点击了空白位置，那么把选中的棋子走到现在点击的位置上
            mStones[mSelectedId].mColumn = col;
            mStones[mSelectedId].mRow = row;
            mSelectedId = -1;
            mIsRedTurn = !mIsRedTurn;
            update();
        }
    }
}

bool Board::canMove(int moveId, int row, int col, int killId)
{
    if(moveId == killId)
    {
        return false;
    }
    if(mStones[moveId].mIsRed == mStones[killId].mIsRed)
    {
        mSelectedId = killId;
        update();
        return false;
    }
    switch (mStones[moveId].mType)
    {
    case Stone::jiang:
        return jiangCanMove(moveId, row, col, killId);
        break;
    case Stone::shi:
        return shiCanMove(moveId, row, col, killId);
        break;
    case Stone::xiang:
        return xiangCanMove(moveId, row, col, killId);
        break;
    case Stone::ma:
        return maCanMove(moveId, row, col, killId);
        break;
    case Stone::che:
        return cheCanMove(moveId, row, col, killId);
        break;
    case Stone::pao:
        return paoCanMove(moveId, row, col, killId);
        break;
    case Stone::bing:
        return bingCanMove(moveId, row, col, killId);
        break;
    }
    return true;
}

bool Board::jiangCanMove(int moveId, int row, int col, int killId)
{
    if(col<3 || col>5)
    {
        return false;
    }
    if(mStones[moveId].mIsRed)
    {
        if(row>2)
        {
            return false;
        }
    }
    else
    {
        if(row<7)
        {
            return false;
        }
    }

    //步长
    int d = abs(mStones[moveId].mColumn - col)*1 + abs(mStones[moveId].mRow - row)*10;
    if(d == 1 || d == 10)
    {
        return true;
    }
    return false;
}

bool Board::shiCanMove(int moveId, int row, int col, int killId)
{
    if(col<3 || col>5)
    {
        return false;
    }
    if(mStones[moveId].mIsRed)
    {
        if(row>2)
        {
            return false;
        }
    }
    else
    {
        if(row<7)
        {
            return false;
        }
    }

    //步长
    int d = abs(mStones[moveId].mColumn - col)*1 + abs(mStones[moveId].mRow - row)*10;
    if(d == 11)
    {
        return true;
    }
    return false;
}

bool Board::exitStoneOnthePosition(int row, int col)
{
    for(int i=0; i<32; ++i)
    {
        if( !mStones[i].mIsDead && mStones[i].mColumn == col && mStones[i].mRow == row)  //正好点击到了棋盘内的一颗棋子
        {
            return true;
        }
    }
    return false;
}

bool Board::xiangCanMove(int moveId, int row, int col, int killId)
{
    if(!(col == 0 ||col == 2 || col == 4 || col == 6 || col == 8))
    {
        return false;
    }
    if(mStones[moveId].mIsRed)
    {
        if(!(row == 0 || row == 2 || row == 4))
        {
            return false;
        }
    }
    else
    {
        if(!(row == 9 || row == 7 || row == 5))
        {
            return false;
        }
    }

    //步长
    int d = abs(mStones[moveId].mColumn - col)*1 + abs(mStones[moveId].mRow - row)*10;
    if(d != 22)
    {
        return false;
    }

    //判断是否有其他棋子蹩脚
    if(!exitStoneOnthePosition((mStones[moveId].mRow + row)/2, (mStones[moveId].mColumn + col)/2))
    {
        return true;
    }

    return false;
}

bool Board::maCanMove(int moveId, int row, int col, int killId)
{
    //步长
    int d = abs(mStones[moveId].mColumn - col)*1 + abs(mStones[moveId].mRow - row)*10;
    if(d != 21 && d != 12)
    {
        return false;
    }

    //确定蹩脚点的坐标
    int roadBlockCol = -1;
    int roadBlockRow = -1;
    if(abs(mStones[moveId].mColumn - col) == 2)
    {
        roadBlockRow = mStones[moveId].mRow;
        roadBlockCol = mStones[moveId].mColumn + (mStones[moveId].mColumn - col < 0 ? 1:-1);
    }
    else
    {
        roadBlockCol = mStones[moveId].mColumn;
        roadBlockRow = mStones[moveId].mRow + (mStones[moveId].mRow - row < 0 ? 1:-1);
    }
    if(!exitStoneOnthePosition(roadBlockRow,roadBlockCol))
    {
        return true;
    }
    return false;
}

bool Board::cheCanMoveInLine(int moveId, int row, int col, int killId)
{
    bool flagRow = mStones[moveId].mRow == row;
    int min = -1;
    int max = -1;
    if(flagRow)
    {
        min = mStones[moveId].mColumn < col ? mStones[moveId].mColumn:col;
        max = mStones[moveId].mColumn > col ? mStones[moveId].mColumn:col;
    }
    else
    {
        min = mStones[moveId].mRow < row ? mStones[moveId].mRow:row;
        max = mStones[moveId].mRow > row ? mStones[moveId].mRow:row;
    }
    //如果走棋的起点和终点之间有棋子挡住，直接返回false
    if(flagRow)
    {
        for(int i=0; i<32; i++)
        {
            if(mStones[i].mRow == row && !mStones[i].mIsDead && mStones[i].mColumn < max && mStones[i].mColumn > min)
            {
                return false;
            }
        }
    }
    else
    {
        for(int i=0; i<32; i++)
        {
            if(mStones[i].mColumn == col && !mStones[i].mIsDead && mStones[i].mRow < max && mStones[i].mRow > min)
            {
                return false;
            }
        }
    }
    return true;
}

bool Board::cheCanMove(int moveId, int row, int col, int killId)
{
    if((mStones[moveId].mColumn == col && mStones[moveId].mRow == row) || (mStones[moveId].mColumn != col && mStones[moveId].mRow != row))   //走棋的起点和终点不在一条直线上
    {
        return false;
    }
    if(cheCanMoveInLine(moveId,row,col,killId))  //如果直线上没有其他棋子挡住，那么可以走直线
    {
        return true;
    }
    return false;
}

bool Board::paoCanMoveInLine(int moveId, int row, int col, int killId)
{
    bool flagRow = mStones[moveId].mRow == row;
    int min = -1;
    int max = -1;
    if(flagRow)
    {
        min = mStones[moveId].mColumn < col ? mStones[moveId].mColumn:col;
        max = mStones[moveId].mColumn > col ? mStones[moveId].mColumn:col;
    }
    else
    {
        min = mStones[moveId].mRow < row ? mStones[moveId].mRow:row;
        max = mStones[moveId].mRow > row ? mStones[moveId].mRow:row;
    }
    //如果走棋的起点和终点之间有棋子挡住，直接返回false
    int roadBlockNum = 0;  //记录有多少颗棋子挡住了走起的路线
    if(flagRow)
    {
        for(int i=0; i<32; i++)
        {
            if(mStones[i].mRow == row && !mStones[i].mIsDead && mStones[i].mColumn < max && mStones[i].mColumn > min)
            {
                roadBlockNum++;
                continue;
            }
        }
    }
    else
    {
        for(int i=0; i<32; i++)
        {
            if(mStones[i].mColumn == col && !mStones[i].mIsDead && mStones[i].mRow < max && mStones[i].mRow > min)
            {
                roadBlockNum++;
                continue;
            }
        }
    }
    if(killId < 32 && roadBlockNum == 1)  //killId小于32情况：炮吃掉killId这个棋子，但是要判断是否符合炮走起的规则，即moveId和killId之间只有1个其他棋子
    {
        return true;
    }
    else if(killId >= 32 && roadBlockNum == 0)
    {
        return true;
    }
    return false;
}

bool Board::paoCanMove(int moveId, int row, int col, int killId)
{
    if((mStones[moveId].mColumn == col && mStones[moveId].mRow == row) || (mStones[moveId].mColumn != col && mStones[moveId].mRow != row))   //走棋的起点和终点不在一条直线上
    {
        return false;
    }
    if(paoCanMoveInLine(moveId,row,col,killId))
    {
        return true;
    }
    return false;
}

bool Board::bingCanMove(int moveId, int row, int col, int killId)
{
    //步长
    int d = abs(mStones[moveId].mColumn - col)*1 + abs(mStones[moveId].mRow - row)*10;
    if(d != 1 && d != 10)
    {
        return false;
    }
    if(mStones[moveId].mIsRed)
    {
        if(mStones[moveId].mRow < 5) //兵还没过河
        {
            if(mStones[moveId].mRow+1 == row)
            {
                return true;
            }
        }
        else
        {
            if(mStones[moveId].mRow <= row)
            {
                return true;
            }
        }
    }
    else
    {
        if(mStones[moveId].mRow > 4)  //兵没过河
        {
            if(mStones[moveId].mRow-1 == row)
            {
                return true;
            }
        }
        else
        {
            if(mStones[moveId].mRow >= row)
            {
                return true;
            }
        }
    }
    return false;
}
