#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiParam.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class Actor;

namespace ai {

/// Base class for actions and AIs, which can be seen as looping actions.
class ActionBase {
    SEAD_RTTI_BASE(ActionBase)
public:
    struct InitArg {
        Actor* actor;
        /// The index of the query definition in the actor's AI program.
        s32 def_idx;
        s32 root_idx;
    };
    KSYS_CHECK_SIZE_NX150(InitArg, 0x10);

    explicit ActionBase(const InitArg& arg);
    virtual ~ActionBase() = default;

    const char* getName() const;
    bool init(sead::Heap* heap, bool load_map_or_tree_params);

    virtual bool isFinished() const;
    virtual bool isFailed() const;
    virtual bool isFlag4Set() const;

    virtual bool m7() { return false; }
    virtual bool m8() { return false; }
    virtual void m9() {}
    virtual bool oneShot() { return true; }
    virtual bool init_(sead::Heap* heap) { return true; }
    virtual void enter_(InlineParamPack* params) {}
    virtual bool reenter_(ActionBase* other, bool x);
    virtual void leave_() {}
    virtual void loadParams_() {}
    virtual bool m16() { return false; }
    virtual bool m17() { return false; }
    virtual bool m18() { return true; }
    virtual void m19() {}
    virtual void calc() {}
    virtual void getCurrentName(sead::BufferedSafeString* name, ActionBase* parent) const;
    virtual void* m22() { return nullptr; }
    virtual void getParams(ParamNameTypePairs* pairs, bool update_use_count) const;
    virtual s32 m24() { return 0; }
    virtual bool m25() { return true; }
    virtual ActionBase* getCurrentChild() const { return nullptr; }
    virtual bool isAction() const = 0;
    virtual bool reenter(ActionBase* other) { return reenter_(other, false); }
    virtual void postLeave() {}
    virtual ActionBase* getAction(s32 idx) const { return nullptr; }

protected:
    enum class Flag : u8 {
        Finished = 1,
        Failed = 2,
        _4 = 4,
        TriggerAction = 8,
        DynamicParamChild = 0x10,
        _20 = 0x20,
        _40 = 0x40,
        _80 = 0x80,
    };

    void setFinished();
    void setFailed();

    template <typename T>
    void getParamStatic(ParamRef<T>* value, const sead::SafeString& key);

    Actor* mActor;
    ParamPack mParams;
    u16 mDefinitionIdx;
    u8 mRootIdx;
    sead::TypedBitFlag<Flag> mFlags;
    u16 mClassIdx;
    u16 mPrevClassIdx;
};
KSYS_CHECK_SIZE_NX150(ActionBase, 0x20);

}  // namespace ai

}  // namespace ksys::act
