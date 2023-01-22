#pragma once

#include <string>
#include <string_view>

class QNodeEditorNode;
enum class PortType;

class QNodeEditorPort
{
public:
    QNodeEditorPort();
    QNodeEditorPort(
        QNodeEditorNode* node, uint64_t index, PortType type, std::string_view name
    );

public:
    QNodeEditorNode* _node = nullptr;
    uint64_t _index;
    PortType _type;
    std::string _name;
};

Q_DECLARE_METATYPE(QNodeEditorPort*)
