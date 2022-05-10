#include "dialplate.h"
#include "dialplateplugin.h"

#include <QtPlugin>

DialPlatePlugin::DialPlatePlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void DialPlatePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool DialPlatePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *DialPlatePlugin::createWidget(QWidget *parent)
{
    return new DialPlate(parent);
}

QString DialPlatePlugin::name() const
{
    return QLatin1String("DialPlate");
}

QString DialPlatePlugin::group() const
{
    return QLatin1String("");
}

QIcon DialPlatePlugin::icon() const
{
    return QIcon();
}

QString DialPlatePlugin::toolTip() const
{
    return QLatin1String("");
}

QString DialPlatePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool DialPlatePlugin::isContainer() const
{
    return false;
}

QString DialPlatePlugin::domXml() const
{
    return QLatin1String("<widget class=\"DialPlate\" name=\"dialPlate\">\n</widget>\n");
}

QString DialPlatePlugin::includeFile() const
{
    return QLatin1String("dialplate.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(dialplateplugin, DialPlatePlugin)
#endif // QT_VERSION < 0x050000
