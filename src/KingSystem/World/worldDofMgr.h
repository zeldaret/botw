#pragma once

#include <agl/Utils/aglParameterObj.h>
#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {

// TODO
class DofMgr : public Job {
public:
    DofMgr();

    JobType getType() const override { return JobType::Dof; }

    void reset();

private:
    friend class Manager;

    u8 _20[0x138 - 0x20];
    agl::utl::ParameterObj mDofMgrParamObj;
    u8 _168[0x1c0 - 0x168];
};
KSYS_CHECK_SIZE_NX150(DofMgr, 0x1c0);

}  // namespace ksys::world
