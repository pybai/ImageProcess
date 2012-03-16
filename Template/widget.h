#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QImage>


#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"

using namespace std;
using namespace cv;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_closeButton_clicked();

    void on_openButton_clicked();

private:
    Ui::Widget *ui;
    QImage* qimg;

    void clearImg(QImage* img);
    void MatToQImage(Mat* mat,QImage* img);
    void QImageToMat(QImage* img,Mat* mat);
};

#endif // WIDGET_H
