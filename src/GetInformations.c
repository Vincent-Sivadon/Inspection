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
	void* start = NULL;
	int i, fd;
	struct stat stat;
	char *strtab;
	int nb_symbols;

    // Get binary name
    char name[1024];
    int ret;

    ret = readlink("/proc/self/exe",name,sizeof(name)-1);
    if(ret ==-1) {
        perror("readlink");
        exit(1);
    }
    name[ret] = 0;

	// ouverture du fichier (pour être mappé)
	fd = open(name, O_RDONLY, 660);
	if(fd < 0)
		perror("open");

	// récupération de la taille du fichier
	fstat(fd, &stat);

	//projection du fichier (MAP_SHARED importe peu ici)
	start = mmap(0, stat.st_size, PROT_READ , MAP_FILE | MAP_SHARED, fd, 0);
	if(start == MAP_FAILED)
	{
		perror("mmap");
		abort();
	}

	// le premier octet mappé est le premier octet du fichier ELF
	// Via un cast, on va pouvoir manipuler le fichier ELF mappé en mémoire
	Elf64_Ehdr* hdr = (Elf64_Ehdr *) start;
	Elf64_Sym* symtab;

	// le header contient un champ donnant l'offset (en octet) où se trouve
	// les sections headers
	Elf64_Shdr* sections = (Elf64_Shdr *)((char *)start + hdr->e_shoff);

	// parcours des sections
	for (i = 0; i < hdr->e_shnum; i++)
	{
		// si la section courante est de type 'table de symbole'
		if (sections[i].sh_type == SHT_SYMTAB) {
			// on sauvegarde:
			// 1. le pointeur sur la table de symboles
			// 2. Le nombre de symboles dans cette table
			symtab = (Elf64_Sym *)((char *)start + sections[i].sh_offset);
			nb_symbols = sections[i].sh_size / sections[i].sh_entsize;

			strtab = (char*)((char*)start + sections[sections[i].sh_link].sh_offset);
		}
	}

	// on parcourt alors la table des symboles
	// pour chaque entrée, le champ st_name est un offset en octet depuis 
	// le début du tableau où se trouve le nom.
	char * ignore = "_";
	for (i = 0; i < nb_symbols; ++i)
		if (strncmp(ignore, strtab + symtab[i].st_name, 1) != 0) printf("%s\n", strtab + symtab[i].st_name);
}


/* */
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

/*
int puts(const char * s)
{
	int (*original_puts)(const char*);
	original_puts = dlsym(RTLD_NEXT, "puts");
	(*original_puts)("hahaha");
	return 0;
}
*/


/*
FILE *fopen(const char *path, const char *mode) {
    printf("In our own fopen, opening %s\n", path);

    FILE *(*original_fopen)(const char*, const char*);
    original_fopen = dlsym(RTLD_NEXT, "fopen");
    return (*original_fopen)(path, mode);
}
*/

