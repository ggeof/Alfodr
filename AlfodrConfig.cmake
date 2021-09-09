add_library(alfodr STATIC IMPORTED)
find_library(ALFODR_LIBRARY_PATH alfodr HINTS "${CMAKE_CURRENT_LIST_DIR}/../../")
set_target_properties(alfodr PROPERTIES IMPORTED_LOCATION "${ALFODR_LIBRARY_PATH}")