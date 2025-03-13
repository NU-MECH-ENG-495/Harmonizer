# Funky Music

## Overview
This Funky Music application is a program that interacts with a harmonica device over serial communication. It can play a MIDI file through the device as well as check the hardware calibration if no file is provided.

## Requirements
Libserial

## Compilation and Installation
Generate build files with `cmake -B build`
Build with `cmake --build build`

## Usage
execute with `./build/src/music_run`. If no file is provided the app will run a routine to check the calibration of the hardware.
There are two midi files provided in this repo as samples.

execute tests by changing your directory to `build/test/` and running `ctest` or by running `./build/test/music_test`

build doxygen documentaiton with `doxygen Doxyfile` and loading the index.html in your browser
