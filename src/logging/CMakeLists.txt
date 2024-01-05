project(logging)

add_library(${PROJECT_NAME} logger.cpp)
target_link_libraries(${PROJECT_NAME} systemd)
target_include_directories(${PROJECT_NAME} PUBLIC "./")