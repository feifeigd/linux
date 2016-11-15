
aux_source_directory(src SRC)
add_executable(thread ${SRC})
target_link_libraries(thread pthread)
