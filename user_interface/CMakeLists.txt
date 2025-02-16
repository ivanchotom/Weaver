add_library(user_interface STATIC
    # Core
    core/Element.cpp

    # Database
    database/Database.cpp

    # Factory
    factory/ImGuiFactory.cpp

    # Internal ImGui implementations
    internal/imGui/widget/ImGuiButton.cpp
    internal/imGui/window/ImGuiWindow.cpp

    # Public interfaces
    widget/Button.cpp
    window/Window.cpp
)

target_include_directories(user_interface PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/internal
    ${CMAKE_CURRENT_SOURCE_DIR}/internal/base
    ${CMAKE_CURRENT_SOURCE_DIR}/internal/base/widget
    ${CMAKE_CURRENT_SOURCE_DIR}/internal/base/window
    ${IMGUI_DIR}
    ${GLFW_DIR}/include
)

target_link_libraries(user_interface PUBLIC
    imgui
    ${GLFW_LIB}
    glad
) 