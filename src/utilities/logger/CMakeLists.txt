project(Fuse-Logger)
set(FUSE_LOGGER ${PROJECT_NAME} CACHE INTERNAL "FUSE_LOGGER")

set(FUSEL_PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/private/logger/logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/private/logger/sink.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/private/logger/source.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/private/logger/record.cpp
)
set(FUSEL_PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/public/logger/logger.h
    ${CMAKE_CURRENT_SOURCE_DIR}/public/logger/sink.h
    ${CMAKE_CURRENT_SOURCE_DIR}/public/logger/source.h
    ${CMAKE_CURRENT_SOURCE_DIR}/public/logger/record.h
)

set(FUSEL_COLLECTIVE
    ${FUSEL_PRIVATE}
    ${FUSEL_PUBLIC}
)

add_library(${PROJECT_NAME} SHARED
    ${FUSEL_COLLECTIVE}
)
add_library(fuse::logger ALIAS ${PROJECT_NAME})

add_source_group(${FUSEL_COLLECTIVE})

generate_export_header(${FUSE_LOGGER})

# Defines the headers for this library,
# and will be added to build paths.
target_include_directories(${FUSE_LOGGER} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/public>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/private)

# "make install" to the correct locations (GNUInstallDirs).
install(TARGETS ${FUSE_LOGGER} EXPORT ${PROJECT_NAME}LibraryConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows.
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Importable from the install directory.
# Config file per-project dir or into "cmake".
install(EXPORT ${PROJECT_NAME}LibraryConfig DESTINATION share/${PROJECT_NAME}Library/cmake)

# Importable from build directory.
export(TARGETS ${FUSE_LOGGER} FILE ${PROJECT_NAME}LibraryConfig.cmake)

target_link_libraries(${PROJECT_NAME} PUBLIC
    fuse::utilities
)