include ../../config.Mk

OBJ=Environment.o Shell.o Ini.o Filesystem.o ExceptionDialog.o Workspace.o vdesk.o
OUT=../../lib/libopencde.so

.SUFFIXES: .o

.PHONY: all
all: ${OUT}

${OUT}: ${OBJ}
	${CPP} -shared -o ${OUT} ${OBJ} ${LDFLAGS} -lXpm -lXm -lXt -lX11
	cp -r include/* ../../include

.cpp.o:
	${CPP} ${CPPFLAGS} -fPIC -DPLATFORM_${PLATFORM} -c -Iinclude -I../../include $< -o $@

.PHONY: clean
clean:
	rm -f ${OUT} ${OBJ}

