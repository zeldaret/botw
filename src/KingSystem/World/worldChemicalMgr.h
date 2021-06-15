#pragma once

#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {

// TODO
class ChemicalMgr : public Job {
public:
    ChemicalMgr();

    JobType getType() const override { return JobType::Chemical; }

    void initBeforeStageGen();
    void unload2();

    u8 _20[0xdc0 - 0x20];
};
KSYS_CHECK_SIZE_NX150(ChemicalMgr, 0xdc0);

}  // namespace ksys::world
