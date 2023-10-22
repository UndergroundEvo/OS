#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    const char *elfFile = argv[1];
    Elf64_Ehdr header;
    Elf64_Shdr sheader;
    Elf64_Shdr dynsym;
    Elf64_Shdr strtab;
    Elf64_Sym sym;
    char sname[32];
    int i;
    FILE *file = fopen(elfFile, "rb");

    fread(&header, sizeof(header), 1, file);
    fseek(file, header.e_shoff, SEEK_SET);
    for (i = 0; i < header.e_shnum; i++)
    {
        fread(&sheader, sizeof(sheader), 1, file);
        if (sheader.sh_type == SHT_DYNSYM)
            dynsym = sheader;
        if (sheader.sh_type == SHT_STRTAB)
            strtab = sheader;
    }

    if (dynsym.sh_size == 0)
    {
        printf("No .dynsym section found in the ELF file.\n");
        return 1;
    }

    for (i = 0; i < dynsym.sh_size / dynsym.sh_entsize; i++)
    {
        fseek(file, dynsym.sh_offset + dynsym.sh_entsize * i, SEEK_SET);
        fread(&sym, sizeof(Elf64_Sym), 1, file);
        fseek(file, strtab.sh_offset + sym.st_name, SEEK_SET);
        fread(sname, 1, 32, file);
        printf("%d\t%ld\t%u\t%u\t%hd\t%s\n", i,
               sym.st_size,
               ELF64_ST_TYPE(sym.st_info),
               ELF64_ST_BIND(sym.st_info),
               sym.st_shndx, sname);
    }

    fclose(file);
    return 0;
}
