#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText(" ");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QFileDialog *file = new QFileDialog;
    file->setWindowTitle("Open file");
    QList<QUrl> elements = file->getOpenFileUrls();
    //QUrl elem = file->getOpenFileUrl();

    if(elements.size() == 1)
    {
        QFile jfile(elements[0].toLocalFile());
        QString resolution = "";
        if (jfile.fileName().lastIndexOf('.') == -1)
        {

            return;
        }
        for(int i = jfile.fileName().lastIndexOf('.'); i < jfile.fileName().size(); i++)
        {
            resolution.append(jfile.fileName()[i]);
        }
        if (resolution != ".jpg" && resolution != ".gif" && resolution != ".tif" && resolution != ".bmp" &&
            resolution != ".png" && resolution != ".pcx" && resolution != ".BMP")

        {
            return;
        }

        QString fileName = "";
        for(int i = jfile.fileName().lastIndexOf('/') + 1; i < jfile.fileName().lastIndexOf('.'); i++)
        {
            fileName.append(jfile.fileName()[i]);
        }
        QImage im(elements[0].toLocalFile());
        QImageWriter a(elements[0].toLocalFile());
        ui->FileName->setText(fileName);
        ui->Size->setText(QString::number(im.size().width() )+ "x" + QString::number(im.size().height() ));
        ui->Contraction->setText(QString::number(a.compression()));
        ui->Color_depth->setText(QString::number(im.depth()));
        ui->Resolution->setText(QString::number(im.physicalDpiX()));
        ui->lineEdit->setText(jfile.fileName());
        int w = ui->Picture->width();
        int h = ui->Picture->height();
        ui->Picture->setPixmap(QPixmap(jfile.fileName()).scaled(w,h,Qt::KeepAspectRatio));
    }
    else{
        QDialog *tableW = new QDialog();
        QGridLayout *tableGL = new QGridLayout;
        table = new QTableWidget;
        table->setColumnCount(5);
        table->setRowCount(elements.size());
        table->setHorizontalHeaderItem(0, new QTableWidgetItem("Файл"));
        table->setHorizontalHeaderItem(1, new QTableWidgetItem("Размер"));
        table->setHorizontalHeaderItem(2, new QTableWidgetItem("Сжатие"));
        table->setHorizontalHeaderItem(3, new QTableWidgetItem("Глубина цвета"));
        table->setHorizontalHeaderItem(4, new QTableWidgetItem("Разрешение"));
        for(int i = 0; i < elements.size(); i++)
        {
            QFile temp(elements[i].toLocalFile());
            QString resolution = "";
            if (temp.fileName().lastIndexOf('.') == -1)
            {
                table->setRowCount(table->rowCount()-1);
                continue;
            }
            for(int i = temp.fileName().lastIndexOf('.'); i < temp.fileName().size(); i++)
            {
                resolution.append(temp.fileName()[i]);
            }
            if (resolution != ".jpg" && resolution != ".gif" && resolution != ".tif" && resolution != ".bmp" &&
                resolution != ".png" && resolution != ".pcx" && resolution != ".BMP")

            {
                table->setRowCount(table->rowCount()-1);
                continue;
            }
            QString fileName = "";
            for(int i = temp.fileName().lastIndexOf('/') + 1; i < temp.fileName().lastIndexOf('.'); i++)
            {
                fileName.append(temp.fileName()[i]);
            }
            table->setItem(i,0,new QTableWidgetItem(fileName));
            QImage im(elements[i].toLocalFile());
            QImageWriter a(elements[i].toLocalFile());
            table->setItem(i, 1, new QTableWidgetItem(QString::number(im.size().width())+"x"+QString::number(im.size().height())));
            table->setItem(i, 4, new QTableWidgetItem(QString::number(im.physicalDpiX())));
            table->setItem(i, 3, new QTableWidgetItem(QString::number(im.depth())));
            table->setItem(i, 2, new QTableWidgetItem(QString::number(a.compression())));
        }
        if (table->rowCount() == 0)
        {
            return;
        }
        tableGL->addWidget(table,0,0);
        tableW->setLayout(tableGL);
        tableW->show();
        tableW->setMinimumSize(540,200);
        connect(tableW, SIGNAL(rejected()), this, SLOT(widgetClose()));
        this->hide();
    }
}

void MainWindow::widgetClose()
{
    this->show();
}
