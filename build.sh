#!/bin/bash

g++ -o program main.cpp graphics.cpp $(sdl2-config --cflags --libs) -lSDL2_image -lSDL2_ttf
