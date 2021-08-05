#pragma once

#include <container/seadBuffer.h>
#include <container/seadOrderedSet.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <prim/seadEnum.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class AwarenessInstance;

class Awareness {
    SEAD_SINGLETON_DISPOSER(Awareness)

    Awareness() = default;
    virtual ~Awareness();

public:
    struct InitArg {
        int num_instances_max;
        // TODO: rename
        int num_links_max;
        int num_links2_max;
    };

    bool init(const InitArg& arg, sead::Heap* heap);
    bool initBeforeStageGen();
    void setPaused(bool paused);
    void setEventActive(bool active);
    void calc();

private:
    friend class AwarenessInstance;

    SEAD_ENUM(Flag, _0, Paused, _2, _3, EventActive, _5, _6)

    // FIXME: rename
    struct Unk1 {
        virtual ~Unk1() { finalize(); }
        void finalize();
        void calc();

        void* _8{};
        void* _10{};
    };

    struct TerrorFilter {
        bool operator<(const TerrorFilter& rhs) const { return target < rhs.target; }

        u32 flags;
        u32 target;
    };

    struct SensorFilter {
        bool operator<(const SensorFilter& rhs) const { return target < rhs.target; }

        u32 flags;
        u32 target;
    };

    struct SensorFilterBuffer {
        bool operator<(const SensorFilterBuffer& rhs) const { return target < rhs.target; }

        union Params {
            struct {
                int system;
                int sense;
                int sight;
                int worry;
                int hearing;
            };
            sead::SafeArray<int, 5> raw;
        };
        Params params;
        u32 target;
    };

    struct InstanceRef {
        AwarenessInstance* instance{};
    };

    struct Instances {
        ~Instances() { instances.freeBuffer(); }
        bool registerInstance(AwarenessInstance* instance);
        void deregisterInstance(AwarenessInstance* instance);
        void calc();
        void calcForEvent(bool check_334);
        AwarenessInstance*& get(int i) { return instances[i].instance; }
        AwarenessInstance*& operator[](int i) { return get(i); }

        sead::Buffer<InstanceRef> instances;
        int count = 0;
        int ticks = 0;
        sead::CriticalSection critical_section;
    };

    // FIXME: rename
    struct Link {
        BaseProcLink link;
        // TODO: physics body?
        void* _10{};
    };

    // FIXME: rename
    struct Link2 {
        Link2() { _10 = 0; }
        BaseProcLink link;
        u8 _10{};
        u32 _14{};
        void* _18{};
    };

    // FIXME: rename
    struct Links {
        void calc();

        sead::Buffer<Link> buffer;
        sead::Atomic<int> count;
    };

    // FIXME: rename
    struct Links2 {
        void calc();

        sead::Buffer<Link2> buffer;
        sead::Atomic<int> count;
    };

    void finalize();
    bool loadSystemData();

    bool checkFlag(Flag flag) const { return (1u << flag) & mFlags.getDirect(); }
    void setFlag(Flag flag) { mFlags.setBit(flag); }
    void resetFlag(Flag flag) { mFlags.resetBit(flag); }

    Instances mInstances;
    Links mLinks;
    Links2 mLinks2;
    Unk1 mUnk;
    sead::OrderedSet<TerrorFilter> mTerrorFilters;
    sead::OrderedSet<SensorFilter> mSensorFilters;
    sead::OrderedSet<SensorFilterBuffer> mSensorFilterBuffers;
    sead::BitFlag8 mFlags;
    sead::Heap* mHeap{};
};
KSYS_CHECK_SIZE_NX150(Awareness, 0x138);

}  // namespace ksys::act
