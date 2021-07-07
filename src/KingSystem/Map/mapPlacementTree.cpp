#include "KingSystem/Map/mapPlacementTree.h"

namespace ksys::map {

PlacementTree::PlacementTree() = default;

PlacementTree::~PlacementTree() {
    mBuffer.freeBuffer();
    mObjects.freeBuffer();
    delete[] _28;
}

}  // namespace ksys::map
