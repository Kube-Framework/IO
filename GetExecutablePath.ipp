/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: IO GetExecutablePath
 */

#include <whereami.h>
#include <Kube/Core/Abort.hpp>

#include "GetExecutablePath.hpp"

template<typename Type>
Type kF::IO::GetExecutablePath(void) noexcept
{
    // Init container
    const auto expectedSize = wai_getExecutablePath(nullptr, 0, nullptr);
    if (expectedSize == -1) [[unlikely]]
        return Type {};
    Type container(expectedSize);

    // Query path
    const auto finalSize = wai_getExecutablePath(container.data(), static_cast<int>(container.size()), nullptr);
    kFEnsure(finalSize == expectedSize,
        "IO::GetExecutableDirectory: Couldn't retreive executable path");

    return container;
}

template<typename Type>
Type kF::IO::GetExecutableDirectory(void) noexcept
{
    // Init container
    const auto expectedSize = wai_getExecutablePath(nullptr, 0, nullptr);
    if (expectedSize == -1) [[unlikely]]
        return Type {};
    Type container(expectedSize);

    // Query path
    int dirIndex {};
    const auto finalSize = wai_getExecutablePath(container.data(), static_cast<int>(container.size()), &dirIndex);
    kFEnsure(finalSize == expectedSize,
        "IO::GetExecutableDirectory: Couldn't retreive executable path");

    // Remove executable part
    container.erase(container.begin() + dirIndex, container.end());

    return container;
}
