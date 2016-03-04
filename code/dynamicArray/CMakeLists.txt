
INCLUDE_DIRECTORIES( ${CodingInterview_SOURCE_DIR}/code/)

#local files
FILE (GLOB SOURCES *.h *.cpp)
SOURCE_GROUP("application" FILES ${SOURCES})

#reusables files
FILE (GLOB REUSABLES ${CodingInterview_SOURCE_DIR}/code/reusable/*.h ${CodingInterview_SOURCE_DIR}/code/reusable/*.cpp)
SOURCE_GROUP("reusable" FILES ${REUSABLES})

ADD_EXECUTABLE( dynamicArray ${SOURCES} ${REUSABLES})

INSTALL(TARGETS dynamicArray DESTINATION ${CodingInterview_SOURCE_DIR}/bin)