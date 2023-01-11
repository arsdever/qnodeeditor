add_executable(qnodeeditor_sample sample.cpp)

target_link_libraries(qnodeeditor_sample Qt::Core Qt::Gui Qt::Widgets qnodeeditor::lib)
