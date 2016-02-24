cmake_minimum_required(VERSION 2.8)
project (Diaparser)
set(CMAKE_BUILD_TYPE Debug)
SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage -O0 --coverage -g")
SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")
SET (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
SET (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
add_library(Diaparser SHARED DIA_AVP.cxx)

SET(CMAKE_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../inc)

if(TESTS)
FIND_PACKAGE(CxxTest REQUIRED)
endif()

if(TESTS AND CXXTEST_FOUND)
    INCLUDE_DIRECTORIES(${CXXTEST_INCLUDE_DIR})
    enable_testing()
    
    #creates a cxxtest runner                         
    CXXTEST_ADD_TEST(test_${PROJECT_NAME} runner.cpp
                        ${CMAKE_CURRENT_SOURCE_DIR}/tests/t_DIA_AVP.test ${CMAKE_CURRENT_SOURCE_DIR}/tests/t_DIA_AVP_copy.test)                     
                                                
    TARGET_LINK_LIBRARIES(test_${PROJECT_NAME} Diaparser)
        
    ADD_CUSTOM_COMMAND(TARGET test_${PROJECT_NAME}
    POST_BUILD
    COMMAND lcov --zerocounters --directory .
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Cleaning up old coverage data...}"
    )
                     
    ADD_CUSTOM_COMMAND(TARGET test_${PROJECT_NAME}
    POST_BUILD
    COMMAND test_${PROJECT_NAME} 
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Running tests in ${CMAKE_CURRENT_SOURCE_DIR}"
    )
    
    ADD_CUSTOM_COMMAND(TARGET test_${PROJECT_NAME}
    POST_BUILD
    COMMAND lcov --directory  ${CMAKE_CURRENT_SOURCE_DIR}${CMAKE_FILES_DIRECTORY}/${PROJECT_NAME}.dir --capture --output-file ${CMAKE_CURRENT_SOURCE_DIR}${CMAKE_FILES_DIRECTORY}/${PROJECT_NAME}.coverage
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Running lcov --directory ${CMAKE_CURRENT_SOURCE_DIR}${CMAKE_FILES_DIRECTORY}/${PROJECT_NAME}.dir --capture --output-file ${CMAKE_CURRENT_SOURCE_DIR}${CMAKE_FILES_DIRECTORY}/${PROJECT_NAME}.coverage "
    )
    
    ADD_CUSTOM_COMMAND(TARGET test_${PROJECT_NAME}
    POST_BUILD
    COMMAND genhtml --output-directory ${CMAKE_CURRENT_SOURCE_DIR}${CMAKE_FILES_DIRECTORY}/coverage_output ${CMAKE_CURRENT_SOURCE_DIR}${CMAKE_FILES_DIRECTORY}/${PROJECT_NAME}.coverage
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Running genhtml --output-directory ${CMAKE_CURRENT_SOURCE_DIR}${CMAKE_FILES_DIRECTORY}/coverage_output ${CMAKE_CURRENT_SOURCE_DIR}${CMAKE_FILES_DIRECTORY}/${PROJECT_NAME}.coverage"
    )
   
endif()

