#pragma once

namespace ksys {

class BasicProfiler {
public:
    class Scope {
    public:
        explicit Scope(const char* description) : mDescription(description) { push(description); }
        ~Scope() { pop(mDescription); }
        Scope(const Scope&) = delete;
        auto operator=(const Scope&) = delete;

    private:
        const char* mDescription;
    };

    static void push(const char* description);
    static void pop(const char* description);
};

}  // namespace ksys
