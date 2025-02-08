/**
 * Copyright (c) 2025 Dmitry.Popov. All rights reserved.
 */

#pragma once

#include <memory>

namespace mt_scratches::patterns
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

    TypeStorage() : ErasedType{std::make_unique<ErasedHolder<T>>()}
    {
    }
};
} // namespace mt_scratches::patterns