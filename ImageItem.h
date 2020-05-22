#ifndef IMAGEITEM_H
#define IMAGEITEM_H
#include <QImage>
#include <QQuickPaintedItem>

class ImageItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)
    Q_PROPERTY(int image_width MEMBER width NOTIFY widthChanged)
    Q_PROPERTY(int image_height MEMBER height NOTIFY heightChanged)
public:
    ImageItem(QQuickItem *parent = nullptr);
    QImage image() const;
    int width;
    int height;

    void setImage(const QImage &image);



    void paint(QPainter *painter);
signals:
    void imageChanged();
    void widthChanged();
    void heightChanged();
private:
    QImage m_image;
};
#endif // IMAGEITEM_H
