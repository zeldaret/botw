#include "Game/AI/Action/actionAddAutoPlacementCreator.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapAutoPlacementMgr.h"
#include "KingSystem/Map/mapDebug.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

AddAutoPlacementCreator::AddAutoPlacementCreator(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AddAutoPlacementCreator::~AddAutoPlacementCreator() = default;

bool AddAutoPlacementCreator::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AddAutoPlacementCreator::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);

    bool is_box = true;

    if (mInitialised)
        return;

    ksys::act::Actor* actor = mActor;

    if (mShape_m == "Sphere") {
        if (!sead::Mathf::equalsEpsilon(actor->getScale().x, actor->getScale().z, 0.01f)) {
            ksys::map::printDebugMsg(actor, "スケールのXとZは一致していないといけません", nullptr);
            return;
        }
        is_box = false;
    } else if (mShape_m == "Box") {
        is_box = true;
    } else {
        ksys::map::printDebugMsg(actor, "形状は球か箱以外無効です", nullptr);
        return;
    }

    if (!sead::Mathf::equalsEpsilon(ksys::util::dot(sead::Vector3f::ey, actor->getMtx(), 1), 1.0f,
                                    0.01f)) {
        ksys::map::printDebugMsg(actor, "回転はY以外無効です", nullptr);
        return;
    }

    if (ksys::map::AutoPlacementMgr::instance() != nullptr &&
        ksys::map::AutoPlacementMgr::instance()->sub_7100659E40(mActor, mActorName_m, *mCount_m,
                                                                is_box)) {
        actor->setDeleteDistance(actor->getDeleteDistance() + 100.0f);
        mInitialised = true;
    }
}

void AddAutoPlacementCreator::leave_() {
    ksys::act::ai::Action::leave_();

    if (!mInitialised)
        return;

    if (ksys::map::AutoPlacementMgr::instance() != nullptr)
        ksys::map::AutoPlacementMgr::instance()->sub_7100659F94(mActor);

    mInitialised = false;
}

void AddAutoPlacementCreator::loadParams_() {
    getMapUnitParam(&mCount_m, "Count");
    getMapUnitParam(&mActorName_m, "ActorName");
    getMapUnitParam(&mShape_m, "Shape");
}

void AddAutoPlacementCreator::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
