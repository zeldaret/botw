#pragma once

#include <basis/seadTypes.h>
#include <math/seadMathCalcCommon.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/ActorSystem/actAiParam.h"
#include "KingSystem/Utils/Types.h"

namespace ksys {
struct AIDefSet;
class Message;
struct MesTransceiverId;
}  // namespace ksys

namespace ksys::res {
class AIProgram;
class GParamList;
}  // namespace ksys::res

namespace ksys::act {

class Actor;
class BaseProcHandle;

namespace ai {

class Action;

enum class ActionType {
    AI = 0,
    Action = 1,
};

enum class RootAiFlag : u16;
enum class RootAiFlag2 : u16;

sead::SafeString* getDefaultString();
s32* getDefaultInt();
f32* getDefaultFloat();
sead::Vector3f* getDefaultVec3();
bool* getDefaultBool();
BaseProcLink* getDefaultBaseProcLink();
MesTransceiverId* getDefaultMesTransceiverId();
BaseProcHandle** getDefaultBaseProcHandle();
Rail** getDefaultRail();
sead::FixedSafeString<32>* getDefaultString32();

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

    Action* getCurrentAction();
    bool handleMessage(Message* message);
    // TODO: rename
    bool handleMessage2(Message* message);

    Actor* getActor() const { return mActor; }
    s32 getDefinitionIdx() const { return mDefinitionIdx; }
    const char* getClassName() const;
    const char* getName() const;

    virtual bool isFailed() const { return mFlags.isOn(Flag::Failed); }
    virtual bool isFinished() const { return mFlags.isOn(Flag::Finished); }
    virtual bool isFlag4Set() const { return mFlags.isOn(Flag::_4); }

    virtual bool hasPreDeleteCb() { return false; }
    virtual bool hasUpdateForPreDeleteCb() { return false; }

    virtual void m9() {}

protected:
    virtual bool oneShot_() { return true; }
    virtual bool init_(sead::Heap* heap) { return true; }
    virtual void enter_(InlineParamPack* params) {}
    virtual bool reenter_(ActionBase* other, bool x);
    virtual void leave_() {}
    virtual void loadParams_() {}
    virtual bool handleMessage_(Message* message) { return false; }
    // TODO: rename
    virtual bool handleMessage2_(Message* message) { return false; }

public:
    virtual bool updateForPreDelete() { return true; }
    virtual void onPreDelete() {}
    virtual void calc() {}
    virtual void getCurrentName(sead::BufferedSafeString* name, ActionBase* last) const;

    virtual ActionBase* changeChildLater(const sead::SafeString& name) { return nullptr; }
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

    void setRootAiFlagBit(int bit) const;
    void setRootAiFlag(RootAiFlag flag) const { setRootAiFlagBit(sead::log2(u32(flag))); }

    void resetRootAiFlagBit(int bit) const;
    void resetRootAiFlag(RootAiFlag flag) const { resetRootAiFlagBit(sead::log2(u32(flag))); }

    bool testRootAiFlag2Bit(int bit) const;
    bool testRootAiFlag2(RootAiFlag2 flag) const {
        return testRootAiFlag2Bit(sead::log2(u32(flag)));
    }

    void resetFlags() {
        mFlags.reset(Flag::Failed);
        mFlags.reset(Flag::Finished);
        mFlags.reset(Flag::_4);
    }

    res::AIProgram* getAIProg() const;
    auto& getDef() const;
    res::GParamList* getGParamList() const;

    template <typename T>
    bool getStaticParam(T* value, const sead::SafeString& key) const;

    void logMissingParam(const sead::SafeString& param) const;

    template <typename T>
    bool getMapUnitParam(T* value, const sead::SafeString& key) const;

    template <typename T>
    bool getAITreeVariable(T** value, const sead::SafeString& key) const;

    template <typename T>
    bool getDynamicParamImpl(T* value, const sead::SafeString& key,
                             bool (ParamPack::*getter)(T* value, const sead::SafeString& key) const,
                             T* default_value) const {
        auto* action = this;
        while (action && action->mFlags.isOff(Flag::_80)) {
            if ((action->mParams.*getter)(value, key))
                return true;
            if (action->mFlags.isOff(Flag::DynamicParamChild))
                goto fail;
            action = action->getCurrentChild();
            if (!action)
                goto fail;
        }

        for (s32 i = 0, n = action->getNumChildren(); i < n; ++i) {
            auto* child = action->getChild(i);
            if (child->getDynamicParamImpl<T>(value, key, getter, default_value))
                return true;
        }

    fail:
        logMissingParam(key);
        *value = *default_value;
        return false;
    }

    template <AIDefParamType Type, typename T>
    bool getDynamicParamPtrImpl(T** value, const sead::SafeString& key, T* default_value) const {
        return getDynamicParamImpl(value, key, &ParamPack::getPtrGeneric<T, Type>, &default_value);
    }

    bool getDynamicParam(sead::SafeString* value, const sead::SafeString& key) const {
        return getDynamicParamImpl(value, key, &ParamPack::getString, getDefaultString());
    }

    bool getDynamicParam(int** value, const sead::SafeString& key) const {
        return getDynamicParamPtrImpl<AIDefParamType::Int>(value, key, getDefaultInt());
    }

    bool getDynamicParam(float** value, const sead::SafeString& key) const {
        return getDynamicParamPtrImpl<AIDefParamType::Float>(value, key, getDefaultFloat());
    }

    bool getDynamicParam(sead::Vector3f** value, const sead::SafeString& key) const {
        return getDynamicParamPtrImpl<AIDefParamType::Vec3>(value, key, getDefaultVec3());
    }

    bool getDynamicParam(bool** value, const sead::SafeString& key) const {
        return getDynamicParamPtrImpl<AIDefParamType::Bool>(value, key, getDefaultBool());
    }

    bool getDynamicParam(BaseProcLink** value, const sead::SafeString& key) const {
        return getDynamicParamPtrImpl<AIDefParamType::BaseProcLink>(value, key,
                                                                    getDefaultBaseProcLink());
    }

    bool getDynamicParam(MesTransceiverId** value, const sead::SafeString& key) const {
        return getDynamicParamPtrImpl<AIDefParamType::MesTransceiverId>(
            value, key, getDefaultMesTransceiverId());
    }

    bool getDynamicParam(BaseProcHandle*** value, const sead::SafeString& key) const {
        return getDynamicParamPtrImpl<AIDefParamType::BaseProcHandle>(value, key,
                                                                      getDefaultBaseProcHandle());
    }

    bool getDynamicParam(Rail*** value, const sead::SafeString& key) const {
        return getDynamicParamPtrImpl<AIDefParamType::Rail>(value, key, getDefaultRail());
    }

    bool getDynamicParam(sead::SafeString** value, const sead::SafeString& key) const {
        return getDynamicParamPtrImpl<AIDefParamType::String>(
            value, key, static_cast<sead::SafeString*>(getDefaultString32()));
    }

    // TODO: rename -- why do these exist?
    template <AIDefParamType Type, typename T>
    bool getDynamicParamPtrImpl2(T** value, const sead::SafeString& key, T* default_value) const {
        return getDynamicParamImpl(value, key, &ParamPack::getPtrGeneric2<T, Type>, &default_value);
    }

    bool getDynamicParam2(int** value, const sead::SafeString& key) const {
        return getDynamicParamPtrImpl2<AIDefParamType::Int>(value, key, getDefaultInt());
    }

    bool getDynamicParam2(float** value, const sead::SafeString& key) const {
        return getDynamicParamPtrImpl2<AIDefParamType::Float>(value, key, getDefaultFloat());
    }

    bool getDynamicParam2(sead::Vector3f** value, const sead::SafeString& key) const {
        return getDynamicParamPtrImpl2<AIDefParamType::Vec3>(value, key, getDefaultVec3());
    }

    bool getDynamicParam2(bool** value, const sead::SafeString& key) const {
        return getDynamicParamPtrImpl2<AIDefParamType::Bool>(value, key, getDefaultBool());
    }

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
