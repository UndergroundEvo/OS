#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	const char *elfFile = argv[1];
	Elf64_Ehdr header;
	Elf64_Phdr phheader;
	int i;
	FILE *file = fopen(elfFile, "rb");

	fread(&header, sizeof(header), 1, file);
	fclose(file);

	for (i = 0; i < 16; i++) fprintf(stdout, "%x\t", header.e_ident[i]);

	fprintf(stdout, "\n");
	fprintf(stdout, "type: %x\t machine: %x\n",header.e_type, header.e_machine);
//	fprintf(stdout, "e_phoff: %x\n",header.e_phoff);
    fprintf(stdout, "e_phoff: %lx\n",header.e_phoff);
	fprintf(stdout, "e_phnum: %d\n",header.e_phnum);

	file = fopen(elfFile, "rb");
	fseek(file, header.e_phoff, SEEK_SET);

	for (i = 0; i < header.e_phnum; i++){
		if (i > 0)	fseek(file,header.e_phoff + header.e_phentsize * i,SEEK_SET);
		fread(&phheader, header.e_phentsize, 1,file);
		fprintf(stdout, "%x\t%lx\t%lx\t%lx\n",phheader.p_type, phheader.p_offset,phheader.p_vaddr, phheader.p_paddr);
		fprintf(stdout, "%lx\t%lx\t%x\t%lx\n",phheader.p_filesz, phheader.p_memsz,phheader.p_flags, phheader.p_align);
		fprintf(stdout, "\n");
	}

	fclose(file);
	return 0;
}