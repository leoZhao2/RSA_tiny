aux_source_directory(. DIR_LIB_SRCS)

add_library(librsa ${DIR_LIB_SRCS})
target_link_libraries(librsa gmp)