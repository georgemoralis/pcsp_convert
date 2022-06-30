/*
 * 30/06/2022 - Ported from jpscp 2a9c39b0(16/09/2008)
 *
 */
#pragma once
class PSPModuleInfo {
   public:
    PSPModuleInfo();
    PSPModuleInfo(std::ifstream &f);
    ~PSPModuleInfo();

    void read(std::ifstream &f);

    u16 getM_attr() const;
    u16 getM_version() const;
    const char *getM_name() const;
    u32 getM_gp() const;
    u32 getM_exports() const;
    u32 getM_exp_end() const;
    u32 getM_imports() const;
    u32 getM_imp_end() const;
    std::string getM_namez() const;

   private:
    std::string m_namez;  // string version of m_name
    struct {
        u16 m_attr;
        u16 m_version;
        char m_name[28];
        u32 m_gp;
        u32 m_exports;  // .lib.ent
        u32 m_exp_end;
        u32 m_imports;  // .lib.stub
        u32 m_imp_end;
    } data;
};
