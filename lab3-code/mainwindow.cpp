#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    button = new QPushButton("Выбор файла");
    QGridLayout *lay = new QGridLayout;
    QLabel *text1 = new QLabel("Глобальная пороговая обработка");
    text1->setAlignment(Qt::AlignCenter);
    QLabel *text2 = new QLabel("Адаптивная пороговая обработка");
    text2->setAlignment(Qt::AlignCenter);
    QLabel *text3 = new QLabel("Сегментация изображения");
    text3->setAlignment(Qt::AlignCenter);
    QLabel *text4 = new QLabel("Оригинальное изображение");
    text4->setAlignment(Qt::AlignCenter);
    lab1 = new QLabel;
    lab2 = new QLabel;
    lab3 = new QLabel;
    lab4 = new QLabel;
    lab5 = new QLabel;
    connect(button,SIGNAL(clicked()),this,SLOT(on_button_clicked()));
    lay->addWidget(button,0,0,1,6);
    lay->addWidget(text1,1,0,1,4);
    lay->addWidget(text4,1,4,1,2);
    lay->addWidget(lab1,2,0,5,2);
    lay->addWidget(lab2,2,2,5,2);
    lay->addWidget(lab3,2,4,5,2);
    lay->addWidget(text2,7,0,1,3);
    lay->addWidget(text3,7,3,1,3);
    lay->addWidget(lab4,8,0,8,3);
    lay->addWidget(lab5,8,3,8,3);
    ui->centralwidget->setLayout(lay);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_clicked()
{
    QFileDialog *file = new QFileDialog;
    file->setWindowTitle("Open file");
    QUrl element = file->getOpenFileUrl();

    QPixmap pixmap = QPixmap(element.toLocalFile());
    QImage originalImage = pixmap.toImage();

    lab3->setPixmap(pixmap);
    lab3->setScaledContents(false);

    cv::Mat inputImage(originalImage.height(), originalImage.width(), CV_8UC4, originalImage.bits(), originalImage.bytesPerLine());
    cv::Mat processedImage;

    cv::cvtColor(inputImage, processedImage, cv::COLOR_BGR2GRAY);

    QImage processedQImage(processedImage.data, processedImage.cols, processedImage.rows, processedImage.step, QImage::Format_Grayscale8);
    QPixmap processedPixmap = QPixmap::fromImage(processedQImage);

    lab1->setPixmap(processedPixmap);
    lab1->setScaledContents(false);


    cv::Mat inputImage1(originalImage.height(), originalImage.width(), CV_8UC4, originalImage.bits(), originalImage.bytesPerLine());
    cv::Mat processedImage1;

    cv::cvtColor(inputImage1, processedImage1, cv::COLOR_BGR2GRAY);
    cv::threshold(processedImage1, processedImage1, 128, 255, cv::THRESH_BINARY);

    QImage processedQImage1(processedImage1.data, processedImage1.cols, processedImage1.rows, processedImage1.step, QImage::Format_Grayscale8);

    QPixmap processedPixmap1 = QPixmap::fromImage(processedQImage1);
    lab2->setPixmap(processedPixmap1);
    lab2->setScaledContents(false);

    cv::Mat inputImage2(originalImage.height(), originalImage.width(), CV_8UC4, originalImage.bits(), originalImage.bytesPerLine());
    cv::Mat processedImage2;

    cv::cvtColor(inputImage2, processedImage2, cv::COLOR_BGR2GRAY);
    cv::adaptiveThreshold(processedImage2, processedImage2, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 11, 2);

    QImage processedQImage2(processedImage2.data, processedImage2.cols, processedImage2.rows, processedImage2.step, QImage::Format_Grayscale8);

    QPixmap processedPixmap2 = QPixmap::fromImage(processedQImage2);

    lab4->setPixmap(processedPixmap2);
    lab4->setScaledContents(false);

    cv::Mat inputImage3(originalImage.height(), originalImage.width(), CV_8UC4, originalImage.bits(), originalImage.bytesPerLine());
    cv::Mat processedImage3;
    cv::cvtColor(inputImage3, processedImage3, cv::COLOR_BGR2GRAY);

    // Обнаружение точек (Harris-углы)
    cv::Mat harrisCorners;
    cv::cornerHarris(processedImage, harrisCorners, 2, 3, 0.04);
    cv::dilate(harrisCorners, harrisCorners, cv::Mat());

    // Обнаружение линий (Преобразование Хафа)
    std::vector<cv::Vec2f> houghLines;
    cv::HoughLines(processedImage, houghLines, 1, CV_PI / 180, 100);

    // Обнаружение перепадов яркости (Canny-границы)
    cv::Mat cannyEdges;
    cv::Canny(processedImage, cannyEdges, 50, 150);


    QLabel processedLabel;
    lab5->setPixmap(QPixmap::fromImage(QImage(cannyEdges.data, cannyEdges.cols, cannyEdges.rows, cannyEdges.step, QImage::Format_Grayscale8)));
    lab5->setScaledContents(false);
}

