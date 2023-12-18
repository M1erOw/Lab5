#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include "customwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    QGridLayout *layout = new QGridLayout;
    QLabel* choose = new QLabel;
    QPushButton *SBS_Alg = new QPushButton;
    QPushButton *DDA = new QPushButton;
    QPushButton *Bres= new QPushButton;
    QPushButton *BresCircle = new QPushButton;
    QPushButton *CastlePitway = new QPushButton;
    QPushButton *Wu = new QPushButton;
    CustomWidget *wdgt = new CustomWidget;
public slots:
    void showCastlePitway();
    void showSBS();
    void showDDA();
    void showBresCircle();
    void showBres();
    void showWu();
};
#endif // MAINWINDOW_H
