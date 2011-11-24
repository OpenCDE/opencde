# Available platforms:- FREEBSD LINUX OTHER
PLATFORM=FREEBSD
USE_FSH=no
PREFIX=/usr/local

INST=install -c
CC=gcc
CFLAGS=-Wall -Os -I/usr/X11R6/include -I/usr/local/include

CPP=g++
CPPFLAGS=-Wall -Os -I/usr/X11R6/include -I/usr/local/include

LDFLAGS=-L/usr/X11R6/lib -L/usr/local/lib

