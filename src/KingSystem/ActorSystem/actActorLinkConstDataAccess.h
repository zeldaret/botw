#pragma once

namespace ksys {

namespace act {

class BaseProc;

/// Provides read-only access to actor data for safe, multi-threaded access.
class ActorLinkConstDataAccess {
public:
    ~ActorLinkConstDataAccess();

private:
    bool mAcquired = false;
    BaseProc* mProc = nullptr;
};

}  // namespace act

}  // namespace ksys
