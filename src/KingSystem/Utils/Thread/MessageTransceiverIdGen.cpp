#include "KingSystem/Utils/Thread/MessageTransceiverIdGen.h"

namespace ksys {

u32 MesTransceiverIdGen::sId{};

MesTransceiverIdGen::MesTransceiverIdGen() : mTransceiverId(sId, this) {}

MesTransceiverIdGen::~MesTransceiverIdGen() = default;

MesTransceiverId* MesTransceiverIdGen::getId() {
    return &mTransceiverId;
}

bool MesTransceiverIdGen::m1(void*) {
    return true;
}

void MesTransceiverIdGen::m2(void* x) {}

}  // namespace ksys
