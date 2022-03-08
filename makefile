CC=gcc

# INCLUDE
HEADER_FILES=./include/*
HEADER_DIR=./include/

# SOURCES
SRC_FILES=./src/*
SRC_DIR=./src/

# DESTINATION
LIB_DEST=/usr/local/lib
LIB_HEADER_DEST=/usr/local/include/Inspection/
LIB_BIN_DEST=/usr/local/bin

# Compilation flags
CFLAGS_LIB=-Wall -I$(HEADER_DIR) -fPIC -shared


# =============== LIBRARY INSTALLATION ===============

# Creates Inspection library
# Copy header files in destination
# Create inspection binary
install: Inspection.c $(SRC_FILES) $(HEADER_FILES)
	$(CC) $(CFLAGS_LIB) $(SRC_FILES) -o $(LIB_DEST)/libinspection.so
	cp -R $(HEADER_DIR) $(LIB_HEADER_DEST)
	$(CC) Inspection.c -o $(LIB_BIN_DEST)/inspection

# Remove .so library file
# Remove header file directory
# Remove inspection binary
uninstall:
	rm -f $(LIB_DEST)/libinspection.so
	rm -r $(LIB_HEADER_DEST)
	rm -f $(LIB_BIN_DEST)/inspection


# ====================== TESTS ======================

# Infinite loop
loop: test/loop.c
	$(CC) $< -o bin/loop

# SIGITN raise
sigint: test/sigint.c
	$(CC) $< -o bin/sigint

# ALL tests target
TESTS: sigint


# ==================== RUN TESTS ====================
check: TESTS
	inspection bin/sigint


# CLEAN
clean:
	rm -f bin/*
.PHONY: clean