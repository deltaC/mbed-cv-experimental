cmake_minimum_required(VERSION 3.14)
project(nn_tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(${CMAKE_SOURCE_DIR}/third-party/googletest)

include(CTest)

function(add_test test_name)
  set(test_dir "${CMAKE_SOURCE_DIR}/tests/test_${test_name}")
  set(test_header "${test_dir}/test_${test_name}.hpp")
  set(test_source "${test_dir}/test_${test_name}.cpp")
  
  if(NOT EXISTS "${test_header}")
    message(WARNING "Header file ${test_header} not found, skipping test ${test_name}")
    return()
  endif()
  
  if(NOT EXISTS "${test_source}")
    message(WARNING "Source file ${test_source} not found, skipping test ${test_name}")
    return()
  endif()
  
  set(test_target "test_${test_name}")
  add_executable(${test_target} ${test_source})
  
  target_include_directories(${test_target} PRIVATE 
    ${test_dir}
    ${CMAKE_SOURCE_DIR}
  )
  
  target_link_libraries(${test_target} PRIVATE 
    gtest 
    gmock
    pthread
  )
  
  add_test(NAME ${test_name} COMMAND ${test_target})
  
  message(STATUS "Added test: ${test_name}")
endfunction()

file(GLOB test_dirs LIST_DIRECTORIES true 
  "${CMAKE_SOURCE_DIR}/tests/test_*"
)

# Проходим по всем найденным директориям
foreach(test_dir ${test_dirs})
  if(IS_DIRECTORY ${test_dir})
    get_filename_component(dir_name ${test_dir} NAME)
    string(SUBSTRING ${dir_name} 5 -1 test_name)
    add_test(${test_name})
  endif()
endforeach()