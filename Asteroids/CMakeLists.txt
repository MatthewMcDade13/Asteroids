find_package(PureEngine REQUIRED)

add_executable(
    Asteroids 
    Main.cpp
    Asteroid.cpp
    AsteroidPlayer.cpp
    AsteroidsGame.cpp
    Bullet.cpp
    Explosion.cpp
    GameAudio.cpp
    GameOverState.cpp
    GetRectCenter.cpp
    PausedState.cpp
    PlayState.cpp
    ResourcePaths.cpp
    SpaceEntity.cpp
    SpaceShip.cpp
    WireFrameShape.cpp
)

target_link_libraries(Asteroids ${PUREENGINE_LIBRARIES} ${SFML_LIBRARIES})

target_include_directories(Asteroids PRIVATE ${PUREENGINE_INCLUDE_DIRS})
