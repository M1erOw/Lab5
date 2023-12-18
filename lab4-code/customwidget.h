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
    QList<QPointF> PointList;
    QList<float> ListOfIntensy;
    QList<char> PointListForCastlePitway;
    int startX;
    int startY;
};

#endif // CUSTOMWIDGET_H
