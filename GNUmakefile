include Makefile

# It's expected that the casual user will "make install"
# These sub-targets are meant for packagers who need a modular system
# otherwise install.sys and install.bin would need install.lib
# and install.all
# install.xm is for straight Motif binaries.
install: install.lib install.sys install.xm install.bin install.all


install.all: install.dirs
	${INST} -m 0755 bin/dtsession ${INSTDIR}/bin/
	${INST} -m 0755 bin/dtterm ${INSTDIR}/bin/
	${INST} -m 0755 bin/dtwm ${INSTDIR}/bin/
	cp -r share/opencde ${INSTDIR}/share/
ifeq ($(PREFIX),/usr) 
	sed -e 's|export LD_LIB.*PATH||' -i ${INSTDIR}/share/opencde/dtlogin/scripts/session
endif
ifeq ($(FSH),FSH)
	cp -r etc/opencde ${DESTDIR}/etc/
else
	cp -r etc/opencde ${INSTDIR}/etc/
endif

