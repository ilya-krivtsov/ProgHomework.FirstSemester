project("${homeworkName}_task_3")

add_library(newFrequencySearch frequencySearch.c)
add_library(arrayIO arrayIO.c)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} newFrequencySearch arrayIO)

add_executable(${PROJECT_NAME}_test test.c)
target_link_libraries(${PROJECT_NAME}_test newFrequencySearch arrayIO)
