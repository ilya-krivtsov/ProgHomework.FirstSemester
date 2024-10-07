project("${homeworkName}_task_4")

add_library(fibonacci fibonacci.c)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} PRIVATE fibonacci)

add_executable(${PROJECT_NAME}_test test.c)
target_link_libraries(${PROJECT_NAME}_test PRIVATE fibonacci)
