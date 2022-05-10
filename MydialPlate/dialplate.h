#ifndef DIALPLATE_H
#define DIALPLATE_H

#include <QWidget>
#include<QPainter>

class _declspec(dllexport) DialPlate : public QWidget
{
    Q_OBJECT

public:
    DialPlate(QWidget *parent = 0);
    ~DialPlate();
    void paintEvent(QPaintEvent *event);//系统自动调用
    int getBigDivided() const;
    void setBigDivided(int value);

    int getSmallDivided() const;
    void setSmallDivided(int value);

    int getScale() const;
    void setScale(int value);

    int getValue() const;
    void setValue(int value);

private:
    double centerRadius;//表盘中心圆半径
    double inRadius;//表盘内圆半径
    double midRadius;//表盘中间圆半径
    double outRadius;//表盘最外圆半径
    int bigDivided;//大刻度等分数
    int smallDivided;//小刻度等分数
    int scale;//倍率
    int scaleCount;//scale的位数
    int value;//刻度盘的值
    void SetParamsInit();
    void SetOtherBackground(QPainter *painter);
    void DrawPlate(QPainter *painter);
    void DrawRing(QPainter *painter,QColor backColor, QColor ringColor,double inRadius,double outRadius);
    void DrawScale(QPainter *painter);
    void DrawText(QPainter *painter);
    void DrawNeedle(QPainter *painter);
    void DrawArcRing(QPainter *painter);
    void DrawValue(QPainter *painter);
};

#endif

