/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: IO File
 */

#pragma once

#include "File.hpp"

template<kF::IO::Internal::ResizableContainer Container>
inline bool kF::IO::File::readAll(Container &container) noexcept
{
    using Range = decltype(std::declval<Container>().size());

    const auto expectedSize = fileSize();
    container.resize(static_cast<Range>(expectedSize));
    const auto readSize = read(
        reinterpret_cast<std::uint8_t *>(container.data()),
        reinterpret_cast<std::uint8_t *>(container.data()) + expectedSize
    );
    return readSize == expectedSize;
}

template<kF::IO::Internal::ResizableContainer Container>
inline Container kF::IO::File::readAll(void) noexcept
{
    Container container;
    if (!readAll(container)) [[unlikely]]
        container.clear();
    return container;
}