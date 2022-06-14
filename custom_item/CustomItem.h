#ifndef CUSTOMITEM_H
#define CUSTOMITEM_H

#include <QQuickItem>
#include <QImage>
#include <QSGTexture>
#include <QTimer>
#include <QMutex>

#define IMAGE_WIDTH (100)
#define IMAGE_HEIGHT (100)
#define BUFFER_SIZE (IMAGE_WIDTH * IMAGE_HEIGHT)


class CustomItem : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    CustomItem(QQuickItem *parent = nullptr);
    ~CustomItem();
    QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *) override;
    void componentComplete() override;

protected:
    void createImage();
    void timerHandler();

private:
    uint32_t m_buffer[BUFFER_SIZE] = {};
    QSGTexture *m_texture = nullptr;
    QSGTexture *m_newTexture = nullptr;
    QTimer m_timer;
};

#endif // CUSTOMITEM_H
