include ../../config.Mk

OBJ=Environment.o Shell.o Ini.o Filesystem.o ExceptionDialog.o Workspace.o vdesk.o
BASELIB=libopencde.so
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
	cp -r include/* ../../include

.cpp.o:
	${CPP} ${CPPFLAGS} -fPIC -DPLATFORM_${PLATFORM} -c -Iinclude -I../../include $< -o $@

.PHONY: clean
clean:
	rm -f ${OUT} ${OBJ}
	rm -f ../../lib/${BASELIB}*

