# timedout
A Linux tool to display all output with time using pipe redirections.

## Build
This project uses CMake to compile the software. To compile, make sure you have CMake and an C compiler installed on your computer.

```
mkdir build
cd build
cmake ..
make
```

## Install
To install timedout with CMake, following commands can be done, as we can start from scratch:

```
mkdir build
cd build
cmake -S .. -B .
cmake --build .
sudo cmake --install .
```

## Usage
The timedout software prints out the time when each line was printed. It can be used for piping or placing a time prefix in front of every line of a file for example.

For piping, it can be used as
```
[some command] | timedout [options]
```
and for displaying prefixes for lines of files
```
timedout [options] < [filename]
```

When executing with the -h or --help option, timedout displays instructions on how to use timedout.

```
Usage: [some command] | ./timedout [options]
  Options:
    -c                  Display time as current time instead of how much time has elapsed.
    -m                  Display milliseconds also.
    -f [format]         Display as custom format, based on strftime. See man 3 strftime.
```
