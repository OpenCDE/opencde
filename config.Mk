# Available platforms:- FREEBSD LINUX OTHER
PLATFORM=FREEBSD
# FSH values: y n
# FSH=y uses /etc/opencde + /etc/X11/app-defaults
# FSH=n is classic OpenCDE: PREFIX/etc/opencde +
# PREFIX/share/opencde/app-defaults
# To add a configuration, copy makefsh.* to makefsh.${FSH}
FSH=n
PREFIX=/usr/local
LIBSUFFIX=
INST=install -c
CC=gcc
CFLAGS=-Wall -Os -I/usr/X11R6/include -I/usr/local/include

CPP=g++
CPPFLAGS=-Wall -Os -I/usr/X11R6/include -I/usr/local/include

LDFLAGS=-L/usr/X11R6/lib -L/usr/local/lib

