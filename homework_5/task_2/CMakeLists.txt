project("${homeworkName}_task_2")

add_library(postfixCalc postfixCalc.c)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} postfixCalc)
target_link_libraries(${PROJECT_NAME} stack)

add_executable(${PROJECT_NAME}_test test.c)
target_link_libraries(${PROJECT_NAME}_test postfixCalc)
target_link_libraries(${PROJECT_NAME}_test stack)