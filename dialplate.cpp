#include "dialplate.h"
#include"math.h"

#include<QDebug>
#include<cmath>

DialPlate::DialPlate(QWidget *parent) :
    QWidget(parent)
{
    bigDivided=10;
    smallDivided=10;
    scale=1;
    scaleCount=1;
    value=0;
}

DialPlate::~DialPlate()
{

}

void DialPlate::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);//声明一个画家对象
    painter.setRenderHint(QPainter::Antialiasing);//抗锯齿形
    //初始化参数设置
    this->SetParamsInit();
    //填充表盘周围为透明色
    this->SetOtherBackground(&painter);
    //画表盘
    this->DrawPlate(&painter);
}

int DialPlate::getValue() const
{
    return value;
}

void DialPlate::setValue(int value)
{
    this->value = value;
}

int DialPlate::getScale() const
{
    return scale;
}

void DialPlate::setScale(int value)
{
    this->scale = value;
}

int DialPlate::getSmallDivided() const
{
    return smallDivided;
}

void DialPlate::setSmallDivided(int value)
{
    this->smallDivided = value;
}

int DialPlate::getBigDivided() const
{
    return bigDivided;
}

void DialPlate::setBigDivided(int value)
{
    this->bigDivided = value;
}
//初始化参数设置
void DialPlate::SetParamsInit()
{
    centerRadius=(this->width()-290/340.0*this->width())/2;
    inRadius=(this->width()-76/340.0*this->width())/2;
    midRadius=(this->width()-38/340.0*this->width())/2;
    outRadius=(this->width()-14/340.0*this->width())/2;
}
//设置表盘周围为透明色
void DialPlate::SetOtherBackground(QPainter *painter)
{
    painter->save();
    painter->setBrush(Qt::transparent);
    painter->fillRect(this->rect(),QColor(0,0,0,0));
    painter->restore();
}
//画表盘
void DialPlate::DrawPlate(QPainter *painter)
{
    //画最外环
    DrawRing(painter,QColor(240,240,240), QColor(100,100,100),midRadius,outRadius);
    //画中间黑环
    DrawRing(painter,QColor(240,240,240), QColor(0,0,0),inRadius,midRadius);
    //画小环
    DrawRing(painter,QColor(240,240,240), QColor(100,100,100),centerRadius,inRadius);
    //画刻度
    DrawScale(painter);
    //画黄色指示条
    DrawArcRing(painter);
    //画中心点圆
    DrawRing(painter,QColor(240,240,240), QColor(233,123,90),0,centerRadius);
    //画数字
    DrawText(painter);
    //画指针
    DrawNeedle(painter);
    //画值
    DrawValue(painter);
}
//画圆环
void DialPlate::DrawRing(QPainter *painter,QColor backColor, QColor ringColor, double inRadius, double outRadius)
{
    QBrush qbrush(ringColor);
    painter->setBrush(qbrush);
    painter->drawEllipse(QPointF(this->width()/2.0,this->height()/2.0),outRadius,outRadius);
    qbrush.setColor(backColor);
    painter->setBrush(qbrush);
    painter->drawEllipse(QPointF(this->width()/2.0,this->height()/2.0),inRadius,inRadius);

}
//画刻度
void DialPlate::DrawScale(QPainter *painter)
{
    QPen qpen(Qt::white);
    double startRadius;//起点半径
    double endRadius=midRadius;//终点半径
    //绘制刻度
    for(int i=0;i<=bigDivided*smallDivided;i++)
    {
        if(i%smallDivided==0)
        {
            startRadius=inRadius;//大刻度
            qpen.setWidthF(2.5);
        }
        else
        {
            startRadius=inRadius+(midRadius-inRadius)/2;//小刻度
            qpen.setWidthF(1.5);
        }
        painter->setPen(qpen);
        //起点坐标
        double xPosStart=this->width()/2+startRadius*cos(3.14*3/4+i*3.14*3/2/bigDivided/smallDivided);
        double yPosStart=this->height()/2+startRadius*sin(3.14*3/4+i*3.14*3/2/bigDivided/smallDivided);
        //终点坐标
        double xPosEnd=this->width()/2+endRadius*cos(3.14*3/4+i*3.14*3/2/bigDivided/smallDivided);
        double yPosEnd=this->height()/2+endRadius*sin(3.14*3/4+i*3.14*3/2/bigDivided/smallDivided);
        painter->drawLine(QPointF(xPosStart,yPosStart),QPointF(xPosEnd,yPosEnd));
    }

}
//画数字
void DialPlate::DrawText(QPainter *painter)
{
    //计算scale是几位数
    int scaleCount=1;
    int tempScale=scale;
    while (tempScale/10)
    {
        scaleCount++;
        tempScale/=10;
    }
    int fontSize=30-3*scaleCount;
    QPen qpen(Qt::green);
    qpen.setWidthF(1.0);
    painter->setPen(qpen);
    QFont font=painter->font();
    font.setPixelSize(fontSize);
    painter->setFont(font);
    double textRadius=inRadius-30;
    for(int i=0;i<=bigDivided;i++)
    {
        double xPosText=this->width()/2+textRadius*cos(3.14*3/4+i*3.14*3/2/bigDivided);
        double yPosText=this->height()/2+textRadius*sin(3.14*3/4+i*3.14*3/2/bigDivided);
        QRectF textQRect(xPosText-25,yPosText-12,50,24);
        painter->drawText(textQRect,Qt::AlignCenter,QString::number(i*scale));
    }

}
//画指针
void DialPlate::DrawNeedle(QPainter *painter)
{
    double needleRadius=this->width()/2-90/340.0*this->width();
    double needleCenterRadius=centerRadius-16/340.0*this->width();
    //画指针的圆
    DrawRing(painter,Qt::red, Qt::red,0,needleCenterRadius+4);
    double biggestValue=bigDivided*scale;
    //超出量程则显示为最大值
    if(value>biggestValue)
    {
        value=bigDivided*scale;
    }
    //指针三角形的三个点坐标
    double xPosNeedle0=this->width()/2+needleRadius*cos(3.14*3/4+value/biggestValue*3.14*3/2);
    double yPosNeedle0=this->height()/2+needleRadius*sin(3.14*3/4+value/biggestValue*3.14*3/2);
    double xPosNeedle1=this->width()/2+needleCenterRadius*cos(3.14*3/4+value/biggestValue*3.14*3/2+3.14/2);
    double yPosNeedle1=this->height()/2+needleCenterRadius*sin(3.14*3/4+value/biggestValue*3.14*3/2+3.14/2);
    double xPosNeedle2=this->width()/2+needleCenterRadius*cos(3.14*3/4+value/biggestValue*3.14*3/2-3.14/2);
    double yPosNeedle2=this->height()/2+needleCenterRadius*sin(3.14*3/4+value/biggestValue*3.14*3/2-3.14/2);
    //画三角形
    QPen qpen(Qt::red);
    QBrush qbrush(Qt::red);
    painter->setPen(qpen);
    painter->setBrush(qbrush);
    QPointF points[3]={QPointF(xPosNeedle0,yPosNeedle0),QPointF(xPosNeedle1,yPosNeedle1),
                       QPointF(xPosNeedle2,yPosNeedle2)};
    painter->drawPolygon(points,3);
}
//画黄色刻度条上的环形指示带(两个扇形相减）
void DialPlate::DrawArcRing(QPainter *painter)
{
    //画黄色扇形
    if(value>bigDivided*scale)
    {
        value=bigDivided*scale;
    }
    QBrush qbrush(QColor(255,255,0,100));
    QPen qpen(QColor(255,255,0,100));
    painter->setBrush(qbrush);
    painter->setPen(qpen);
    QRectF outRect(19/340.0*this->width(),19/340.0*this->height(),2*midRadius,2*midRadius);
    int startAngle=225*16;
    int endAngle=(int)(225+(value/(double)(bigDivided*scale))*270)*16;
    int spanAngle=startAngle-endAngle;//角度差(默认为逆时针，负数则为顺时针）
    painter->drawPie(outRect,startAngle,spanAngle);
    //画减去部分的扇形
    QRectF inRect(38/340.0*this->width(),38/340.0*this->height(),2*inRadius,2*inRadius);
    qbrush.setColor(QColor(100,100,100));
    qpen.setColor(QColor(100,100,100));
    painter->setBrush(qbrush);
    painter->setPen(qpen);
    painter->drawPie(inRect,startAngle,spanAngle+(-16));//为了完全减去黄色内部区域，多减一个单位(16)
}
//在表盘上显示数值
void DialPlate::DrawValue(QPainter *painter)
{
    //计算scale是几位数
    int scaleCount=1;
    int tempScale=scale;
    while (tempScale/10)
    {
        scaleCount++;
        tempScale/=10;
    }
    int fontSize=30-3*scaleCount;
    QBrush qbrush(Qt::blue);
    QPen qpen(Qt::blue);
    QFont font=painter->font();
    font.setPixelSize(fontSize);
    painter->setFont(font);
    painter->setBrush(qbrush);
    painter->setPen(qpen);
    QRectF valueRect(this->width()/2-25,this->height()/2+90/340.0*this->width(),50,30);
    painter->drawText(valueRect,Qt::AlignCenter,QString::number(value));
}

