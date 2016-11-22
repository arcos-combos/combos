BIN_FILES  = boinc_simulator create_platform create_deployment

INSTALL_PATH = $(HOME)/simgrid

CC = gcc

CPPFLAGS = -I$(INSTALL_PATH)/include #-D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64


#NO_PRAYER_FOR_THE_WICKED =	-w -O3 -g
NO_PRAYER_FOR_THE_WICKED =	-Wall -g

LDFLAGS = -L$(INSTALL_PATH)/lib/
LDLIBS = -lm -lsimgrid -rdynamic $(INSTALL_PATH)/lib/libsimgrid.so -Wl,-rpath,$(INSTALL_PATH)/lib


all: CFLAGS=$(NO_PRAYER_FOR_THE_WICKED)
all: $(BIN_FILES)
.PHONY : all

boinc_simulator: boinc_simulator.o rand.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

create_platform: create_platform.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

create_deployment: create_deployment.o rand.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -Ofast $<

clean:
	rm -f $(BIN_FILES) *.o

.SUFFIXES:
.PHONY : clean
