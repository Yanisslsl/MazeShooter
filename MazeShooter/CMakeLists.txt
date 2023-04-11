cmake_minimum_required(VERSION 3.24)
project(MazeShooter)

set(CMAKE_CXX_STANDARD 17)
include("C:/Dev/vcpkg/scripts/buildsystems/vcpkg.cmake")
add_executable(MazeShooter MazeShooter.cpp include/managers/AssetManager.h include/managers/WindowManager.h include/managers/InputManager.h include/managers/LevelManager.h include/managers/GameManager.h include/models/Bullet.h include/models/Entity.h include/models/Player.h include/models/Level.h include/utils/Vector2.h src/managers/AssetManager.cpp  src/managers/WindowManager.cpp src/managers/GameManager.cpp src/managers/InputManager.cpp src/managers/LevelManager.cpp src/models/Bullet.cpp src/models/Entity.cpp src/models/Player.cpp src/models/Level.cpp)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/bullet.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/idle.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)





find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

target_link_libraries(MazeShooter PRIVATE sfml-system sfml-graphics sfml-window sfml-network)