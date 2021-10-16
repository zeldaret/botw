#pragma once

#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

class UserTag {
    SEAD_RTTI_BASE(UserTag)
public:
    UserTag() = default;

    // FIXME: names and types
    virtual void m2(void* a);
    // a and b are probably physics bodies?
    virtual void m3(void* a, void* b, float c);
    virtual void m4();
    virtual void m5();
    virtual const sead::SafeString& getName() const { return sead::SafeString::cEmptyString; }
    virtual void m7();
    virtual const sead::SafeString& getName2() const { return sead::SafeString::cEmptyString; }
    virtual ~UserTag() = default;
};
KSYS_CHECK_SIZE_NX150(UserTag, 0x8);

}  // namespace ksys::phys
