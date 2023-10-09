#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	// const char* elfFile="liblab5.so";
	const char *elfFile = argv[1];
	Elf64_Ehdr header;
	Elf64_Shdr sheader;
	Elf64_Shdr symtab;
	Elf64_Shdr strtab;
	Elf64_Sym sym;
	char sname[32];
	int i;
	FILE *file = fopen(elfFile, "rb");

	fread(&header, sizeof(header), 1, file);
	fseek(file, header.e_shoff, SEEK_SET);
	fread(&sheader, sizeof(sheader), 1, file);
	for (i = 0; i < header.e_shnum; i++)
	{
		fseek(file, header.e_shoff + header.e_shentsize * i, SEEK_SET);
		fread(&sheader, sizeof(sheader), 1, file);
		if (i == 4)
			symtab = (Elf64_Shdr)sheader;
		if (i == 5)
			strtab = (Elf64_Shdr)sheader;
	}

	for (i = 0; i < symtab.sh_size / symtab.sh_entsize; i++)
	{
		fseek(file, symtab.sh_offset + symtab.sh_entsize * i, SEEK_SET);
		fread(&sym, sizeof(Elf64_Sym), 1, file);
		fseek(file, strtab.sh_offset + sym.st_name, SEEK_SET);
		fread(sname, 1, 32, file);
		fprintf(stdout, "%d\t%lld\t%u\t%u\t%hd\t%s\n", i,
						sym.st_size,
						ELF64_ST_TYPE(sym.st_info),
						ELF64_ST_BIND(sym.st_info),
						sym.st_shndx, sname);
	}
	return 0;
}
