cmake_minimum_required(VERSION 3.1)

project(mysqlConnPool)
#设置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g )
#设置可执行文件编译输出位置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#项目头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)

#mysql C++连接器头文件路径

include_directories(${PROJECT_SOURCE_DIR}/mysqlConn/include)


#项目源文件
aux_source_directory(./src SRC_LIST)
aux_source_directory(./tests TESTS_LIST)

#连接器库文件搜索路径
link_directories(${PROJECT_SOURCE_DIR}/mysqlConn/lib)

add_executable(mysqlConnPool  ${SRC_LIST} ${TESTS_LIST}  )

target_link_libraries(mysqlConnPool   mysqlcppconn pthread)