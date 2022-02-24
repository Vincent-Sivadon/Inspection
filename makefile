CC=gcc

# Directories
INC=./include

# Compilation flags
CFLAGS_LIB=-Wall -I$(INC) -fPIC -shared


# =============== LIBRARY COMPILATION ===============
Inspection: src/Inspection.c include/Inspection.h
	$(CC) $(CFLAGS_LIB) src/$@.c -o lib/lib$@.so


# =============== LIBRARY INSTALLATION ===============
install: Inspection
	cp lib/libInspection.so /usr/local/lib
uninstall:
	rm -f /usr/local/lib/libInspection.so


# ====================== TESTS ======================
fopen: test/fopen.c
	$(CC) $< -o bin/fopen
test2: test/test2.c
	$(CC) $< -o bin/test2
TESTS:fopen test2


# ==================== RUN TESTS ====================
check: Inspection TESTS
	LD_PRELOAD=./lib/libInspection.so bin/fopen
	LD_PRELOAD=./lib/libInspection.so bin/test2


# CLEAN
clean:
	rm -f bin/* lib/*