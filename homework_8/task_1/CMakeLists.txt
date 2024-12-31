project("${homeworkName}_task_1")

add_library(stringDictionary stringDictionary.c)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} stringDictionary)

add_executable(${PROJECT_NAME}_test test.c)
target_link_libraries(${PROJECT_NAME}_test stringDictionary)
