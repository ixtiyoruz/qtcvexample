#ifndef CUPPROVIDERCONTROLLER_H
#define CUPPROVIDERCONTROLLER_H
#include <QObject>
#include <QThread>
#include <CupProvider.h>
#include <QDebug>
#include <QMutex>
class CupProviderController : public QObject
{
    Q_OBJECT
    QThread workerThread;
    Q_PROPERTY(QImage image MEMBER m_image READ image WRITE setImage NOTIFY imageChanged)
    QImage m_image;
    QMutex mutex;
    bool paused=false;
public:
    CupProvider *worker;
    explicit CupProviderController(QObject *parent = nullptr): QObject(parent) {
        worker = new CupProvider;
        worker->moveToThread(&workerThread);
        connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
        connect(this, &CupProviderController::operate, worker, &CupProvider::doWork);
        connect(worker, &CupProvider::imageChanged, this, &CupProviderController::handleCup);
        workerThread.start();

    }
    ~CupProviderController() {
        workerThread.quit();
        workerThread.wait();
    }

    void setImage(QImage const &image)
    {
//        qDebug() << "cup provider controller provided image";
//        mutex.lock();
        m_image = image;
        emit imageChanged(image);
//        mutex.unlock();
    }

    QImage image() const
    {
        return m_image;
    }
    void pause(){
        if(paused){
            paused = false;
            worker->on_resume();
        }
        else{
            paused = true;
            worker->on_pause();
        }
    }

signals:
    void imageChanged(QImage image);
    void operate();
public slots:
    void handleCup(const cv::Mat image_cv){
        QImage image_tosend(image_cv.data, image_cv.cols, image_cv.rows, QImage::Format_RGB888);
        setImage(image_tosend);
    }
    void pauseButtonClicked(){
         qDebug() << "pause clicked";
        pause();
    }
};
#endif // CUPPROVIDERCONTROLLER_H
