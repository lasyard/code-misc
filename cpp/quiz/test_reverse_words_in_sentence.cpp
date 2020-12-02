// Add $(VCInstallDir)UnitTest\include to Additional Include Directories
// Add $(VCInstallDir)UnitTest\lib to Additional Library Directories
// Application type must be dll

#include <CppUnitTest.h>

#include "reverse_words_in_sentence.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// clang-format off
namespace Test
{
    TEST_CLASS(TestReverseWordsInSentence) {
    public:
        TEST_METHOD(n_u_l_l) {
            reverseWordsInSentence((char *)0);
        }

        TEST_METHOD(empty) {
            char text[] = "";
            reverseWordsInSentence(text);
            Assert::AreEqual("", text);
        }

        TEST_METHOD(spaces) {
            char text[] = "     ";
            reverseWordsInSentence(text);
            Assert::AreEqual("     ", text);
        }

        TEST_METHOD(I_am_superman) {
            char text[] = "I am superman. ";
            reverseWordsInSentence(text);
            Assert::AreEqual(" superman. am I", text);
        }
    };
}
