#include "Stone.h"
#include<QPoint>

Stone::Stone()
{
    mRadius = 20;
}

Stone::~Stone()
{

}

void Stone::Init(int id)
{
    struct
    {
        int row,colume;
        Stone::Type type;
    } pos [16] ={
        {0,0,Stone::che},
        {0,1,Stone::ma},
        {0,2,Stone::xiang},
        {0,3,Stone::shi},
        {0,4,Stone::jiang},
        {0,5,Stone::shi},
        {0,6,Stone::xiang},
        {0,7,Stone::ma},
        {0,8,Stone::che},

        {2,1,Stone::pao},
        {2,7,Stone::pao},

        {3,0,Stone::bing},
        {3,2,Stone::bing},
        {3,4,Stone::bing},
        {3,6,Stone::bing},
        {3,8,Stone::bing},
    };

    this->mId = id;
    this->mIsDead = false;

    if(id<16)
    {
        this->mIsRed = true;
        this->mColumn = pos[id].colume;
        this->mRow = pos[id].row;
        this->mType = pos[id].type;
    }
    else
    {
        this->mIsRed = false;
        this->mColumn = 8 - pos[id-16].colume;
        this->mRow = 9 - pos[id-16].row;
        this->mType = pos[id-16].type;
    }

}

QString Stone::getText()
{
    switch(this->mType)
    {
        case che:
            return "车";
        case ma:
            return "马";
        case xiang:
            return "相";
        case shi:
            return "士";
        case jiang:
            return "将";
        case pao:
            return "炮";
        case bing:
            return "兵";
    }
    return "错误";
}
