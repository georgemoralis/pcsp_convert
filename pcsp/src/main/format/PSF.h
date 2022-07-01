/*
 * 01/07/2022 - Ported from jpscp 74d7b02e(18/10/2008)
 *
 */
#pragma once
class PsfValue {
    friend class PSF;

   public:
    PsfValue();
    ~PsfValue();

    u32 GetSize() const;

    const u8 *GetData() const;
    const char *GetString() const;
    const u32 *GetNumber() const;

   private:
    std::vector<u8> data;
    u32 number;
    u8 type;
};

class PSF {
   public:
    PSF();
    PSF(u32 p_offset_param_sfo);
    ~PSF();

    void read(std::ifstream &f);

    const PsfValue *get(const std::string &key) const;
    bool getNumeric(const std::string &key, u32 &num) const;
    bool getString(const std::string &key, std::string &str) const;

    // kxploit patcher tool adds "\nKXPloit Boot by PSP-DEV Team"
    bool getPrintableString(const std::string &key, std::string &str) const;

   private:
    static const u32 psfident = 0x46535000;
    std::map<std::string, PsfValue> psfMap;
    u32 p_offset_param_sfo;
};
