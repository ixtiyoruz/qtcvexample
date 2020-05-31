#include "ImageItem.h"
#include <QDebug>
#include <QPainter>

ImageItem::ImageItem(QQuickItem *parent):QQuickPaintedItem(parent)
{
    QImage image(100,100, QImage::Format_ARGB32);
    image.fill(QColor(0, qrand()%255, qrand()%255));
    setImage(image);
}

QImage ImageItem::image() const
{
    return m_image;
}

void ImageItem::setImage(const QImage &image)
{
    if(image == m_image)
        return;
    m_image = image;
    width = image.size().width();
    height = image.size().height();
//update();
    emit imageChanged();
    emit widthChanged();
    emit heightChanged();
}

void ImageItem::paint(QPainter *painter)
{
    if(m_image.isNull())
        return;
//    qDebug() << Q_FUNC_INFO << "paint requested..." << width << height;

    QRectF bounding_rect = boundingRect();
    QImage scaled;

    if((width * bounding_rect.height())/height <= bounding_rect.width())

        scaled = m_image.scaled((width * bounding_rect.height())/height, bounding_rect.height());

    else if((height * bounding_rect.width())/width <= bounding_rect.height())
        scaled = m_image.scaled(bounding_rect.width(),(height * bounding_rect.width())/width);


//    else if( bounding_rect.height() <= bounding_rect.width())

//        scaled = m_image.scaled((width * bounding_rect.height())/height, bounding_rect.height());
//    else

//        scaled = m_image.scaled(bounding_rect.width(),(height * bounding_rect.width())/width);




    int x =0 * (bounding_rect.width() - scaled.width())/2;
    int y =0 * (bounding_rect.height() - scaled.height())/2;

//    QPen pen(Qt::red, 10);
//    painter->setPen(pen);

    painter->drawImage(x, y , scaled);

//    painter->setPen(QColor(Qt::red));
//    painter->drawRect(0,0, bounding_rect.width(), bounding_rect.height());

}
