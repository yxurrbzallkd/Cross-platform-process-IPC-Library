# PROBLEM

```Boost.process``` and ```Boost.Interprocess``` are header only libraries.

That is supposed to make things easier (simply include ```/usr/include/boost``` directory and, perhaps, also ```/usr/include/boost/process``` etc.)

BUT!!! I could not make it work with CMake...

The Boost website + [a stackowerflow thread](https://stackoverflow.com/questions/13863508/linking-errors-when-compiling-boost-asio-on-linux) recommend to do it like this:

```c++ main.cpp -o main -I /usr/include -lboost_system -lboost_thread -lpthread```

I managed to compile a file (./src/main.cpp) with a bunch of imports

This is good enough for little Boost examples that I am intending to experiment with
