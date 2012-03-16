#include "widget.h"
#include "ui_widget.h"
#include<QtGui>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    qimg = NULL;

    ui->setupUi(this);
    this->resize(800,600);    
}

Widget::~Widget()
{
    clearImg(qimg);
    delete ui;
}

void Widget::on_closeButton_clicked()
{
    this->close();
}

void Widget::on_openButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"OpenImage","G:/","Image Files(*.jpg *.png *.jpeg *.bmp)");

    clearImg(qimg);
    qimg =new QImage(fileName);
    *qimg = qimg->convertToFormat(QImage::Format_RGB888);

    ui->imglabel->setPixmap(QPixmap::fromImage(*qimg));

}

void Widget::clearImg(QImage *img)
{
    if(img)
        delete img;
}

void Widget::MatToQImage(Mat *mat, QImage *img)
{
    int channels = mat->channels();
    if(channels == 3)
        cvtColor(*mat,*mat,CV_BGR2RGB);
    uchar* matPtr = mat->data;
    uchar* imgPtr = img->bits();
    for(int j = 0;j<mat->rows;j++)
    {
        for(int i=0;i<mat->cols;i++)
        {
            if(channels == 3)
            {
                *(imgPtr++) = *(matPtr++);
                *(imgPtr++) = *(matPtr++);
                *(imgPtr++) = *(matPtr++);
            }else
            {
                *(imgPtr++) = *matPtr;
                *(imgPtr++) = *matPtr;
                *(imgPtr++) = *matPtr++;
            }
        }
    }
}

void Widget::QImageToMat(QImage *img, Mat *mat)
{
    int channels = mat->channels();
    uchar* matPtr = mat->data;
    uchar* imgPtr = img->bits();
    for(int j = 0;j<mat->rows;j++)
    {
        for(int i=0;i<mat->cols;i++)
        {
            if(channels == 3)
            {
                *(matPtr++)=*(imgPtr++) ;
                *(matPtr++)=*(imgPtr++) ;
                *(matPtr++)=*(imgPtr++) ;
            }else
            {
                *matPtr=*(imgPtr++) ;
                *matPtr=*(imgPtr++) ;
                *matPtr=*(imgPtr++) ;
            }
        }
    }
    cvtColor(*mat,*mat,CV_BGR2RGB);
}
