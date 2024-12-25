project("${homeworkName}_task_1")

add_library(frequencyLookup frequencyList.c frequencyLookup.c)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} frequencyLookup)

add_executable(${PROJECT_NAME}_test test.c)
target_link_libraries(${PROJECT_NAME}_test frequencyLookup)
