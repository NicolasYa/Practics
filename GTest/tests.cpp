#include "pch.h"

#include "../safe_queue.h"


using TestQueue = typename SafeQueue<int>;
using Result = typename TestQueue::Result;
using Item = typename TestQueue::Item;

//--------------------------------------------------------------------------

TEST(SafeQueueTest, Closed) {
    TestQueue q(0);
    q.close();
    ASSERT_EQ(q.get_closed(), true);
    Item item = -1;
    EXPECT_EQ(q.push(1), Result::Closed);
    EXPECT_EQ(q.pop(item), Result::Closed);
    EXPECT_EQ(item, -1);
    EXPECT_EQ(q.blocked_push(1), Result::Closed);
    EXPECT_EQ(q.blocked_pop(item), Result::Closed);
    EXPECT_EQ(item, -1);
}

//--------------------------------------------------------------------------

TEST(SafeQueueTest, ZeroMaxSize) {
    TestQueue q(0);
    EXPECT_EQ(q.get_closed(), true);
}

//--------------------------------------------------------------------------

TEST(SafeQueueTest, ToUpperLimit) {
    TestQueue q(5);
    for (auto i = 0; i < q.get_max_size(); ++i) {
        ASSERT_EQ(q.push(i), Result::Success);
    }
    ASSERT_EQ(q.push(100), Result::Full);
}

//--------------------------------------------------------------------------

TEST(SafeQueueTest, ToLowerLimit) {
    TestQueue q(5);
    for (auto i = 0; i < q.get_max_size(); ++i) {
        ASSERT_EQ(q.push(i), Result::Success);
    }
    int value;
    for (auto i = 0; i < q.get_max_size(); ++i) {
        ASSERT_EQ(q.pop(value), Result::Success);
    }
    ASSERT_EQ(q.pop(value), Result::Empty);
}

//--------------------------------------------------------------------------

TEST(SafeQueueTest, FIFO) {
    constexpr unsigned int QueueMaxSize = 1000;

    TestQueue q(QueueMaxSize);

    for (int i = 0; i < QueueMaxSize; i++) {
        EXPECT_EQ( q.push(i), Result::Success);
    }
    EXPECT_EQ(q.push(QueueMaxSize), Result::Full);


    for (int i = 0; i < QueueMaxSize; i++) {
        int item;
        EXPECT_EQ( q.pop(item), Result::Success);
        EXPECT_EQ(item, i );
    }
    int item;
    EXPECT_EQ(q.pop(item), Result::Empty);
}

//--------------------------------------------------------------------------

TEST(SafeQueueTest, find_if) {
    constexpr int QueueMaxSize = 10;

    TestQueue q(QueueMaxSize);
    for (int i = 0; i < QueueMaxSize; i++) {
        ASSERT_EQ(q.push(i), Result::Success);
    }

    constexpr int ExistedItem = QueueMaxSize - 1;
    constexpr int NotExistedItem = -1;

   {
        const auto found{ q.find_if(
            [ExistedItem](const TestQueue::Item& i) { return i == ExistedItem; }) 
        };
        EXPECT_EQ(found.has_value() && *found == ExistedItem, true);
   }
   {
        const auto found{ q.find_if(
            [NotExistedItem](const TestQueue::Item& i) { return i == NotExistedItem; }) 
        };
        EXPECT_EQ(found.has_value(), false);
    }
    {
        const auto found{ q.find_if__templated_version(
            [ExistedItem](const TestQueue::Item& i)->bool { return i == ExistedItem; }) 
        };
        EXPECT_EQ(found.has_value() && *found == ExistedItem, true);
    }
    {
        const auto found{ q.find_if__templated_version(
            [NotExistedItem](const TestQueue::Item& i)->bool { return i == NotExistedItem; })
        };
        EXPECT_EQ(found.has_value(), false);
    }
}

//--------------------------------------------------------------------------
