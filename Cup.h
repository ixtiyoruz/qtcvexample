#ifndef CUP_H
#define CUP_H

#include <QObject>
#include <QImage>
#include <opencv2/opencv.hpp>
//#include <opencv2/gpu/gpu.hpp>
#include <QMutex>
#include <QWaitCondition>

class CupWorker : public QObject
{
    Q_OBJECT
    cv::VideoCapture cam;
    QMutex sync;
    QWaitCondition pauseCond;
    bool pause= false;

public:
    explicit CupWorker(QObject *parent = nullptr);
    void on_resume();
    void on_pause();
    bool is_paused();
public slots:
    void doWork();
signals:
    void imageChanged(cv::Mat image);
};
#endif // CUP_H
