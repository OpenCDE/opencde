include ../../config.Mk

OBJ=Application.o Component.o Window.o MessageBox.o Panel.o Button.o ScrolledText.o Dialog.o Container.o Text.o Label.o Password.o MenuBar.o PulldownMenu.o Color.o ToggleButton.o Custom.o IconButton.o Timer.o
OUT=../../lib/libmotifmm.so

.SUFFIXES: .o

.PHONY: all
all: ${OUT}

${OUT}: ${OBJ}
	${CPP} -shared -o ${OUT} ${OBJ} ${LDFLAGS} -lXpm -lXm -lXt -lX11
	cp -r include/* ../../include

.cpp.o:
	${CPP} ${CPPFLAGS} -fPIC -DPLATFORM_${PLATFORM} -c -Iinclude $< -o $@

.PHONY: clean
clean:
	rm -f ${OUT} ${OBJ}

