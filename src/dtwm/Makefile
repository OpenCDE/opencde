include ../../config.Mk

OBJ=WmCDInfo.o WmCDecor.o WmCEvent.o WmCPlace.o WmCmd.o WmColormap.o WmError.o WmEvent.o WmFeedback.o WmFunction.o WmGraphics.o WmIDecor.o WmIPlace.o WmIconBox.o WmImage.o WmInitWs.o WmKeyFocus.o WmMain.o WmManage.o WmMenu.o WmProperty.o WmProtocol.o WmResCvt.o WmResParse.o WmResource.o WmSignal.o WmWinConf.o WmWinInfo.o WmWinList.o WmWinState.o WmWsm.o WmXSMP.o version.o debug.o free.o recv.o util.o disp.o pack.o send.o utm_send.o

OUT=../../bin/dtwm

.SUFFIXES: .o

.PHONY: all
all: $(OUT)

$(OUT): $(OBJ)
	$(CC) -o $(OUT) $(OBJ) -lXpm -lXm -lXt -lX11 $(LDFLAGS)

.c.o:
	$(CC) -DNO_OL_COMPAT -DLARGECURSORS -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f $(OUT) $(OBJ)

