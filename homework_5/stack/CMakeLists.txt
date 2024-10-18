project("${homeworkName}_stack")

add_library(stack stack.c)

add_executable(${PROJECT_NAME}_test test.c)
target_link_libraries(${PROJECT_NAME}_test PRIVATE stack)
