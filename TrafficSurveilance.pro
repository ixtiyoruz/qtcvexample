QT += quick core gui

CONFIG += c++11

#opencv
INCLUDEPATH += /usr/local/include/opencv4
INCLUDEPATH += /home/ixtiyor/my_programms/boost_1_73_0
#LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_videoio#$(shell pkg-config opencv --libs)
LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_videoio
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Cup.cpp \
        ImageItem.cpp \
        main.cpp \
        utils.cpp

RESOURCES += qml.qrc  \
            imagine-assets/imagine-assets.qrc \
            logos.qrc \
            qtquickcontrols2.conf \
            webresources.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Cup.h \
    CupProvider.h \
    ImageItem.h \
    providers.h \
    utils.h \
    utils_.h
