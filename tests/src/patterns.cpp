#include <gtest/gtest.h>

#include <mt_scratches/singletones.h>

template <typename SingletonT>
void singleton_test()
{
    SingletonT& singletonFirst{SingletonT::GetInstance()};
    SingletonT& singletonSecond{SingletonT::GetInstance()};

    EXPECT_EQ(std::addressof(singletonFirst), std::addressof(singletonSecond));
}

TEST(Patterns, Singleton_Basics)
{
    singleton_test<mt_scratches::singleton::NoMtSupportSingleton>();
    singleton_test<mt_scratches::singleton::DoubleCheckingSingleton>();
    singleton_test<mt_scratches::singleton::MeyersSingleton>();
}
