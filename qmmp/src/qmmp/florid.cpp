#include "florid.h"

#include <soundcore.h>
#include <math.h>
#include <QBitmap>
#include <QPainter>
#include <QMenu>
#include <QKeyEvent>

RoundAnimationLabel::RoundAnimationLabel(QWidget *parent)
    : QWidget(parent)
{
    m_timer.setInterval(100);
    connect(&m_timer, SIGNAL(timeout()), SLOT(timeout()));
}

RoundAnimationLabel::~RoundAnimationLabel()
{
    stop();
}

void RoundAnimationLabel::setPixmap(const QPixmap &pix)
{
    m_pixmap = pix.scaled(2 * DISTANCE, 2 * DISTANCE);

    QRect rect(QPoint(0, 0), m_pixmap.size());
    QBitmap mask(rect.size());
    QPainter painter(&mask);
    painter.fillRect(rect, Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.drawRoundedRect(rect, DISTANCE, DISTANCE);
    m_pixmap.setMask(mask);
}

void RoundAnimationLabel::start()
{
    if(!m_timer.isActive())
    {
        m_timer.start();
    }
}

void RoundAnimationLabel::stop()
{
    m_timer.stop();
}

void RoundAnimationLabel::timeout()
{
    if(++m_rotateAngle >= 360)
    {
        m_rotateAngle -= 360;
    }
    update();
}

void RoundAnimationLabel::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);

    const QSize &self = size();
    const QRect rotatedRect(-self.width() / 2, -self.height() / 2, self.width(), self.height());
    const int cx = self.width() / 2;
    const int cy = self.height() / 2;

    painter.save();
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.translate(cx, cy);
    painter.rotate(m_rotateAngle);
    painter.drawPixmap(rotatedRect, m_pixmap);
    painter.restore();
}



Florid::Florid(QWidget *parent)
    : Visual(parent)
{
    setMinimumSize(580, 320);

    m_roundLabel = new RoundAnimationLabel(this);

    connect(SoundCore::instance(), SIGNAL(trackInfoChanged()), SLOT(mediaUrlChanged()));
}

Florid::~Florid()
{

}

void Florid::setPixmap(const QPixmap &pix)
{
    if(!m_useImage)
    {
        return;
    }

    m_image = pix.toImage();
    update();
}

void Florid::start()
{
    Visual::start();
    processPatch(true);
}

void Florid::stop()
{
    Visual::stop();
    processPatch(false);
}

void Florid::mediaUrlChanged()
{
    m_renderLabel = false;
    update();
}

void Florid::reRenderImage(QColor &avg, const QImage *input)
{
   if(input->isNull())
   {
       return;
   }

   QRgb r = 0, g = 0, b = 0;
   for(int w=0; w<input->width(); w++)
   {
       for(int h=0; h<input->height(); h++)
       {
           QRgb rgb = input->pixel(w, h);
           r += qRed(rgb);
           g += qGreen(rgb);
           b += qBlue(rgb);
       }
   }

   const int size = input->width() * input->height();
   avg.setRed(r /= size);
   avg.setGreen(g /= size);
   avg.setBlue(b /= size);
}

void Florid::reRenderLabel()
{
    if(!m_image.isNull() && !m_renderLabel)
    {
        reRenderImage(m_averageColor, &m_image);

        m_roundLabel->setPixmap(QPixmap::fromImage(m_image));
        m_renderLabel = true;
    }
}

void Florid::processPatch(bool state)
{
    if(!m_useImage)
    {
        return;
    }

    state ? m_roundLabel->start() : m_roundLabel->stop();
}

void Florid::hideEvent(QHideEvent *e)
{
    Visual::hideEvent(e);
    processPatch(false);
}

void Florid::showEvent(QShowEvent *e)
{
    Visual::showEvent(e);
    if(m_running)
    {
        processPatch(true);
    }
}

void Florid::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(!m_image.isNull())
    {
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        painter.drawImage(0, 0, m_image.scaled(size()));
        painter.fillRect(rect(), QColor(150, 150, 150, 150));

        const QPoint &pt = rect().center();
        if(m_gradientOn)
        {
            const int length = DISTANCE + 20;
            QRadialGradient gradient(pt.x(), pt.y(), length, pt.x(), pt.y());
            painter.setPen(Qt::NoPen);
            gradient.setColorAt(0.7, m_averageColor);
            QColor color = m_averageColor;
            color.setAlpha(0);
            gradient.setColorAt(1.0, color);
            painter.setBrush(gradient);
            painter.drawEllipse(pt.x() - length, pt.y() - length, 2 * length, 2 * length);
        }

        reRenderLabel();
        m_roundLabel->setGeometry(pt.x() - DISTANCE, pt.y() - DISTANCE, 2 * DISTANCE, 2 * DISTANCE);
    }
    else
    {
        painter.fillRect(rect(), Qt::black);
    }
}

void Florid::contextMenuEvent(QContextMenuEvent *)
{
    QMenu menu(this);

    menu.addAction(m_screenAction);
    menu.exec(QCursor::pos());
}