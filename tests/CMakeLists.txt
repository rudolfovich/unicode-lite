project(unicodelite-test CXX)

set(SRC_LIST
  pragma_once_test.cc
  unicodelite_test.cc
  ucs4_to_utf8_test.cc
  utf8_to_ucs4_test.cc
  utf8_to_ucs4_1_test.cc
  utf8_to_ucs4_2_test.cc
)
set(HDR_LIST
  utf8_to_ucs4_test.h
)
include_directories(../gtest/include)
include_directories(../sources)

set_source_files_properties(${HDR_LIST} PROPERTIES HEADER_FILE_ONLY TRUE)
add_executable(${PROJECT_NAME} ${SRC_LIST} ${HDR_LIST})
target_link_libraries(${PROJECT_NAME} unicodelite gtest)
