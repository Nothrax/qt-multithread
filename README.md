# QT QThread functionality presentation
Written and tested on ubuntu 20.04.

# Prerequisites
* cmake >= 3.20
* Qt5
* gcc >= 9.3

# Build
Ubuntu:
```
mkdir _build
cd _build
cmake ..
make
```

#How to use it
Prime section and factorial section calculates its results independently in their own threads, they can be paused or stopped.
Factorial output will show maximum of 1000 characters and since calculation of factorial is really fast, after each iteration there is a 100 millisecond sleep so,
it gives us the ability to see the calculation and pause it, since without this sleep the calculation is almost immediate.
Prime numbers will be calculated using erasthotenes sieve in given interval, maximum value INTMAX. The output window is limited and can overflow so be
careful with chosen window.