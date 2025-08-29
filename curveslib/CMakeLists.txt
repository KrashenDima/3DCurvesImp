add_library(curveslib SHARED
    Circle.cpp
    Ellipse.cpp
    Helix.cpp
)

target_compile_definitions(curveslib PRIVATE CURVESLIB_EXPORTS)

target_include_directories(curveslib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})