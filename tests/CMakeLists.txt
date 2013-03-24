set(QT_USE_QTTEST TRUE)
include(${QT_USE_FILE})

set(TEST_GLOBAL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR})

function(CREATE_TEST TEST_NAME DEPS)
    include_directories(
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${ROOT_DIR}
        ${TEST_GLOBAL_INCLUDE}
    )
    
    message(STATUS ${TEST_GLOBAL_HDRS})
    
    file(GLOB TEST_SRCS "*.cpp")
    file(GLOB TEST_HDRS "*.h")

    qt4_wrap_cpp(TEST_MOC ${TEST_HDRS})
    
    add_executable(${TEST_NAME} ${TEST_SRCS} ${TEST_MOC})
    target_link_libraries(${TEST_NAME} ${QT_LIBRARIES} circuitmod-core ${DEPS})
    
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

add_subdirectory(and2_circuit_test)