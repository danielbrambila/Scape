cmake_minimum_required(VERSION 3.20)

project(AStarGame LANGUAGES CXX)

# ========================================
# C++
# ========================================

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ========================================
# SFML 3.1.0
# ========================================

set(SFML_DIR
    "C:/Users/danie/Documents/libreries/SFML-3.1.0/lib/cmake/SFML"
)

find_package(
    SFML 3.1.0 EXACT

    COMPONENTS
        Graphics
        Window
        System
        Audio

    CONFIG REQUIRED
)

# ========================================
# EJECUTABLE
# ========================================

add_executable(
    AStarGame

    src/main.cpp
    src/Game.cpp
    src/Grid.cpp
    src/AStar.cpp
)

# ========================================
# HEADERS
# ========================================

target_include_directories(
    AStarGame PRIVATE

    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ========================================
# SFML
# ========================================

target_link_libraries(
    AStarGame PRIVATE

    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
)

# ========================================
# COPIAR EJECUTABLE A LA CARPETA RAÍZ
# ========================================

add_custom_command(
    TARGET AStarGame
    POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_if_different

        "$<TARGET_FILE:AStarGame>"

        "${CMAKE_CURRENT_SOURCE_DIR}/AStarGame.exe"
)

# ========================================
# COPIAR ASSETS A LA CARPETA RAÍZ
# ========================================

add_custom_command(
    TARGET AStarGame
    POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_directory

        "${CMAKE_CURRENT_SOURCE_DIR}/assets"

        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
)

# ========================================
# COPIAR DLLS RELEASE DE SFML
# ========================================

file(
    GLOB SFML_RELEASE_DLLS
    "C:/Users/danie/Documents/libreries/SFML-3.1.0/bin/*.dll"
)

foreach(
    DLL
    ${SFML_RELEASE_DLLS}
)

    if(NOT DLL MATCHES "-d-3\\.dll$")

        add_custom_command(
            TARGET AStarGame
            POST_BUILD

            COMMAND ${CMAKE_COMMAND} -E copy_if_different

                "${DLL}"

                "${CMAKE_CURRENT_SOURCE_DIR}"
        )

    endif()

endforeach()

# ========================================
# DLLS DE GCC / UCRT64
# ========================================

add_custom_command(
    TARGET AStarGame
    POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_if_different

        "C:/msys64/ucrt64/bin/libstdc++-6.dll"

        "${CMAKE_CURRENT_SOURCE_DIR}"
)

add_custom_command(
    TARGET AStarGame
    POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_if_different

        "C:/msys64/ucrt64/bin/libgcc_s_seh-1.dll"

        "${CMAKE_CURRENT_SOURCE_DIR}"
)