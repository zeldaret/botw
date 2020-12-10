#pragma once

#include <basis/seadTypes.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiParam.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {
class AIProgram;
}

namespace ksys::act {

class Actor;

namespace ai {

enum class ActionType {
    AI = 0,
    Action = 1,
};

enum class RootAiFlag : u16;

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

    bool init(sead::Heap* heap, bool skip_loading_map_or_tree_params);
    void enter(InlineParamPack* params, const sead::SafeString& context);
    bool takeOver(ActionBase* src, const sead::SafeString& context);
    void leave();
    bool oneShot(InlineParamPack* params);

    const char* getClassName() const;
    const char* getName() const;

    virtual bool isFailed() const { return mFlags.isOn(Flag::Failed); }
    virtual bool isFinished() const { return mFlags.isOn(Flag::Finished); }
    virtual bool isFlag4Set() const { return mFlags.isOn(Flag::_4); }

    virtual bool m7() { return false; }
    virtual bool m8() { return false; }
    virtual void m9() {}
    virtual bool oneShot_() { return true; }
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
    virtual s32 getNumChildren() const { return 0; }
    virtual bool initChildren(const AIDefSet& set, sead::Heap* heap) { return true; }
    virtual ActionBase* getCurrentChild() const { return nullptr; }
    virtual ActionType getType() const = 0;
    virtual bool reenter(ActionBase* other, const sead::SafeString& context) {
        return reenter_(other, false);
    }
    virtual void postLeave() {}
    virtual ActionBase* getChild(s32 idx) const { return nullptr; }

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

    bool isRootAiParamINot5() const;
    bool isActorDeletedOrDeleting() const;
    bool isActorGoingBackToRootAi() const;

    void copyParams(InlineParamPack* dest, bool x) const;

    void setFinished();
    void setFailed();
    void setRootAiFlagBit(int bit);
    void setRootAiFlag(RootAiFlag flag) { setRootAiFlagBit(sead::log2(u32(flag))); }

    void resetFlags() {
        mFlags.reset(Flag::Failed);
        mFlags.reset(Flag::Finished);
        mFlags.reset(Flag::_4);
    }

    res::AIProgram* getAIProg() const;

    template <typename T>
    void getParamStatic(ParamRef<T>* value, const sead::SafeString& key);

    Actor* mActor;
    ParamPack mParams;
    s16 mDefinitionIdx;
    s8 mRootIdx;
    sead::TypedBitFlag<Flag> mFlags;

private:
    void initFlags(res::AIProgram* aiprog, s32 def_idx, ActionType type);
    void updateBehaviorsOnEnter();
    void updateBehaviorsOnLeave();
};
KSYS_CHECK_SIZE_NX150(ActionBase, 0x20);

}  // namespace ai

}  // namespace ksys::act
