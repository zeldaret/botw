#include "KingSystem/Resource/resArchiveWork.h"
#include "KingSystem/System/OverlayArena.h"
#include "KingSystem/Utils/SafeDelete.h"
#include "KingSystem/Utils/Thread/Event.h"

namespace ksys::res {

ArchiveWork::ArchiveWork() = default;

ArchiveWork::~ArchiveWork() {
    if (mArena) {
        mArena->clearUnits();
        util::safeDelete(mArena);
    }
    util::safeDelete(mEvent);
}

bool ArchiveWork::init(const ArchiveWork::InitArg& arg) {
    mEvent = new (arg.heap) util::Event(
        nullptr, sead::IDisposer::HeapNullOption::DoNotAppendDisposerIfNoHeapSpecified, false);
    mEvent->resetSignal();

    mArena = new (arg.heap) OverlayArena;

    OverlayArena::InitArg arena_arg;
    arena_arg.set_flag_1 = true;
    arena_arg.size = arg.arena_size;
    arena_arg.use_best_fit_alloc_mode = false;
    arena_arg.set_flag_10 = false;
    arena_arg.set_flag_8 = arg.arena_set_flag_8;
    arena_arg.name = arg.name;
    arena_arg.heap = arg.arena_heap;
    arena_arg.heap2 = arg.arena_heap2;
    return mArena->init(arena_arg);
}

u32 ArchiveWork::getHeapSize() const {
    return mArena->getHeap()->getSize();
}

OverlayArena* ArchiveWork::getArena() const {
    return mArena;
}

bool ArchiveWork::waitForEvent(u32 milliseconds) {
    if (milliseconds != 0) {
        const auto duration = sead::TickSpan::makeFromMilliSeconds(milliseconds);
        if (!mEvent->wait(duration))
            return false;
    } else {
        mEvent->wait();
    }
    return true;
}

void ArchiveWork::setEvent() {
    mEvent->setSignal();
}

}  // namespace ksys::res
