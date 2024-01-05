project(stockUpdater)

add_library(${PROJECT_NAME} stockUpdater.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC "./")