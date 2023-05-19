project(Fuse-Utilities)
set(FUSE_UTILITIES ${PROJECT_NAME} CACHE INTERNAL "FUSE_UTILITIES")

set(FUSEU_PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/private/utilities/utilites.cpp
)
set(FUSEU_PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/public/utilities/platform.h
)

set(FUSEU_COLLECTIVE
    ${FUSEU_PRIVATE}
    ${FUSEU_PUBLIC}
)

add_library(${FUSE_UTILITIES} SHARED
    ${FUSEU_COLLECTIVE}
)

add_source_group(${FUSEU_COLLECTIVE})

generate_export_header(${FUSE_UTILITIES})

# Defines the headers for this library,
# and will be added to build paths.
target_include_directories(${FUSE_UTILITIES} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/public>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/private)

# "make install" to the correct locations (GNUInstallDirs).
install(TARGETS ${FUSE_UTILITIES} EXPORT ${PROJECT_NAME}LibraryConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows.
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Importable from the install directory.
# Config file per-project dir or into "cmake".
install(EXPORT ${PROJECT_NAME}LibraryConfig DESTINATION share/${PROJECT_NAME}Library/cmake)

# Importable from build directory.
export(TARGETS ${FUSE_UTILITIES} FILE ${PROJECT_NAME}LibraryConfig.cmake)

target_link_libraries(${PROJECT_NAME} PUBLIC
        
)