#pragma once

#include "KingSystem/Utils/Thread/MessageTransceiverIdGenEx.h"

namespace ksys {

class MesTransceiverIdGenExAdapter : public MesTransceiverIdGenEx {
    SEAD_RTTI_OVERRIDE(MesTransceiverIdGenExAdapter, MesTransceiverIdGenEx)
public:
    explicit MesTransceiverIdGenExAdapter(MesTransceiverIdGen* wrapped);
    ~MesTransceiverIdGenExAdapter() override;

protected:
    bool m6(void* x) override;
    void m7(void* x) override;

private:
    MesTransceiverIdGen* mGenerator;
};

}  // namespace ksys
