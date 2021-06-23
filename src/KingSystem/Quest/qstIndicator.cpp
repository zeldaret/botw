#include "KingSystem/Quest/qstIndicator.h"
#include "KingSystem/Quest/qstStep.h"

namespace ksys::qst {

Indicator::Indicator(Step* step, sead::Heap* heap) {
    this->heap = heap;
    this->step = step;
}

Indicator::~Indicator() {
    finalize();
}

// NON_MATCHING: Confusing control flow
bool Indicator::init(al::ByamlIter* iter, sead::BufferedSafeString* out_message) {
    if (!iter->isValid()) {
        // Step (%s) is invalid data.
        out_message->format("ステップ(%s)は無効なデータです。", step->name);
        return false;
    }

    sead::FixedSafeString<32> actor_key("IndicatorActors");
    sead::FixedSafeString<32> param_key("");
    al::ByamlIter actor_iter;
    if (iter->tryGetIterByKey(&actor_iter, actor_key.cstr())) {
        if (!actor_iter.isValid()) {
            // Parameter [%s] for step (%s) is invalid data.
            out_message->format("ステップ(%s)のパラメータ [%s] は無効なデータです。", step->name,
                                actor_key.cstr());
            return false;
        }

        int size = actor_iter.getSize();
        if (size >= 1) {
            if (!actors.tryAllocBuffer(size, heap, 8)) {
                // Failed to set the actor indicator storage buffer for step (%s). (Insufficient
                // memory?)
                out_message->format(
                    "ステップ(%s)のアクター光点格納バッファの設定に失敗しました。（メモリ不足？）",
                    step->name);
                return false;
            }

            al::ByamlIter param_iter;
            for (int i = 0; i < size; ++i) {
                if (!actor_iter.tryGetIterByIndex(&param_iter, i)) {
                    // Failed to get the actor indicator (%d) for step (%s).
                    out_message->format("ステップ(%s)のアクター光点(%d)の取得に失敗しました。",
                                        step->name, i);
                    return false;
                }
                if (!param_iter.isValid()) {
                    // Actor indicator (%d) in step (%s) is invalid data.
                    out_message->format("ステップ(%s)のアクター光点(%d)は無効なデータです。",
                                        step->name, i);
                    return false;
                }

                bool has_far = false;
                const char* instance_name = &sead::SafeString::cNullChar;
                sead::Vector3f location = sead::Vector3f::zero;
                const char* name = &sead::SafeString::cNullChar;
                const char* off_flag = &sead::SafeString::cNullChar;
                bool is_remains = false;

                param_key.format("HasFar");
                if (!param_iter.tryGetBoolByKey(&has_far, param_key.cstr())) {
                    continue;
                }

                param_key.format("InstanceName");
                if (!param_iter.tryGetStringByKey(&instance_name, param_key.cstr())) {
                    // Failed to get parameter [%s] of actor indicator (%d) for step (%s).
                    out_message->format(
                        "ステップ(%s)のアクター光点(%d)のパラメータ [%s] の取得に失敗しました。",
                        step->name, i, param_key.cstr());
                    break;
                }

                param_key.format("Location");
                if (!al::tryGetByamlV3f(&location, param_iter, param_key.cstr())) {
                    // Failed to get parameter [%s] of actor indicator (%d) for step (%s).
                    out_message->format(
                        "ステップ(%s)のアクター光点(%d)のパラメータ [%s] の取得に失敗しました。",
                        step->name, i, param_key.cstr());
                    break;
                }

                param_key.format("Name");
                if (!param_iter.tryGetStringByKey(&name, param_key.cstr())) {
                    // Failed to get parameter [%s] of actor indicator (%d) for step (%s).
                    out_message->format(
                        "ステップ(%s)のアクター光点(%d)のパラメータ [%s] の取得に失敗しました。",
                        step->name, i, param_key.cstr());
                    break;
                }

                param_key.format("OffFlag");
                if (!param_iter.tryGetStringByKey(&off_flag, param_key.cstr())) {
                    // Failed to get parameter [%s] of actor indicator (%d) for step (%s).
                    out_message->format(
                        "ステップ(%s)のアクター光点(%d)のパラメータ [%s] の取得に失敗しました。",
                        step->name, i, param_key.cstr());
                    break;
                }

                param_key.format("IsRemains");
                param_iter.tryGetBoolByKey(&is_remains, param_key.cstr());

                IndicatorActor* actor = actors.emplaceBack();
                actor->has_far = has_far;
                actor->instance_name = instance_name;
                actor->location = location;
                actor->name = name;
                actor->off_flag = off_flag;
                actor->is_remains = is_remains;
                actor->hash_instance_name = sead::HashCRC32::calcStringHash(instance_name);
                actor->hash_name = sead::HashCRC32::calcStringHash(name);

                if (actor == nullptr) {
                    // Failed to generate actor indicator information (%d) for step (%s).
                    out_message->format("ステップ(%s)のアクター光点情報(%d)の生成に失敗しました。",
                                        step->name, i);
                    break;
                }
            }
        }
    }

    sead::FixedSafeString<32> loc_key("IndicatorLocations");
    al::ByamlIter loc_iter;
    if (iter->tryGetIterByKey(&loc_iter, loc_key.cstr())) {
        if (!loc_iter.isValid()) {
            // Parameter [%s] for step (%s) is invalid data.
            out_message->format("ステップ(%s)のパラメータ [%s] は無効なデータです。", step->name,
                                loc_key.cstr());
            return false;
        }
    }

    acquireActors();
    return true;
}

void Indicator::finalize() {
    actors.freeBuffer();
    _28.freeBuffer();
}

void Indicator::acquireActors() {
    sead::FixedSafeString<64> s;

    for (int i = 0; i < actors.size(); ++i) {
        IndicatorActor* actor = actors[i];
        if (actor == nullptr)
            continue;

        act::BaseProc* proc = Manager::sub_7100FD5848(actor->name, actor->instance_name);
        if (proc != nullptr) {
            if (actor->is_remains == 1) {
                actor->link.acquire(proc, false);
            }
            continue;
        }

        if (actor->has_far) {
            s = actor->name;
            s.append("_Far");
            proc = Manager::sub_7100FD5848(s, actor->instance_name);
            if (proc != nullptr) {
                if (actor->is_remains == 1) {
                    actor->link.acquire(proc, false);
                }
            }
        }
    }
}

const IndicatorActor* Indicator::sub_7100FD54E4(int idx) const {
    if (actors.size() < 1 || idx < 0 || idx >= actors.size())
        return nullptr;
    return actors[idx];
}

const IndicatorActor* Indicator::sub_7100FD5518(int idx) const {
    if (_28.size() < 1 || idx < 0 || idx >= _28.size())
        return nullptr;
    return _28[idx];
}

IndicatorActor::~IndicatorActor() = default;

}  // namespace ksys::qst
