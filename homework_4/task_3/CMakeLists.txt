project("${homeworkName}_task_3")

add_library(frequencySearch frequencySearch.c)
add_library(arrayIO arrayIO.c)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} frequencySearch arrayIO)

add_executable(${PROJECT_NAME}_test test.c)
target_link_libraries(${PROJECT_NAME}_test PRIVATE frequencySearch arrayIO)
