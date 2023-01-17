#include <QApplication>
#include <QListView>

#include "qnodeeditor/qnodeeditor.hpp"
#include "qnodeeditor/qnodeeditor_tree.hpp"

void configureColorScheme()
{
#ifdef Q_OS_WIN
    QSettings settings(
        "HKEY_CURRENT_"
        "USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personaliz"
        "e",
        QSettings::NativeFormat
    );
    if (settings.value("AppsUseLightTheme") == 0) {
        qApp->setStyle(QStyleFactory::create("Fusion"));
        QPalette darkPalette;
        QColor darkColor = QColor(45, 45, 45);
        QColor disabledColor = QColor(127, 127, 127);
        darkPalette.setColor(QPalette::Window, darkColor);
        darkPalette.setColor(QPalette::WindowText, Qt::white);
        darkPalette.setColor(QPalette::Base, QColor(18, 18, 18));
        darkPalette.setColor(QPalette::AlternateBase, darkColor);
        darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
        darkPalette.setColor(QPalette::ToolTipText, Qt::white);
        darkPalette.setColor(QPalette::Text, Qt::white);
        darkPalette.setColor(QPalette::Disabled, QPalette::Text, disabledColor);
        darkPalette.setColor(QPalette::Button, darkColor);
        darkPalette.setColor(QPalette::ButtonText, Qt::white);
        darkPalette.setColor(
            QPalette::Disabled, QPalette::ButtonText, disabledColor
        );
        darkPalette.setColor(QPalette::BrightText, Qt::red);
        darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

        darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
        darkPalette.setColor(QPalette::HighlightedText, Qt::black);
        darkPalette.setColor(
            QPalette::Disabled, QPalette::HighlightedText, disabledColor
        );

        qApp->setPalette(darkPalette);

        qApp->setStyleSheet(
            "QToolTip { color: #ffffff; background-color: #2a82da; "
            "border: 1px solid white; }"
        );
    }
#endif
}

void populateModel(std::shared_ptr<QNodeEditorTree> tree)
{
    uint64_t node1Id = tree->addNode();
    uint64_t node2Id = tree->addNode();
    tree->addConnection(node1Id, node2Id);
}

int main(int argc, char** argv)
{
    Q_INIT_RESOURCE(qnodeeditor_resources);

    QApplication app(argc, argv);

    configureColorScheme();

    QListView view;

    std::shared_ptr<QNodeEditorTree> tree = std::make_unique<QNodeEditorTree>();
    view.setModel(tree->model());

    populateModel(tree);

    view.show();

    QNodeEditor editor;
    editor.show();

    return app.exec();
}
