#include "KingSystem/Event/evtInfoData.h"
#include <basis/seadNew.h>
#include <prim/seadSafeString.h>
#include <resource/seadResource.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Utils/Byaml/Byaml.h"

namespace ksys::evt {

SEAD_SINGLETON_DISPOSER_IMPL(InfoData)

InfoData::InfoData() = default;

void InfoData::init(sead::Heap* heap) {
    doInit(heap, nullptr);
}

void InfoData::doInit(sead::Heap* heap, OverlayArena* arena) {
    ksys::res::LoadRequest load_request;

    load_request.mRequester = "evt::InfoData";
    load_request._22 = true;
    load_request.mArena = arena;

    mHandle.load("Event/EventInfo.product.byml", &load_request, nullptr);
    auto* resource = sead::DynamicCast<sead::DirectResource>(mHandle.getResource());

    if (mRootIter)
        delete mRootIter;

    mRootIter = new (heap) al::ByamlIter(resource->getRawData());
}

InfoData::~InfoData() {
    if (mRootIter)
        delete mRootIter;

    if (_80) {
        delete _80;
    }
}

bool InfoData::getEntry(al::ByamlIter* iter, const sead::SafeString& event_flow_name,
                        const sead::SafeString& entry_point) {
    sead::FixedSafeString<256> formatted_key;

    if (entry_point.isEmpty()) {
        formatted_key.format("%s<%s>", event_flow_name.cstr(), event_flow_name.cstr());
    } else {
        formatted_key.format("%s<%s>", event_flow_name.cstr(), entry_point.cstr());
    }

    return mRootIter->tryGetIterByKey(iter, formatted_key.cstr());
}

bool InfoData::getSceneChangeEventTraverseLimit(const sead::SafeString& event_flow_name) {
    if (event_flow_name != "ClearRemains") {
        al::ByamlIter dict;
        if (!getEntry(&dict, event_flow_name, "")) {
            return false;
        }

        f32 value{};
        if (!(dict.tryGetFloatByKey(&value, "traverse_limit") && value > 0.0)) {
            return false;
        }
    }
    return true;
}

}  // namespace ksys::evt
