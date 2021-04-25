#include "KingSystem/Resource/resResourceAttClient.h"

namespace ksys::res {

AttClient::~AttClient() {
    // TODO
    mChecks.freeBuffer();
}

void AttClient::doCreate_(u8*, u32, sead::Heap*) {}

}  // namespace ksys::res
