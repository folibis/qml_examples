#include "CustomItem.h"
#include <QSGSimpleRectNode>
#include <QRandomGenerator>
#include <QSGSimpleTextureNode>
#include <QMutexLocker>

CustomItem::CustomItem(QQuickItem *parent):
    QQuickItem(parent)
{
    setFlag( QQuickItem::ItemHasContents, true);
    QObject::connect(&m_timer, &QTimer::timeout, this, &CustomItem::timerHandler);
}

CustomItem::~CustomItem()
{
    if(m_texture != nullptr)
    {
        delete m_texture;
        m_texture = nullptr;
    }
    if(m_newTexture != nullptr)
    {
        delete m_newTexture;
        m_newTexture = nullptr;
    }
}

QSGNode *CustomItem::updatePaintNode(QSGNode *node, UpdatePaintNodeData *)
{
    QSGSimpleTextureNode *n = static_cast<QSGSimpleTextureNode *>(node);
    if (n == nullptr)
    {
        if(m_newTexture != nullptr)
        {
            n = new QSGSimpleTextureNode();
            n->setRect(boundingRect());
        }
    }

    if(n != nullptr)
    {
        if(m_newTexture != nullptr)
        {
            if(m_texture != nullptr)
            {
                delete m_texture;
                m_texture = nullptr;
            }
            m_texture = m_newTexture;
            m_newTexture = nullptr;
            n->setTexture(m_texture);
        }
    }

    return n;
}

void CustomItem::componentComplete()
{
    createImage();
    m_timer.start(1000);
    QQuickItem::componentComplete();
}

void CustomItem::createImage()
{
    if(m_newTexture == nullptr)
    {
        QRandomGenerator::global()->fillRange(m_buffer, BUFFER_SIZE);
        QImage img(reinterpret_cast<uchar *>(m_buffer), IMAGE_WIDTH, IMAGE_HEIGHT, QImage::Format_ARGB32);

        auto wnd = window();
        if(wnd != nullptr)
        {
            m_newTexture = wnd->createTextureFromImage(img);
        }
    }
}

void CustomItem::timerHandler()
{
    createImage();
    update();
}
