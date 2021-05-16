#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/Map/mapMubinIter.h"

namespace ksys {

namespace map {
class Object;
}  // namespace map

namespace act {

namespace ai {
class RootAi;
}

class LifeRecoverInfo;
class ActorCreator;
class ActorParam;

class Actor : public BaseProc {
public:
    enum class StasisFlag {
        _1 = 1,
        _2 = 2,
        _4 = 4,
    };

    enum class ActorFlag {
        _18 = 0x18,
        _25 = 0x25,
        _29 = 0x29,
        _2b = 0x2b,
        _2e = 0x2e,
        _39 = 0x39,
    };

    enum class ActorFlag2 {
        NoDistanceCheck = 0x80,
    };

    enum class DeleteType {
        _1 = 1,
        _2 = 2,
        _3 = 3,
    };

    Actor();  // FIXME
    ~Actor() override;

    SEAD_RTTI_OVERRIDE(Actor, BaseProc)

    const sead::SafeString& getProfile() const;
    const char* getUniqueName() const;

    ai::RootAi* getRootAi() const { return mRootAi; }
    const ActorParam* getParam() const { return mActorParam; }
    map::Object* getMapObject() const { return mMapObject; }
    const map::MubinIter& getMapObjIter() const { return mMapObjIter; }

    bool checkFlag(ActorFlag flag) const;
    bool deleteEx(DeleteType type, DeleteReason reason, bool* ok = nullptr);

    void setProperties(int x, const sead::Matrix34f& mtx, const sead::Vector3f& vel,
                       const sead::Vector3f& ang_vel, const sead::Vector3f& scale,
                       bool is_life_infinite, int i, int life) const;

    virtual s32 getMaxLife();

    virtual LifeRecoverInfo* getLifeRecoverInfo();

    void emitBasicSigOn();
    void emitBasicSigOff();

    void nullsub_4649();  // Some kind of logging which has been excluded from the build?

    sead::TypedBitFlag<ActorFlag2>& getActorFlags2() { return mActorFlags2; }
    const sead::TypedBitFlag<ActorFlag2>& getActorFlags2() const { return mActorFlags2; }

    const sead::TypedBitFlag<StasisFlag>& getStasisFlags() const { return mStasisFlags; }

    void onAiEnter(const char* name, const char* context);

    static constexpr size_t getCreatorListNodeOffset() { return offsetof(Actor, mCreatorListNode); }

protected:
    friend class ActorCreator;

    /* 0x17c */ u8 TEMP_0x17c[0x518 - 0x17c];  // FIXME
    /* 0x518 */ sead::TypedBitFlag<ActorFlag2> mActorFlags2;
    /* 0x51c */ u8 TEMP_0x51c[0x558 - 0x51c];
    /* 0x558 */ ai::RootAi* mRootAi;
    /* 0x560 */ void* mASList;   // FIXME
    /* 0x568 */ void* mEffects;  // FIXME
    /* 0x570 */ ActorParam* mActorParam;
    /* 0x578 */ u8 TEMP_0x578[0x648 - 0x578];
    /* 0x648 */ map::MubinIter mMapObjIter;
    /* 0x658 */ u8 TEMP_0x650[0x710 - 0x658];
    /* ..... */  // The name could be incorrect.
    /* 0x710 */ sead::TypedBitFlag<StasisFlag> mStasisFlags;
    /* 0x714 */ u8 TEMP_0x714[0x7b0 - 0x714];  // FIXME
    /* 0x7b0 */ ActorCreator* mCreator{};
    /* 0x7b8 */ sead::ListNode mCreatorListNode;
    /* 0x7c8 */ map::Object* mMapObject;
    /* 0x7d0 */ u8 TEMP_0x7d0[0x838 - 0x7d0];
};
KSYS_CHECK_SIZE_NX150(Actor, 0x838);
}  // namespace act

}  // namespace ksys
