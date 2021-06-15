#pragma once

#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"
#include "KingSystem/ActorSystem/actAiParam.h"
#include "KingSystem/ActorSystem/actAiQueries.h"
#include "KingSystem/ActorSystem/actAiQuery.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act::ai {

class IRootAi {
public:
    virtual ~IRootAi() = default;
};

enum class RootAiFlag : u16 {
    _100 = 0x100,  // 8
};

// TODO: rename
enum class RootAiFlag2 : u16 {};

class RootAi : public Ai, public IRootAi {
    SEAD_RTTI_OVERRIDE(RootAi, Ai)
public:
    explicit RootAi(const InitArg& arg);
    ~RootAi() override;

    bool isFlag4Set() const override { return true; }
    bool init_(sead::Heap* heap) override;
    void enter_(InlineParamPack* params) override;
    void leave_() override;
    bool handleMessage_(Message* message) override;
    void calc() override;

    const ParamPack& getMapUnitParams() const { return mMapUnitParams; }
    const ParamPack& getAiTreeParams() const { return mAiTreeParams; }
    u32 getI() const { return mI; }
    bool isActorDeletedOrDeleting() const;

    const Actions& getActions() const { return mActions; }
    const Ais& getAis() const { return mAis; }
    const Behaviors& getBehaviors() const { return mBehaviors; }
    const Queries& getQueries() const { return mQueries; }

    bool loadMapUnitParams(const AIDef& def, sead::Heap* heap);
    bool loadAITreeParams(const AIDef& def, sead::Heap* heap);

    bool getMapUnitParam(sead::SafeString* value, const sead::SafeString& key) const;
    bool getMapUnitParam(const s32** value, const sead::SafeString& key) const;
    bool getMapUnitParam(const f32** value, const sead::SafeString& key) const;
    bool getMapUnitParam(const sead::Vector3f** value, const sead::SafeString& key) const;
    bool getMapUnitParam(const bool** value, const sead::SafeString& key) const;

    bool getAITreeVariable(sead::SafeString** value, const sead::SafeString& key) const;
    bool getAITreeVariable(s32** value, const sead::SafeString& key) const;
    bool getAITreeVariable(f32** value, const sead::SafeString& key) const;
    bool getAITreeVariable(sead::Vector3f** value, const sead::SafeString& key) const;
    bool getAITreeVariable(bool** value, const sead::SafeString& key) const;
    bool getAITreeVariable(void** value, const sead::SafeString& key) const;
    bool getAITreeVariable(u32** value, const sead::SafeString& key) const;
    // TODO: rename
    bool getAITreeVariable2(sead::Vector3f** value, const sead::SafeString& key) const;
    // TODO: rename
    bool getAITreeVariable2(bool** value, const sead::SafeString& key) const;

    void setBehavior(Behavior* behavior);
    void resetBehavior(Behavior* behavior);

private:
    friend class ActionBase;

    // TODO: rename and put this in a different translation unit
    struct SomeStruct {
        SomeStruct();
        virtual ~SomeStruct();

        void* _8{};
    };
    KSYS_CHECK_SIZE_NX150(SomeStruct, 0x10);

    void calc_() override;

    f32 _40 = 1.0;
    u32 _44{};
    Actions mActions;
    Ais mAis;
    Behaviors mBehaviors;
    Queries mQueries;
    sead::SafeArray<Behavior*, 3> mBehaviorsByStopAndCalcTiming[2]{};
    void* _138{};
    SomeStruct* _140{};
    u32 mI{};
    u16 mAt{};
    u8 _14e{};
    void* _150{};
    void* _158{};
    void* _160{};
    // TODO: is this really an atomic?
    sead::Atomic<f32> _168 = 1.0;
    sead::TypedBitFlag<RootAiFlag> _16c;
    sead::TypedBitFlag<RootAiFlag2> _16e;
    ParamPack mMapUnitParams;
    ParamPack mAiTreeParams;
};
KSYS_CHECK_SIZE_NX150(RootAi, 0x180);

const char* getDefaultAiName(s32 root_idx);
const char* getDefaultActionName(s32 idx);

inline const char* getDefaultName(ActionType type, s32 idx) {
    if (type == ActionType::AI)
        return getDefaultAiName(idx);
    return getDefaultActionName(idx);
}

}  // namespace ksys::act::ai
