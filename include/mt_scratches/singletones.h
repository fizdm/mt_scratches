/**
 * Copyright (c) 2025 Dmitry.Popov. All rights reserved.
 */

#pragma once

/**
 * THEORY:
 * Singleton and SOLID:
 *   - Single responsibility -- violates
 *   - Open/closure principle -- violates, due to single construction point
 *   - Liskov substitution -- violates, due to meaning of singleton (if we can substitute different realizations,
 *                                                                   we don't have single class)
 *   - Interface segregation -- we cannot use interfaces
 *   - Dependency inversion -- violates, due to single construction point
 *
 *
 * Alternatives:
 *   - Static fabric
 *   - Static polymorphism
 *   - Service locator -- but somehow you should initialize this container T_T
 *   - Dependency Injection
 */

namespace mt_scratches::patterns::singleton
{
class NoMtSupportSingleton
{
public:
    static NoMtSupportSingleton& GetInstance();

    NoMtSupportSingleton(NoMtSupportSingleton const&) = delete;
    NoMtSupportSingleton& operator=(NoMtSupportSingleton const&) = delete;

private:
    static NoMtSupportSingleton* _instance;

    NoMtSupportSingleton() = default;
    ~NoMtSupportSingleton() = default;
};

class DoubleCheckingSingleton
{
public:
    static DoubleCheckingSingleton& GetInstance();

    DoubleCheckingSingleton(DoubleCheckingSingleton const&) = delete;
    DoubleCheckingSingleton& operator=(DoubleCheckingSingleton const&) = delete;

private:
    static DoubleCheckingSingleton* _instance;

    DoubleCheckingSingleton() = default;
    ~DoubleCheckingSingleton() = default;
};

class MeyersSingleton
{
public:
    static MeyersSingleton& GetInstance()
    {
        static MeyersSingleton instance;
        return instance;
    }

    MeyersSingleton(MeyersSingleton const&) = delete;
    MeyersSingleton& operator=(MeyersSingleton const&) = delete;

private:
    MeyersSingleton() = default;
    ~MeyersSingleton() = default;
};

/// Static Fabric
struct Dummy
{
};

inline Dummy& GetDummy()
{
    static Dummy dummy;
    return dummy;
}

/// Static Polymorphism
class Interface
{
public:
    virtual ~Interface() = default;
    virtual void call() = 0;
};

class CallRealization final : public Interface
{
public:
    void call() override
    {
    }
};

class SingletonCallerExample
{
public:
    static Interface& getInterface()
    {
        static Interface* instance;
        if (instance == nullptr)
            instance = new CallRealization(); // Memory leak and not thread-safe

        return *instance;
    }

    static void doCall()
    {
        getInterface().call();
    }
};

} // namespace mt_scratches::singleton
