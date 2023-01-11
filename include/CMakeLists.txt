add_library(qnodeeditor_interface INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/qnodeeditor/qnodeeditor.hpp)
add_library(qnodeeditor::interface ALIAS qnodeeditor_interface)

target_include_directories(qnodeeditor_interface
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
