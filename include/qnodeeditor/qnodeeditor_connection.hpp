#pragma once

class QNodeEditorPort;

class QNodeEditorConnection
{
public:
    QNodeEditorConnection();
    QNodeEditorConnection(QNodeEditorPort* from, QNodeEditorPort* to);

public:
    QNodeEditorPort* _from = nullptr;
    QNodeEditorPort* _to = nullptr;
};

Q_DECLARE_METATYPE(QNodeEditorConnection*)
