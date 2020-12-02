#include <CppUnitTest.h>

#include "complete_btree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// clang-format off
namespace Test
{
    TEST_CLASS(TestCompleteBtree) {
    public:
        TEST_METHOD(full) {
            int list[] = { 1, 2, 3, 4, 5, 6, 7 };
            Node *tree = makeBtree(list, sizeof(list) / sizeof(int), 0);
            int depth;
            BtreeType type = testBtree(tree, depth);
            destroyBtree(tree);
            Assert::IsTrue(type == FULL);
            Assert::AreEqual(depth, 3);
        }

        TEST_METHOD(full_full_complete) {
            int list[] = { 1, 2, 3, 4, 5 };
            Node *tree = makeBtree(list, sizeof(list) / sizeof(int), 0);
            int depth;
            BtreeType type = testBtree(tree, depth);
            destroyBtree(tree);
            Assert::IsTrue(type == COMPLETE);
            Assert::AreEqual(depth, 3);
        }

        TEST_METHOD(full_complete_complete) {
            int list[] = { 1, 2, 3, 4, 5, 6 };
            Node *tree = makeBtree(list, sizeof(list) / sizeof(int), 0);
            int depth;
            BtreeType type = testBtree(tree, depth);
            destroyBtree(tree);
            Assert::IsTrue(type == COMPLETE);
            Assert::AreEqual(depth, 3);
        }

        TEST_METHOD(complete_full_complete) {
            int list[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
            Node *tree = makeBtree(list, sizeof(list) / sizeof(int), 0);
            int depth;
            BtreeType type = testBtree(tree, depth);
            destroyBtree(tree);
            Assert::IsTrue(type == COMPLETE);
            Assert::AreEqual(depth, 4);
        }

        TEST_METHOD(none) {
            int list[] = { 1, 2, 3, 4, 0, 6, 7 };
            Node *tree = makeBtree(list, sizeof(list) / sizeof(int), 0);
            int depth;
            BtreeType type = testBtree(tree, depth);
            destroyBtree(tree);
            Assert::IsTrue(type == NONE);
            Assert::AreEqual(depth, 3);
        }
    };
}
