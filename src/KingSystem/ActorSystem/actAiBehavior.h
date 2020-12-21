#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
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

    bool init(sead::Heap* heap);

    virtual bool hasPreDeleteCb() { return false; }
    virtual bool hasUpdateForPreDeleteCb() { return false; }
    virtual bool m6() { return true; }
    virtual void m7() {}
    virtual void m8() {}
    virtual void m9() {}
    virtual void m10() {}
    virtual void m11() {}
    virtual bool updateForPreDelete() { return true; }
    virtual void onPreDelete() {}

protected:
    Actor* mActor{};
    u16 mDefIdx{};
    u8 _12{};
    u8 _13{};
    void* _18{};
    void* _20{};
};
KSYS_CHECK_SIZE_NX150(Behavior, 0x28);

struct BehaviorFactory {
    using CreateFn = Behavior* (*)(const Behavior::InitArg& arg, sead::Heap* heap);
    u32 hash;
    CreateFn create_fn;
};

class Behaviors {
public:
    Behaviors();
    ~Behaviors();

    void finalize();

    bool init(Actor* actor, sead::Heap* heap);
    bool updateForPreDelete() const;
    void onPreDelete() const;

    const sead::Buffer<Behavior*>& getClasses() const { return mClasses; }

    static BehaviorFactory* getFactory(const sead::SafeString& name);
    static void setFactories(int count, BehaviorFactory* factories);

private:
    static inline sead::Buffer<BehaviorFactory> sFactories;
    sead::Buffer<Behavior*> mClasses;
    // Non-owning buffer.
    sead::Buffer<Behavior*> mOnPreDeleteCbs;
    // Non-owning buffer.
    sead::Buffer<Behavior*> mUpdateForPreDeleteCbs;
};

}  // namespace ksys::act::ai
