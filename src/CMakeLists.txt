include_directories(.)
add_executable(main main.c activation.c loss.c grad.c simple_net.c)

add_executable(mnist mnist_main.c mnist.c)

add_executable(train_nueralnet train_nueralnet.c mnist.c two_layer_net.c
    activation.c loss.c)
