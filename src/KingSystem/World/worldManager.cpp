#include "KingSystem/World/worldManager.h"

namespace ksys::world {

SEAD_SINGLETON_DISPOSER_IMPL(Manager)

// NON_MATCHING: stores in a different order (handwritten assignments?) but should be equivalent
Manager::Manager() = default;

}  // namespace ksys::world
