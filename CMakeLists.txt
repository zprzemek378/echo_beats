cmake_minimum_required(VERSION 3.27)
project(echo_beats)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS audio system graphics REQUIRED)

add_executable(echo_beats main.cpp
        src/SoundManager.cpp
        src/SoundManager.h
        src/Sequence.cpp
        src/Sequence.h
        src/Game.cpp
        src/Game.h
)


target_link_libraries(echo_beats sfml-audio sfml-graphics sfml-system)