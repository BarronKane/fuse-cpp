project(Fuse-Ffmpeg)
set(FUSE_FFMPEG ${PROJECT_NAME} CACHE INTERNAL "FUSE_FFMPEG")

set(FUSEF_PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/private/ffmpeg/fuse-ffmpeg.cpp
)
set(FUSEF_PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/public/ffmpeg/fuse-ffmpeg.h
)

set(FUSEF_COLLECTIVE
    ${FUSEF_PRIVATE}
    ${FUSEF_PUBLIC}
)

add_library(${FUSE_FFMPEG} SHARED
    ${FUSEF_COLLECTIVE}
)
add_library(fuse::ffmpeg ALIAS ${FUSE_FFMPEG})

add_source_group(${FUSEF_COLLECTIVE})

generate_export_header(${FUSE_FFMPEG})

# Defines the headers for this library,
# and will be added to build paths.
target_include_directories(${FUSE_FFMPEG} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/public>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/private)

# "make install" to the correct locations (GNUInstallDirs).
install(TARGETS ${FUSE_FFMPEG} EXPORT ${PROJECT_NAME}LibraryConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows.
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Importable from the install directory.
# Config file per-project dir or into "cmake".
install(EXPORT ${PROJECT_NAME}LibraryConfig DESTINATION share/${PROJECT_NAME}Library/cmake)

# Importable from build directory.
export(TARGETS ${FUSE_FFMPEG} FILE ${PROJECT_NAME}LibraryConfig.cmake)

target_link_libraries(${PROJECT_NAME} PUBLIC
    fuse::utilities
    fuse::logger
)