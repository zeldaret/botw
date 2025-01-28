#include "KingSystem/ActorSystem/actPlayerInfo.h"
namespace ksys::act {
// these are separate from actPlayerInfo.cpp so clang doesn't inline/dedupe them
[[gnu::noinline]] PlayerInfoBase::PlayerInfoBase() = default;
[[gnu::noinline]] PlayerInfoBase::~PlayerInfoBase() = default;
}  // namespace ksys::act
