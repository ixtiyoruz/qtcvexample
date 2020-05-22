#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <QQuickWindow>
#include <QTimer>
#include <QQmlProperty>
#include <QTime>
#include "ImageItem.h"

void checkItem(QQmlApplicationEngine *pEngine);

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qsrand(QTime::currentTime().msec());
    qmlRegisterType<ImageItem>("com.mycompany.qmlcomponents", 1, 0, "ImageItem");
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    QObject *obj = engine.rootObjects().first()->findChild<QObject *>("imageViewer");
    if(obj){
        QImage image(100,100, QImage::Format_ARGB32);
        image.fill(QColor(0, 255, 255));
        QQmlProperty::write(obj, "image", image);
    }else{
        std::cout << "object is not found " << std::endl;
    }

//    QTimer::singleShot(200, [&]() {
//           checkItem(&engine);
//       });

    return app.exec();

//cv::VideoCapture cam(0);
//cv::Mat pic;
//while(1){

//     cam>>pic;
//     cv::imshow("img", pic);
//     int key = cv::waitKey(3);
//     if(key == 27){
//         cv::destroyAllWindows();
//         break;
//     }
//}

}

void checkItem(QQmlApplicationEngine *pEngine) {
    QObject *obj = pEngine->rootObjects().first();
//    obj->children().first()
    qDebug() << "topItem: " << obj;
    qDebug() << "topItem: in obj " << obj->children().first();
}
