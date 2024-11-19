add_library(adapter_interface INTERFACE)
target_include_directories(adapter_interface INTERFACE include/)

add_library(adapter::interface ALIAS adapter_interface)
