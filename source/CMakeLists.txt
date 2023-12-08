include_directories(../include)

add_library(cpu SHARED CPU.cpp)

add_library(config STATIC Config.cpp)

add_executable(${TARGET} main.cpp)
target_link_libraries(${TARGET} cpu config)

install(TARGETS cpu DESTINATION /usr/local/lib)
install(TARGETS ${TARGET} DESTINATION /usr/local/bin)