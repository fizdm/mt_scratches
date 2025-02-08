#include <gtest/gtest.h>

#include <mt_scratches/singletones.h>
#include <mt_scratches/static_polymorphism.h>

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

TEST(Patterns, Static_Polymorphism)
{
    struct A
    {
        char p[20];
    };

    struct B
    {
        char p[5];
    };

    EXPECT_EQ(mt_scratches::patterns::TypeStorage<A>().ErasedType->GetErasedSize(), sizeof(A));
    EXPECT_EQ(mt_scratches::patterns::TypeStorage<B>().ErasedType->GetErasedSize(), sizeof(B));
    EXPECT_NE(mt_scratches::patterns::TypeStorage<A>().ErasedType->GetErasedSize(), sizeof(B));
}
