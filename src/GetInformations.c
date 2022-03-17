/* Implementation of functions called to get and print informations on the executable */

#include "GetInformations.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <elf.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <execinfo.h>
#include <sys/wait.h>


/* Print the values of category "name" in /proc/self/status */
void getStatusInfo(const char * name, const char * message)
{
    // Open /proc/self/status file
    char * status_path = "/proc/self/status";
    FILE* status_file = fopen(status_path, "r");
    if (!status_file) perror("can't open /proc/self/status");

	// Read file until we found name
    char line[100], current_name[10]; char values[20];
    do
    {
        fgets(line, 100, status_file);
        sscanf(line, "%[^:]", current_name);
        memcpy(values, &line[strlen(current_name)+2], 20);
    } while ( strcmp(name,current_name) );

    // Display information
    printf("%s: %s", message, values);
    fflush(stdout);

    // Free memory
    fclose(status_file);
}

/* Read ELF file to get symbols list */
void getSymbolList()
{
	//
	void* start = NULL;
	int i, fd;
	struct stat stat;
	char *strtab;
	int nb_symbols;

    // Get binary name
    char name[1024];
    int ret;

	// Get resolved symbolic links
    ret = readlink("/proc/self/exe",name,sizeof(name)-1);
    if(ret ==-1) {
        perror("readlink");
        exit(1);
    }
    name[ret] = 0;

	// Open file
	fd = open(name, O_RDONLY, 660);
	if(fd < 0)
		perror("open");

	// Get size
	fstat(fd, &stat);

	// Mapping : memory projection
	start = mmap(0, stat.st_size, PROT_READ , MAP_FILE | MAP_SHARED, fd, 0);
	if(start == MAP_FAILED)
	{
		perror("mmap");
		abort();
	}

	// Getting header (ELF file beginning) from mapped ELF file
	// Casting to use <elf.h> library to analyse it's content
	Elf64_Ehdr* hdr = (Elf64_Ehdr *) start;

	// Symbols tab
	Elf64_Sym* symtab;

	// Getting the offset for each sections defined in the header
	Elf64_Shdr* sections = (Elf64_Shdr *)((char *)start + hdr->e_shoff);

	// Run through all sections
	for (i = 0; i < hdr->e_shnum; i++)
	{
		// If the current session is of type SYMTAB
		if (sections[i].sh_type == SHT_SYMTAB) {
			// Storing the offset for that sections
			symtab = (Elf64_Sym *)((char *)start + sections[i].sh_offset);

			// Storing size of the section
			nb_symbols = sections[i].sh_size / sections[i].sh_entsize;

			// 
			strtab = (char*)((char*)start + sections[sections[i].sh_link].sh_offset);
		}
	}

	char * ignore = "_";
	// Run through all symbols
	for (i = 0; i < nb_symbols; ++i)
		if (strncmp(ignore, strtab + symtab[i].st_name, 1) != 0) printf("%s\n", strtab + symtab[i].st_name);
}


/* Displays Stack Trace */
void getBacktrace()
{
	int size = 10;
	int nptrs;
	void *buffer[size];
	char **strings;
	char * isp = "/usr/local/lib/libinspection.so";

	nptrs = backtrace(buffer, size);
	printf("backtrace() returned %d addresses\n", nptrs);

	strings = backtrace_symbols(buffer, nptrs);
	if (strings == NULL) {
		perror("backtrace_symbols");
		exit(EXIT_FAILURE);
	}

	for (int j = 0; j < nptrs; j++)
		if (strncmp(strings[j], isp, strlen(isp)) != 0) printf("%s\n", strings[j]);

	free(strings);
}

/* Get linked shared libraries */
void ldd()
{
	pid_t child = fork();

	if (child == 0)
	{
		// We need to specify LD_PRELOAD empty, or else it will load
		// again the Inspection library
    	char *const args[] = {"sh", "-c", "ldd bin/signals",NULL};
    	char *const envs[] = {"LD_PRELOAD=",NULL};
    	execve("/bin/sh",args,envs);
	} else {
		wait(NULL);
	}
}