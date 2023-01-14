#set the output directory of the documentation
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/docs)
# sanity check...
message("Doxygen Output ${DOXYGEN_OUTPUT_DIR}")
doxygen_add_docs (
	doxygen
	liberic
	COMMENT "Erstelle Dokumentation"
)
