#include "CupProvider.h"
#include <QDebug>
#include <QThread>

CupProvider::CupProvider(QObject *parent)
    : QObject(parent)
{
    cam.open(0);
}


void CupProvider::doWork(){
    cv::Mat pic;
    while(1){
        if(pause)
            QThread::msleep(500);
        else{
            cam>>pic;
            cvtColor(pic, pic, CV_BGR2RGB);
            imageChanged(pic);
        }
    }
}



void  CupProvider::on_resume()
{
    sync.lock();
    pause = false;
    sync.unlock();
}


void  CupProvider::on_pause()
{
    sync.lock();
    pause = true;
    sync.unlock();

}
bool  CupProvider::is_paused()
{
    bool ret = false;
    sync.lock();
    ret = pause;
    sync.unlock();
    return ret;
}
