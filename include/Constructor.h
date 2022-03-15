#pragma once

/* Dynamic Library Constructor */
static void __attribute__((constructor)) lib_init(void);
static void __attribute__((destructor)) lib_close(void);