#pragma once

#include <container/seadPtrArray.h>
#include <hostio/seadHostIONode.h>
#include <thread/seadCriticalSection.h>

namespace ksys::phys {

class StaticCompound;
class SystemGroupHandler;

/// Provides convenient access to all loaded StaticCompounds.
class StaticCompoundMgr : public sead::hostio::Node {
public:
    StaticCompoundMgr();
    virtual ~StaticCompoundMgr();

    bool init();

    // 0x0000007100fcb554
    void addStaticCompound(StaticCompound* sc);
    // 0x0000007100fcb5e0
    void removeStaticCompound(StaticCompound* sc);

    SystemGroupHandler* getGroupHandler() const { return mGroupHandler; }

    // TODO: more functions

private:
    sead::FixedPtrArray<StaticCompound, 0x40> mStaticCompounds;
    sead::CriticalSection mCS;
    SystemGroupHandler* mGroupHandler{};
};

}  // namespace ksys::phys
