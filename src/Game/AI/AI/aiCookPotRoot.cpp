#include "Game/AI/AI/aiCookPotRoot.h"
#include "Game/DLC/aocHardModeManager.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/ActorSystem/Attention/actAttention.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldManager.h"

namespace uking::ai {

CookPotRoot::CookPotRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CookPotRoot::~CookPotRoot() = default;

// NON_MATCHING
bool CookPotRoot::init_(sead::Heap* heap) {
    auto* ingredients =
        new (heap, std::nothrow) sead::FixedSafeString<64>[CookingMgr::NumIngredientsMax];
    mCookIngredients.setBuffer(CookingMgr::NumIngredientsMax, ingredients);
    if (!mCookIngredients.isBufferReady()) {
        return false;
    }
    if (*mInitBurnState_m) {
        // TODO
    }
    mActor->getChemicalStuff();
    mProcLink.reset();
    return true;
}

void CookPotRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void CookPotRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CookPotRoot::loadParams_() {
    getMapUnitParam(&mInitBurnState_m, "InitBurnState");
    getAITreeVariable(&mCurrentCookResultHolder_a, "CurrentCookResultHolder");
}

// NON_MATCHING
bool CookPotRoot::handleMessage_(const ksys::Message& message) {
    if (message.getType().value == (u32)ksys::act::AttActionCode::Cook) {
        // 着火: "ignition" or "on fire"
        // This is checking if the pot is lit.
        if (isCurrentChild("着火")) {
            // TODO: sub_7100EDC4B8
            // TODO: GameSceneSubsys12 class
            // GameSceneSubsys12 handles carried items.
            // This needs to check if the player is targeting the pot.
            if (true /* TODO */) {
                if (!_48 /* TODO */) {
                    _48 = true;

                    const int num_ingredients = 5;  // TODO
                    auto* cooking_mgr = CookingMgr::instance();

                    cooking_mgr->resetArgCookData(mCookArg, mCookIngredients, num_ingredients,
                                                  mCookItem);

                    CookingMgr::BoostArg boost_arg{.always_boost = false,
                                                   .enable_random_boost = true};

                    if (ksys::world::Manager::instance()->getEnvMgr()->isInBloodMoonTimeRange()) {
                        boost_arg.always_boost = true;
                    }

                    if (cooking_mgr->cook(mCookArg, mCookItem, boost_arg)) {
                        if (const auto* hard_mode_manager = aoc::HardModeManager::instance()) {
                            if (hard_mode_manager->checkFlag(
                                    aoc::HardModeManager::Flag::EnableHardMode)) {
                                if (hard_mode_manager->isHardModeChangeOn(
                                        aoc::HardModeManager::HardModeChange::NerfHpRestore)) {
                                    hard_mode_manager->nerfHpRestore(&mCookItem.life_recover);
                                }
                            }
                        }
                        if (true /* TODO: callCookingDemo */) {
                            ui::PauseMenuDataMgr::instance()->removeGrabbedItems();
                            cooking_mgr->setCookItem(mCookItem);
                            mHasFinishedCookItem = true;
                            return true;
                        }
                        _48 = false;
                        mHasFinishedCookItem = false;
                        // TODO
                    } else {
                        _48 = false;
                        mHasFinishedCookItem = false;
                        // TODO
                    }
                }
            }
        }
    }

    if (message.getType().value != (u32)ksys::act::AttActionCode::KillTime) {
        return false;
    }

    // TODO: callDemo007_1
    return isCurrentChild("着火");
}

}  // namespace uking::ai
