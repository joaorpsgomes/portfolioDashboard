project(portfolioDashboard)

add_subdirectory(logging)
add_subdirectory(databaseWrapper)
add_subdirectory(assetUpdaters)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC logging databaseWrapper)
