include config.Mk

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
	mkdir -p ${PREFIX}/bin
	mkdir -p ${PREFIX}/lib
	mkdir -p ${PREFIX}/share
	mkdir -p ${PREFIX}/etc

install.sys: install.dirs
	${INST} -s -m 0755 bin/dtlock ${PREFIX}/bin/
	chmod u+s ${PREFIX}/bin/dtlock
	${INST} -s -m 0755 bin/dtlogin ${PREFIX}/bin/

install.bin: install.dirs
	${INST} -s -m 0755 bin/dtfile ${PREFIX}/bin/
	${INST} -s -m 0755 bin/dtpanel ${PREFIX}/bin/
	${INST} -s -m 0755 bin/dtrun ${PREFIX}/bin/
	${INST} -s -m 0755 bin/dtsplash ${PREFIX}/bin/

install.xm: install.dirs
	${INST} -s -m 0755 bin/dtpad ${PREFIX}/bin/

install.all: install.dirs
	${INST} -s -m 0755 bin/dtsession ${PREFIX}/bin/
	${INST} -s -m 0755 bin/dtterm ${PREFIX}/bin/
	${INST} -s -m 0755 bin/dtwm ${PREFIX}/bin/
	cp -r share/opencde ${PREFIX}/share/
	cp -r etc/opencde ${PREFIX}/etc/


install.lib: install.dirs
	cp lib/libmotifmm.so* ${PREFIX}/lib/
	cp lib/libopencde.so* ${PREFIX}/lib/

uninstall:
	rm -r -f ${PREFIX}/share/opencde
	rm -r -f ${PREFIX}/etc/opencde
	rm -f ${PREFIX}/bin/dtfile
	rm -f ${PREFIX}/bin/dtlock
	rm -f ${PREFIX}/bin/dtlogin
	rm -f ${PREFIX}/bin/dtpad
	rm -f ${PREFIX}/bin/dtpanel
	rm -f ${PREFIX}/bin/dtrun
	rm -f ${PREFIX}/bin/dtsession
	rm -f ${PREFIX}/bin/dtsplash
	rm -f ${PREFIX}/bin/dtterm
	rm -f ${PREFIX}/bin/dtwm

	rm -f ${PREFIX}/lib/libmotifmm.so
	rm -f ${PREFIX}/lib/libopencde.so

