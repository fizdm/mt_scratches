/**
 * Copyright (c) 2025 Dmitry.Popov. All rights reserved.
 */

#include <mt_scratches/singletones.h>
#include <mutex>

namespace mt_scratches::patterns::singleton
{
NoMtSupportSingleton* NoMtSupportSingleton::_instance = nullptr;

NoMtSupportSingleton& NoMtSupportSingleton::GetInstance()
{
    if (_instance == nullptr)
    {
        _instance = new NoMtSupportSingleton(); // Not thread safe
    }

    return *_instance;
}

static std::mutex double_check_mutex;
DoubleCheckingSingleton* DoubleCheckingSingleton::_instance = nullptr;

DoubleCheckingSingleton& DoubleCheckingSingleton::GetInstance()
{
    if (_instance == nullptr)
    {
        std::lock_guard lock(double_check_mutex); // slow
        if (_instance == nullptr)
            _instance = new DoubleCheckingSingleton();
    }

    return *_instance;
}


} // namespace mt_scratches::singleton