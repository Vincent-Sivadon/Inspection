CC=gcc

# Directories
SRC_LIB=src/Constructor.c src/Core.c
SRC_BIN=src/Inspection.c
LIB=/usr/local/lib/libinspection.so

# Compilation flags
CFLAGS_LIB=-Wall -I./include/ -fPIC -shared


# =============== LIBRARY INSTALLATION ===============
install: $(SRC_LIB) $(SRC_BIN) include/*
	$(CC) $(CFLAGS_LIB) $(SRC_LIB) -o /usr/local/lib/libinspection.so
	cp -R include/ /usr/local/include/Inspection/
	$(CC) src/Inspection.c -o /usr/local/bin/inspection -linspection
uninstall:
	rm -f /usr/local/lib/libinspection.so
	rm -r /usr/local/include/Inspection/
	rm -f /usr/local/bin/inspection


# ====================== TESTS ======================
loop: test/loop.c
	$(CC) $< -o bin/loop
sigint: test/sigint.c
	$(CC) $< -o bin/sigint

TESTS: sigint


# ==================== RUN TESTS ====================
check: $(SRC_LIB) $(SRC_BIN) $(INC) TESTS
	inspection bin/sigint


# CLEAN
clean:
	rm -f bin/*
.PHONY: clean