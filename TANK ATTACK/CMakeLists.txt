cmake_minimum_required(VERSION 3.28)
project(TANK_ATTACK)

set(CMAKE_CXX_STANDARD 23)

# Agregar ejecutable primero
add_executable(TANK_ATTACK main.cpp
        Tank.cpp
        Tank.h
        Map.cpp
        Map.h
        Bullet.cpp
        Bullet.h
        PowerUp.cpp
        PowerUp.h
)

# Buscar las bibliotecas de SFML
set(SFML_DIR "C:/Users/joelg/OneDrive/Desktop/Clion 2024.1.4/bin/mingw/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

# Vincular las bibliotecas necesarias de SFML
target_link_libraries(TANK_ATTACK sfml-system sfml-window sfml-graphics sfml-audio)
