# PROBLEM

```Boost.process``` and ```Boost.Interprocess``` are header only libraries.

That is supposed to make things easier (simply include ```/usr/include/boost``` directory and, perhaps, also ```/usr/include/boost/process``` etc.)

BUT!!! I could not make it work with CMake... AT FIRST!!!

The Boost website + [a stackowerflow thread](https://stackoverflow.com/questions/13863508/linking-errors-when-compiling-boost-asio-on-linux) recommend to do it like this:

```c++ main.cpp -o main -I /usr/include -lboost_system -lboost_thread -lpthread```

I managed to compile a file (./src/main.cpp) with a bunch of imports

This is good enough for little Boost examples that I am intending to experiment with

The I looked again at the error that it gives me.
```
/usr/bin/ld: CMakeFiles/main.dir/src/main.cpp.o: in function `boost::asio::detail::posix_global_impl<boost::asio::system_context>::~posix_global_impl()':
main.cpp:(.text._ZN5boost4asio6detail17posix_global_implINS0_14system_contextEED2Ev[_ZN5boost4asio6detail17posix_global_implINS0_14system_contextEED5Ev]+0xb3): undefined reference to `pthread_join'
/usr/bin/ld: main.cpp:(.text._ZN5boost4asio6detail17posix_global_implINS0_14system_contextEED2Ev[_ZN5boost4asio6detail17posix_global_implINS0_14system_contextEED5Ev]+0xd4): undefined reference to `pthread_detach'
```

and tried this in my ```CMakeLists.txt```:

```cmake
find_package(Boost 1.71.0 COMPONENTS thread program_options regex filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
# Boost::thread - not explicitly used in my program, but required by Boost.process and Boost.Interprocess
target_link_libraries(${PROJECT_NAME} Boost::thread) 
target_link_libraries(${PROJECT_NAME} Boost::program_options)
target_link_libraries(${PROJECT_NAME} Boost::regex)
target_link_libraries(${PROJECT_NAME} Boost::filesystem)
```



