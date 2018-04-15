cmake_minimum_required(VERSION 3.9)
project(InterviewFucker)

set(CMAKE_CXX_STANDARD 11)

add_executable(sort
        sort/main.cpp
        sort/quick_sort.hpp
        sort/bubble_sort.hpp
        sort/selection_sort.hpp
        sort/heap_sort.hpp)


add_executable(test_vector
        others/test_vector.cpp)

add_executable(test_string
        others/test_string.cpp)

add_executable(array_and_string
        ctci/array_and_string.cpp)
add_executable(linklist
        ctci/linklist.cpp)
add_executable(dp_and_recursion
        ctci/dp_and_recursion.cpp)
add_executable(median
        ctci/median.cpp)
add_executable(difficult
        ctci/difficult.cpp)

add_executable(offer_chapter4
        offer/chapter4.cpp)
add_executable(offer_chapter5
        offer/chapter5.cpp)
add_executable(offer_chapter6
        offer/chapter6.cpp)
add_executable(offer_chapter8
        offer/chapter8.cpp)

add_executable(lintcode_100
        lintcode/one.cpp)
add_executable(lintcode_200
        lintcode/two.cpp)

add_executable(way02
        effective_c++/way03.cpp)

add_executable(004_char_combination 004_char_combination.cpp)
add_executable(005_palindrome 005_palindrome.cpp)
add_executable(reverse_list list/reverse_list.cpp)