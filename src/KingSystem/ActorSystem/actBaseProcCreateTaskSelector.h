#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadDelegate.h>
#include "KingSystem/Utils/Thread/TaskQueueBase.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class BaseProcCreateTaskSelector {
    SEAD_SINGLETON_DISPOSER(BaseProcCreateTaskSelector)
    BaseProcCreateTaskSelector() = default;

public:
    auto& getDelegate() { return mDelegate; }

private:
    util::Task* selectTask(const util::TaskSelectionContext& context);

    util::TaskSelectionDelegateT<BaseProcCreateTaskSelector> mDelegate{
        this, &BaseProcCreateTaskSelector::selectTask};
};
KSYS_CHECK_SIZE_NX150(BaseProcCreateTaskSelector, 0x40);

}  // namespace ksys::act
