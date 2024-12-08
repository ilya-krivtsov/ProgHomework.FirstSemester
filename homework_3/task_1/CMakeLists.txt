project("${homeworkName}_task_1")

add_library(frequencySearch frequencySearch.c)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} frequencySearch)

add_executable(${PROJECT_NAME}_test test.c)
target_link_libraries(${PROJECT_NAME}_test frequencySearch)
