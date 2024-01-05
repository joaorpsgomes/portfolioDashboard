project(cryptoUpdater)

add_library(${PROJECT_NAME} cryptoUpdater.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC "./")