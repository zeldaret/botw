#pragma once

#include <evfl/Action.h>
#include <evfl/Query.h>
#include "Game/AutoPlacement/StringViewCompare.h"

// These are inferred interfaces to the original undecompiled placement handlers.
// Names describe independently identified binding roles, rather than original symbols.
namespace uking {

namespace AutoPlacementFlowHandlers {
void createData(const evfl::ActionArg& arg, evfl::ActionDoneHandler done_handler);
void nearCreate(const evfl::ActionArg& arg, evfl::ActionDoneHandler done_handler);
void appearWeatherRate(const evfl::ActionArg& arg, evfl::ActionDoneHandler done_handler);
void equipCategory(const evfl::ActionArg& arg, evfl::ActionDoneHandler done_handler);
void defaultAction(const evfl::ActionArg& arg, evfl::ActionDoneHandler done_handler);
int groundNorm(const evfl::QueryArg& arg);
int groundMat(const evfl::QueryArg& arg);
int treeRate(const evfl::QueryArg& arg);
int posHeight(const evfl::QueryArg& arg);
int waterDepth(const evfl::QueryArg& arg);
int routeDistance(const evfl::QueryArg& arg);
int grassHeight(const evfl::QueryArg& arg);
int waterSurface(const evfl::QueryArg& arg);
int playerRideHorse(const evfl::QueryArg& arg);
int ecoAreaActorName(const evfl::QueryArg& arg);
int waterSubMat(const evfl::QueryArg& arg);
int checkGameData(const evfl::QueryArg& arg);
int checkPouchItemCount(const evfl::QueryArg& arg);
int checkPouchItemCountFromActor(const evfl::QueryArg& arg);
int timeType(const evfl::QueryArg& arg);
int railDistance(const evfl::QueryArg& arg);
int waterDistance(const evfl::QueryArg& arg);
int navMeshFace(const evfl::QueryArg& arg);
int defaultQuery(const evfl::QueryArg& arg);
}  // namespace AutoPlacementFlowHandlers

}  // namespace uking
