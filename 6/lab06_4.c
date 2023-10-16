#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <library.so>\n", argv[0]);
        return 1;
    }

    const char* elfFile = argv[1];
    Elf64_Ehdr header;
    FILE* file = fopen(elfFile, "rb");

    if (file == NULL)
    {
        perror("Failed to open the ELF file");
        return 1;
    }

    fread(&header, sizeof(header), 1, file);

    // Find the section header string table
    Elf64_Shdr shstrtab;
    fseek(file, header.e_shoff + header.e_shstrndx * header.e_shentsize, SEEK_SET);
    fread(&shstrtab, sizeof(shstrtab), 1, file);

    // Iterate through section headers to find the .symtab section
    for (int i = 0; i < header.e_shnum; i++)
    {
        fseek(file, header.e_shoff + i * header.e_shentsize, SEEK_SET);
        Elf64_Shdr sheader;
        fread(&sheader, sizeof(sheader), 1, file);

        // Get the section name from the section header string table
        char sname[32];
        fseek(file, shstrtab.sh_offset + sheader.sh_name, SEEK_SET);
        fread(sname, 1, 32, file);

        if (strcmp(sname, ".symtab") == 0)
        {
            // We found the .symtab section, now read and print symbol names
            fseek(file, sheader.sh_offset, SEEK_SET);
            int numSymbols = sheader.sh_size / sheader.sh_entsize;
            Elf64_Sym sym;
            for (int j = 0; j < numSymbols; j++)
            {
                fread(&sym, sizeof(Elf64_Sym), 1, file);
                if (ELF64_ST_BIND(sym.st_info) == STB_GLOBAL)
                {
                    // Symbol is global, print its name
                    fseek(file, shstrtab.sh_offset + sym.st_name, SEEK_SET);
                    fread(sname, 1, 32, file);
                    printf("%s\n", sname);
                }
            }
            break;
        }
    }

    fclose(file);
    return 0;
}
