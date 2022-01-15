
add_executable(image-test image_test.cpp)


set(app_targets image-test)



foreach(target ${app_targets})
  target_link_libraries(${target}  PRIVATE ceng391)
  target_compile_features(${target} PRIVATE cxx_std_17)
  if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "GCC detected, adding compile flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -pedantic -Wall -Wextra")
  endif(CMAKE_COMPILER_IS_GNUCXX)
  set_target_properties(${target} PROPERTIES CXX_EXTENSIONS OFF)
endforeach()


