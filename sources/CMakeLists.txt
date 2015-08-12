project(unicodelite C CXX)

set(SRC_LIST
  unicodelite.cpp
  ucs4_to_utf8.c
  utf8_to_ucs4.c
)
set(HDR_LIST
  unicodelite.h
)
set_source_files_properties(${HDR_LIST} PROPERTIES HEADER_FILE_ONLY TRUE)
add_library(${PROJECT_NAME} STATIC ${SRC_LIST} ${HDR_LIST})
