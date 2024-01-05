project(caUpdater)

add_library(${PROJECT_NAME} caUpdater.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC "./")