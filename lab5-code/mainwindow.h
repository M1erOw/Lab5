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
    QPushButton *Central = new QPushButton;
    QPushButton *Polygon = new QPushButton;
    CustomWidget *wdgt = new CustomWidget;
public slots:
    void showCentral();
    void showPolygon();

};
#endif // MAINWINDOW_H
