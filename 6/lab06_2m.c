#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void find_sections_names(FILE* file, Elf64_Ehdr header) {
    Elf64_Shdr shstrtab;
    fseek(file, header.e_shoff + (header.e_shstrndx * header.e_shentsize), SEEK_SET);
    fread(&shstrtab, sizeof(shstrtab), 1, file);

    char shstrtab_data[shstrtab.sh_size];
    fseek(file, shstrtab.sh_offset, SEEK_SET);
    fread(shstrtab_data, 1, shstrtab.sh_size, file);

    printf("Section Names:\n");
    for (int i = 0; i < header.e_shnum; i++) {
        Elf64_Shdr sheader;
        fseek(file, header.e_shoff + (i * header.e_shentsize), SEEK_SET);
        fread(&sheader, sizeof(sheader), 1, file);
        char* section_name = shstrtab_data + sheader.sh_name;
        printf("%d: %s\n", i, section_name);
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <ELF file>\n", argv[0]);
        return 1;
    }

    const char* elfFile = argv[1];
    Elf64_Ehdr header;
    FILE* file = fopen(elfFile, "rb");

    if (!file) {
        perror("Error opening file");
        return 1;
    }

    fread(&header, sizeof(header), 1, file);
    fseek(file, header.e_shoff, SEEK_SET);

    // Find .symtab and .strtab sections
    Elf64_Shdr symtab;
    Elf64_Shdr strtab;

    for (int i = 0; i < header.e_shnum; i++) {
        Elf64_Shdr sheader;
        fseek(file, header.e_shoff + (i * header.e_shentsize), SEEK_SET);
        fread(&sheader, sizeof(sheader), 1, file);

        if (strcmp(".symtab", (char*)&header + sheader.sh_name) == 0) {
            symtab = sheader;
        }
        if (strcmp(".strtab", (char*)&header + sheader.sh_name) == 0) {
            strtab = sheader;
        }
    }

    if (symtab.sh_size == 0 || strtab.sh_size == 0) {
        fprintf(stderr, "Symbol or string table not found.\n");
        fclose(file);
        return 1;
    }

    // Read and print exported function names
    char* strtab_data = (char*)malloc(strtab.sh_size);
    fseek(file, strtab.sh_offset, SEEK_SET);
    fread(strtab_data, 1, strtab.sh_size, file);

    printf("Exported Function Names:\n");

    for (int i = 0; i < symtab.sh_size / symtab.sh_entsize; i++) {
        Elf64_Sym sym;
        fseek(file, symtab.sh_offset + symtab.sh_entsize * i, SEEK_SET);
        fread(&sym, sizeof(Elf64_Sym), 1, file);
        char* sym_name = strtab_data + sym.st_name;
        if (ELF64_ST_BIND(sym.st_info) == STB_GLOBAL && sym.st_shndx != SHN_UNDEF) {
            printf("%s\n", sym_name);
        }
    }

    free(strtab_data);
    find_sections_names(file, header);
    fclose(file);

    return 0;
}
