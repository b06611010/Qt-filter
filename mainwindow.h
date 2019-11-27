#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QDebug"
#include "opencv2/opencv.hpp"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_reverse_clicked();


    void on_Slider_G_valueChanged(int value);

    void on_pb_reset_clicked();

    void on_Slider_R_valueChanged(int value);

    void on_Slider_B_valueChanged(int value);

    void on_Slider_H_valueChanged(int value);

    void on_Slider_S_valueChanged(int value);

    void on_Slider_V_valueChanged(int value);

    void on_pb_unsharp_clicked();

    void on_Slider_unsharp_valueChanged(int value);

    void on_Slider_box_valueChanged(int value);

    void on_Slider_Guassian_valueChanged(int value);

    void on_Slider_Bilateral_valueChanged(int value);

    void on_Slider_sharp_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    cv::Mat img;
    cv::Mat changedcolor ;
    cv::Mat hsvimage;
    cv::Mat last;
    QImage cvMat2QImage(const cv::Mat& mat)
    {
        // 8-bits unsigned, NO. OF CHANNELS = 1
        if(mat.type() == CV_8UC1)
        {
            QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
            // Set the color table (used to translate colour indexes to qRgb values)
            image.setColorCount(256);
            for(int i = 0; i < 256; i++)
            {
                image.setColor(i, qRgb(i, i, i));
            }
            // Copy input Mat
            uchar *pSrc = mat.data;
            for(int row = 0; row < mat.rows; row ++)
            {
                uchar *pDest = image.scanLine(row);
                memcpy(pDest, pSrc, mat.cols);
                pSrc += mat.step;
            }
            return image;
        }
        // 8-bits unsigned, NO. OF CHANNELS = 3
        else if(mat.type() == CV_8UC3)
        {
            // Copy input Mat
            const uchar *pSrc = (const uchar*)mat.data;
            // Create QImage with same dimensions as input Mat
            QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
            return image.rgbSwapped();
        }
        else if(mat.type() == CV_8UC4)
        {
            qDebug() << "CV_8UC4";
            // Copy input Mat
            const uchar *pSrc = (const uchar*)mat.data;
            // Create QImage with same dimensions as input Mat
            QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
            return image.copy();
        }
        else
        {
            qDebug() << "ERROR: Mat could not be converted to QImage.";
            return QImage();
        }
    }

};

#endif // MAINWINDOW_H
