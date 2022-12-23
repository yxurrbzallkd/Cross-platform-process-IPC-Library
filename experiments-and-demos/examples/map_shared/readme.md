# ./file: Testing ```mmap(..., MAP_SHARED)```
```
g++ writer.cpp -o writer; g++ watcher.cpp -o watcher
```
```
echo hello world > file.txt
```
Now open 2 terminals, run ```./watcher``` first, it will print "hello world", and wait, checking ```mmap```ed file.txt against that result ("hello world"). Now run ```./writer```, it will ```mmap``` file.txt, and write into it, replacing first 8 characters with '-'. As soon as the ```writer``` is started, the ```watcher``` will be triggered and will print warnings about mismatched characters.

# ./anonymous: Testing ```shm_open()``` + ```mmap(..., MAP_SHARED)```

```
g++ writer.cpp -o writer -lrt; g++ watcher.cpp -o watcher -lrt
```
Now, run ```./watcher``` - it creates an empty ```shm``` object, then waits, until its contents have been re-written. Now run writer and pass it some string in the command line. As soon as you do this, ```watcher``` will exit, and print the string you passed to ```writer``` (well, first 8 characters - the shm object is only 1 byte).
