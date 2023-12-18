#include "customwidget.h"
#include <fstream>
#include<iostream>
#include <cmath>

CustomWidget::CustomWidget(QWidget *parent)
    : QWidget{parent}
{

}

void CustomWidget::paintEvent(QPaintEvent *)
{
    QPainter painter1(this);
    double h = this->height();
    double w = this->width();
    h = h * abs(yMax) / (abs(yMin) + abs(yMax));
    w =  w * abs(xMin) / (abs(xMin) + abs(xMax));
    double hScale = h / (abs(yMax) + 2);
    double wScale = w / (abs(xMin) + 2);
    painter1.translate(w,h);
    painter1.setPen(QPen(Qt::black, 3));
    painter1.drawLine((xMin - 2) * wScale, 0, (xMax + 1) * wScale, 0);
    painter1.drawLine(0, (-yMax - 2) * hScale, 0, (-yMin + 2) * hScale);
    painter1.drawText(-12,15,QString::number(0));
    painter1.setPen(QPen(Qt::black, 1));
    for(int i = xMin - 1; i <= xMax ; i++){
        painter1.setPen(QPen(Qt::black, 3));
        painter1.drawPoint(i*wScale, 0);
        painter1.setPen(QPen(Qt::black, 1));
        painter1.drawLine(QLine(-i*wScale, (-yMax - 2) * hScale, -i*wScale, (-yMin + 2) * hScale));
        painter1.drawLine(QLine(i*wScale, (-yMax - 2) * hScale, i*wScale, (-yMin + 2) * hScale));
        if(i != 0 )
            painter1.drawText(i*wScale, 15, QString::number(i));
    }
    for(int i = yMin - 2; i <= yMax + 2; i++){
        painter1.setPen(QPen(Qt::black, 3));
        painter1.drawPoint(0, i*hScale);
        painter1.setPen(QPen(Qt::black, 1));
        painter1.drawLine(QLine((xMin - 2) * wScale, -i*hScale, (xMax + 1) * wScale, -i*hScale));
        painter1.drawLine(QLine((xMin - 2) * wScale, i*hScale, (xMax + 1) * wScale, i*hScale));
        if(i != 0 )
            painter1.drawText(5, -i*hScale - 1, QString::number(i));
    }
    painter1.setPen(QPen(Qt::red, 4));
    painter1.drawLine(QLine(windXMin * wScale, -windYMin * hScale, windXMax * wScale, -windYMin * hScale));
    painter1.drawLine(QLine(windXMin * wScale, -windYMax * hScale, windXMax * wScale, -windYMax * hScale));
    painter1.drawLine(QLine(windXMin * wScale, -windYMax * hScale, windXMin * wScale, -windYMin * hScale));
    painter1.drawLine(QLine(windXMax * wScale, -windYMax * hScale, windXMax * wScale, -windYMin * hScale));
    for(QPair<QPointF,QPointF> p : lines){
        DrawLine(p);
        painter1.setPen(QPen(Qt::black, 2));
        painter1.drawLine(QLine(p.first.x() * wScale,-p.first.y() * hScale,p.second.x() * wScale,-p.second.y() * hScale));
    }
    if(flag)
    {
        QList<QPair<QPointF,QPointF>> Add;
        for(int i = 0; i < procLines.size() - 1;++i){
            Add.push_back(qMakePair(QPointF(procLines[i].second.x(),procLines[i].second.y()),QPointF(procLines[i + 1].first.x(),procLines[i + 1].first.y())));
        }
        Add.push_back(qMakePair(QPointF(procLines[procLines.size() - 1].second.x(),procLines[procLines.size() - 1].second.y()),
                                QPointF(procLines[0].first.x(),procLines[0].first.y())));
        for(QPair<QPointF,QPointF> p : Add){
            procLines.push_back(p);
        }
        flag = false;
    }
    for(QPair<QPointF,QPointF> p : procLines){
        painter1.setPen(QPen(Qt::green, 4));
        painter1.drawLine(QLine(p.first.x() * wScale,-p.first.y() * hScale,p.second.x() * wScale,-p.second.y() * hScale));
    }
}

void CustomWidget::DrawLine(QPair<QPointF, QPointF> p)
{
    int p1Code = getCode(p.first);
    int p2Code = getCode(p.second);
    if(sqrt(pow(p.first.x() - p.second.x(), 2) + pow(p.first.y() - p.second.y(), 2)) <= 0.001){
        return;
    }
    if((p1Code | p2Code) == 0)
    {
        procLines.push_back(p);
    }
    else if((p1Code & p2Code) !=0 )
    {
        return;
    }
    else
    {
        DrawLine(qMakePair(QPointF(p.first.x(),p.first.y()),QPointF((p.first.x() + p.second.x()) / 2,(p.first.y() + p.second.y()) / 2)));
        DrawLine(qMakePair(QPointF((p.first.x() + p.second.x()) / 2,(p.first.y() + p.second.y()) / 2),QPointF(p.second.x(),p.second.y())));
    }
}

int CustomWidget::getCode(QPointF point)
{
    double x = point.x();
    double y = point.y();

    int code = 0;

    if(x < windXMin)
        code +=1;
    if(x>windXMax)
        code +=2;
    if(y<windYMin)
        code +=4;
    if(y>windYMax)
        code +=8;
    return code;
}


