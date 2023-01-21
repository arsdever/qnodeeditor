set(SOURCES
    qnodeeditor_connection_graphics_object.cpp
    qnodeeditor_connection.cpp
    qnodeeditor_node_graphics_object.cpp
    qnodeeditor_node.cpp
    qnodeeditor_port_graphics_object.cpp
    qnodeeditor_port.cpp
    qnodeeditor_tree_model.cpp
    qnodeeditor_tree.cpp
    qnodeeditor_tree.cpp
    qnodeeditor.cpp)
set(HEADERS
    qnodeeditor_connection_graphics_object.hpp
    qnodeeditor_node_graphics_object.hpp qnodeeditor_port_graphics_object.hpp
    qnodeeditor_tree_model.hpp)
set(RESOURCES qnodeeditor_resources.qrc)

add_library(qnodeeditor_lib STATIC ${HEADERS} ${SOURCES} ${RESOURCES})
add_library(qnodeeditor::lib ALIAS qnodeeditor_lib)

target_link_libraries(qnodeeditor_lib PUBLIC qnodeeditor::interface)
