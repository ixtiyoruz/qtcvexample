#ifndef CUPPROVIDER_H
#define CUPPROVIDER_H

#include <QObject>
#include <QImage>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <QMutex>
#include <QWaitCondition>

class CupProvider : public QObject
{
    Q_OBJECT
    cv::VideoCapture cam;
    QMutex sync;
    QWaitCondition pauseCond;
    bool pause= false;

public:
    explicit CupProvider(QObject *parent = nullptr);    
    void on_resume();
    void on_pause();
    bool is_paused();
public slots:
    void doWork();
signals:
    void imageChanged(cv::Mat image);
};
#endif // CUPPROVIDER_H
