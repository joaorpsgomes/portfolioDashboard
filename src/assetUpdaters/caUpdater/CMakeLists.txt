project(caUpdater)

add_library(${PROJECT_NAME} caUpdater.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC ${CURL_LIBRARIES} logging)

target_include_directories(${PROJECT_NAME} PUBLIC "./" "../")