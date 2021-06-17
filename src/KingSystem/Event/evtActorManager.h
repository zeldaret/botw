#pragma once

namespace evfl {
struct ActionArg;
class ActionDoneHandler;
struct QueryArg;
}  // namespace evfl

namespace ksys::evt {

// TODO
class ActorManager {
public:
    static void actionHandler(const evfl::ActionArg& arg, evfl::ActionDoneHandler handler);
    static int queryHandler(const evfl::QueryArg& arg);
};

}  // namespace ksys::evt
