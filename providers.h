#ifndef PROVIDERS_H
#define PROVIDERS_H
#include <QObject>
#include <QThread>
#include <QDebug>
#include <QMutex>
#include "utils.h"

class CameraInfoProvider : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList  names MEMBER cam_names READ names WRITE setNames NOTIFY namesChanged)
    Q_PROPERTY(QStringList  paths MEMBER cam_paths READ paths WRITE setPaths NOTIFY pathsChanged)
    Q_PROPERTY(int  selected MEMBER selected_cam READ selected WRITE setSelected NOTIFY selectedChanged)
    QStringList cam_names;
    QStringList cam_paths;
    int selected_cam;
public:
    explicit CameraInfoProvider(QObject *parent = nullptr): QObject(parent) {
        std::vector<camera_info> camera_infos = find_cameras_linux();
        for(camera_info &info: camera_infos){
            cam_names.append(info.name.c_str());
            cam_paths.append(info.path.c_str());
        }
        selected_cam = 0;
    }

    QStringList names(){
        return cam_names;
    }
    QStringList paths(){
        return cam_paths;
    }
    int selected(){
        return selected_cam;
    }
    void setSelected(int selected_cam_id){
        selected_cam = selected_cam_id;
    }
    void setNames(QStringList names){
        cam_names = names;
    }
    void setPaths(QStringList paths){
        cam_paths = paths;
    }
signals:
    void namesChanged(QStringList  names);
    void pathsChanged(QStringList  paths);
    void selectedChanged(int  selected_cam_id);

public slots:
    void onNamesChanged(){
    }
    void onPathsChanged(){
    }
    void onSelectedChanged(int  selected_cam_id){
        selected_cam = selected_cam_id;
        if(cam_names.size() > selected_cam_id){

            qDebug() << Q_FUNC_INFO << "camera id changed" << selected_cam_id <<"\t" <<selected_cam;//cam_names.at(selected_cam) << "\t"<<cam_paths.at(selected_cam);
        }
    }
};
#endif // PROVIDERS_H
