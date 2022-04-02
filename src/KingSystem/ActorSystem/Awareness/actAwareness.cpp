#include "KingSystem/ActorSystem/Awareness/actAwareness.h"
#include <agl/utl/aglParameter.h>
#include <agl/utl/aglResParameter.h>
#include <container/seadSafeArray.h>
#include <cstring>
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/Awareness/actAwarenessDefs.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resLoadRequest.h"

namespace ksys::act {

SEAD_SINGLETON_DISPOSER_IMPL(Awareness)

bool Awareness::Instances::registerInstance(AwarenessInstance* instance) {
    auto lock = sead::makeScopedLock(critical_section);

    if (instances.size() <= count)
        return false;

    instances[count].instance = instance;
    ++count;
    return true;
}

void Awareness::Instances::deregisterInstance(AwarenessInstance* instance) {
    auto lock = sead::makeScopedLock(critical_section);

    for (int i = 0; i < count; ++i) {
        if (instances[i].instance == instance) {
            // Swap and remove. The instance order doesn't matter here.
            --count;
            instances[i] = instances[count];
            break;
        }
    }
}

Awareness::~Awareness() {
    finalize();
}

void Awareness::finalize() {
    mTerrorFilters.finalize();
    mSensorFilters.finalize();
    mSensorFilterBuffers.finalize();
}

bool Awareness::init(const Awareness::InitArg& arg, sead::Heap* heap) {
    mHeap = heap;

    if (!loadSystemData())
        return false;

    mInstances.instances.allocBufferAssert(arg.num_instances_max, heap);
    if (!mInstances.instances.isBufferReady())
        return false;

    mLinks2.buffer.allocBufferAssert(arg.num_links2_max, heap);
    if (!mLinks2.buffer.isBufferReady())
        return false;

    mLinks.buffer.allocBufferAssert(arg.num_links_max, heap);
    if (!mLinks.buffer.isBufferReady())
        return false;

    return true;
}

// agl::utl::ResParameter::getParam being a pain as usual
#ifdef NON_MATCHING
bool Awareness::loadSystemData() {
    if (!mHeap)
        return false;

    res::Handle handle;
    res::LoadRequest req;
    req.mRequester = "AwarenessSystemData";
    req._26 = false;

    {
        const auto* res = sead::DynamicCast<sead::DirectResource>(
            handle.load("Awareness/TerrorFilter.bawntable", &req));
        if (!res)
            return false;

        const agl::utl::ResParameterArchive archive{res->getRawData()};
        const auto root = archive.getRootList();
        const auto list = agl::utl::getResParameterList(root, "TerrorFilter");
        if (list.getResParameterObjNum() == 0)
            return false;
        if (!mTerrorFilters.allocBuffer(list.getResParameterObjNum(), mHeap))
            return false;

        for (auto it = list.objBegin(); it != list.objEnd(); ++it) {
            const auto obj = it.getObj();
            const u32 target = obj.getParameterObjNameHash();
            u32 flags = 0;
            for (auto it_p = obj.begin(); it_p != obj.end(); ++it_p) {
                const auto param = it_p.getParam();
                const auto enabled = *param.getData<int>();
                if (enabled)
                    flags |= getAwarenessTerrorFlags(param.getParameterNameHash());
            }
            mTerrorFilters.insert(TerrorFilter{flags, target});
        }
    }

    handle.requestUnload2();

    {
        const auto* res = sead::DynamicCast<sead::DirectResource>(
            handle.load("Awareness/SensorFilter.bsft", &req));
        if (!res)
            return false;

        const agl::utl::ResParameterArchive archive{res->getRawData()};
        const auto root = archive.getRootList();
        const auto list = agl::utl::getResParameterList(root, "SensorFilter");
        if (list.getResParameterObjNum() == 0)
            return false;
        if (!mSensorFilters.allocBuffer(list.getResParameterObjNum(), mHeap))
            return false;

        for (auto it = list.objBegin(); it != list.objEnd(); ++it) {
            const auto obj = it.getObj();
            const u32 target = obj.getParameterObjNameHash();
            u32 flags = 0;
            for (auto it_p = obj.begin(); it_p != obj.end(); ++it_p) {
                const auto param = it_p.getParam();
                const auto enabled = *param.getData<int>();
                if (enabled)
                    flags |= getAwarenessSensorFlags(param.getParameterNameHash());
            }
            mSensorFilters.insert(SensorFilter{flags, target});
        }
    }

    handle.requestUnload2();

    {
        const auto* res = sead::DynamicCast<sead::DirectResource>(
            handle.load("Awareness/SensorFilterBuffer.bsfbt", &req));
        if (!res)
            return false;

        const agl::utl::ResParameterArchive archive{res->getRawData()};
        const auto root = archive.getRootList();
        const auto list = agl::utl::getResParameterList(root, "SensorFilterBuffer");
        if (list.getResParameterObjNum() == 0)
            return false;
        if (!mSensorFilterBuffers.allocBuffer(list.getResParameterObjNum(), mHeap))
            return false;

        for (auto it = list.objBegin(); it != list.objEnd(); ++it) {
            const auto obj = it.getObj();
            const u32 target = obj.getParameterObjNameHash();

            SensorFilterBuffer::Params params;
            for (auto it_p = obj.begin(); it_p != obj.end(); ++it_p) {
                const auto param = it_p.getParam();
                std::memcpy(&params.raw[it_p.getIndex()],
                            param.ptrBytes() + param.ptr()->getOffset(), sizeof(int));
                if (it_p.getIndex() >= params.raw.size())
                    return false;
            }

            mSensorFilterBuffers.insert(SensorFilterBuffer{params, target});
        }
    }

    handle.requestUnload2();

    return true;
}
#endif

bool Awareness::initBeforeStageGen() {
    mInstances.count = 0;
    mInstances.ticks = 0;
    mLinks2.count = 0;
    mLinks.count = 0;
    mUnk.finalize();
    setPaused(false);
    return true;
}

void Awareness::setPaused(bool paused) {
    mFlags.changeBit(Flag(Flag::Paused), paused);
    if (paused) {
        mFlags.setBit(Flag(Flag::_2));
    } else {
        mFlags.setBit(Flag(Flag::_6));
    }
}

void Awareness::setEventActive(bool active) {
    mFlags.changeBit(Flag(Flag::EventActive), active);
    if (active) {
        mFlags.setBit(Flag(Flag::_5));
    } else {
        mFlags.setBit(Flag(Flag::_6));
    }
}

void Awareness::calc() {
    if (checkFlag(Flag::Paused)) {
        if (checkFlag(Flag::_2))
            resetFlag(Flag::_2);

    } else if (checkFlag(Flag::EventActive)) {
        if (checkFlag(Flag::_5)) {
            mInstances.calcForEvent(true);
            resetFlag(Flag::_5);
        }

    } else if (checkFlag(Flag::_3)) {
        resetFlag(Flag::_3);

    } else if (checkFlag(Flag::_6)) {
        resetFlag(Flag::_6);

    } else {
        mInstances.calc();
    }

    mUnk.calc();
    mLinks2.calc();
    mLinks.calc();
    resetFlag(Flag::_0);
}

void Awareness::Links2::calc() {
    count = 0;
}

void Awareness::Links::calc() {
    count = 0;
}

void Awareness::Instances::calc() {
    ++ticks;
    for (int i = 0; i < count; ++i) {
        if ((i + ticks) % 8 == 0) {
            get(i)->calc2();
        }
        get(i)->calc();
    }
}

void Awareness::Instances::calcForEvent(bool check_334) {
    for (int i = 0; i < count; ++i) {
        if (!check_334 || get(i)->_334 < 0)
            get(i)->calcForEvent();
    }
}

}  // namespace ksys::act
