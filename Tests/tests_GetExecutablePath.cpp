/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Unit tests of File
 */

#include <filesystem>

#include <gtest/gtest.h>

#include <Kube/Core/String.hpp>
#include <Kube/IO/GetExecutablePath.hpp>


using namespace kF;

TEST(GetExecutablePath, Basics)
{
    const auto str = IO::GetExecutablePath<Core::String<>>();

    ASSERT_GT(str.size(), 0);
    ASSERT_TRUE(std::filesystem::exists(str.toView()));
}


TEST(GetExecutableDirectory, Basics)
{
    const auto str = IO::GetExecutableDirectory<Core::String<>>();

    ASSERT_GT(str.size(), 0);
    ASSERT_TRUE(std::filesystem::exists(str.toView()));
}
