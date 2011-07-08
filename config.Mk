# Available platforms:- FREEBSD LINUX OTHER
PLATFORM=FREEBSD

PREFIX=/usr/local

CC=gcc
CFLAGS=-I/usr/X11R6/include -I/usr/local/include

CPP=g++
CPPFLAGS=-I/usr/X11R6/include -I/usr/local/include

LDFLAGS=-L/usr/X11R6/lib -L/usr/local/lib

