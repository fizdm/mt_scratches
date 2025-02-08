#include <gtest/gtest.h>

#include <mt_scratches/singletones.h>
#include <mt_scratches/static_polymorphism.h>

using namespace mt_scratches::patterns;

template <typename SingletonT>
void singleton_test()
{
    SingletonT& singletonFirst{SingletonT::GetInstance()};
    SingletonT& singletonSecond{SingletonT::GetInstance()};

    EXPECT_EQ(std::addressof(singletonFirst), std::addressof(singletonSecond));
}

TEST(Patterns, IsCompilable)
{
    [[maybe_unused]] singleton::SingletonCallerExample sce;
    [[maybe_unused]] mixin::MyMixinClass mixinClass;
}

TEST(Patterns, Singleton_Basics)
{
    singleton_test<singleton::NoMtSupportSingleton>();
    singleton_test<singleton::DoubleCheckingSingleton>();
    singleton_test<singleton::MeyersSingleton>();
}

TEST(Patterns_Static_Polymorphism, Type_erasure)
{
    struct A
    {
        char p[20];
    };

    struct B
    {
        char p[5];
    };

    EXPECT_EQ(type_erasure::TypeStorage<A>().ErasedType->GetErasedSize(), sizeof(A));
    EXPECT_EQ(type_erasure::TypeStorage<B>().ErasedType->GetErasedSize(), sizeof(B));
    EXPECT_NE(type_erasure::TypeStorage<A>().ErasedType->GetErasedSize(), sizeof(B));
}

TEST(Patterns_Static_Polymorphism, CRPT)
{
    crtp::Derived derived;
    EXPECT_TRUE((std::is_same_v<decltype(&derived), decltype(derived.get_most_derived())>));
    EXPECT_EQ(typeid(derived), typeid(*derived.get_most_derived()));

    crtp::DeduceThisDerived deduceThisDerived;
    EXPECT_TRUE((std::is_same_v<decltype(&deduceThisDerived), decltype(deduceThisDerived.get_most_derived())>));
    EXPECT_EQ(typeid(deduceThisDerived), typeid(*deduceThisDerived.get_most_derived()));
}