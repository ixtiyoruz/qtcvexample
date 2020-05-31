#include "Cup.h"
#include <QDebug>
#include <QThread>

#include <boost/algorithm/string.hpp>
using namespace std;
using namespace boost;
CupWorker::CupWorker(QObject *parent)
    : QObject(parent)
{
    cam.open(1);
}


void CupWorker::doWork(){
    cv::Mat pic;
    while(1){
        if(pause)
            QThread::msleep(500);
        else{
            cam>>pic;
            cvtColor(pic, pic, cv::COLOR_BGR2RGB);
            imageChanged(pic);
        }
    }
}



void  CupWorker::on_resume()
{
    sync.lock();
    pause = false;
    sync.unlock();
}


void  CupWorker::on_pause()
{
    sync.lock();
    pause = true;
    sync.unlock();

}
bool  CupWorker::is_paused()
{
    bool ret = false;
    sync.lock();
    ret = pause;
    sync.unlock();
    return ret;
}
