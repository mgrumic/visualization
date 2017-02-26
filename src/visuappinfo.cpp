#include "visuappinfo.h"

VisuAppInfo* VisuAppInfo::instance = nullptr;

VisuAppInfo* VisuAppInfo::getInstance()
{
    if (instance == nullptr)
    {
        instance = new VisuAppInfo();
        instance->inEditorMode = false;
        instance->configWrong = false;
    }
    return instance;
}

bool VisuAppInfo::isInEditorMode()
{
    return getInstance()->inEditorMode;
}

void VisuAppInfo::setInEditorMode(bool mode)
{
    getInstance()->inEditorMode = mode;
}

bool VisuAppInfo::isConfigWrong()
{
    return getInstance()->configWrong;
}

void VisuAppInfo::setConfigWrong(bool wrong)
{
    getInstance()->configWrong = wrong;
}

void VisuAppInfo::setConfigWrong(bool wrong, const QString& issue)
{
    getInstance()->configWrong = wrong;
    getInstance()->configIssues.append(issue);
}

const QStringList& VisuAppInfo::getConfigIssues()
{
    return getInstance()->configIssues;
}