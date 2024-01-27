project(cryptoUpdater)

add_library(${PROJECT_NAME} cryptoUpdater.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC ${CURL_LIBRARIES} logging)

target_include_directories(${PROJECT_NAME} PUBLIC "./" "../")