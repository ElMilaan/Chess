cmake_minimum_required(VERSION 3.20)
project(ProbaChess)

# Crée l'exécutable principal
add_executable(${PROJECT_NAME})

# Choix du standard C++
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# Définition du dossier de sortie des exécutables
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# Désactivation des extensions spécifiques au compilateur
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_EXTENSIONS OFF)

# Ajout des fichiers source
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp src/**/*.cpp src/**/*.hpp)
target_sources(${PROJECT_NAME} PRIVATE ${MY_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src lib)

# Ajout de la bibliothèque quick_imgui
add_subdirectory(lib/quick_imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE quick_imgui::quick_imgui)

include("CMakeUtils/files_and_folders.cmake")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders
)

add_subdirectory(lib/glmax)
target_link_libraries(${PROJECT_NAME} PRIVATE glmax)