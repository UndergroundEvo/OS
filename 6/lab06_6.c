#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <shared_library>\n", argv[0]);
        return 1;
    }

    const char* elfFile = argv[1];
    Elf64_Ehdr header;
    Elf64_Shdr sheader;
    Elf64_Shdr dynsym;
    Elf64_Shdr dynstr;
    Elf64_Sym sym;
    char sname[32];
    int i;
    FILE* file = fopen(elfFile, "rb");

    if (!file) {
        perror("Unable to open file");
        return 1;
    }

    fread(&header, sizeof(header), 1, file);
    fseek(file, header.e_shoff, SEEK_SET);
    fread(&sheader, sizeof(sheader), 1, file);
    for (i = 0; i < header.e_shnum; i++) {
        fseek(file, header.e_shoff + header.e_shentsize * i, SEEK_SET);
        fread(&sheader, sizeof(sheader), 1, file);
        if (sheader.sh_type == SHT_DYNSYM) {
            dynsym = sheader;
        }
        if (sheader.sh_type == SHT_STRTAB && i == dynsym.sh_link) {
            dynstr = sheader;
        }
    }

    if (dynsym.sh_size == 0 || dynstr.sh_size == 0) {
        fprintf(stderr, "Dynamic symbol or string table not found\n");
        fclose(file);
        return 1;
    }

    printf("Exported function names in %s:\n", elfFile);

    for (i = 0; i < dynsym.sh_size / dynsym.sh_entsize; i++) {
        fseek(file, dynsym.sh_offset + dynsym.sh_entsize * i, SEEK_SET);
        fread(&sym, sizeof(Elf64_Sym), 1, file);
        fseek(file, dynstr.sh_offset + sym.st_name, SEEK_SET);
        fread(sname, 1, 32, file);

        // Check if the symbol is a function (STT_FUNC)
        if (ELF64_ST_TYPE(sym.st_info) == STT_FUNC) {
            printf("%s\n", sname);
        }
    }

    fclose(file);
    return 0;
}
