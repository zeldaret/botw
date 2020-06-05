#pragma once

#include <basis/seadTypes.h>

#include "KingSystem/ActorSystem/actAiParam.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class Actor;

namespace ai {

struct ClassArg {
    Actor* actor;
    u32 definitionIdx;
    u32 rootIdx;
};
KSYS_CHECK_SIZE_NX150(ClassArg, 0x10);

class ActionBase {
public:
    ActionBase(const ClassArg& arg);
    virtual ~ActionBase() = default;

protected:
    void setFinished();

    template <typename T>
    void getParamStatic(ParamRef<T>* value, const sead::SafeString& key);

    Actor* mActor;
    ParamPack mParams;
    u16 mDefinitionIdx;
    u8 mRootIdx;
    u8 mStatus = 0;
    u16 mClassIdx;
    u16 mPrevClassIdx;
};
KSYS_CHECK_SIZE_NX150(ActionBase, 0x20);

}  // namespace ai

}  // namespace ksys::act
