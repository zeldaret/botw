#include "KingSystem/ActorSystem/actAiClassDef.h"
#include <algorithm>
#include <codec/seadHashCRC32.h>
#include <prim/seadContainerIterator.h>
#include <resource/seadResource.h>
#include "KingSystem/Resource/resLoadRequest.h"

namespace ksys {

namespace {
const char* str_AIAfter = "AIAfter";
const char* str_ModelAfter = "ModelAfter";
const char* str_ChangeDeleteState = "ChangeDeleteState";
const char* str_StaticInstParams = "StaticInstParams";
const char* str_DynamicInstParams = "DynamicInstParams";
const char* str_MapUnitInstParams = "MapUnitInstParams";
const char* str_AITreeVariables = "AITreeVariables";
const char* str_AIs = "AIs";
const char* str_Actions = "Actions";
const char* str_Behaviors = "Behaviors";
const char* str_Querys = "Querys";
}  // namespace

SEAD_SINGLETON_DISPOSER_IMPL(AIClassDef)

AIClassDef::~AIClassDef() {
    freeData();
}

void AIClassDef::init(const sead::SafeString& aidef_file_name, sead::Heap* heap) {
    res::LoadRequest req;
    req.mRequester = "AIClassDef";
    req._22 = true;
    sead::FixedSafeString<128> path;
    path.format("Actor/AIDef/%s", aidef_file_name.cstr());

    auto* res = sead::DynamicCast<sead::DirectResource>(mResHandle.load(path, &req));

    freeData();
    mData = new (heap) Data(res->getRawData());
    mData->load(heap);
}

// NON_MATCHING: not trying to match the heap sort. The rest should be equivalent
bool AIClassDef::Data::load(sead::Heap* heap) {
    root_iter.tryGetIterByKey(&iters[s32(AIDefType::AI)], str_AIs);
    root_iter.tryGetIterByKey(&iters[s32(AIDefType::Action)], str_Actions);
    root_iter.tryGetIterByKey(&iters[s32(AIDefType::Behavior)], str_Behaviors);
    root_iter.tryGetIterByKey(&iters[s32(AIDefType::Query)], str_Querys);

    idx_StaticInstParams = root_iter.getKeyIndex(str_StaticInstParams);
    idx_DynamicInstParams = root_iter.getKeyIndex(str_DynamicInstParams);
    idx_MapUnitInstParams = root_iter.getKeyIndex(str_MapUnitInstParams);
    idx_AITreeVariables = root_iter.getKeyIndex(str_AITreeVariables);
    idx_Childs = root_iter.getKeyIndex("childs");

    static_cast<void>(heap->getFreeSize());

    for (s32 type = 0; type < NumAIDefTypes; ++type) {
        if (!iters[type].isValid())
            continue;

        const s32 count = iters[type].getSize();
        if (count <= 0)
            continue;

        auto& buffer = defs[type];
        buffer.allocBufferAssert(count, heap);

        for (s32 i = 0; i < count; ++i) {
            buffer[i].name_hash = 0;
            const char* name = nullptr;
            if (iters[type].tryGetIterAndKeyNameByIndex(&buffer[i].iter, &name, i))
                buffer[i].name_hash = sead::HashCRC32::calcStringHash(name);
        }

        auto ct = sead::stdIterator(buffer);
        std::sort(ct.begin(), ct.end(),
                  [](const Def& lhs, const Def& rhs) { return lhs.name_hash < rhs.name_hash; });
    }

    return true;
}

// NON_MATCHING: binary search might be a handwritten loop?
bool AIClassDef::isSystemQuery(const sead::SafeString& query) const {
    bool ret = false;
    const u32 hash = sead::HashCRC32::calcStringHash(query);

    if (!mData)
        return false;

    const s32 idx = mData->defs[s32(AIDefType::Query)].binarySearchC(
        [hash](const Data::Def& def) -> s32 { return hash - def.name_hash; });

    if (idx < 0)
        return false;

    mData->defs[s32(AIDefType::Query)][idx].iter.tryGetBoolByKey(&ret, "SystemQuery");
    return ret;
}

}  // namespace ksys
