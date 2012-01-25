include ../../config.Mk

OBJ=main.o PanelWindow.o ExitDialog.o Grab.o MenuWindow.o
OUT=../../bin/dtpanel

.SUFFIXES: .o

.PHONY: all
all: ${OUT}

${OUT}: ${OBJ}
	${CPP} -o ${OUT} ${OBJ} -L../../lib ${LDFLAGS} -lmotifmm -lopencde -lX11 -lXm -lXpm -lXt

.cpp.o:
	${CPP} ${CPPFLAGS} -DPLATFORM_${PLATFORM} -c -I../libmotifmm/include -I../libopencde/include $< -o $@

.PHONY: clean
clean:
	rm -f ${OUT} ${OBJ}
