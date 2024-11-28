cmake_minimum_required(VERSION 3.16)

project(GIUGAME LANGUAGES CXX)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()


add_library(GIUENGINE
    Engine/GameObject.h             Engine/GameObject.cpp
    Engine/gameview.h               Engine/gameview.cpp
    Engine/Components/GameObjectComponent.h
    Engine/gamecontroller.h         Engine/gamecontroller.cpp
    Engine/IdGenerator.h            Engine/IdGenerator.cpp
    Engine/GameInput.h
    Engine/inputmanager.h           Engine/inputmanager.cpp
)

target_include_directories(GIUENGINE PRIVATE ${CMAKE_SOURCE_DIR}/Engine)
target_include_directories(GIUENGINE PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Components)

target_link_libraries(GIUENGINE PRIVATE Qt6::Widgets)

add_executable(GIUGAME
                main.cpp
                mainwindow.cpp  mainwindow.h    mainwindow.ui
                Images.qrc
                worldloader.h                   worldloader.cpp

                GameObjects/playerobject.h      GameObjects/playerobject.cpp
                GameObjects/enemyobject.h       GameObjects/enemyobject.cpp
                GameObjects/penemyobject.h      GameObjects/penemyobject.cpp
                GameObjects/levelobject.h       GameObjects/levelobject.cpp

    )


target_link_libraries(GIUGAME PUBLIC GIUENGINE)

target_include_directories(GIUGAME PRIVATE ${CMAKE_SOURCE_DIR}/Engine)
target_include_directories(GIUGAME PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Components)

target_include_directories(GIUGAME PRIVATE ${CMAKE_SOURCE_DIR}/GameObjects)
target_include_directories(GIUGAME PRIVATE ${CMAKE_SOURCE_DIR}/InputManagers)
target_include_directories(GIUGAME PRIVATE ${CMAKE_SOURCE_DIR}/Views)

target_link_libraries(GIUGAME PRIVATE Qt6::Widgets)

find_library(WORLDLIB world PATHS ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(GIUGAME PRIVATE ${WORLDLIB})
target_include_directories(GIUGAME PUBLIC include)

include(GNUInstallDirs)
install(TARGETS GIUGAME
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
