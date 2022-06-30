/*
 * 30/06/2022 - Ported from jpscp 2a9c39b0(16/09/2008)
 *
 */
#pragma once
class Elf32Relocate {
   public:
    Elf32Relocate();
    Elf32Relocate(std::ifstream& f);
    ~Elf32Relocate();
    void read(std::ifstream& f);
    static const size_t sizeOf();
    std::string toString() const;

    u32 getOffset() const;
    u32 getInfo() const;

    void setOffset(u32 offset);
    void setInfo(u32 info);

   private:
    struct {
        u32 r_offset;
        u32 r_info;
    } data;
};
