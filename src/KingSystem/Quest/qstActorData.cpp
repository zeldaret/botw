#include "KingSystem/Quest/qstActorData.h"
#include "KingSystem/Utils/Byaml/Byaml.h"

namespace ksys::qst {

CameraTarget::~CameraTarget() = default;

ActorData::ActorData(sead::Heap* heap) {
    this->heap = heap;
}

ActorData::~ActorData() {
    for (int i = 0; i < targets.size(); ++i) {
        /// @bug The object is destructed twice (UB).
        std::destroy_at(targets[i]);
        delete targets[i];
    }
    targets.freeBuffer();
}

bool ActorData::init(al::ByamlIter* iter, sead::BufferedSafeString* out_message) {
    if (iter == nullptr)
        return true;

    sead::FixedSafeString<16> key("CameraTargets");
    al::ByamlIter target_iter;

    if (!iter->tryGetIterByKey(&target_iter, key.cstr()))
        return true;

    if (!targets.tryAllocBuffer(target_iter.getSize(), heap)) {
        // Failed to setup photo target storage buffer. (Insufficient memory?)
        out_message->format("写真対象格納バッファの設定に失敗しました。（メモリ不足？）");
        return false;
    }

    for (int i = 0; i < target_iter.getSize(); ++i) {
        const char* string = nullptr;
        bool result = target_iter.tryGetStringByIndex(&string, i);

        if (string == nullptr || !result) {
            // Failed to get the photo target (%d).
            out_message->format("写真対象(%d)の取得に失敗しました。", i);
            return false;
        }

        auto* target = new (heap, std::nothrow_t()) CameraTarget();
        if (target == nullptr) {
            // Failed to allocate photo target information (%d).
            out_message->format("写真対象情報(%d)の生成に失敗しました。");
            return false;
        }

        target->enabled = false;
        target->name = string;
        targets.pushBack(target);
    }

    return true;
}

const CameraTarget* ActorData::getTarget(int idx) const {
    if (targets.size() < 1 || idx < 0 || idx >= targets.size())
        return nullptr;
    return targets[idx];
}

void ActorData::disableAllTargets() {
    for (int i = 0; i < targets.size(); ++i)
        targets[i]->enabled = false;
}

void ActorData::enableAllTargets() {
    for (int i = 0; i < targets.size(); ++i) {
        targets[i]->enabled = true;
    }
}

}  // namespace ksys::qst
