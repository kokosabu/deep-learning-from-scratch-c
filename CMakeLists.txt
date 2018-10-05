# CMakeのバージョンを設定
cmake_minimum_required(VERSION 2.8)

# プロジェクト名と使用する言語を設定
project(deep-learning-from-scratch-c C)

# コンパイルオプション指定
set(CMAKE_C_FLAGS "-Wall")

# サブディレクトリを登録
add_subdirectory(src)
add_subdirectory(test)

