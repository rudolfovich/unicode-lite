project(unicodelite-test CXX)

set(SRC_LIST
  unicodelite_test.cc
  ucs4_to_utf8_test.cc
  utf8_to_ucs4_test.cc
)
include_directories(../gtest/include)
include_directories(../sources)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} unicodelite gtest)
