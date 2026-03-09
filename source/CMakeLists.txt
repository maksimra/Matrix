add_executable (Matrix
                mathUtils.cpp
                main.cpp
)

target_link_libraries (Matrix PRIVATE matrixLib)

target_include_directories (Matrix PUBLIC ${PROJECT_SOURCE_DIR}
                                          ${PROJECT_SOURCE_DIR}/include)