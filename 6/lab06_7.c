#include <stdio.h>
#include <stdlib.h>
#include <libelf.h>
#include <gelf.h>

//void print_sections(Elf* elf) {
//    Elf_Scn* scn = NULL;
//    GElf_Shdr shdr;
//    Elf_Scn* shstrtab_scn = NULL;
//    GElf_Shdr shstrtab_shdr;
//    char* shstrtab;
//    int section_count = 0;
//
//    // Находим раздел .shstrtab для получения имен разделов
//    shstrtab_scn = elf_getscn(elf, elf_getshnum(elf) - 1);
//    gelf_getshdr(shstrtab_scn, &shstrtab_shdr);
//    shstrtab = (char*)elf_getdata(shstrtab_scn, NULL)->d_buf;
//
//    printf("Section Header Table:\n");
//    printf("%-4s %-25s %-18s %-12s %-8s\n", "Num", "Name", "Type", "Address", "Offset");
//
//    while ((scn = elf_nextscn(elf, scn)) != NULL) {
//        gelf_getshdr(scn, &shdr);
//        printf("%-4d %-25s 0x%08lx %-18s 0x%08lx\n",
//            section_count, shstrtab + shdr.sh_name,
//            shdr.sh_type, "0x", shdr.sh_addr, shdr.sh_offset);
//        section_count++;
//    }
//    printf("Total Sections: %d\n", section_count);
//}

//void print_elf_headers(Elf* elf) {
//    Elf_Scn* scn;
//    GElf_Ehdr ehdr;
//    GElf_Phdr phdr;
//
//    if (gelf_getehdr(elf, &ehdr) == NULL) {
//        fprintf(stderr, "gelf_getehdr() failed: %s\n", elf_errmsg(-1));
//        return;
//    }
//
//    printf("ELF Header:\n");
//    printf("  Class:                             %d-bit\n", ehdr.e_ident[EI_CLASS] == ELFCLASS32 ? 32 : 64);
//    printf("  Data:                              %s\n", ehdr.e_ident[EI_DATA] == ELFDATA2LSB ? "2's complement, little-endian" : "2's complement, big-endian");
//    printf("  OS/ABI:                            %d\n", ehdr.e_ident[EI_OSABI]);
//    printf("  Type:                              %d\n", ehdr.e_type);
//    printf("  Machine:                           %d\n", ehdr.e_machine);
//    printf("  Version:                           %d\n", ehdr.e_version);
//    printf("  Entry point address:               0x%lx\n", (unsigned long)ehdr.e_entry);
//
//    printf("\nProgram Headers:\n");
//    printf("  Type                Offset             VirtAddr           PhysAddr           FileSiz            MemSiz             Flags  Align\n");
//
//    scn = NULL;
//    while ((scn = elf_nextscn(elf, scn)) != NULL) {
//        gelf_getphdr(elf ,scn, &phdr);
//        printf("  %-20s 0x%016lx 0x%016lx 0x%016lx 0x%016lx 0x%016lx 0x%lx %ld\n",
//            (phdr.p_type == PT_LOAD ? "LOAD" : "OTHER"),
//            (unsigned long)phdr.p_offset, (unsigned long)phdr.p_vaddr,
//            (unsigned long)phdr.p_paddr, (unsigned long)phdr.p_filesz,
//            (unsigned long)phdr.p_memsz, (unsigned long)phdr.p_flags, (long)phdr.p_align);
//    }
//}

//void print_section_headers(Elf* elf) {
//    Elf_Scn* scn = NULL;
//    GElf_Shdr shdr;
//
//    printf("Section Headers:\n");
//    printf("%-4s %-20s %-20s %-10s\n", "Num", "Name", "Type", "Address");
//
//    while ((scn = elf_nextscn(elf, scn)) != NULL) {
//        gelf_getshdr(scn, &shdr);
//        printf("%-4ld %-20s %-20s 0x%016lx\n", (long)elf_ndxscn(scn), elf_strptr(elf, 0, shdr.sh_name),
//            shdr.sh_type == SHT_PROGBITS ? "PROGBITS" : "Other", (unsigned long)shdr.sh_addr);
//    }
//}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <elf_file>\n", argv[0]);
        return 1;
    }

    const char* elf_filename = argv[1];
    Elf* elf;
    Elf_Scn* scn;
    GElf_Shdr shdr;
    Elf_Data* data;
    int symbol_count = 0;

    if (elf_version(EV_CURRENT) == EV_NONE) {
        fprintf(stderr, "ELF library initialization failed: %s\n", elf_errmsg(-1));
        return 1;
    }

    elf = elf_begin(fileno(fopen(elf_filename, "r")), ELF_C_READ, NULL);
    if (!elf) {
        fprintf(stderr, "elf_begin() failed: %s\n", elf_errmsg(-1));
        return 1;
    }

    while ((scn = elf_nextscn(elf, scn)) != NULL) {
        gelf_getshdr(scn, &shdr);
        if (shdr.sh_type == SHT_DYNSYM) {
            data = elf_getdata(scn, NULL);
            Elf64_Sym* symbol_table = (Elf64_Sym*)data->d_buf;
            int symbol_entries = data->d_size / sizeof(Elf64_Sym);

            printf("Symbol Table (.dynsym):\n");
            printf("%-4s %-25s %-15s %-5s\n", "Num", "Name", "Value", "Type");

            for (int i = 0; i < symbol_entries; i++) {
                if ((symbol_table[i].st_name != 0)&&(symbol_table[i].st_value != 0)) {
                    char* symbol_name = elf_strptr(elf, shdr.sh_link, symbol_table[i].st_name);
                    printf("%-4d %-25s 0x%016lx %u\n", i, symbol_name, (unsigned long)symbol_table[i].st_value, ELF64_ST_TYPE(symbol_table[i].st_info));
                    symbol_count++;
                }
            }
            printf("Total Symbols: %d\n", symbol_count);
        }
    }

    elf_end(elf);
    return 0;
}
