project(docs NONE)

set(DOCUMENT_LIST
  sample-utf8-withbom-cyrillic.txt
  sample-utf8-withoutbom-cyrillic.txt
  test-ucs4_to_utf8.txt
  test-utf8_to_ucs4.txt
  utf8-converter.txt
)
set_source_files_properties(${DOCUMENT_LIST} PROPERTIES HEADER_FILE_ONLY TRUE)
add_custom_target(${PROJECT_NAME} SOURCES ${DOCUMENT_LIST})
