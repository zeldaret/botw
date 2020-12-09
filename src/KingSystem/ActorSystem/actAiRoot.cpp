#include "KingSystem/ActorSystem/actAiRoot.h"

namespace ksys::act::ai {

RootAi::RootAi(const InitArg& arg) : Ai(arg) {
    mBehaviorsByStopAndCalcTiming[0].fill({});
    mBehaviorsByStopAndCalcTiming[1].fill({});
}

RootAi::~RootAi() {
    mQueries.finalize();
    mBehaviors.finalize();
    mAis.finalize();
    mActions.finalize();
    if (_140)
        delete _140;
}

bool RootAi::loadMapUnitParams(const AIDef& def, sead::Heap* heap) {
    return mMapUnitParams.load(*mActor, def, heap, AIDefInstParamKind::MapUnit);
}

bool RootAi::loadAITreeParams(const AIDef& def, sead::Heap* heap) {
    return mAiTreeParams.load(*mActor, def, heap, AIDefInstParamKind::AITree);
}

}  // namespace ksys::act::ai
