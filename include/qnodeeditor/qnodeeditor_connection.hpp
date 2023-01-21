#pragma once

class QNodeEditorPort;

class QNodeEditorConnection
{
public:
    QNodeEditorConnection();
    QNodeEditorConnection(QNodeEditorPort* from, QNodeEditorPort* to);

public:
    QNodeEditorPort* _from;
    QNodeEditorPort* _to;
};

Q_DECLARE_METATYPE(QNodeEditorConnection*)
