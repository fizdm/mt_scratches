/**
 * Copyright (c) 2025 Dmitry.Popov. All rights reserved.
 */

#pragma once

#include <memory>

namespace mt_scratches::patterns
{
namespace type_erasure
{
    /**
     *
     * Why do we need to erase type?
     * The answer is: How would you store different types that doesn't have any common bases?
     *                How would you make different compile-time behaviour and store it together?
     */
    template <typename T>
    class TypeStorage
    {
    private:
        struct IErased
        {
            virtual size_t GetErasedSize() = 0;
            virtual ~IErased() = default;
        };

        template <typename ErasedType>
        struct ErasedHolder : public IErased
        {
            virtual size_t GetErasedSize()
            {
                return sizeof(ErasedType);
            }
        };

    public:
        std::unique_ptr<IErased> ErasedType;

        TypeStorage()
            : ErasedType{std::make_unique<ErasedHolder<T>>()}
        {
        }
    };
} // namespace type_erasure

namespace crtp
{
    template <typename T>
    class Base
    {
    public:
        T* get_most_derived()
        {
            return static_cast<T*>(this);
        }
    };

    class Derived : public Base<Derived>
    {
    };

    /**
     * Deducing this (after c++23)
     * For what?
     *  this can be cv-qualified but we need pure this and template substitution doesn't help
     */

    class DeduceThisBase
    {
    public:
        template <typename Self>
        auto* get_most_derived(this Self&& self)
        {
            return &self;
        }
    };

    class DeduceThisDerived : public DeduceThisBase
    {
    };

} // namespace crtp


namespace mixin
{
    /**
     * Why?
     *  Add methods to class without modifying base interface or inherit from this class
     */

    template <typename... Types>
    class BaseClass : public Types...
    {
    };

    struct Color
    {
    };
    struct Icon
    {
    };
    struct Material
    {
    };

    using MyMixinClass = BaseClass<Color, Icon, Material>;
} // namespace mixin
} // namespace mt_scratches::patterns