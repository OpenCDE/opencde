include config.Mk
INSTDIR=${DESTDIR}${PREFIX}

all:
	@${MAKE} -C src

clean:
	@${MAKE} -C src clean

# It's expected that the casual user will "make install"
# These sub-targets are meant for packagers who need a modular system
# otherwise install.sys and install.bin would need install.lib
# and install.all
# install.xm is for straight Motif binaries.
install: install.lib install.sys install.xm install.bin install.all

install.dirs:
	mkdir -p ${INSTDIR}/bin
	mkdir -p ${INSTDIR}/lib
	mkdir -p ${INSTDIR}/share
	mkdir -p ${INSTDIR}/etc

install.sys: install.dirs
	${INST} -s -m 0755 bin/dtlock ${INSTDIR}/bin/
	chmod u+s ${INSTDIR}/bin/dtlock
	${INST} -s -m 0755 bin/dtlogin ${INSTDIR}/bin/

install.bin: install.dirs
	${INST} -s -m 0755 bin/dtfile ${INSTDIR}/bin/
	${INST} -s -m 0755 bin/dtpanel ${INSTDIR}/bin/
	${INST} -s -m 0755 bin/dtrun ${INSTDIR}/bin/
	${INST} -s -m 0755 bin/dtsplash ${INSTDIR}/bin/

install.xm: install.dirs
	${INST} -s -m 0755 bin/dtpad ${INSTDIR}/bin/

install.all: install.dirs
	${INST} -m 0755 bin/dtsession ${INSTDIR}/bin/
	${INST} -m 0755 bin/dtterm ${INSTDIR}/bin/
	${INST} -m 0755 bin/dtwm ${INSTDIR}/bin/
	cp -r share/opencde ${INSTDIR}/share/
	test "${PREFIX}" = "/usr" && sed -e 's|export LD_LIB.*PATH||' -i ${INSTDIR}/share/opencde/dtlogin/scripts/session
	cp -r etc/opencde ${INSTDIR}/etc/


install.lib: install.dirs
	cp lib/libmotifmm.so* ${INSTDIR}/lib/
	cp lib/libopencde.so* ${INSTDIR}/lib/

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

	rm -f ${INSTDIR}/lib/libmotifmm.so
	rm -f ${INSTDIR}/lib/libopencde.so

