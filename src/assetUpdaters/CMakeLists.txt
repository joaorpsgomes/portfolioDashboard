project(assetUpdater)

add_subdirectory(stockUpdater)
add_subdirectory(cryptoUpdater)
add_subdirectory(caUpdater)

add_library(${PROJECT_NAME} assetUpdater.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC "./")