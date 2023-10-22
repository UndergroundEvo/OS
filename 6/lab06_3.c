#include <stdio.h>
#include <fcntl.h>
#include <libelf.h>
#include <gelf.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <ELF-file>\n", argv[0]);
        return 1;
    }

    // Инициализируем библиотеку libelf
    if (elf_version(EV_CURRENT) == EV_NONE) {
        fprintf(stderr, "libelf initialization failed: %s\n", elf_errmsg(-1));
        return 1;
    }

    // Открываем ELF-файл
    int fd = open(argv[1], O_RDONLY, 0);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // Инициализируем структуру ELF
    Elf* elf = elf_begin(fd, ELF_C_READ, NULL);
    if (!elf) {
        fprintf(stderr, "elf_begin() failed: %s\n", elf_errmsg(-1));
        pclose(fd);
        return 1;
    }

    // Получаем секцию .dynsym
    Elf_Scn* scn = NULL;
    GElf_Shdr shdr;
    while ((scn = elf_nextscn(elf, scn)) != NULL) {
        gelf_getshdr(scn, &shdr);
        if (shdr.sh_type == SHT_DYNSYM) {
            break;
        }
    }

    if (!scn) {
        fprintf(stderr, ".dynsym section not found\n");
        elf_end(elf);
        pclose(fd);
        return 1;
    }

    Elf_Data* data = elf_getdata(scn, NULL);
    if (!data) {
        fprintf(stderr, "elf_getdata() failed: %s\n", elf_errmsg(-1));
        elf_end(elf);
        pclose(fd);
        return 1;
    }

    // Получаем секцию .strtab для имен символов
    scn = NULL;
    while ((scn = elf_nextscn(elf, scn)) != NULL) {
        gelf_getshdr(scn, &shdr);
        if (shdr.sh_type == SHT_STRTAB && strcmp(elf_strptr(elf, shdr.sh_link, 0), ".strtab") == 0) {
            break;
        }
    }

    if (!scn) {
        fprintf(stderr, ".strtab section not found\n");
        elf_end(elf);
        pclose(fd);
        return 1;
    }

    Elf_Data* strtab_data = elf_getdata(scn, NULL);
    if (!strtab_data) {
        fprintf(stderr, "elf_getdata() for .strtab failed: %s\n", elf_errmsg(-1));
        elf_end(elf);
        pclose(fd);
        return 1;
    }

    // Извлекаем имена экспортируемых функций
    GElf_Sym sym;
    size_t num_syms = shdr.sh_size / shdr.sh_entsize;
    for (size_t i = 0; i < num_syms; i++) {
        gelf_getsym(data, i, &sym);
        if (ELF32_ST_TYPE(sym.st_info) == STT_FUNC) {
            printf("Function Name: %s\n", elf_strptr(elf, shdr.sh_link, sym.st_name));
        }
    }

    // Освобождаем ресурсы
    elf_end(elf);
    pclose(fd);

    return 0;
}
