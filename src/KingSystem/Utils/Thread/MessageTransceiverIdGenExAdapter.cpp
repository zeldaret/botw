#include "KingSystem/Utils/Thread/MessageTransceiverIdGenExAdapter.h"

namespace ksys {

MesTransceiverIdGenExAdapter::MesTransceiverIdGenExAdapter(MesTransceiverIdGen* wrapped)
    : mGenerator(wrapped) {}

MesTransceiverIdGenExAdapter::~MesTransceiverIdGenExAdapter() = default;

bool MesTransceiverIdGenExAdapter::m6(void* x) {
    return mGenerator->m1(x);
}

void MesTransceiverIdGenExAdapter::m7(void* x) {
    return mGenerator->m2(x);
}

}  // namespace ksys
