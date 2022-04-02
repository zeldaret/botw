#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectSwarm : public GParamListObject {
public:
    GParamListObjectSwarm();
    const char* getName() const override { return "Swarm"; }

    agl::utl::Parameter<s32> mSwarmSubActorNum;
    agl::utl::Parameter<s32> mSwarmPattern;
    agl::utl::Parameter<sead::SafeString> mDeadActorName;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectSwarm, 0xa0);

inline GParamListObjectSwarm::GParamListObjectSwarm() {
    auto* const obj = &mObj;

    mSwarmSubActorNum.init(50, "SwarmSubActorNum", "", obj);
    mSwarmPattern.init(0, "SwarmPattern", "", obj);
    mDeadActorName.init("", "DeadActorName", "", obj);
}

}  // namespace ksys::res
