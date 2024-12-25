project("${homeworkName}_task_3")

add_library(shuntingYard shuntingYard.c)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} shuntingYard)
target_link_libraries(${PROJECT_NAME} stack)

add_executable(${PROJECT_NAME}_test test.c)
target_link_libraries(${PROJECT_NAME}_test shuntingYard)
target_link_libraries(${PROJECT_NAME}_test stack)
