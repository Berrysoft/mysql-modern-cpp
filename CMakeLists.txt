cmake_minimum_required(VERSION 3.1)
project(mysqlppp)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
include_directories(include)

file(GLOB LIB_HEADERS "include/mysql+++/*.h")
file(GLOB POLYFILL_HEADERS "include/mysql+++/polyfill/*.h")
add_library(mysqlppp INTERFACE)

install(FILES ${LIB_HEADERS} DESTINATION include/mysql+++)
install(FILES ${POLYFILL_HEADERS} DESTINATION include/mysql+++/polyfill)
install(TARGETS mysqlppp EXPORT mysqlppp_targets)

include(CMakePackageConfigHelpers)

export(EXPORT mysqlppp_targets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/mysql+++/mysqlppp-targets.cmake"
  NAMESPACE mysqlppp::
)
configure_file(cmake/mysqlppp-config.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/mysql+++/mysqlppp-config.cmake"
  COPYONLY
)

set(ConfigPackageLocation lib/mysql+++)
install(EXPORT mysqlppp_targets
  FILE
  mysqlppp-targets.cmake
  NAMESPACE
  mysqlppp::
  DESTINATION
    ${ConfigPackageLocation}
)
install(
  FILES
    cmake/mysqlppp-config.cmake
  DESTINATION
    ${ConfigPackageLocation}
  COMPONENT
    Devel
)

file(GLOB TEST_SOURCE "test/*.cpp")
add_executable(test ${TEST_SOURCE})
target_link_libraries(test mysqlclient)
