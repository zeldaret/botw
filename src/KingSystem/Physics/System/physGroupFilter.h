#pragma once

#include <Havok/Physics2012/Collide/Filter/Group/hkpGroupFilter.h>
#include <basis/seadTypes.h>
#include <container/seadOffsetList.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Physics/System/physDefines.h"

namespace ksys::phys {

class GroupFilter : public hkpGroupFilter {
    SEAD_RTTI_BASE(GroupFilter)
public:
    GroupFilter(ContactLayerType type, ContactLayer::ValueType layer_first,
                ContactLayer::ValueType layer_last);
    ~GroupFilter() override;

protected:
    virtual bool m2() { return true; }
    virtual void m3() = 0;
    virtual void m4() = 0;
    virtual void m5() = 0;
    virtual void m6() = 0;
    virtual void m7() = 0;
    virtual void m8() = 0;
    virtual void m9() {}
    virtual void m10() = 0;
    virtual void m11() = 0;
    virtual void m12() = 0;
    virtual void m13();

    u32 mIdxLayerFirst{};
    u32 mIdxLayerLast{};
    ContactLayerType mLayerType{};
    u8 _11c{};
    // FIXME: types
    sead::OffsetList<void*> _120;
    sead::OffsetList<void*> _138;
    sead::CriticalSection mCS;
    sead::OffsetList<void*> _190;
};

}  // namespace ksys::phys
