set(sc2renderer_sources
    sc2_renderer.cc
    sc2_renderer.h
)

add_library(sc2renderer STATIC ${sc2renderer_sources})

set_target_properties(sc2renderer PROPERTIES FOLDER utilities)

target_include_directories(sc2renderer SYSTEM PRIVATE "${sdl_SOURCE_DIR}/include")

target_link_libraries(sc2renderer PRIVATE SDL2-static)

if (MSVC)
    target_compile_options(sc2renderer PRIVATE /W4 /WX-)
endif()
