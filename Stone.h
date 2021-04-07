#ifndef STONE_H
#define STONE_H
#include<QString>


class Stone
{
public:
    Stone();
    ~Stone();
    void Init(int id);
    enum Type{che,ma,xiang,shi,jiang,pao,bing};
    QString getText();
    int mColumn, mRow, mId, mRadius;
    Type mType;
    bool mIsRed;
    bool mIsDead;
};

#endif // STONE_H
