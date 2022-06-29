# This Makefile
# gives instructions to the command
# make
# about how and whether to build programs
#
# The syntax is

# thingtobuld:  what-it-needs-or-depends-on
#    instructions on how to build it
#

# make uses the modification dates to determine
# is the programs need to be re-built

all: main

main: main.cpp
	g++ -g -std=c++11 main.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system -lcpr -lX11  `pkg-config gtkmm-3.0 --cflags --libs`
