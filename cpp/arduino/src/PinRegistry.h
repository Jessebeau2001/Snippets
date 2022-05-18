#ifndef PINSINGLETON_H
#define PINSINGLETON_H

class PinRegistry
{
protected:
    explicit PinRegistry(const int value) : value_(value) { }

    static PinRegistry * singleton_; // NOLINT(bugprone-dynamic-static-initializers)
    int value_;

public:
    PinRegistry(PinRegistry() & other) = delete;
    void operator= (const PinRegistry &) = delete;
    static PinRegistry * getInstance(const int & value);

    void registerPin()
    {

    }

    int value() const { return value_; }
};

PinRegistry * PinRegistry::singleton_ = nullptr;

PinRegistry * PinRegistry::getInstance(const int & value) {
    if (singleton_ == nullptr)
    {
        singleton_ = new PinRegistry(value);
    }
    return singleton_;
}


#endif