if(MSVC)
    # Enable new MSVC runtime library flag handling
    cmake_policy(SET CMP0091 NEW)
    
    # Set runtime library for all targets
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
    
    # Disable specific warnings about MSVCRT
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRT")
endif()

cmake_minimum_required(VERSION 3.10)
project(Weaver)

# Third-party paths
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/third_party/glfw")
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/third_party/imgui")
set(GLAD_DIR "${CMAKE_SOURCE_DIR}/third_party/glad")

# Find required packages
find_package(OpenGL REQUIRED)

# GLAD setup
add_library(glad STATIC
    ${GLAD_DIR}/src/glad.c
)
target_include_directories(glad PUBLIC ${GLAD_DIR}/include)

# ImGui setup
add_library(imgui STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC 
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${GLFW_DIR}/include
)
target_compile_definitions(imgui PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD)

# GLFW configuration
if(WIN32)
    set(GLFW_LIB_DIR "${GLFW_DIR}/lib-vc2022/glfw3.lib")
else()
    find_package(glfw3 REQUIRED)
endif()

# Link ImGui dependencies
target_link_libraries(imgui PUBLIC 
    OpenGL::GL
    ${GLFW_LIB_DIR}
    glad
)

# Add subdirectories
add_subdirectory(user_interface)

# Main application
add_executable(weaver_app main.cpp)
set_target_properties(weaver_app PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Link main application
target_link_libraries(weaver_app PRIVATE user_interface)
if(WIN32)
    target_link_libraries(weaver_app PRIVATE 
        gdi32
        user32
        shell32
    )
endif()
