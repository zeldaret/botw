#pragma once

namespace ksys {

// FIXME: incomplete; requires GameData
class ProductReporter {
public:
    ProductReporter() = default;
    virtual ~ProductReporter();

    static bool getSomeBool();
};

}  // namespace ksys
