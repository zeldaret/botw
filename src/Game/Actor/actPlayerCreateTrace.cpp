#include "Game/Actor/actPlayerCreateTrace.h"

namespace uking::act {

PlayerCreateTraceScope::PlayerCreateTraceScope(PlayerCreateTrace* trace,
                                               const sead::SafeString& name,
                                               const sead::SafeString& caller, s32 level) {
    mTrace = trace;
}

PlayerCreateTraceScope::~PlayerCreateTraceScope() {
    // force D1 to be non-trivial
    ;
}

PlayerCreateTrace* PlayerCreateTrace::make(const sead::SafeString& name, s32 level) {
    return nullptr;
}

// void PlayerCreateTracerStub::destroyRoot(PlayerCreateTracerStub ** tracker) { }
void PlayerCreateTracer::finish() {}

}  // namespace uking::act
