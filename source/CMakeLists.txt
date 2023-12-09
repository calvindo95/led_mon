include_directories(../include)

add_library(config SHARED Config.cpp)

add_library(cpu SHARED CPU.cpp)
target_link_libraries(cpu config)

add_executable(${TARGET} main.cpp)
target_link_libraries(${TARGET} cpu config)

install(TARGETS cpu config DESTINATION /usr/local/lib)
install(TARGETS ${TARGET} DESTINATION /usr/local/bin)