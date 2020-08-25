#pragma once

#include <basis/seadTypes.h>
#include "actBaseProcUnit.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class BaseProcUnit;

class BaseProcHandle {
public:
    BaseProcHandle();
    ~BaseProcHandle();

    static BaseProcHandle sDummyBaseProcHandle;
private:
    BaseProcUnit* mUnit;
    u8 mFlag;
};
KSYS_CHECK_SIZE_NX150(BaseProcHandle, 0x10);

}  // namespace ksys::act