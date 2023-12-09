include_directories(../include)

add_library(config SHARED../scripts/Dockerfile_img_x86../scripts/Dockerfile_img_x86 Config.cpp)

add_library(cpu SHARED CPU.cpp)
target_link_libraries(cpu config)

add_executable(${TARGET} main.cpp)
target_link_libraries(${TARGET} cpu config)

install(TARGETS cpu DESTINATION /usr/local/lib)
install(TARGETS ${TARGET} DESTINATION /usr/local/bin)