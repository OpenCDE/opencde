include ../../config.Mk

OBJ=main.o LoginWindow.o
OUT=../../bin/dtlogin

.SUFFIXES: .o

.PHONY: all
all: ${OUT}

${OUT}: ${OBJ}
	${CPP} -o ${OUT} ${OBJ} -L../../lib ${LDFLAGS} -lmotifmm -lopencde -lcrypt

.cpp.o:
	${CPP} ${CPPFLAGS} -DPLATFORM_${PLATFORM} -c -I../../include $< -o $@

.PHONY: clean
clean:
	rm -f ${OUT} ${OBJ}
