include config.Mk

all:
	@${MAKE} -C src

clean:
	@${MAKE} -C src clean

install:
	mkdir -p ${PREFIX}
	mkdir -p ${PREFIX}/share
	mkdir -p ${PREFIX}/etc
	cp -r share/opencde ${PREFIX}/share/
	cp -r etc/opencde ${PREFIX}/etc/

	mkdir -p ${PREFIX}/bin
	cp bin/dtlock ${PREFIX}/bin/
	chmod u=rwxs ${PREFIX}/bin/dtlock
	chmod g=rx ${PREFIX}/bin/dtlock
	chmod o=rx ${PREFIX}/bin/dtlock

	cp bin/dtlogin ${PREFIX}/bin/
	# cp bin/dtpad ${PREFIX}/bin/
	cp bin/dtpanel ${PREFIX}/bin/
	cp bin/dtrun ${PREFIX}/bin/
	cp bin/dtsession ${PREFIX}/bin/
	cp bin/dtsplash ${PREFIX}/bin/
	cp bin/dtterm ${PREFIX}/bin/
	cp bin/dtwm ${PREFIX}/bin/

	mkdir -p ${PREFIX}/lib
	cp lib/libmotifmm.so ${PREFIX}/lib/
	cp lib/libopencde.so ${PREFIX}/lib/

uninstall:
	rm -r -f ${PREFIX}/share/opencde
	rm -r -f ${PREFIX}/etc/opencde
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

