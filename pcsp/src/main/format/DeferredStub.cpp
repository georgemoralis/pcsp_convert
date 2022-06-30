/*
 * 30/06/2022 - Ported from jpscp 2a9c39b0(16/09/2008)
 *
 */
#include "..\PCSPCommon.h"
#include "DeferredStub.h"

DeferredStub::DeferredStub() {}

DeferredStub::DeferredStub(const std::string &moduleName, u32 importAddress, u32 nid)
    : moduleName(moduleName), importAddress(importAddress), nid(nid) {}

DeferredStub::~DeferredStub() {}

std::string DeferredStub::getModuleName() const { return moduleName; }

u32 DeferredStub::getImportAddress() const { return importAddress; }

u32 DeferredStub::getNid() const { return nid; }
