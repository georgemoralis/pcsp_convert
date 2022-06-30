/*
 * 30/06/2022 - Ported from jpscp 2a9c39b0(16/09/2008)
 *
 */
#pragma once
class Elf32Header 
{
   public:
    Elf32Header();
    Elf32Header(std::ifstream &f);
    ~Elf32Header();

    void read(std::ifstream &f);

    bool isValid() const;
    bool isMIPSExecutable() const;
    bool isPRXDetected() const;
    bool requiresRelocation() const;

    std::string toString() const;

    
	u32 getE_magic() const;
    u8 getE_class() const;
    u8 getE_data() const;
    u8 getE_idver() const;
    std::vector<u8> getE_pad() const;
    u16 getE_type() const;
    u16 getE_machine() const;
    u32 getE_version() const;
    u32 getE_entry() const;
    u32 getE_phoff() const;
    u32 getE_shoff() const;
    u32 getE_flags() const;
    u16 getE_ehsize() const;
    u16 getE_phentsize() const;
    u16 getE_phnum() const;
    u16 getE_shentsize();
    u16 getE_shnum() const;
    u16 getE_shstrndx() const;

   private:
    struct {
        u32 e_magic;
        u8 e_class;
        u8 e_data;
        u8 e_idver;
        u8 e_pad[9];
        u16 e_type;
        u16 e_machine;
        u32 e_version;
        u32 e_entry;
        u32 e_phoff;
        u32 e_shoff;
        u32 e_flags;
        u16 e_ehsize;
        u16 e_phentsize;
        u16 e_phnum;
        u16 e_shentsize;
        u16 e_shnum;
        u16 e_shstrndx;
    } data;
};
