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

    BaseProcHandle(const BaseProcHandle&) = delete;
    BaseProcHandle(BaseProcHandle&&) = delete;
    auto operator=(const BaseProcHandle&) = delete;
    auto operator=(BaseProcHandle&&) = delete;

    bool isProcReady() const;
    bool hasProcCreationFailed() const;
    bool isProcCreationCancelled() const;

    void deleteProcIfFailed();
    void deleteProc();

    BaseProc* getProc() const;
    BaseProc* releaseProc();
    BaseProc* releaseAndWakeProc();
    BaseProcCreateTask* getCreateTask() const;
    BaseProcUnit* getUnit() const { return mUnit; }
    bool allocUnit();

    bool hasFailed() const { return mFailed; }
    void setFailed(bool failed) { mFailed = failed; }

private:
    BaseProcUnit* mUnit = nullptr;
    bool mFailed = false;
};
KSYS_CHECK_SIZE_NX150(BaseProcHandle, 0x10);

}  // namespace ksys::act
