include ../../config.Mk

OBJ=main.o RunWindow.o
OUT=../../bin/dtrun

.SUFFIXES: .o

.PHONY: all
all: ${OUT}

${OUT}: ${OBJ}
	${CPP} -o ${OUT} ${OBJ} -L../../lib ${LDFLAGS} -lmotifmm -lopencde

.cpp.o:
	${CPP} ${CPPFLAGS} -DPLATFORM_${PLATFORM} -c -I../../include $< -o $@

.PHONY: clean
clean:
	rm -f ${OUT} ${OBJ}
