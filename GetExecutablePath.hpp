/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: IO GetExecutablePath
 */

#pragma once

#include <Kube/Core/Utils.hpp>

namespace kF::IO
{
    /** @brief Default guessed path size */
    constexpr std::size_t DefaultPathSize = 260;


    /** @brief Get executable path */
    template<typename Type>
    [[nodiscard]] Type GetExecutablePath(void) noexcept;

    /** @brief Get executable directory */
    template<typename Type>
    [[nodiscard]] Type GetExecutableDirectory(void) noexcept;
}

#include "GetExecutablePath.ipp"