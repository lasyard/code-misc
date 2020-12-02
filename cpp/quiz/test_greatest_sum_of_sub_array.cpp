#include <CppUnitTest.h>

#include "greatest_sum_of_sub_array.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// clang-format off
namespace Test
{
    TEST_CLASS(TestGetLongestCommonSubsequence) {
    public:
        TEST_METHOD(all_negative) {
            int A[] = { -3, -2, -1, -2 };
            Assert::AreEqual(-1, greatestSumOfSubArray(A, sizeof(A) / sizeof(int)));
        }

        TEST_METHOD(cross_negative) {
            int A[] = { 1, 0, 2, -1, 3, -2, -3, 1 };
            Assert::AreEqual(5, greatestSumOfSubArray(A, sizeof(A) / sizeof(int)));
        }

        TEST_METHOD(cross_negative_discard) {
            int A[] = { 1, 0, 2, -1, 3, -2, -3, 1, 6 };
            Assert::AreEqual(7, greatestSumOfSubArray(A, sizeof(A) / sizeof(int)));
        }
    };
}
