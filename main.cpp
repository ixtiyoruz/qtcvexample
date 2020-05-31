#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <QQuickWindow>
#include <QTimer>
#include <QQmlProperty>
#include <QTime>
#include <QQmlContext>
#include "ImageItem.h"
#include "CupProvider.h"
#include "providers.h"
#include <QtWebView/QtWebView>

void checkItem(QQmlApplicationEngine *pEngine);

Q_DECLARE_METATYPE(cv::Mat)
Q_DECLARE_METATYPE(cv::UMat)

int main(int argc, char *argv[])
{
    qRegisterMetaType<cv::Mat>();
    qRegisterMetaType<cv::UMat>();
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qsrand(QTime::currentTime().msec());
    qmlRegisterType<ImageItem>("com.mycompany.qmlcomponents", 1, 0, "ImageItem");
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QGuiApplication app(argc, argv);


    CupProvider *cup_provider = new CupProvider();
    CameraInfoProvider *cam_info_provider = new CameraInfoProvider();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("cup_provider", cup_provider);
    engine.rootContext()->setContextProperty("cam_info_provider", cam_info_provider);
    QIcon::setThemeName("automotive");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    cup_provider->operate();

// this is how you can find qml object in c++ just dont use it if not neccessary ( time consuming)
// QObject *obj = engine.rootObjects().first()->findChild<QObject *>("imageViewer");
//    if(obj){
//        QImage image(100,100, QImage::Format_ARGB32);
//        image.fill(QColor(0, 255, 255));
//        QQmlProperty::write(obj, "image", image);
//    }else{
//        std::cout << "object is not found " << std::endl;
//    }
//    QTimer::singleShot(200, [&]() {
//           checkItem(&engine);
//       });
//        QTimer::singleShot(1000, [&cap_provider](){
//            QImage image{480, 480, QImage::Format_RGB32};
//            image.fill(Qt::yellow);
//            cap_provider.setImage(std::move(image));
//        });

    return app.exec();
}

void checkItem(QQmlApplicationEngine *pEngine) {
    QObject *obj = pEngine->rootObjects().first();
//    obj->children().first()
    qDebug() << "topItem: " << obj;
    qDebug() << "topItem: in obj " << obj->children().first();
}
