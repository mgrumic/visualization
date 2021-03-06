#include "instdigital.h"
#include <QPainter>
#include <QFont>

const QString InstDigital::TAG_NAME = "DIGITAL";

bool InstDigital::updateProperties(const QString& key, const QString& value)
{
    mProperties[key] = value;
    InstDigital::loadProperties();
    return VisuInstrument::refresh(key);
}

void InstDigital::loadProperties()
{
    VisuInstrument::loadProperties();

    GET_PROPERTY(cShowSignalName, mProperties, mPropertiesMeta);
    GET_PROPERTY(cShowSignalUnit, mProperties, mPropertiesMeta);
    GET_PROPERTY(cPadding, mProperties, mPropertiesMeta);
    GET_PROPERTY(cLeadingDigits, mProperties, mPropertiesMeta);
    GET_PROPERTY(cDecimalDigits, mProperties, mPropertiesMeta);

    mTagName = InstDigital::TAG_NAME;
}

void InstDigital::renderStatic(QPainter* painter)
{
    clear(painter);
}

void InstDigital::renderDynamic(QPainter* painter)
{
    setFont(painter);
    setPen(painter, cColorForeground);

    QString text =  QString::number(mSignal->getRealValue(), 'f', cDecimalDigits).rightJustified(cLeadingDigits, '0');

    if (cShowSignalName) {
        text = mSignal->getName() + " = " + text;
    }

    if (cShowSignalUnit) {
        text += " " + mSignal->getUnit();
    }

    painter->drawText(cPadding, cHeight - cPadding, text);
}
