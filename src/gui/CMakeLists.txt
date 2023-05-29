project(Fuse-Gui)
set(FUSE_GUI ${PROJECT_NAME} CACHE INTERNAL "FUSE_GUI")

set(FUSEG_PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/private/gui/gui.cpp
)
set(FUSEG_PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/public/gui/gui.h
)

set(FUSEG_COLLECTIVE
    ${FUSEG_PRIVATE}
    ${FUSEG_PUBLIC}
)

add_library(${FUSE_GUI} SHARED
    ${FUSEG_COLLECTIVE}
)

add_source_group(${FUSEG_COLLECTIVE})

generate_export_header(${FUSE_GUI})

# Defines the headers for this library,
# and will be added to build paths.
target_include_directories(${FUSE_GUI} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/public>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/private)

# "make install" to the correct locations (GNUInstallDirs).
install(TARGETS ${FUSE_GUI} EXPORT ${PROJECT_NAME}LibraryConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows.
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Importable from the install directory.
# Config file per-project dir or into "cmake".
install(EXPORT ${PROJECT_NAME}LibraryConfig DESTINATION share/${PROJECT_NAME}Library/cmake)

# Importable from build directory.
export(TARGETS ${FUSE_GUI} FILE ${PROJECT_NAME}LibraryConfig.cmake)

target_link_libraries(${PROJECT_NAME} PUBLIC
        
)