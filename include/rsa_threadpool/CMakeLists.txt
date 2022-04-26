aux_source_directory(. DIR_LIB_SRCS)

add_library(rsa_threadpool ${DIR_LIB_SRCS})
target_link_libraries(rsa_threadpool librsa pthread gmp)