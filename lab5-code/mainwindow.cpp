#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include<iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMinimumSize(590,490);
    connect(Polygon, SIGNAL(clicked()), this, SLOT(showPolygon()));
    connect(Central, SIGNAL(clicked()), this, SLOT(showCentral()));
    Polygon->setText("Алгоритм отсечения выпуклого многоугольника");
    Central->setText("Алгоритм средней точки");
    layout->addWidget(Polygon, 0, 0, 1, 1);
    layout->addWidget(Central, 0,1,1,1);
    layout->addWidget(wdgt,1,0,9,2);
    ui->centralwidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showCentral()
{
    wdgt->lines.clear();
    wdgt->procLines.clear();
    wdgt->flag = false;
    std::ifstream fin("C:/Users/user/QT_lab/PKG_lab5/input.txt");
    int n;
    fin >> n;
    int x1,y1,x2,y2;
    int xMin = 0,xMax = 0,yMin = 0,yMax = 0;
    for(int i = 0; i < n; i++){
        fin>>x1>>y1>>x2>>y2;
        if(x1 > xMax)
            xMax = x1;
        if(x2 > xMax)
            xMax = x2;
        if(y1 > yMax)
            yMax = y1;
        if(y2 > yMax)
            yMax = y2;
        if(x1 < xMin)
            xMin = x1;
        if(x2 < xMin)
            xMin = x2;
        if(y1 < yMin)
            yMin = y1;
        if(y2 < yMin)
            yMin = y2;
        wdgt->lines.push_back(qMakePair(QPointF(x1,y1),QPointF(x2,y2)));
    }
    fin>>wdgt->windXMin>>wdgt->windYMin>>wdgt->windXMax>>wdgt->windYMax;
    wdgt->xMin = xMin < wdgt->windXMin ? xMin : wdgt->windXMin;
    wdgt->xMax = xMax > wdgt->windXMax ? xMax : wdgt->windXMax;
    wdgt->yMin = yMin < wdgt->windYMin ? yMin : wdgt->windYMin;
    wdgt->yMax = yMax > wdgt->windYMax ? yMax : wdgt->windYMax;
    wdgt->repaint();
}

void MainWindow::showPolygon()
{
    std::ifstream fin("C:/Users/user/QT_lab/PKG_lab5/input2.txt");
    wdgt->lines.clear();
    wdgt->procLines.clear();
    //wdgt->flag = true;
    int n;
    fin >> n;
    int x1,y1;
    int xMin = 0,xMax = 0,yMin = 0,yMax = 0;
    QList<QPointF> Points;
    for(int i = 0; i < n; i++){
        fin>>x1>>y1;
        if(x1 > xMax)
            xMax = x1;
        if(y1 > yMax)
            yMax = y1;
        if(x1 < xMin)
            xMin = x1;
        if(y1 < yMin)
            yMin = y1;
        Points.push_back(QPointF(x1,y1));
    }
    for(int i = 0; i < Points.size(); ++i){
        if(i != Points.size() - 1)
            wdgt->lines.push_back(qMakePair(Points[i],Points[i + 1]));
        else
            wdgt->lines.push_back(qMakePair(Points[i],Points[0]));
    }
    int wxmi;
    int wymi;
    int wxma;
    int wyma;
    fin>>wxmi>>wymi>>wxma>>wyma;
    wdgt->windXMin = wxmi;
    wdgt->windYMin = wymi;
    wdgt->windXMax = wxma;
    wdgt->windYMax = wyma;
    QList<QPointF> WPoints;
    WPoints.push_back(QPointF(wxmi,wymi));
    WPoints.push_back(QPointF(wxmi,wyma));
    WPoints.push_back(QPointF(wxma,wyma));
    WPoints.push_back(QPointF(wxma,wymi));
    QList<QPointF> ProcPoints;
    for(int i = 0; i < WPoints.size(); ++i){
        QPointF startW = WPoints[i],endW;
        if(i == WPoints.size() - 1)
            endW = WPoints[0];
        else
            endW = WPoints[i + 1];
        for(int j = 0; j < Points.size(); ++j){
            QPointF start = Points[j],end;
            if(j == Points.size() - 1)
                end = Points[0];
            else
                end = Points[j + 1];
            if(((endW.x() - startW.x()) * (start.y() - startW.y()) - (start.x() - startW.x()) * (endW.y() - startW.y())) < 0 &&
                ((endW.x() - startW.x()) * (end.y() - startW.y()) - (end.x() - startW.x()) * (endW.y() - startW.y())) < 0){
                ProcPoints.push_back(end);
            }
            else if(((endW.x() - startW.x()) * (start.y() - startW.y()) - (start.x() - startW.x()) * (endW.y() - startW.y())) < 0){
                if(startW.x() == endW.x())
                {
                    float k = (float)(end.y() - start.y()) / (end.x() - start.x());
                    float b = (float)end.y() - k * (float)end.x();
                    float ynew = k * startW.x() + b;
                    ProcPoints.push_back(QPointF(startW.x(),ynew));
                }
                else{
                    float k = (float)(end.x() - start.x()) / (end.y() - start.y());
                    float b = (float)end.x() - k * (float)end.y();
                    float xnew = k * startW.y() + b;
                    ProcPoints.push_back(QPointF(xnew,startW.y()));
                }
            }
            else if(((endW.x() - startW.x()) * (end.y() - startW.y()) - (end.x() - startW.x()) * (endW.y() - startW.y())) < 0){
                if(startW.x() == endW.x())
                {
                    float k = (float)(end.y() - start.y()) / (end.x() - start.x());
                    float b = (float)end.y() - k * (float)end.x();
                    float ynew = k * startW.x() + b;
                    ProcPoints.push_back(QPointF(startW.x(),ynew));
                }
                else{
                    float k = (float)(end.x() - start.x()) / (end.y() - start.y());
                    float b = (float)end.x() - k * (float)end.y();
                    float xnew = k * startW.y() + b;
                    ProcPoints.push_back(QPointF(xnew,startW.y()));
                }
                ProcPoints.push_back(end);
            }
        }
        Points = ProcPoints;
        ProcPoints.clear();
    }
    for(int i = 0; i < Points.size(); ++i){
        if(i != Points.size() - 1)
            wdgt->procLines.push_back(qMakePair(Points[i],Points[i + 1]));
        else
            wdgt->procLines.push_back(qMakePair(Points[i],Points[0]));
    }
    wdgt->xMin = xMin < wdgt->windXMin ? xMin : wdgt->windXMin;
    wdgt->xMax = xMax > wdgt->windXMax ? xMax : wdgt->windXMax;
    wdgt->yMin = yMin < wdgt->windYMin ? yMin : wdgt->windYMin;
    wdgt->yMax = yMax > wdgt->windYMax ? yMax : wdgt->windYMax;
    wdgt->repaint();
}
