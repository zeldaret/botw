#include <heap/seadDisposer.h>
#include <thread/seadCriticalSection.h>

namespace ksys {

class AutoDim {
    SEAD_SINGLETON_DISPOSER(AutoDim)
    AutoDim() = default;

public:
    void setEnabled(bool enable);
    bool isEnabled() const;

private:
    bool mEnabled = true;
    sead::CriticalSection mCS{};
};

}  // namespace ksys
