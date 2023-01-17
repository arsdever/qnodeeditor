set(SOURCES qnodeeditor.cpp qnode_tree_model.cpp)
set(HEADERS)
set(RESOURCES qnodeeditor_resources.qrc)

add_library(qnodeeditor_lib STATIC ${HEADERS} ${SOURCES} ${RESOURCES})
add_library(qnodeeditor::lib ALIAS qnodeeditor_lib)

target_link_libraries(qnodeeditor_lib PUBLIC qnodeeditor::interface)
