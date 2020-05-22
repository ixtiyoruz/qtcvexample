#include "ImageItem.h"
#include <QDebug>
#include <QPainter>

ImageItem::ImageItem(QQuickItem *parent):QQuickPaintedItem(parent)
{
    qDebug() << Q_FUNC_INFO << "initializing new item, parent is: " << parent;
    QImage image(100,100, QImage::Format_ARGB32);
    image.fill(QColor(0, qrand()%255, qrand()%255));
    setImage(image);
}

QImage ImageItem::image() const
{
    qDebug() << Q_FUNC_INFO << "image requested...";
    return m_image;
}

void ImageItem::setImage(const QImage &image)
{
    qDebug() << Q_FUNC_INFO << "setting new image...";
    if(image == m_image)
        return;
    m_image = image;
    width = image.size().width();
    height = image.size().height();

    emit imageChanged();
    emit widthChanged();
    emit heightChanged();
    update();
}

void ImageItem::paint(QPainter *painter)
{
    if(m_image.isNull())
        return;
    qDebug() << Q_FUNC_INFO << "paint requested...";

    QRectF bounding_rect = boundingRect();
    QImage scaled = m_image.scaledToHeight(bounding_rect.height());

    painter->drawImage(0, 0 , scaled);
}
