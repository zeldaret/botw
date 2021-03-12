#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class BaseProc;
class BaseProcCreateTask;
class BaseProcUnit;

class BaseProcHandle {
public:
    BaseProcHandle();
    ~BaseProcHandle();

    bool procReady();

    BaseProc* getProc();
    BaseProcUnit* getUnit() const { return mUnit; }
    bool allocUnit();
    BaseProcCreateTask* getCreateTask() const;

    bool getFlag() const { return mFlag; }
    void setFlag(bool flag) { mFlag = flag; }

    static BaseProcHandle sDummyHandle;

private:
    BaseProcUnit* mUnit;
    bool mFlag;
};
KSYS_CHECK_SIZE_NX150(BaseProcHandle, 0x10);

}  // namespace ksys::act
