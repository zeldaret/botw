#pragma once

#include <prim/seadSafeString.h>

namespace ksys::res {

class EntryFactoryBase;

void registerEntryFactory(EntryFactoryBase* factory, const sead::SafeString& name);

// In release builds, the only thing this function does is return 1.
// TODO: figure out what this is used for. Stubbed log function?
bool stubbedLogFunction();

// In release builds, the only thing this function does is return 0.
// TODO: figure out what this is used for. Stubbed log function?
bool returnFalse();

// In release builds, the only thing this function does is return 0.
// TODO: figure out what this is used for. Stubbed log function?
bool returnFalse2(const sead::SafeString&);

s32 getDefaultAlignment();

}  // namespace ksys::res
