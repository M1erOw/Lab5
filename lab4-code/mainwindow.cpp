#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDialog>
#include <QTime>
#include <QSpinBox>
#include <ctime>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMinimumSize(590,490);
    connect(SBS_Alg, SIGNAL(clicked()), this, SLOT(showSBS()));
    connect(DDA, SIGNAL(clicked()), this, SLOT(showDDA()));
    connect(Bres, SIGNAL(clicked()), this, SLOT(showBres()));
    connect(BresCircle, SIGNAL(clicked()), this, SLOT(showBresCircle()));
    connect(CastlePitway, SIGNAL(clicked()), this, SLOT(showCastlePitway()));
    connect(Wu, SIGNAL(clicked()), this, SLOT(showWu()));
    choose->setText("Выберите алгоритм");
    choose->setAlignment(Qt::AlignCenter);
    SBS_Alg->setText("Пошаговый алгоритм");
    DDA->setText("Алгоритм ЦДА");
    Wu->setText("Алгоритм Ву");
    Bres->setText("Алгоритм Брезенхема");
    BresCircle->setText("Алгоритм Брезенхема (окружность)");
    CastlePitway->setText("Алгоритм Кастла-Питвея");
    layout->addWidget(choose, 0, 0, 1, 6);
    layout->addWidget(BresCircle, 11,0,1,1);
    layout->addWidget(Bres, 11,1,1,1);
    layout->addWidget(SBS_Alg, 11,2,1,1);
    layout->addWidget(DDA, 11,3,1,1);
    layout->addWidget(CastlePitway,11,4,1,1);
    layout->addWidget(Wu,11,5,1,1);
    layout->addWidget(wdgt,1,0,10,6);
    ui->centralwidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showSBS()
{
    QDialog *dial = new QDialog(this);
    QGridLayout *gl = new QGridLayout();
    QSpinBox *sbX1 = new QSpinBox;
    QSpinBox *sbX2 = new QSpinBox;
    QSpinBox *sbY1 = new QSpinBox;
    QSpinBox *sbY2 = new QSpinBox;
    int X1 = -12;
    int X2 = -12;
    int Y1 = -12;
    int Y2 = -12;
    sbX1->setMaximum(10);
    sbX1->setMinimum(-10);
    sbX2->setMaximum(10);
    sbX2->setMinimum(-10);
    sbY1->setMaximum(10);
    sbY1->setMinimum(-10);
    sbY2->setMaximum(10);
    sbY2->setMinimum(-10);
    QLabel *lX1 = new QLabel("X1 = ");
    QLabel *lX2 = new QLabel("X2 = ");
    QLabel *lY1 = new QLabel("Y1 = ");
    QLabel *lY2 = new QLabel("Y2 = ");
    QPushButton* Ok = new QPushButton("&Ok");
    QPushButton* Cancel = new QPushButton("&Cancel");
    connect(Ok, SIGNAL(clicked()),dial, SLOT(accept()));
    connect(Cancel, SIGNAL(clicked()),dial, SLOT(reject()));
    gl->addWidget(lX1, 0,0,1,1);
    gl->addWidget(lY1, 1,0,1,1);
    gl->addWidget(lX2, 0,2,1,1);
    gl->addWidget(lY2, 1,2,1,1);
    gl->addWidget(sbX1, 0,1,1,1);
    gl->addWidget(sbY1, 1,1,1,1);
    gl->addWidget(sbX2, 0,3,1,1);
    gl->addWidget(sbY2, 1,3,1,1);
    gl->addWidget(Ok, 2, 0,1,2);
    gl->addWidget(Cancel, 2, 3);
    dial->setLayout(gl);
    double k;
    double X = 0,Y = 0;
    double mem;
    switch(dial->exec() ) {
    case QDialog::Accepted:
        wdgt->PointList.clear();
        wdgt->PointListForCastlePitway.clear();
        wdgt->ListOfIntensy.clear();
        qDebug() << "Accepted";
        X1 = sbX1->value();
        X2 = sbX2->value();
        Y1 = sbY1->value();
        Y2 = sbY2->value();
        if(abs(X2 - X1) >= abs(Y2 - Y1))
        {
            k = (double)(Y2 - Y1)/(X2 - X1);
            if (X2 < X1){
                mem = X1;
                X1 = X2;
                X2 = mem;
                Y1 = Y2;
            }
            X = X1;
            Y = Y1;
            while (X <= X2) {
                wdgt->PointList.push_back(QPointF(round(X),round(Y)));
                ++X;
                Y += k;
            }
        }
        else{
            k = (double)(X2 - X1)/(Y2 - Y1);
            if (Y2 < Y1){
                mem = Y1;
                Y1 = Y2;
                Y2   = mem;
                X1 = X2;
            }
            Y = Y1;
            X = X1;

            while (Y <= Y2) {
                wdgt->PointList.push_back(QPointF(round(X),round(Y)));
                ++Y;
                X += k;
            }
        }
        break;
    case QDialog::Rejected:
        qDebug() << "Rejected";
        break;
    default:
        qDebug() << "Unexpected";
    }
    wdgt->repaint();
}
void MainWindow::showDDA()
{
    QDialog *dial = new QDialog(this);
    QGridLayout *gl = new QGridLayout();
    QSpinBox *sbX1 = new QSpinBox;
    QSpinBox *sbX2 = new QSpinBox;
    QSpinBox *sbY1 = new QSpinBox;
    QSpinBox *sbY2 = new QSpinBox;
    int X1 = -12;
    int X2 = -12;
    int Y1 = -12;
    int Y2 = -12;
    sbX1->setMaximum(10);
    sbX1->setMinimum(-10);
    sbX2->setMaximum(10);
    sbX2->setMinimum(-10);
    sbY1->setMaximum(10);
    sbY1->setMinimum(-10);
    sbY2->setMaximum(10);
    sbY2->setMinimum(-10);
    QLabel *lX1 = new QLabel("X1 = ");
    QLabel *lX2 = new QLabel("X2 = ");
    QLabel *lY1 = new QLabel("Y1 = ");
    QLabel *lY2 = new QLabel("Y2 = ");
    QPushButton* Ok = new QPushButton("&Ok");
    QPushButton* Cancel = new QPushButton("&Cancel");
    connect(Ok, SIGNAL(clicked()),dial, SLOT(accept()));
    connect(Cancel, SIGNAL(clicked()),dial, SLOT(reject()));
    gl->addWidget(lX1, 0,0,1,1);
    gl->addWidget(lY1, 1,0,1,1);
    gl->addWidget(lX2, 0,2,1,1);
    gl->addWidget(lY2, 1,2,1,1);
    gl->addWidget(sbX1, 0,1,1,1);
    gl->addWidget(sbY1, 1,1,1,1);
    gl->addWidget(sbX2, 0,3,1,1);
    gl->addWidget(sbY2, 1,3,1,1);
    gl->addWidget(Ok, 2, 0,1,2);
    gl->addWidget(Cancel, 2, 3);
    dial->setLayout(gl);
    double L,dx,dy;
    double X,Y;
    int i = 0;
    switch(dial->exec() ) {
    case QDialog::Accepted:
        wdgt->PointList.clear();
        wdgt->PointListForCastlePitway.clear();
        wdgt->ListOfIntensy.clear();
        qDebug() << "Accepted";
        X1 = sbX1->value();
        X2 = sbX2->value();
        Y1 = sbY1->value();
        Y2 = sbY2->value();
        dx = X2 - X1;
        dy = Y2 - Y1;
        X = X1;
        Y = Y1;
        L = fmax(abs(dx),abs(dy));
        while(i <= L)
        {
            wdgt->PointList.push_back(QPointF(round(X),round(Y)));
            X += dx / L;
            Y += dy / L;
            ++i;
        }
        break;
    case QDialog::Rejected:
        qDebug() << "Rejected";
        break;
    default:
        qDebug() << "Unexpected";
    }
    wdgt->repaint();
}
void MainWindow::showBres()
{
    QDialog *dial = new QDialog(this);
    QGridLayout *gl = new QGridLayout();
    QSpinBox *sbX1 = new QSpinBox;
    QSpinBox *sbX2 = new QSpinBox;
    QSpinBox *sbY1 = new QSpinBox;
    QSpinBox *sbY2 = new QSpinBox;
    int X1 = -12;
    int X2 = -12;
    int Y1 = -12;
    int Y2 = -12;
    sbX1->setMaximum(10);
    sbX1->setMinimum(-10);
    sbX2->setMaximum(10);
    sbX2->setMinimum(-10);
    sbY1->setMaximum(10);
    sbY1->setMinimum(-10);
    sbY2->setMaximum(10);
    sbY2->setMinimum(-10);
    QLabel *lX1 = new QLabel("X1 = ");
    QLabel *lX2 = new QLabel("X2 = ");
    QLabel *lY1 = new QLabel("Y1 = ");
    QLabel *lY2 = new QLabel("Y2 = ");
    QPushButton* Ok = new QPushButton("&Ok");
    QPushButton* Cancel = new QPushButton("&Cancel");
    connect(Ok, SIGNAL(clicked()),dial, SLOT(accept()));
    connect(Cancel, SIGNAL(clicked()),dial, SLOT(reject()));
    gl->addWidget(lX1, 0,0,1,1);
    gl->addWidget(lY1, 1,0,1,1);
    gl->addWidget(lX2, 0,2,1,1);
    gl->addWidget(lY2, 1,2,1,1);
    gl->addWidget(sbX1, 0,1,1,1);
    gl->addWidget(sbY1, 1,1,1,1);
    gl->addWidget(sbX2, 0,3,1,1);
    gl->addWidget(sbY2, 1,3,1,1);
    gl->addWidget(Ok, 2, 0,1,2);
    gl->addWidget(Cancel, 2, 3);
    dial->setLayout(gl);
    bool step;
    int dx,dy,error,ystep,Y ;
    switch( dial->exec() ) {
    case QDialog::Accepted:
        wdgt->PointList.clear();
        wdgt->PointListForCastlePitway.clear();
        wdgt->ListOfIntensy.clear();
        qDebug() << "Accepted";
        X1 = sbX1->value();
        X2 = sbX2->value();
        Y1 = sbY1->value();
        Y2 = sbY2->value();
        step = abs(Y2 - Y1) > abs(X2 - X1);
        if (step)
        {
            int mem = X1;
            X1 = Y1;
            Y1 = mem;
            mem = X2;
            X2 = Y2;
            Y2 = mem;
        }
        if(X1 > X2){
            int mem = X1;
            X1 = X2;
            X2 = mem;
            mem = Y1;
            Y1 = Y2;
            Y2 = mem;
        }
        dx = X2 - X1;
        dy = abs(Y2 - Y1);
        error = dx/2;
        ystep = (Y1 < Y2) ? 1 : -1;
        Y = Y1;
        for(int X = X1; X <= X2; ++X)
        {
            wdgt->PointList.push_back(QPointF(step ? Y : X,step ? X : Y));
            error -= dy;
            if (error < 0)
            {
                Y += ystep;
                error += dx;
            }
        }
        break;
    case QDialog::Rejected:
        qDebug() << "Rejected";
        break;
    default:
        qDebug() << "Unexpected";
    }
    wdgt->repaint();
}
void MainWindow::showBresCircle()
{
    QDialog *dial = new QDialog(this);
    QGridLayout *gl = new QGridLayout();
    QSpinBox *sbX1 = new QSpinBox;
    QSpinBox *sbY1 = new QSpinBox;
    QSpinBox *sbR = new QSpinBox;
    int X1 = 0;
    int Y1 = 0;
    int R = 0;
    sbX1->setMaximum(10);
    sbX1->setMinimum(-10);
    sbY1->setMaximum(10);
    sbY1->setMinimum(-10);
    sbR->setMaximum(10);
    sbR->setMinimum(0);
    QLabel *lX1 = new QLabel("X0 = ");
    QLabel *lY1 = new QLabel("Y0 = ");
    QLabel *lR = new QLabel("R = ");
    QPushButton* Ok = new QPushButton("&Ok");
    QPushButton* Cancel = new QPushButton("&Cancel");
    connect(Ok, SIGNAL(clicked()),dial, SLOT(accept()));
    connect(Cancel, SIGNAL(clicked()),dial, SLOT(reject()));
    gl->addWidget(lX1, 0,0,1,1);
    gl->addWidget(lY1, 1,0,1,1);
    gl->addWidget(lR, 0,2,2,1);
    gl->addWidget(sbX1, 0,1,1,1);
    gl->addWidget(sbY1, 1,1,1,1);
    gl->addWidget(sbR, 0,3,2,1);
    gl->addWidget(Ok, 2, 0,1,2);
    gl->addWidget(Cancel, 2, 3);
    dial->setLayout(gl);
    int X,Y,E;
    switch( dial->exec() ) {
    case QDialog::Accepted:
        wdgt->PointList.clear();
        wdgt->PointListForCastlePitway.clear();
        wdgt->ListOfIntensy.clear();
        qDebug() << "Accepted";
        X1 = sbX1->value();
        Y1 = sbY1->value();
        R = sbR->value();
        if(X1 + R > 10 || Y1 + R > 10 || X1 - R < -10 || Y1 - R < -10){
            qDebug() << "I cant draw it :(";
            break;
        }
        X = 0;
        Y = R;
        E = 3 - 2 * R;
        while(X <= Y)
        {
            wdgt->PointList.push_back(QPointF(X + X1,Y + Y1));
            wdgt->PointList.push_back(QPointF(X + X1,-Y + Y1));
            wdgt->PointList.push_back(QPointF(-X + X1,Y + Y1));
            wdgt->PointList.push_back(QPointF(-X + X1,-Y + Y1));
            wdgt->PointList.push_back(QPointF(Y + X1,X + Y1));
            wdgt->PointList.push_back(QPointF(Y + X1,-X + Y1));
            wdgt->PointList.push_back(QPointF(-Y + X1,X + Y1));
            wdgt->PointList.push_back(QPointF(-Y + X1,-X + Y1));
            E += E < 0 ? 4 * X + 6 : 4 * (X - Y--) + 10;
            ++X;
        }
        break;
    case QDialog::Rejected:
        qDebug() << "Rejected";
        break;
    default:
        qDebug() << "Unexpected";
    }
    wdgt->repaint();
}
void MainWindow::showCastlePitway()
{
    QDialog *dial = new QDialog(this);
    QGridLayout *gl = new QGridLayout();
    QSpinBox *sbX1 = new QSpinBox;
    QSpinBox *sbX2 = new QSpinBox;
    QSpinBox *sbY1 = new QSpinBox;
    QSpinBox *sbY2 = new QSpinBox;
    int X1 = -12;
    int X2 = -12;
    int Y1 = -12;
    int Y2 = -12;
    sbX1->setMaximum(10);
    sbX1->setMinimum(-10);
    sbX2->setMaximum(10);
    sbX2->setMinimum(-10);
    sbY1->setMaximum(10);
    sbY1->setMinimum(-10);
    sbY2->setMaximum(10);
    sbY2->setMinimum(-10);
    QLabel *lX1 = new QLabel("X1 = ");
    QLabel *lX2 = new QLabel("X2 = ");
    QLabel *lY1 = new QLabel("Y1 = ");
    QLabel *lY2 = new QLabel("Y2 = ");
    QPushButton* Ok = new QPushButton("&Ok");
    QPushButton* Cancel = new QPushButton("&Cancel");
    connect(Ok, SIGNAL(clicked()),dial, SLOT(accept()));
    connect(Cancel, SIGNAL(clicked()),dial, SLOT(reject()));
    gl->addWidget(lX1, 0,0,1,1);
    gl->addWidget(lY1, 1,0,1,1);
    gl->addWidget(lX2, 0,2,1,1);
    gl->addWidget(lY2, 1,2,1,1);
    gl->addWidget(sbX1, 0,1,1,1);
    gl->addWidget(sbY1, 1,1,1,1);
    gl->addWidget(sbX2, 0,3,1,1);
    gl->addWidget(sbY2, 1,3,1,1);
    gl->addWidget(Ok, 2, 0,1,2);
    gl->addWidget(Cancel, 2, 3);
    dial->setLayout(gl);
    std::string m1 = "s",m2 = "d";
    switch(int Y,X; dial->exec() ) {
    case QDialog::Accepted:
        wdgt->PointList.clear();
        wdgt->PointListForCastlePitway.clear();
        wdgt->ListOfIntensy.clear();
        qDebug() << "Accepted";
        X1 = sbX1->value();
        X2 = sbX2->value();
        Y1 = sbY1->value();
        Y2 = sbY2->value();
        Y = Y2 - Y1;
        X = X2 - X1 - Y;
        while(X != Y)
        {
            if(X > Y)
            {
                X -= Y;
                reverse(m2.begin(),m2.end());
                m2 = m1 + m2;
                reverse(m2.begin(),m2.end());
            }
            else{
                Y -= X;
                reverse(m1.begin(),m1.end());
                m1 = m2 + m1;
                reverse(m1.begin(),m1.end());
            }
        }
        reverse(m1.begin(),m1.end());
        for(int i = 0; i < (int)(m2 + m1).size(); ++i)
            wdgt->PointListForCastlePitway.push_back((m2 + m1)[i]);
        if(wdgt->PointListForCastlePitway.size() != X2 - X1)
        {
            int a = wdgt->PointListForCastlePitway.size();
            for(int i = 0; i < ((X2 - X1) / a) - 1; ++i)
                for(int j = 0; j < (int)(m2 + m1).size(); ++j)
                    wdgt->PointListForCastlePitway.push_back((m2 + m1)[j]);
        }
        break;
    case QDialog::Rejected:
        qDebug() << "Rejected";
        break;
    default:
        qDebug() << "Unexpected";
    }
    wdgt->startX = X1;
    wdgt->startY = Y1;

}
void MainWindow::showWu()
{
    QDialog *dial = new QDialog(this);
    QGridLayout *gl = new QGridLayout();
    QSpinBox *sbX1 = new QSpinBox;
    QSpinBox *sbX2 = new QSpinBox;
    QSpinBox *sbY1 = new QSpinBox;
    QSpinBox *sbY2 = new QSpinBox;
    int X1 = -12;
    int X2 = -12;
    int Y1 = -12;
    int Y2 = -12;
    sbX1->setMaximum(10);
    sbX1->setMinimum(-10);
    sbX2->setMaximum(10);
    sbX2->setMinimum(-10);
    sbY1->setMaximum(10);
    sbY1->setMinimum(-10);
    sbY2->setMaximum(10);
    sbY2->setMinimum(-10);
    QLabel *lX1 = new QLabel("X1 = ");
    QLabel *lX2 = new QLabel("X2 = ");
    QLabel *lY1 = new QLabel("Y1 = ");
    QLabel *lY2 = new QLabel("Y2 = ");
    QPushButton* Ok = new QPushButton("&Ok");
    QPushButton* Cancel = new QPushButton("&Cancel");
    connect(Ok, SIGNAL(clicked()),dial, SLOT(accept()));
    connect(Cancel, SIGNAL(clicked()),dial, SLOT(reject()));
    gl->addWidget(lX1, 0,0,1,1);
    gl->addWidget(lY1, 1,0,1,1);
    gl->addWidget(lX2, 0,2,1,1);
    gl->addWidget(lY2, 1,2,1,1);
    gl->addWidget(sbX1, 0,1,1,1);
    gl->addWidget(sbY1, 1,1,1,1);
    gl->addWidget(sbX2, 0,3,1,1);
    gl->addWidget(sbY2, 1,3,1,1);
    gl->addWidget(Ok, 2, 0,1,2);
    gl->addWidget(Cancel, 2, 3);
    dial->setLayout(gl);
    bool step;
    switch(float dx,gradient,y,dy; dial->exec() ) {
    case QDialog::Accepted:
        wdgt->PointList.clear();
        wdgt->PointListForCastlePitway.clear();
        wdgt->ListOfIntensy.clear();
        qDebug() << "Accepted";
        X1 = sbX1->value();
        X2 = sbX2->value();
        Y1 = sbY1->value();
        Y2 = sbY2->value();
        step = abs(Y2 - Y1) > abs(X2 - X1);
        if (step)
        {
            int mem = X1;
            X1 = Y1;
            Y1 = mem;
            mem = X2;
            X2 = Y2;
            Y2 = mem;
        }
        if(X1 > X2){
            int mem = X1;
            X1 = X2;
            X2 = mem;
            mem = Y1;
            Y1 = Y2;
            Y2 = mem;
        }
        if(step){
            wdgt->PointList.push_back(QPointF(Y1, X1));
            wdgt->PointList.push_back(QPointF(Y2, X2));
            wdgt->ListOfIntensy.push_back(1);
            wdgt->ListOfIntensy.push_back(1);
        }
        else{
            wdgt->PointList.push_back(QPointF(X1, Y1));
            wdgt->PointList.push_back(QPointF(X2, Y2));
            wdgt->ListOfIntensy.push_back(1);
            wdgt->ListOfIntensy.push_back(1);
        }
        dx = X2 - X1;
        dy = Y2 - Y1;
        gradient = dy / dx;
        y = Y1 + gradient;
        for (int x = X1 + 1; x <= X2 - 1; ++x)
        {
            if(step){
                wdgt->PointList.push_back(QPointF((int)y, x));
                wdgt->PointList.push_back(QPointF((int)y + 1, x));
                wdgt->ListOfIntensy.push_back(1 - (y - (int)y));
                wdgt->ListOfIntensy.push_back(y - (int)y);
            }
            else{
                wdgt->PointList.push_back(QPointF(x, (int)y));
                wdgt->PointList.push_back(QPointF(x, (int)y + 1));
                wdgt->ListOfIntensy.push_back(1 - (y - (int)y));
                wdgt->ListOfIntensy.push_back(y - (int)y);
            }
            y += gradient;
        }
        break;
    case QDialog::Rejected:
        qDebug() << "Rejected";
        break;
    default:
        qDebug() << "Unexpected";
    }
    wdgt->repaint();
}


