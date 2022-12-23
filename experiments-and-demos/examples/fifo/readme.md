# ```mkfifo()```

## 1) filename 
We provide a filename to ```./combine```.

Try to provide different arguments, look at the result.

|filename|outcome|
|-|-|
|/tmp/any_filename|<span style="color:green">success</span>|
|/any_filename|<span style="color:red">Permission denied</span>|
|/home/any_filename|<span style="color:red">Permission denied</span>|
|./any_filename|<span style="color:red">Operation not supported</span>|
|/home/diana/any_filename|<span style="color:green">success</span>|

Why does ./any_filename fails? Because we are not working on the Linux disk right now?

I checked that:
1) tried to run the program while in /home/diana specifying the full path to ```./combined``` - <span style="color:green">success</span>
2) copied the program to /home/diana and ran it there - same error - <span style="color:green">success</span>

## 2) O_NONBLOCK
If we add this 
1) to ```open()``` call for reading - <span style="color:red">failed to read: Resource temporarily unavailable</span>
2) to ```open()``` call for writing - <span style="color:red">failed to open writing end: No such device or address</span>



