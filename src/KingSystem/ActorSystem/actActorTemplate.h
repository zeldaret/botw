#pragma once

#include <heap/seadDisposer.h>
#include "KingSystem/Utils/Types.h"

namespace al {
class ByamlIter;
}

namespace ksys::act {

class ActorTemplate {
    SEAD_SINGLETON_DISPOSER(ActorTemplate)
    ActorTemplate() = default;
    virtual ~ActorTemplate();

public:
    void init(const u8* data, sead::Heap* heap);

    bool getActorClass(const char** actor_class, const char* profile) const;
    s32 getNumAttPriorityEntries(const char* profile) const;
    bool getAttPriority(const char** priority, const char* profile, s32 idx) const;
    bool getAttDefPriority(const char** priority, const char* profile) const;
    s32 getNumProfiles() const;
    const char* getProfileName(s32 idx) const;

    al::ByamlIter* getRootIter() const { return mIter; }

private:
    al::ByamlIter* mIter = nullptr;
};
KSYS_CHECK_SIZE_NX150(ActorTemplate, 0x30);

}  // namespace ksys::act
