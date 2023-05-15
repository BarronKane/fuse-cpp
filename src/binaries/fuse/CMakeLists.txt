project(Fuse)
set(FUSE ${PROJECT_NAME} CACHE INTERNAL "FUSE")

set(FUSE_PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/private/fuse.cpp
)
set(FUSE_PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/public/fuse.h
)

set(FUSE_COLLECTIVE
    ${FUSE_PRIVATE}
    ${FUSE_PUBLIC}
)

add_executable(${PROJECT_NAME}
    ${FUSE_COLLECTIVE}
)

add_source_group(${FUSE_COLLECTIVE})

target_link_libraries(${PROJECT_NAME}
    ${FUSE_UTILITIES}
    ${FUSE_LOGGER}
    
)