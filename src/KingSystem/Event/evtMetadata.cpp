#include "KingSystem/Event/evtMetadata.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtOrderParam.h"

namespace ksys::evt {

Metadata::Metadata() {
    reset();
    initOrderParam_();
}

Metadata::Metadata(const char* event, const char* entry_point, const char* type) {
    reset();
    initOrderParam_();
    init(event, entry_point, type);
}

Metadata::~Metadata() {
    if (mOrderParam) {
        delete mOrderParam;
        mOrderParam = nullptr;
    }
}

void Metadata::doAssign_(const Metadata& other) {
    reset();
    init(other.mEventName.cstr(), other.mEntryPointName.cstr(), other.mType.cstr());

    mCurrentActor = other.mCurrentActor;
    if (other.mSetNoDeleteCurrentActor)
        mSetNoDeleteCurrentActor = true;
    _18 = other._18;
    _20 = other._20;
    mIsAsync = other.mIsAsync;
    mSkipIsStartableAirCheck = other.mSkipIsStartableAirCheck;
    mForceNoChild = other.mForceNoChild;
    _13 = other._13;
    mEventStartWaitFrame = other.mEventStartWaitFrame;
    if (mOrderParam && other.mOrderParam)
        *mOrderParam = *other.mOrderParam;
}

Metadata& Metadata::operator=(const Metadata& other) {
    if (this != &other)
        doAssign_(other);
    return *this;
}

void Metadata::init(const char* event, const char* entry_point, const char* type) {
    mEventName = event;
    mEntryPointName = entry_point;
    mType = type;
    initFlags_();
}

void Metadata::reset() {
    mEventName.clear();
    mEntryPointName.clear();
    mType.clear();
    mFlags = Flag::DefaultFlags;
    _18 = {};
    mIsAsync = false;
    mSetNoDeleteCurrentActor = false;
    mSkipIsStartableAirCheck = false;
    mForceNoChild = false;
    _13 = false;
    mCurrentActor = nullptr;
    _20 = 0;
    mEventStartWaitFrame = -1;
}

void Metadata::initOrderParam_() {
    if (mOrderParam)
        return;

    if (!Manager::instance())
        return;

    sead::Heap* heap = Manager::instance()->getEventHeap();
    if (!heap)
        return;

    mOrderParam = new (heap, std::nothrow_t()) OrderParam(heap);
    if (mOrderParam)
        mOrderParam->initialize(8);
}

void Metadata::initFlags_() {
    if (mEventName == "Demo006_0") {
        mFlags = Flag::_4;
    } else if (mEventName == "Demo017_0") {
        mFlags = Flag::_4 | Flag::_1;
    } else if (mEventName == "ClearRemains" || mEventName.comparen("Demo", 4) == 0) {
        mFlags = Flag::_8 | Flag::_4 | Flag::_2 | Flag::_1;
    } else if (mEventName.comparen("OpenDoor", 8) == 0) {
        mFlags = Flag::_8 | Flag::_4 | Flag::_2 | Flag::_1;
    } else if (mType == "Timeline") {
        mFlags = Flag::_4;
    } else if (mType == "Talk") {
        mFlags = Flag::_100 | Flag::_80 | Flag::_10;
    } else if (mType == "EachFrame") {
        mFlags = Flag::_100 | Flag::_80 | Flag::_40 | Flag::_20 | Flag::_10 | Flag::_4;
    } else if (mType == "Near" || mType == "NearActors") {
        mFlags = Flag::_100 | Flag::_80 | Flag::_10 | Flag::_8 | Flag::_2;
    } else if (mType == "StepStart") {
        mFlags = Flag::_8 | Flag::_2;
    } else if (mType == "Background") {
        mFlags = Flag::_100 | Flag::_80 | Flag::_40 | Flag::_20 | Flag::_10 | Flag::_8 | Flag::_4 |
                 Flag::_2;
    } else {
        mFlags = Flag::_40 | Flag::_20 | Flag::_4;
    }
}

}  // namespace ksys::evt
