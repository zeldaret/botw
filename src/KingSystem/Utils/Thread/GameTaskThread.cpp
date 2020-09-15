#include "KingSystem/Utils/Thread/GameTaskThread.h"

namespace ksys::util {

GameTaskThread::GameTaskThread(const sead::SafeString& name, sead::Heap* heap, s32 priority,
                               sead::MessageQueue::BlockType block_type, long quit_msg,
                               s32 stack_size, s32 message_queue_size)
    : TaskThread(name, heap, priority, block_type, quit_msg, stack_size, message_queue_size) {}

void GameTaskThread::quit(bool) {
    mMessageQueue.push(cMessage_GameThreadQuit, sead::MessageQueue::BlockType::Blocking);
    Thread::quit(false);
}

}  // namespace ksys::util
