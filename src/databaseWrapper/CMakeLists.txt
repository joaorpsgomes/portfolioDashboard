project(databaseWrapper)

add_library(${PROJECT_NAME} databaseWrapper.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC mysqlcppconn logging)
target_include_directories(${PROJECT_NAME} PUBLIC "./" "../logging")