#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <QPainter>

class CustomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    void DrawLine(QPair<QPointF,QPointF>);
    int getCode(QPointF);
    int xMin,xMax,yMin,yMax;
    QList<QPair<QPointF,QPointF>> lines;
    QList<QPair<QPointF,QPointF>> procLines;
    int windXMin, windXMax, windYMin, windYMax;
    bool flag = false;
};

#endif // CUSTOMWIDGET_H
