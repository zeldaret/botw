#include "KingSystem/ActorSystem/actIDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace ksys::act {

void IDamageManager::addDamageCallback(s32 eventId, DamageCallback* callback) {
    if (mCallbacks.isBufferReady() && !callback->mDamageManager) {
        DamageCallback* next = mCallbacks[eventId];
        if (next) {
            DamageCallback* prev;
            while (next) {
                prev = next;
                next = next->mNext;
            }

            prev->mNext = callback;
            callback->mPrev = prev;
        } else {
            mCallbacks[eventId] = callback;
        }

        callback->mDamageManager = this;
        callback->mEventId = eventId;
    }
}

void IDamageManager::removeDamageCallback(DamageCallback* callback) {
    if (!mCallbacks.isBufferReady() || callback->mDamageManager != this) {
        return;
    }

    u32 event_id = callback->mEventId;
    DamageCallback* current_callback = mCallbacks[event_id];
    if (!current_callback) {
        if (mActor) {
            // Logging about trying to remove missing callback?
            mActor->nullsub_4649();
        }

        callback->mDamageManager = nullptr;
        callback->mEventId = -1;
#ifdef MATCHING_HACK_NX_CLANG
        asm("");  // Stop optimizing with the other clear below
#endif
        return;
    }

    if (current_callback == callback) {
        mCallbacks[event_id] = callback->mNext;
        current_callback = mCallbacks[event_id];
        if (current_callback) {
            current_callback->mPrev = nullptr;
        }
#ifdef MATCHING_HACK_NX_CLANG
        asm("");  // Stop re-using variables, generating an extra register
#endif
    } else {
        do {
            if (current_callback == callback) {
                DamageCallback* prev = callback->mPrev;
                if (prev) {
                    prev->mNext = callback->mNext;
                }
                DamageCallback* next = callback->mNext;
                if (next) {
                    next->mPrev = callback->mPrev;
                }
            }
            current_callback = current_callback->mNext;
        } while (current_callback);
    }
    callback->mNext = nullptr;
#ifdef MATCHING_HACK_NX_CLANG
    asm("");  // Stop combining the mNext and mDamageManager
#endif
    callback->mDamageManager = nullptr;
    callback->mEventId = -1;
    callback->mPrev = nullptr;
}

}  // namespace ksys::act
