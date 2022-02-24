CC=gcc

# Directories
INC=./include

# Compilation flags
CFLAGS_LIB=-Wall -I$(INC) -fPIC -shared


# =============== LIBRARY COMPILATION ===============
Inspection: src/Constructor.c include/Constructor.h
	$(CC) $(CFLAGS_LIB) $< -o lib/libinspection.so
	$(CC) src/$@.c -o bin/inspection

# =============== LIBRARY INSTALLATION ===============
install: Inspection
	cp lib/libinspection.so /usr/local/lib
	cp bin/inspection /usr/local/bin
uninstall:
	rm -f /usr/local/lib/libinspection.so
	rm -f /usr/local/bin/inspection


# ====================== TESTS ======================
loop: test/loop.c
	$(CC) $< -o bin/loop
TESTS: loop


# ==================== RUN TESTS ====================
check: Inspection TESTS
	bin/inspection bin/loop
#LD_PRELOAD=./lib/libinspection.so bin/loop

# CLEAN
clean:
	rm -f bin/* lib/*
.PHONY: clean