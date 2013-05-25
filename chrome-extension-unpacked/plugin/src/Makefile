CFLAGS = -Wall -DXP_UNIX=1 -DMOZ_X11=1 -fPIC -g

np_adb_wrapper : adb_wrapper.o
	cc $(CFLAGS) -shared adb_wrapper.o -o np_adb_wrapper.so

adb_wrapper.o : adb_wrapper.c adb_wrapper.h
	cc `pkg-config --cflags gtk+-2.0` $(CFLAGS) -c adb_wrapper.c

clean :
	rm np_adb_wrapper.so adb_wrapper.o

