#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(){
	const char* elfFile = "liblab05.so";
    int i,j;
    char a, sname[32];
	Elf64_Ehdr header;
	Elf64_Shdr sheader;
	Elf64_Shdr symtab;
	Elf64_Shdr strtab;
	Elf64_Shdr shstrtab;
	Elf64_Sym sym;

	FILE* file = fopen(elfFile, "rb");
	fread(&header, sizeof(header), 1, file);
	fseek(file, header.e_shoff, SEEK_SET);
	for(i=0; i < header.e_shnum; i++){
		fseek(file, header.e_shoff + header.e_shentsize * i, SEEK_SET);
		fread(&sheader, sizeof(sheader), 1, file);
		if(i == 4)	symtab = (Elf64_Shdr)sheader;
		if(i == 5)	strtab = (Elf64_Shdr)sheader;
		if (i == header.e_shstrndx)	shstrtab = (Elf64_Shdr)sheader;
	}
    fprintf(stdout, "%s\t%s\t%s\t%s\t%s\t%s\n","№ ", "st_size","ST_TYPE","ST_BIND","st_shndx","sname");
	for(i=0; i < symtab.sh_size / symtab.sh_entsize; i++){
		fseek(file, symtab.sh_offset + symtab.sh_entsize * i, SEEK_SET);
		fread(&sym, sizeof(Elf64_Sym), 1, file);
		fseek(file, strtab.sh_offset + sym.st_name, SEEK_SET);
		fread(sname, 1,32, file);
        if (sym.st_shndx != 0) fprintf(stdout, "%d\t%ld\t%u\t%u\t%hd\t%s\n",	i, sym.st_size,	ELF64_ST_TYPE(sym.st_info),	ELF64_ST_BIND(sym.st_info),
                sym.st_shndx, sname);
	}
	j = 0;
	for(i=0; i < shstrtab.sh_size; i++){
		fseek(file, shstrtab.sh_offset + i, SEEK_SET);
		fread(&a, sizeof(char), 1, file);
		if (a == '\0'){
			fprintf(stdout, "\n #%d - ", j);
			j++;
		}
		else fprintf(stdout, "%c", a);
	}
	return 0;
}