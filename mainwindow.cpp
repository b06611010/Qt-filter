#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    img=cv::imread("987.jpg");
    QImage abc =cvMat2QImage(img);
    changedcolor=img.clone();
//    cvtColor(img,hsvimage,CV_BGR2HSV);

    const int w = ui->label_image->width();
    const int h = ui->label_image->height();

    ui->label_image->setPixmap(QPixmap::fromImage(abc.scaled(w,h,Qt::KeepAspectRatio)));

}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_pb_reverse_clicked()

{
    //cv::imshow("img", img);
    const int w = ui->label_image->width();
    const int h = ui->label_image->height();
    cv::Mat reverseImage =changedcolor.clone();
    for(int i=0;i<img.cols;i++)
    {
        for(int j=0;j<img.rows;j++)
        {
            reverseImage.at<cv::Vec3b>(changedcolor.rows-j-1,i)=changedcolor.at<cv::Vec3b>(j,i);
        }
    }
    changedcolor=reverseImage.clone();
    ui->label_image->setPixmap(QPixmap::fromImage(cvMat2QImage(changedcolor).scaled(w,h,Qt::KeepAspectRatio)));
}


void MainWindow::on_Slider_G_valueChanged(int value)
{
    ui->lcdNumber_G->display(value);
    const int w = ui->label_image->width();
    const int h = ui->label_image->height();
//    cv::Mat changedcolor = img.clone();

    for (int i=0;i<img.cols;i++)
    {
        for (int j=0;j<img.rows;j++)
        {
            int green = img.at<cv::Vec3b>(j,i).val[1];

            if(green+value>255)
            {
                changedcolor.at<cv::Vec3b>(j,i).val[1]=255;
            }
            else if(green+value<0)
            {
                changedcolor.at<cv::Vec3b>(j,i).val[1]=0;
            }
            else
            {
                changedcolor.at<cv::Vec3b>(j,i).val[1]=green+value;
            }

        }
    }
    ui->label_image->setPixmap(QPixmap::fromImage(cvMat2QImage(changedcolor).scaled(w,h,Qt::KeepAspectRatio)));
}

void MainWindow::on_pb_reset_clicked()
{
    const int w = ui->label_image->width();
    const int h = ui->label_image->height();

    ui->Slider_R->setValue(0);
    ui->Slider_G->setValue(0);
    ui->Slider_B->setValue(0);
    ui->Slider_H->setValue(0);
    ui->Slider_S->setValue(0);
    ui->Slider_V->setValue(0);
    changedcolor=img.clone();
    ui->label_image->setPixmap(QPixmap::fromImage(cvMat2QImage(changedcolor).scaled(w,h,Qt::KeepAspectRatio)));
}

void MainWindow::on_Slider_R_valueChanged(int value)
{
    ui->lcdNumber_R->display(value);
    const int w = ui->label_image->width();
    const int h = ui->label_image->height();
//    cv::Mat changedcolor = img.clone();

    for (int i=0;i<img.cols;i++)
    {
        for (int j=0;j<img.rows;j++)
        {
            int red = img.at<cv::Vec3b>(j,i).val[2];

            if(red+value>255)
            {
                changedcolor.at<cv::Vec3b>(j,i).val[2]=255;
            }
            else if(red+value<0)
            {
                changedcolor.at<cv::Vec3b>(j,i).val[2]=0;
            }
            else
            {
                changedcolor.at<cv::Vec3b>(j,i).val[2]=red+value;
            }

        }
    }
    ui->label_image->setPixmap(QPixmap::fromImage(cvMat2QImage(changedcolor).scaled(w,h,Qt::KeepAspectRatio)));
}

void MainWindow::on_Slider_B_valueChanged(int value)
{
    ui->lcdNumber_B->display(value);
    const int w = ui->label_image->width();
    const int h = ui->label_image->height();
//    cv::Mat changedcolor = img.clone();

    for (int i=0;i<img.cols;i++)
    {
        for (int j=0;j<img.rows;j++)
        {
            int blue = img.at<cv::Vec3b>(j,i).val[0];

            if(blue+value>255)
            {
                changedcolor.at<cv::Vec3b>(j,i).val[0]=255;
            }
            else if(blue+value<0)
            {
                changedcolor.at<cv::Vec3b>(j,i).val[0]=0;
            }
            else
            {
                changedcolor.at<cv::Vec3b>(j,i).val[0]=blue+value;
            }

        }
    }
    ui->label_image->setPixmap(QPixmap::fromImage(cvMat2QImage(changedcolor).scaled(w,h,Qt::KeepAspectRatio)));
}

void MainWindow::on_Slider_H_valueChanged(int value)
{
    ui->lcdNumber_H->display(value);
    const int w = ui->label_image->width();
    const int h = ui->label_image->height();
    cvtColor(changedcolor,hsvimage,CV_BGR2HSV);


    for (int i=0;i<img.cols;i++)
    {
        for (int j=0;j<img.rows;j++)
        {

            int H = hsvimage.at<cv::Vec3b>(j,i).val[0];

//             if(H+value>180)
//             {
//                 hsvimage.at<cv::Vec3b>(j,i).val[0]=180;
//             }
//             else if(H+value<0)
//             {
//                 hsvimage.at<cv::Vec3b>(j,i).val[0]=0;
//             }
//             else
//             {
//                 hsvimage.at<cv::Vec3b>(j,i).val[0]=H+value;
//             }
            hsvimage.at<cv::Vec3b>(j,i).val[0]=H+value;

        }
    }
    cvtColor(hsvimage,changedcolor,CV_HSV2BGR);
    ui->label_image->setPixmap(QPixmap::fromImage(cvMat2QImage(changedcolor).scaled(w,h,Qt::KeepAspectRatio)));
}

void MainWindow::on_Slider_S_valueChanged(int value)
{
    ui->lcdNumber_S->display(value);
    const int w = ui->label_image->width();
    const int h = ui->label_image->height();
    cvtColor(changedcolor,hsvimage,CV_BGR2HSV);


    for (int i=0;i<img.cols;i++)
    {
        for (int j=0;j<img.rows;j++)
        {

           int S = hsvimage.at<cv::Vec3b>(j,i).val[1];

            if(S+value>255)
            {
                hsvimage.at<cv::Vec3b>(j,i).val[1]=255;
            }
            else if(S+value<1)
            {
                hsvimage.at<cv::Vec3b>(j,i).val[1]=1;
            }
            else
            {
                hsvimage.at<cv::Vec3b>(j,i).val[1]=S+value;
            }

        }
    }
    cvtColor(hsvimage,changedcolor,CV_HSV2BGR);
    ui->label_image->setPixmap(QPixmap::fromImage(cvMat2QImage(changedcolor).scaled(w,h,Qt::KeepAspectRatio)));
}

void MainWindow::on_Slider_V_valueChanged(int value)
{
    ui->lcdNumber_V->display(value);
    const int w = ui->label_image->width();
    const int h = ui->label_image->height();
    cvtColor(changedcolor,hsvimage,CV_BGR2HSV);


    for (int i=0;i<img.cols;i++)
    {
        for (int j=0;j<img.rows;j++)
        {

           int V = hsvimage.at<cv::Vec3b>(j,i).val[2];

            if(V+value>255)
            {
                hsvimage.at<cv::Vec3b>(j,i).val[2]=255;
            }
            else if(V+value<1)
            {
                hsvimage.at<cv::Vec3b>(j,i).val[2]=1;
            }
            else
            {
                hsvimage.at<cv::Vec3b>(j,i).val[2]=V+value;
            }

        }
    }
    cvtColor(hsvimage,changedcolor,CV_HSV2BGR);
    ui->label_image->setPixmap(QPixmap::fromImage(cvMat2QImage(changedcolor).scaled(w,h,Qt::KeepAspectRatio)));
}

void MainWindow::on_pb_unsharp_clicked()
{
    cv::medianBlur(changedcolor,changedcolor,15);
    const int w = ui->label_image->width();
    const int h = ui->label_image->height();
    ui->label_image->setPixmap(QPixmap::fromImage(cvMat2QImage(changedcolor).scaled(w,h,Qt::KeepAspectRatio)));
}

void MainWindow::on_Slider_unsharp_valueChanged(int value)
{
    cv::medianBlur(img,changedcolor,value*2+1);
    const int w = ui->label_image->width();
    const int h = ui->label_image->height();
    ui->label_image->setPixmap(QPixmap::fromImage(cvMat2QImage(changedcolor).scaled(w,h,Qt::KeepAspectRatio)));
}

void MainWindow::on_Slider_box_valueChanged(int value)
{
    int k =0;
    k=value*2+1;
    cv::blur(img, changedcolor, cv::Size(k,k));
    const int w = ui->label_image->width();
    const int h = ui->label_image->height();
    ui->label_image->setPixmap(QPixmap::fromImage(cvMat2QImage(changedcolor).scaled(w,h,Qt::KeepAspectRatio)));
}

void MainWindow::on_Slider_Guassian_valueChanged(int value)
{
    int k =0;
    k=value*2+1;
    cv::GaussianBlur(img,changedcolor,cv::Size(k,k),0,0);
    const int w = ui->label_image->width();
    const int h = ui->label_image->height();
    ui->label_image->setPixmap(QPixmap::fromImage(cvMat2QImage(changedcolor).scaled(w,h,Qt::KeepAspectRatio)));
}

void MainWindow::on_Slider_Bilateral_valueChanged(int value)
{
    int k =0;
    k=value*2+1;
    cv::bilateralFilter(img,changedcolor,k,k*2,k/2);
    const int w = ui->label_image->width();
    const int h = ui->label_image->height();
    ui->label_image->setPixmap(QPixmap::fromImage(cvMat2QImage(changedcolor).scaled(w,h,Qt::KeepAspectRatio)));
}

void MainWindow::on_Slider_sharp_valueChanged(int value)
{
    int k =0;
    k=value*2+1;
    cv::Mat Kernel=(cv::Mat_<double>(3,3)<<0,-k,0,-k,k+4,-k,0,-k,0);
    cv::filter2D(img,changedcolor,0,Kernel);
    const int w = ui->label_image->width();
    const int h = ui->label_image->height();
    ui->label_image->setPixmap(QPixmap::fromImage(cvMat2QImage(changedcolor).scaled(w,h,Qt::KeepAspectRatio)));
}
