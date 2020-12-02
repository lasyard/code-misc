// Add $(VCInstallDir)UnitTest\include to Additional Include Directories
// Add $(VCInstallDir)UnitTest\lib to Additional Library Directories
// Application type must be dll

#include <CppUnitTest.h>

#include "longest_symmetrical_length.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// clang-format off
namespace Test
{
    TEST_CLASS(TestGetLongestSymmetricalLength) {
    public:
        TEST_METHOD(n_u_l_l) {
            Assert::AreEqual(0, longestSymmetricalLength((char *)0));
        }

        TEST_METHOD(empty) {
            Assert::AreEqual(0, longestSymmetricalLength(""));
        }

        TEST_METHOD(a) {
            Assert::AreEqual(1, longestSymmetricalLength("a"));
        }

        TEST_METHOD(abbacdc) {
            Assert::AreEqual(4, longestSymmetricalLength("abbacdc"));
        }

        TEST_METHOD(abacddcabadc) {
            Assert::AreEqual(10, longestSymmetricalLength("abacddcabadc"));
        }
    };
}
