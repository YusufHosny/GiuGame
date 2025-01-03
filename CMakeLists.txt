cmake_minimum_required(VERSION 3.16)

project(GIUGAME LANGUAGES CXX)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()


add_library(GIUENGINE
    Engine/gameobject.h             Engine/gameobject.cpp
    Engine/gameview.h
    Engine/gamecontroller.h         Engine/gamecontroller.cpp
    Engine/idgenerator.h            Engine/idgenerator.cpp
    Engine/gameinput.h
    Engine/inputmanager.h           Engine/inputmanager.cpp
    Engine/gameloader.h

    Engine/Components/gameobjectcomponent.h         Engine/Components/gameobjectcomponent.cpp
    Engine/Components/collisionmanagercomponent.h   Engine/Components/collisionmanagercomponent.cpp
    Engine/Components/collidercomponent.h           Engine/Components/collidercomponent.cpp
)

target_include_directories(GIUENGINE PRIVATE ${CMAKE_SOURCE_DIR}/Engine)
target_include_directories(GIUENGINE PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Components)

target_link_libraries(GIUENGINE PRIVATE Qt6::Widgets)

add_executable(GIUGAME
                main.cpp
                mainwindow.cpp  mainwindow.h
                worldloader.h   worldloader.cpp

                Images.qrc

                giugameconfig.h giugameconfig.cpp

                giugamecontroller.h giugamecontroller.cpp

                Components/autoplaycomponent.h      Components/autoplaycomponent.cpp
                Components/pathtracercomponent.h    Components/pathtracercomponent.cpp
                Components/animationcomponent.h     Components/animationcomponent.cpp

                InputManagers/inputmanager2d.h InputManagers/inputmanager2d.cpp

                GameObjects/tileobject.h        GameObjects/tileobject.cpp
                GameObjects/playerobject.h      GameObjects/playerobject.cpp
                GameObjects/enemyobject.h       GameObjects/enemyobject.cpp
                GameObjects/penemyobject.h      GameObjects/penemyobject.cpp
                GameObjects/levelobject.h       GameObjects/levelobject.cpp
                GameObjects/healthpackobject.h  GameObjects/healthpackobject.cpp
                GameObjects/benemyobject.h      GameObjects/benemyobject.cpp
                GameObjects/pathobject.h        GameObjects/pathobject.cpp

                Views/itemview.h            Views/itemview.cpp
                Views/itemviewfactory.h     Views/itemviewfactory.cpp
                Views/spriteloader.h        Views/spriteloader.cpp

                Views/2d/gameview2d.h       Views/2d/gameview2d.cpp
                Views/2d/playerview2d.h     Views/2d/playerview2d.cpp
                Views/2d/pathview2d.h       Views/2d/pathview2d.cpp
                Views/2d/enemyview2d.h      Views/2d/enemyview2d.cpp
                Views/2d/penemyview2d.h     Views/2d/penemyview2d.cpp
                Views/2d/healthpackview2d.h Views/2d/healthpackview2d.cpp
                Views/2d/benemyview2d.h     Views/2d/benemyview2d.cpp
                Views/2d/tileview2d.h       Views/2d/tileview2d.cpp
                Views/2d/animateditemview.h Views/2d/animateditemview.cpp

                Views/text/gameviewtext.h           Views/text/gameviewtext.cpp
                Views/text/playerviewtext.h         Views/text/playerviewtext.cpp
                Views/text/enemyviewtext.h          Views/text/enemyviewtext.cpp
                Views/text/penemyviewtext.h         Views/text/penemyviewtext.cpp
                Views/text/healthpackviewtext.h     Views/text/healthpackviewtext.cpp
                Views/text/tileviewtext.h           Views/text/tileviewtext.cpp
                Views/text/benemyviewtext.h         Views/text/benemyviewtext.cpp
    )


target_link_libraries(GIUGAME PUBLIC GIUENGINE)

target_include_directories(GIUGAME PRIVATE ${CMAKE_SOURCE_DIR}/)

target_include_directories(GIUGAME PRIVATE ${CMAKE_SOURCE_DIR}/Engine)
target_include_directories(GIUGAME PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Components)

target_include_directories(GIUGAME PRIVATE ${CMAKE_SOURCE_DIR}/Components)

target_include_directories(GIUGAME PRIVATE ${CMAKE_SOURCE_DIR}/GameObjects)
target_include_directories(GIUGAME PRIVATE ${CMAKE_SOURCE_DIR}/InputManagers)

target_include_directories(GIUGAME PRIVATE ${CMAKE_SOURCE_DIR}/Views)
target_include_directories(GIUGAME PRIVATE ${CMAKE_SOURCE_DIR}/Views/2d)
target_include_directories(GIUGAME PRIVATE ${CMAKE_SOURCE_DIR}/Views/text)

target_link_libraries(GIUGAME PRIVATE Qt6::Widgets)

find_library(WORLDLIB world PATHS ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(GIUGAME PRIVATE ${WORLDLIB})
target_include_directories(GIUGAME PUBLIC include)

include(GNUInstallDirs)
install(TARGETS GIUGAME
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
