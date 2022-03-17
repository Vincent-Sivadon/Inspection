
---
# <center> <h1>Inspection</h1> </center>
## <center> <h3>(Running Process Analyser)</h3> </center>
---

Inspection is made in the context of a project assignement on creating our own debugger.  
Our library acts similarly as gdb in terms of interactivity, and it allows someone to analyse a running process. The source code is built upon what we have studied in class : signal handler, dynamic library constructor, ELF format manipulation, fork, /proc/self informations, function interceptions...  
When starting the inspection, we execute the binary with the inspection library preloaded (LD_PRELOAD). It allows us to set up a signal handler, and get informations on the binary from inside.


## Features

### Signal Handler
At dynamic construction (when the program is executed with inspection library preloaded), we set up different reactions to different terminaison signals. Signal analysis allows us to print the adress on wich the program had the signal.
```
================ Inspection ================

(isp) run
SIGINT received : program interrupted at
0x7f3d06c01320
(isp)
```

### Read /proc/self/status
A function that takes a string representing the name of a category in /proc/self/status displays the value for that category.
```
(isp) name
Program name: loop
```
### Memory state
By reading in /proc/self/status, we can get memory informations.
```
(isp) mem
Virtual memory (peak)    size:     2556 kB
Virtual memory (current) size:     2556 kB
Virtual memory (data)    size:      196 kB
Virtual memory (stack)   size:      132 kB
```

### ELF format manipulations
Reading into the ELF formatted file we can get access to, among other things, the list of symbols.

```
(isp) nm
crtstuff.c
.
.
malloc@@GLIBC_2.2.5
main
```

### Function interceptions
Because we know our library is going to be the first to be loaded (LD_PRELOAD), we can override functions such as malloc. We use that trick to count the number of malloc, free, fopen, close. At the end of each inspection, a report on how many malloc, free, and file oppenend (and not yet closed) is given to the user.

```
------------------------------
Number of malloc : 5
Number of free : 2
Files not yet closed : 0
------------------------------
```

### Stack Trace
At interruption of the program, we can ask for the stack trace. Compiling the executable with -rdynamic allows the exportation of symbols to be recognized by our backtrace.

```
(isp) bt
backtrace() returned 8 addresses
/lib/x86_64-linux-gnu/libc.so.6(+0x430c0) [0x7f4c55f920c0]
/lib/x86_64-linux-gnu/libc.so.6(gsignal+0xcb) [0x7f4c55f9203b]
bin/loop(main+0x37) [0x5624889661e0]
/lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf3) [0x7f4c55f730b3]
bin/loop(_start+0x2e) [0x5624889660ee]
```


## Installation

To install :
```
sudo make install
```
The following files will be created :
```
/usr/local/lib/libinspection.so (dynamic library)
/usr/local/include/Inspection (all headers)
/usr/local/bin/inspection (the executable 'inspection')
```
To uninstall (deleting all those files) :
```
sudo make uninstall
```


## Usage

To run the analysis on the executable *bin.exe* :
```
inspection bin.exe
```
After that we can ask informations on the program, such as :
* `help` : prints all commands
* `run` : runs bin.exe
* `quit` : stops the analysis and displays a report
* `id` : program identifier
* `pid`, `ppid`, `name` : give single informations
* `ldd` : print all linked shared objects
* `bt` : print stack trace
* `nm` : print all symbols
* `mem` : print memory state
