include config.Mk
INSTDIR=${DESTDIR}${PREFIX}
#This will define -DFSH if proper, etc.dirs, + install.etc
include makefsh.${FSH}

all:
	mkdir -p bin
	cp script/* bin/
	@${MAKE} -C src
	

clean:
	@${MAKE} -C src clean

# It's expected that the casual user will "make install"
# These sub-targets are meant for packagers who need a modular system
# otherwise install.sys and install.bin would need install.lib
# and install.all
# install.xm is for straight Motif binaries.
install: install.lib install.sys install.xm install.bin install.all

install.dirs: etc.dirs
	mkdir -p ${INSTDIR}/bin
	mkdir -p ${INSTDIR}/lib${LIBSUFFIX}
	mkdir -p ${INSTDIR}/share

install.sys: install.dirs install.etc
	${INST} -s -m 0755 bin/dtlock ${INSTDIR}/bin/
	chmod u+s ${INSTDIR}/bin/dtlock
	${INST} -s -m 0755 bin/dtlogin ${INSTDIR}/bin/

install.bin: install.dirs install.etc
	${INST} -s -m 0755 bin/dtfile ${INSTDIR}/bin/
	${INST} -s -m 0755 bin/dtpanel ${INSTDIR}/bin/
	${INST} -s -m 0755 bin/dtrun ${INSTDIR}/bin/
	${INST} -s -m 0755 bin/dtsplash ${INSTDIR}/bin/

install.xm: install.dirs
	${INST} -s -m 0755 bin/dtpad ${INSTDIR}/bin/

install.all: install.dirs install.etc
#	cp -r share/opencde ${INSTDIR}/share/
#ifeq ($(PREFIX),/usr) 
#	sed -e 's|export LD_LIB.*PATH||' -i ${INSTDIR}/share/opencde/dtlogin/scripts/session

install.lib: install.dirs
	cp -P lib/libmotifmm.so* ${INSTDIR}/lib${LIBSUFFIX}/
	cp -P lib/libopencde.so* ${INSTDIR}/lib${LIBSUFFIX}/

uninstall:
	rm -r -f ${INSTDIR}/share/opencde
	rm -r -f ${INSTDIR}/etc/opencde
	rm -f ${INSTDIR}/bin/dtfile
	rm -f ${INSTDIR}/bin/dtlock
	rm -f ${INSTDIR}/bin/dtlogin
	rm -f ${INSTDIR}/bin/dtpad
	rm -f ${INSTDIR}/bin/dtpanel
	rm -f ${INSTDIR}/bin/dtrun
	rm -f ${INSTDIR}/bin/dtsession
	rm -f ${INSTDIR}/bin/dtsplash
	rm -f ${INSTDIR}/bin/dtterm
	rm -f ${INSTDIR}/bin/dtwm

	rm -f ${INSTDIR}/lib/libmotifmm.so*
	rm -f ${INSTDIR}/lib/libopencde.so*

