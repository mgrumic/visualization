#ifndef VISUPROPERTYMETA_H
#define VISUPROPERTYMETA_H

#include <QString>
#include <QStringList>
#include <QMap>

class VisuPropertyMeta
{
public:

    VisuPropertyMeta() :    min(std::numeric_limits<int>::min()),
                            max(std::numeric_limits<int>::max()),
                            defaultVal(""),
                            type(DEFAULT),
                            extra("") {}

    typedef enum
    {
        DEFAULT,
        ENUM,
        COLOR,
        INSTSIGNAL,
        READ_ONLY,
        INT,
        FLOAT,
        SLIDER,
        BOOL,
        FONT,
        IMAGE,
        SERIAL,
        SERIAL_PLACEHOLDER,
        HIDDEN,
        FIRST = DEFAULT,
        LAST = HIDDEN
    } Type;
    static const char* TYPES_MAP[];

    double min;
    double max;
    QString defaultVal;
    Type type;
    QString extra;
    QString label;
    int order;
    QString depends;

    QStringList getEnumOptions();
    bool isEnabled(const QMap<QString, QString>& properties) const;

    static QString stringFromType(VisuPropertyMeta::Type type);
    static Type typeFromString(QString typeStr);

    static const QString DELIMITER;
    static const QString KEY_MIN;
    static const QString KEY_MAX;
    static const QString KEY_TYPE;
    static const QString KEY_EXTRA;
    static const QString KEY_LABEL;
    static const QString KEY_DEPENDS;
};

#endif // VISUPROPERTYMETA_H
