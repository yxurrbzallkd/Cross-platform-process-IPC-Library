# Basic Process Creation

```bash
# compiling
g++ parent.cpp -o parent; g++ child.cpp -o child; g++ create.cpp -o create
# testing
./create.exe child
./create.exe parent
./parent.exe
```
