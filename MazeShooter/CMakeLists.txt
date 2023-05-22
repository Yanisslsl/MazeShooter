cmake_minimum_required(VERSION 3.24)
project(MazeShooter)

set(CMAKE_CXX_STANDARD 17)
include("C:/Dev/vcpkg/scripts/buildsystems/vcpkg.cmake")
add_executable(MazeShooter MazeShooter.cpp include/managers/AssetManager.h include/managers/WindowManager.h include/managers/InputManager.h include/managers/GameManager.h include/models/Bullet.h include/models/Entity.h include/models/Player.h include/models/Level.h include/utils/Vector2.h src/managers/AssetManager.cpp  src/managers/WindowManager.cpp src/managers/GameManager.cpp src/managers/InputManager.cpp  src/models/Bullet.cpp src/models/Entity.cpp src/models/Player.cpp src/models/Level.cpp "include/managers/EntityManager.h" "src/managers/EntityManager.cpp" "include/core/Eventdispatcher.h" "src/core/Eventdispatcher.cpp" "include/Events/Event.h" "src/Events/Event.cpp" "include/models/Enemy.h" "src/models/Enemy.cpp" "include/models/Collider.h" "src/models/Collider.cpp" "include/managers/UIManager.h" "src/managers/UIManager.cpp" "include/models/Scene.h" "src/models/Scene.cpp" "include/models/MazeLevel.h" "src/models/MazeLevel.cpp" "src/models/MenuLevel.cpp" "include/models/MenuLevel.h")
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/bullet.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/idle.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/enemy.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/menu-background.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/arial.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)


find_package(eventpp CONFIG REQUIRED)
find_path(EVENTPP_INCLUDE_DIR eventpp/eventqueue.h)
include_directories(${EVENTPP_INCLUDE_DIR})


find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

target_link_libraries(MazeShooter PRIVATE eventpp::eventpp sfml-system sfml-graphics sfml-window sfml-network)