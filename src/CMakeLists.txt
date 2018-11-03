include_directories(.)
add_executable(main main.c activation.c loss.c grad.c)

add_executable(mnist mnist_main.c mnist.c)
