# hrtimerpp
[![Build Status](https://travis-ci.org/ndoering/hrtimerpp.svg?branch=master)](https://travis-ci.org/ndoering/hrtimerpp)

A high resolution timer for Linux systems written in C++.

This library provides a class based interface for high resolution timers for C++. The goal is to have a usable set of class for the needs of time measuring and statistical analysis for series of an arbitrary number of measurements.

This library makes use of features from the C++14 standard. Please make sure, that your compiler provides support for this standard.To compile code with this library add <code>-std=c++14</code> or <code>-std=c++1y</code> to your  compiler options, if your compiler supports C++14/1y. Add <code>-std=c++11</code> if it does not.

This code respects the version numbering system "Semantic Versioning 2.0.0", as described here: [semver.org](http://semver.org/)

## Requirements
* Linux kernel &ge; 2.6
* GCC &ge; 4.6 or Clang &ge; 3.0
* CMake &ge; 2.8
* Doxygen &ge; 1.8, for documentation

## Roadmap
* Export of Timer and Timerseries
* Import of Timer and Timerseries
