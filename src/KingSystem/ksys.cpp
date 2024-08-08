#include "KingSystem/ksys.h"
#include <heap/seadHeapMgr.h>
#include <thread/seadThread.h>
#include "KingSystem/ActorSystem/actBaseProcCreateTaskSelector.h"
#include "KingSystem/ActorSystem/actBaseProcInitializer.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/System/BasicProfiler.h"
#include "KingSystem/System/HavokWorkerMgr.h"
#include "KingSystem/System/UI/LayoutResourceMgr.h"

namespace ksys {

void initBaseProcMgr(sead::Heap* heap) {
    sead::ScopedCurrentHeapSetter setter(heap);

    act::BaseProcMgr::createInstance(heap);
    act::BaseProcCreateTaskSelector::createInstance(heap);
    auto* worker_mgr = HavokWorkerMgr::instance();

    act::BaseProcInitializerArgs args{};
    args.queue_size = 1024;
    args.thread_name = "ActorCreate";
    args.task_selector = &act::BaseProcCreateTaskSelector::instance()->getDelegate();
    act::BaseProcMgr::instance()->init(
        heap, u32(act::JobType::Invalid), sead::ThreadMgr::instance()->getMainThread()->getId(),
        worker_mgr->getWorkerThreadId(1), worker_mgr->getWorkerThreadId(2), args);

    act::BaseProcMgr::sConstant0 = u32(act::JobType::PreCalc);
    act::BaseProcMgr::sConstant1 = u32(act::JobType::Calc1);
    act::BaseProcMgr::sConstant2 = u32(act::JobType::Calc2);
    act::BaseProcMgr::sConstant4 = u32(act::JobType::Calc4);
}

void preInitializeApp(InitParams* params) {
    ksys::BasicProfiler::push("ksys::PreInitializeApp");

    // TODO - other parts

    ksys::BasicProfiler::push("RequestFontLoad");
    // TODO: FontMgr::createInstance()
    ui::LayoutResourceMgr::createInstance(params->king_sys_heap);
    ui::LayoutResourceMgr::instance()->init(params->king_sys_heap);
    ui::LayoutResourceMgr::instance()->loadLangFont(params->king_sys_heap);
    ui::LayoutResourceMgr::instance()->loadExtraLangFonts(params->king_sys_heap);
    ksys::BasicProfiler::pop("RequestFontLoad");

    // TODO - other parts

    ksys::BasicProfiler::pop("ksys::PreInitializeApp");
}

}  // namespace ksys
