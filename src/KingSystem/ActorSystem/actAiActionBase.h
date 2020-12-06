#pragma once

#include <basis/seadTypes.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiParam.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class Actor;

namespace ai {

class ActionBase {
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

    virtual bool isAction();

    enum class Status : u8 {
        Finished = 1,
        Failed = 2,
        _4 = 4,
        TriggerAction = 8,
        DynamicParamChild = 0x10,
        _20 = 0x20,
        _40 = 0x40,
        _80 = 0x80,
    };

protected:
    bool isFinished();
    bool isFailed();
    void setFinished();
    void setFailed();

    template <typename T>
    void getParamStatic(ParamRef<T>* value, const sead::SafeString& key);

    Actor* mActor;
    ParamPack mParams;
    u16 mDefinitionIdx;
    u8 mRootIdx;
    sead::TypedBitFlag<Status, u8> mStatus;
    u16 mClassIdx;
    u16 mPrevClassIdx;
};
KSYS_CHECK_SIZE_NX150(ActionBase, 0x20);

}  // namespace ai

}  // namespace ksys::act
