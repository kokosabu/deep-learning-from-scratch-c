if(APPLE)
    set(CMAKE_MACOSX_RPATH ON)
    set(CMAKE_SHARED_LIBRARY_SUFFIX_C ".so")
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(CUTTER cutter REQUIRED)

link_directories(${CUTTER_LIBRARY_DIRS})

add_library(test_perceptron SHARED test-perceptron.c ${CMAKE_SOURCE_DIR}/src/perceptron.c)
target_include_directories(test_perceptron PUBLIC ${CUTTER_INCLUDE_DIRS})
target_include_directories(test_perceptron PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(test_perceptron ${CUTTER_LIBRARIES})

add_library(test_activation SHARED test-activation.c ${CMAKE_SOURCE_DIR}/src/activation.c)
target_include_directories(test_activation PUBLIC ${CUTTER_INCLUDE_DIRS})
target_include_directories(test_activation PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(test_activation ${CUTTER_LIBRARIES} m)

add_library(test_loss SHARED test-loss.c ${CMAKE_SOURCE_DIR}/src/loss.c)
target_include_directories(test_loss PUBLIC ${CUTTER_INCLUDE_DIRS})
target_include_directories(test_loss PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(test_loss ${CUTTER_LIBRARIES} m)

add_library(test_grad SHARED test-grad.c ${CMAKE_SOURCE_DIR}/src/grad.c)
target_include_directories(test_grad PUBLIC ${CUTTER_INCLUDE_DIRS})
target_include_directories(test_grad PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(test_grad ${CUTTER_LIBRARIES} m)

add_library(test_simple_net SHARED test-simple_net.c
    ${CMAKE_SOURCE_DIR}/src/simple_net.c
    ${CMAKE_SOURCE_DIR}/src/loss.c
    ${CMAKE_SOURCE_DIR}/src/activation.c
    ${CMAKE_SOURCE_DIR}/src/grad.c)
target_include_directories(test_simple_net PUBLIC ${CUTTER_INCLUDE_DIRS})
target_include_directories(test_simple_net PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(test_simple_net ${CUTTER_LIBRARIES})

add_library(test_two_layer_net SHARED test-two_layer_net.c
    ${CMAKE_SOURCE_DIR}/src/two_layer_net.c
    ${CMAKE_SOURCE_DIR}/src/loss.c
    ${CMAKE_SOURCE_DIR}/src/activation.c
    ${CMAKE_SOURCE_DIR}/src/grad.c)
target_include_directories(test_two_layer_net PUBLIC ${CUTTER_INCLUDE_DIRS})
target_include_directories(test_two_layer_net PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(test_two_layer_net ${CUTTER_LIBRARIES})
