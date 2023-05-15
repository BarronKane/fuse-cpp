project(Fuse-Logger)
set(FUSE_LOGGER ${PROJECT_NAME} CACHE INTERNAL "FUSE_LOGGER")

set(FUSEL_PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/private/logger.cpp
)
set(FUSEL_PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/public/logger.h
)

set(FUSEL_COLLECTIVE
    ${FUSEL_PRIVATE}
    ${FUSEL_PUBLIC}
)

add_library(${PROJECT_NAME}
    ${FUSEL_COLLECTIVE}
)

add_source_group(${FUSEL_COLLECTIVE})

generate_export_header(${FUSE_LOGGER})

# Defines the headers for this library,
# and will be added to build paths.
target_include_directories(${FUSE_LOGGER} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/logger/public>
    $<INSTALL_INTERFACE:public>
    PRIVATE src)

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
    ${FUSE_UTILITES}
)