	#include <stdlib.h>
	#include <string.h>
	#include <stdio.h>
	#include <elf.h>
 
	int main(int argc, char **argv) {
		int read;
		
		if (argc < 2) { 
			printf("Insufficient arguments (expected: 1; found: %i)\n", argc);
			return 1;
		}
		
		FILE* f;
		if (!(f = fopen(argv[1], "r"))) {
			printf("Unable to open file: %s\n", argv[1]);
			return 1;
		}
		
		// verify type is 32 bit
		unsigned char	ident[EI_NIDENT];	/* Magic number and other info */
		if (!fread(&ident, sizeof(ident), 1, f)) {
			printf("Unable to read file: %s\n", argv[1]);
			return 1;
		} else if (ident[4] != 1) {
			printf("Invalid class (Expecting only 32-bit objects)\n");
			return 1;
		}
		
		// read header
		Elf32_Ehdr header;
		rewind(f);
		if (!fread(&header, sizeof(header), 1, f)) {
			printf("Unable to read file: %s\n", argv[1]);
			return 1;
		}
		
		int i = 0;
		char str_ident[48];
		for (i=0; i<EI_NIDENT; ++i) {
			sprintf(str_ident + (i*3), "%02x ", header.e_ident[i]);
		}
		
		printf("ELF Header:\n");
		printf("  Magic:   %s\n", str_ident);
		printf("  Class:                             %i\n", header.e_ident[4]);
		printf("  Data:                              %i\n", header.e_ident[5]);
		printf("  Version:                           %i\n", header.e_ident[6]);
		printf("  OS/ABI:                            %i\n", header.e_ident[7]);
		printf("  ABI Version:                       %i\n", header.e_ident[8]);
		printf("  Type:                              %i\n", header.e_type);
		printf("  Machine:                           %i\n", header.e_machine);
		printf("  Version:                           %i\n", header.e_version);
		printf("  Entry point address:               %x\n", header.e_entry);
		printf("  Start of program headers:          %i (bytes into file)\n", header.e_phoff);
		printf("  Start of section headers:          %i (bytes into file)\n", header.e_shoff);
		printf("  Flags:                             %i\n", header.e_flags);
		printf("  Size of this header:               %i (bytes)\n", header.e_ehsize);
		printf("  Size of program headers:           %i (bytes)\n", header.e_phentsize);
		printf("  Number of program headers:         %i\n", header.e_phnum);
		printf("  Size of section headers:           %i (bytes)\n", header.e_shentsize);
		printf("  Number of section headers:         %i\n", header.e_shnum);
		printf("  Section header string table index: %i\n", header.e_shstrndx);
		
		Elf32_Shdr shdr;
		int nameoff;
		int namesize;
		fseek(f, header.e_shoff + (header.e_shentsize * header.e_shstrndx), SEEK_SET);
		read = fread(&shdr, sizeof(shdr), 1, f);
		nameoff = shdr.sh_offset;
		namesize = shdr.sh_size;
		
		char* names = malloc(namesize);
		fseek(f, nameoff, SEEK_SET);
		read = fread(names, namesize, 1, f);
		
		printf("\n");
		for (i=0; i<header.e_shnum; i++) {
			fseek(f, header.e_shoff + (header.e_shentsize * i), SEEK_SET);
			read = fread(&shdr, sizeof(shdr), 1, f);
			printf("[%02i] name: %s; offset: %06x; size: %06x; type: %i;\n", i, names + shdr.sh_name, shdr.sh_offset, shdr.sh_size, shdr.sh_type);
		}
		
		free(names);
		return 0;                 
 }