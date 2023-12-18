#include "customwidget.h"

CustomWidget::CustomWidget(QWidget *parent)
    : QWidget{parent}
{

}

void CustomWidget::paintEvent(QPaintEvent *)
{
    QPainter painter1(this);
    double h = this->height();
    double w = this->width();
    h /= 2;
    w /= 2;
    double hScale = h / 12;
    double wScale = w / 12;
    painter1.translate(w,h);
    painter1.setPen(QPen(Qt::black, 3));
    painter1.drawLine(-w, 0, w, 0);
    painter1.drawLine(0, -h, 0, h);
    painter1.drawText(-12,15,QString::number(0));
    painter1.setPen(QPen(Qt::black, 1));
    for(int i = 1; i < 11; i++){
        painter1.drawPoint(i*wScale, 0);
        painter1.drawPoint(-i*wScale, 0);
        painter1.drawLine(QLine(-i*wScale, -h, -i*wScale, h));
        painter1.drawLine(QLine(i*wScale, -h, i*wScale, h));
        painter1.drawText(i*wScale, 15, QString::number(i));
        painter1.drawText(-i*wScale, 15, QString::number(-i));
    }
    for(int i = 1; i < 11; i++){
        painter1.drawPoint(0, i*hScale);
        painter1.drawText(5, -i*hScale - 1, QString::number(i));
        painter1.drawPoint(0, -i*hScale);
        painter1.drawText(5, i*hScale - 1, QString::number(-i));
        painter1.drawLine(QLine(-w, -i*hScale, w, -i*hScale));
        painter1.drawLine(QLine(-w, i*hScale, w, i*hScale));
    }
    painter1.setPen(Qt::NoPen);
    painter1.setBrush(QBrush (QColor (0, 0, 0, 90)));
    if(!PointList.empty()){
        if(!ListOfIntensy.empty())
        {
            for(int i = 0; i < PointList.size(); ++i){
                painter1.setBrush(QBrush (QColor (0, 0, 0, 180 * ListOfIntensy[i])));
                painter1.drawRect(PointList[i].x()*wScale,-(PointList[i].y()+1)*hScale,wScale,hScale);
            }
        }
        else
        {
            for(QPointF p : PointList){
                painter1.drawRect(p.x()*wScale,-(p.y()+1)*hScale,wScale,hScale);
            }
        }
    }
    if(!PointListForCastlePitway.empty())
    {
        int sx = startX,sy = startY;
        for(int i = 0; i < PointListForCastlePitway.size(); ++i){
            if(PointListForCastlePitway[i] == 's')
            {
                painter1.setPen(QPen(Qt::blue, 3));
                painter1.drawLine(sx * wScale,-sy*hScale,(sx + 1)*wScale,-sy*hScale);
                ++sx;

            }
            else{
                painter1.setPen(QPen(Qt::green, 3));
                painter1.drawLine(sx*wScale,-sy*hScale,(sx + 1)*wScale,-(sy + 1)*hScale);
                ++sx;
                ++sy;
            }
        }
    }
}

