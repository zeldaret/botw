#pragma once

#include "Game/AI/AI/aiCloseSmallAttackBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CloseSmallAttack : public CloseSmallAttackBase {
    SEAD_RTTI_OVERRIDE(CloseSmallAttack, CloseSmallAttackBase)
public:
    explicit CloseSmallAttack(const InitArg& arg);
    ~CloseSmallAttack() override;

protected:
};

}  // namespace uking::ai
