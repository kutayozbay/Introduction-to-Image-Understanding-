

set(ceng391_sources
  image.cpp)

set(ceng391_headers
  ../include/ceng391/image.hpp)

add_library(ceng391 STATIC ${ceng391_sources} ${ceng391_headers})
target_include_directories(ceng391 PUBLIC ../include)
target_compile_features(ceng391 PRIVATE cxx_std_17)
if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "GCC detected, adding compile flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -pedantic -Wall -Wextra")
endif(CMAKE_COMPILER_IS_GNUCXX)
set_target_properties(ceng391 PROPERTIES CXX_EXTENSIONS OFF)


