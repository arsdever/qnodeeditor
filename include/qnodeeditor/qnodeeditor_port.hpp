#pragma once

#include <string>
#include <string_view>

class QNodeEditorPort
{
public:
    QNodeEditorPort() { }
    QNodeEditorPort(std::string_view name, bool supportsMultipleConnections)
        : name(name)
        , supportsMultipleConnections(supportsMultipleConnections)
    {
    }

    // TODO make private
public:
    std::string name;
    bool supportsMultipleConnections;
};

Q_DECLARE_METATYPE(QNodeEditorPort)
