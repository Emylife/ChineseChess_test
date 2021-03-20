#include "MyWidget.h"
#include "ui_MyWidget.h"
#include <QPainter>
#include <QMouseEvent>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    mIsDrawCircle = false;
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QColor(0, 0, 255));
    painter.setBrush(QBrush(QColor(0, 255, 255)));
    painter.drawLine(QPoint(0,0), QPoint(100,100));
    painter.drawEllipse(QPoint(100,100), 60, 80);
    painter.drawText(50, 110, "This is first text.");
    if(mIsDrawCircle)
    {
        painter.drawEllipse(mPoint, 50, 50);
    }
}

void MyWidget::mousePressEvent(QMouseEvent *event)
{
    mIsDrawCircle = true;
    mPoint = event->pos();
    update();
}
