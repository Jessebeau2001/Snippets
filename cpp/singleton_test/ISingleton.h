#ifndef ISINGLETON_H
#define ISINGLETON_H

class ISingleton
{
protected:
    ISingleton() { }

    static ISingleton * singleton_;

public:
    ISingleton(ISingleton & other) = delete;
    void operator=(const ISingleton &) = delete;
    static ISingleton * getInstance();
};

ISingleton * ISingleton::singleton_ = nullptr;

ISingleton * ISingleton::getInstance()
{
    if (singleton_ == nullptr)
        singleton_ = new ISingleton();

    return singleton_;
}

#endif
