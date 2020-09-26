#include "KingSystem/Resource/resResourceMgrTask.h"
#include <thread/seadThreadUtil.h>
#include "KingSystem/Utils/Thread/GameTaskThread.h"
#include "KingSystem/Utils/Thread/TaskThread.h"

namespace ksys::res {

util::TaskThread* ResourceMgrTask::makeResourceLoadingThread(sead::Heap* heap,
                                                             bool use_game_task_thread) {
    if (use_game_task_thread) {
        return new (heap) util::GameTaskThread(
            "Resource Loading", heap, sead::ThreadUtil::ConvertPrioritySeadToPlatform(19),
            sead::MessageQueue::BlockType::Blocking, 0x7fffffff, 0xfa000, 32);
    }

    return new (heap) util::TaskThread(
        "Resource Loading", heap, sead::ThreadUtil::ConvertPrioritySeadToPlatform(19),
        sead::MessageQueue::BlockType::Blocking, 0x7fffffff, 0xa000, 32);
}

}  // namespace ksys::res
