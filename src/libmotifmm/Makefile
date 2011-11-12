include ../../config.Mk

OBJ=Application.o Component.o Window.o MessageBox.o Panel.o Button.o ScrolledText.o Dialog.o Container.o Text.o Label.o Password.o MenuBar.o PulldownMenu.o Color.o ToggleButton.o Custom.o IconButton.o Timer.o ScrolledPanel.o ScrollBar.o Separator.o
BASELIB=libmotifmm.so
SONAME=${BASELIB}.2
OUTFILE=${SONAME}.0.0
OUT=../../lib/${OUTFILE}

.SUFFIXES: .o

.PHONY: all
all: ${OUT}

${OUT}: ${OBJ}
	${CPP} -shared -Wl,-soname,${SONAME} -o ${OUT} ${OBJ} ${LDFLAGS} -lXpm -lXm -lXt -lX11
	ln -s ${OUTFILE} ../../lib/${SONAME}
	ln -s ${OUTFILE} ../../lib/${BASELIB}
	mkdir -p ../../include
	cp -r include/* ../../include

.cpp.o:
	${CPP} ${CPPFLAGS} -fPIC -DPLATFORM_${PLATFORM} -c -Iinclude $< -o $@

.PHONY: clean
clean:
	rm -f ${OUT} ${OBJ}
	rm -rf ../../include

