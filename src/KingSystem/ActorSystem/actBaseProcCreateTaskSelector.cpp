#include "KingSystem/ActorSystem/actBaseProcCreateTaskSelector.h"
#include <limits>
#include "KingSystem/ActorSystem/actBaseProcCreateTask.h"
#include "KingSystem/Map/mapObject.h"

namespace ksys::act {

SEAD_SINGLETON_DISPOSER_IMPL(BaseProcCreateTaskSelector)

util::Task* BaseProcCreateTaskSelector::selectTask(const util::TaskSelectionContext& context) {
    util::Task* min_task = nullptr;
    util::Task* lane1_task = nullptr;
    auto min = std::numeric_limits<float>::max();

    for (auto& it : context) {
        auto* task = sead::DynamicCast<BaseProcCreateTask>(&it);
        if (!task)
            return &it;

        if (task->getLaneId() == u8(BaseProcCreateTask::LaneId::_2))
            return &it;

        if (task->mMapObject && task->mMapObject->getFlags0().isOff(map::Object::Flag0::_4))
            return &it;

        if (task->mDistanceToLoadSphere >= 0.0 && min > task->mDistanceToLoadSphere)
            min_task = &it;

        if (task->mDistanceToLoadSphere >= 0.0 && min > task->mDistanceToLoadSphere)
            min = task->mDistanceToLoadSphere;

        if (task->getLaneId() == u8(BaseProcCreateTask::LaneId::_1))
            lane1_task = &it;
    }

    if (min_task)
        return min_task;

    if (lane1_task)
        return lane1_task;

    return std::addressof(*context.begin());
}

}  // namespace ksys::act
