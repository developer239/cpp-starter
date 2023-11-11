set(APP_NAME GraphicsProgramming)
set(APP_FOLDER_NAME graphics-programming)

set(APP_NAME_TEST ${LIB_NAME}Test)

set(SOURCES
        src/main.cpp
        src/LoopStrategy.h src/structs/Faces.h src/structs/Triangle.h src/structs/Vec2.h src/structs/Vec3.h src/shapes/Cube.h src/shapes/Mesh.h src/services/Camera.h src/services/Painter.h src/services/Projector.h src/services/WavefrontLoader.h src/GameObject.h)

add_executable(${APP_NAME} ${SOURCES})

# Copy assets
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/src/apps/${APP_FOLDER_NAME})

target_link_libraries(${APP_NAME} Core)
target_link_libraries(${APP_NAME} Logger)
