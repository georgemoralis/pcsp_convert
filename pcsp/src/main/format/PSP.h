/*
 * 01/07/2022 - Ported from jpscp 2a9c39b0(16/09/2008)
 *
 */
#pragma once
class PSP {
   public:
    PSP();
    PSP(std::ifstream &f);
    ~PSP();

    bool isValid() const;

   private:
    struct {
        u32 e_magic;
    } data;
};
