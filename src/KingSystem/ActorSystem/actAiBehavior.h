#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}

namespace ksys::act::ai {

class Behavior {
    SEAD_RTTI_BASE(Behavior)

public:
    struct InitArg {
        Actor* actor;
        /// The index of the behavior definition in the actor's AI program.
        s32 def_idx;
    };
    KSYS_CHECK_SIZE_NX150(InitArg, 0x10);

    explicit Behavior(const InitArg& arg);
    virtual ~Behavior() = default;

    virtual bool m4() { return false; }
    virtual bool m5() { return false; }
    virtual bool m6() { return true; }
    virtual void m7() {}
    virtual void m8() {}
    virtual void m9() {}
    virtual void m10() {}
    virtual void m11() {}
    virtual bool m12() { return true; }
    virtual void m13() {}

protected:
    Actor* mActor{};
    u16 mDefIdx{};
    u8 _12{};
    u8 _13{};
    void* _18{};
    void* _20{};
};
KSYS_CHECK_SIZE_NX150(Behavior, 0x28);

}  // namespace ksys::act::ai
