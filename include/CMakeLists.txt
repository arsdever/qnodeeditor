add_library(
  qnodeeditor_interface
  INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/qnodeeditor/qnodeeditor.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/qnodeeditor/qnodeeditor_connection.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/qnodeeditor/qnodeeditor_node.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/qnodeeditor/qnodeeditor_port.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/qnodeeditor/qnodeeditor_tree.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/qnodeeditor/qnodeeditor_layout_algorithm.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/qnodeeditor/qnodeeditor_flow_layout_algorithm.hpp
  )
add_library(qnodeeditor::interface ALIAS qnodeeditor_interface)

target_include_directories(qnodeeditor_interface
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
