set(QT_USE_QTTEST TRUE)
include(${QT_USE_FILE})

set(TEST_GLOBAL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR})

function(CREATE_TEST TEST_NAME)
    include_directories(
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${ROOT_DIR}
        ${TEST_GLOBAL_INCLUDE}
    )
    
    file(GLOB TEST_SRCS "*.cpp")
    file(GLOB TEST_HDRS "*.h")

    qt4_wrap_cpp(TEST_MOC ${TEST_HDRS})
    
    add_executable(${TEST_NAME} ${TEST_SRCS} ${TEST_MOC})
    target_link_libraries(${TEST_NAME}
        circuitmod-core
        ${QT_QTTEST_LIBRARY})
    
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

add_subdirectory(and2_circuit_test)
add_subdirectory(circuit_test)
add_subdirectory(circuit_combination_test)