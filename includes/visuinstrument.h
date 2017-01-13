#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <QtGlobal>
#include <QWidget>
#include <QColor>
#include <QPixmap>
#include <QMap>
#include <QPainter>

#include "visuhelper.h"
#include "visusignal.h"
#include "visuwidget.h"


class VisuSignal;   // forward declare Signal class

class VisuInstrument : public VisuWidget
{
    Q_OBJECT

protected:

    // configuration properties
    quint16 cSignalId;          // associated signal id
    QColor cColorBackground;    // instrument background color
    QColor cColorStatic;        // color for nonchanging parts (scales, marks, etc)
    QColor cColorForeground;    // color for changing parts (pointers, indicators, etc)

    // pixmaps
    QPixmap mPixmap;        // holds instrument rendered with last received signal value
    QPixmap mPixmapStatic;  // holds prerendered pixmap generated by renderStatic()

    bool    mFirstRun;
    bool    mActive;        // true when widget is active in wysiwyg editor
    const VisuSignal *mSignal; // Pointer to last signal that was updated

    void paintEvent(QPaintEvent* event);
    virtual void renderStatic(QPainter*) = 0;   // Renders static parts of instrument
    virtual void renderDynamic(QPainter*) = 0;  // Renders signal value dependent parts

    void setFont(QPainter* painter, int fontSize);
    void setPen(QPainter* painter, QColor color, int thickness = 1);
    void setBrush(QPainter* painter, QColor color);
    void clear(QPainter* painter);

public slots:
    void signalUpdated(const VisuSignal* const mSignal);
    void initialUpdate(const VisuSignal* const signal);

public:

    explicit VisuInstrument(QWidget *parent, QMap<QString, QString> properties)
        : VisuWidget(parent, properties)
    {
        load(properties);
    }

    void clearPixmaps()
    {
        mPixmap.fill(Qt::transparent);
        mPixmapStatic.fill(Qt::transparent);
    }

    void setActive(bool active)
    {
        mActive = active;
        update();
    }

    virtual void load(QMap<QString, QString> properties)
    {
        VisuWidget::load(properties);

        ConfigLoadException::setInstrumentLoadContext(properties);

        GET_PROPERTY(cSignalId, quint16, properties);
        GET_PROPERTY(cColorBackground, QColor, properties);
        GET_PROPERTY(cColorStatic, QColor, properties);
        GET_PROPERTY(cColorForeground, QColor, properties);

        this->mActive = false;
        this->mFirstRun = true;
        this->mPixmap = QPixmap(cWidth, cHeight);
        this->mPixmapStatic = QPixmap(cWidth, cHeight);

        clearPixmaps();
        setAttribute(Qt::WA_TranslucentBackground);

        setGeometry(cX, cY, cWidth, cHeight);
    }

    // Getters
    quint16 getSignalId();
    quint16 getId();
    void render();
};

#endif // INSTRUMENT_H
