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

