#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>

namespace ksys::phys {

class RigidBody;

class MemSystem {
    SEAD_SINGLETON_DISPOSER(MemSystem)
public:
    struct Struct160 {
        void sub_7100FA6C8C(bool, RigidBody*);
    };

    u8 _20[0x140];
    Struct160* _160;
};

}  // namespace ksys::phys
