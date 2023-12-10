include_directories(../include)

add_library(config SHARED Config.cpp)

add_library(cpu SHARED CPU.cpp)
target_link_libraries(cpu config)

add_library(postjson SHARED PostJson.cpp)
target_link_libraries(postjson config ${CURL_LIBRARIES})

add_executable(${TARGET} main.cpp)
target_link_libraries(${TARGET} cpu config postjson)

install(TARGETS cpu config DESTINATION /usr/local/lib)
install(TARGETS ${TARGET} DESTINATION /usr/local/bin)