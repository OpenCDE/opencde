# Included automatically when FSH=y
# XAPPDIR should be the directory where app-defaults/ may be found
XAPPDIR=/etc/X11
CPPFLAGS+=-DFSH
etc.dirs: 
	mkdir -p ${DESTDIR}/${XAPPDIR}
	mkdir -p ${INSTDIR}/share
install.etc: etc.dirs
	cp -r etc/opencde ${DESTDIR}/etc/
	cp -r share/opencde ${INSTDIR}/share
	cp -r app-defaults/ ${DESTDIR}/${XAPPDIR}
	

