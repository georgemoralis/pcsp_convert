/*
 * 30/06/2022 - Ported from jpscp 2a9c39b0(16/09/2008)
 *
 */
#pragma once
class DeferredStub {
   public:
    DeferredStub();
    DeferredStub(const std::string &moduleName, u32 importAddress, u32 nid);
    ~DeferredStub();

    std::string getModuleName() const;
    u32 getImportAddress() const;
    u32 getNid() const;

   private:
    std::string moduleName;
    u32 importAddress;
    u32 nid;
};
