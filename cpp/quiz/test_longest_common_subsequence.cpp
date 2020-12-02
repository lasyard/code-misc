// Add $(VCInstallDir)UnitTest\include to Additional Include Directories
// Add $(VCInstallDir)UnitTest\lib to Additional Library Directories
// Application type must be dll

#include <CppUnitTest.h>

#include "longest_common_subsequence.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// clang-format off
namespace Test
{
    TEST_CLASS(TestGetLongestCommonSubsequence) {
    public:
        TEST_METHOD(n_u_l_l_abc) {
            Assert::AreEqual(0, longestCommonSubsequence((char *)0, "abc"));
        }

        TEST_METHOD(empty_abc) {
            Assert::AreEqual(0, longestCommonSubsequence("", "abc"));
        }

        TEST_METHOD(abc_defghi) {
            Assert::AreEqual(0, longestCommonSubsequence("abc", "defghi"));
        }

        TEST_METHOD(adbec_deafgbhci) {
            Assert::AreEqual(3, longestCommonSubsequence("adbec", "deafgbhci"));
        }

        TEST_METHOD(abcd_aabdcfgahcid) {
            Assert::AreEqual(4, longestCommonSubsequence("abcd", "aabdcfgahcid"));
        }
    };
}
