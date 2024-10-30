project("${homeworkName}_task_2")

add_library(cyclicList cyclicList.c)

# add_executable(${PROJECT_NAME} main.c)
# target_link_libraries(${PROJECT_NAME} cyclicList)

add_executable(${PROJECT_NAME}_test test.c)
target_link_libraries(${PROJECT_NAME}_test cyclicList)
