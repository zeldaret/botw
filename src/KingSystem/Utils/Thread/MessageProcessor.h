#pragma once

namespace ksys {

class Message;

class MessageProcessor {
public:
    class Logger {
    public:
        Logger() = default;
        virtual ~Logger() = default;
        virtual void log(const Message& message, bool success) = 0;
    };

    /// @param logger Must be non null.
    explicit MessageProcessor(Logger* logger);
    virtual ~MessageProcessor();
    virtual bool process(Message* message);

private:
    Logger* mLogger{};
};

}  // namespace ksys
