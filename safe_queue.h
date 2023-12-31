//
//  safe_queue.cpp : This file contains class SafeQueue for implement thread safe access to queue
//
//  Author: Victor V. Rudakov
// 
//  class SafeQueue<Item> - template of queue for desired item type (Item)
//
//  Class members:
//
//  SafeQueue::Result - result code for queue operations
// 
//  SafeQueue( size_type ) - construct queue with desired size
// 
//  SafeQueue::push         - implemet non-blocked push item to queue
//  SafeQueue::blocked_push - implemet blocked push item to queue
// 
//  SafeQueue::pop          - implemet non-blocked pop item from queue
//  SafeQueue::blocked_pop  - implemet blocked pop item from queue
// 
//  SafeQueue::close - prevent queue from any changing and release all waiting threads
//  SafeQueue::get_size - return queue size (thread safe)
// 
//  SafeQueue::find_if - implement thread safe standart search STL algorithm (std::find_if)
//  SafeQueue::find_if__templated_version - templated implementation of SafeQueue::find_if
// 

#ifndef SAFEQUEUE_H
#define SAFEQUEUE_H

#include <deque>
#include <mutex>
#include <condition_variable>
#include <optional>
#include <functional>
#include <cassert>

template < class T >
class SafeQueue {
public:
    using Item = T;
    using Queue = typename std::deque<T>;
    using size_type = typename Queue::size_type;
    using iterator = typename Queue::iterator;
    using Optional = typename std::optional<Item>;
    using Callback = typename std::function<void(const Item& item)>;
    using Callbacks = typename std::vector<Callback>;
    using Locker = typename std::lock_guard<std::mutex>;
    using UniqueLocker = typename std::unique_lock<std::mutex>;

    enum class Result {
        Success,
        Closed,
        Full,
        Empty
    };

    SafeQueue(const SafeQueue&) = delete;
    SafeQueue& operator=(const SafeQueue&) = delete;
    
    explicit SafeQueue(size_type size)
        : max_size_(size) 
    {
        if (max_size_ <= 0)  // non usable queue
            close();
    }

    Result push(const Item& item);
    Result blocked_push(const Item& item);
    Result pop(Item& item);
    Result blocked_pop(Item& item);

    void close();

    // Ordinary function version of item search:
    using Predicate = typename std::function<bool(const Item& i)>;

    Optional find_if(const Predicate& predicate) {
        Locker locker(mutex_);

        auto found = std::find_if(queue_.begin(), queue_.end(), predicate);
        return (found == queue_.end()) ? std::nullopt : Optional(*found);
    }

    // Templated function version of item search:
    template<class Predicate>
    Optional find_if__templated_version(const Predicate& predicate) {
        Locker locker(mutex_);

        auto found = std::find_if(queue_.begin(), queue_.end(), predicate);
        return (found == queue_.end()) ? std::nullopt : Optional(*found);
    }

    void register_push_callback(Callback callback) {
        push_callbacks_.push_back(callback);
    }

    void register_pop_callback(Callback callback) {
        pop_callbacks_.push_back(callback);
    }

    size_type get_size() const {
        Locker locker(mutex_);
        return size();
    }

    size_type get_max_size() const {
        return max_size_;
    }

    bool get_closed() const {
        Locker locker(mutex_);
        return is_closed();
    }

private:
    size_type size() const {
        return queue_.size();
    }

    void push_data(const Item & item) {
        queue_.push_back(item); 
        on_push(item);
    } 

    Item pop_data() {
        Item item = queue_.front();
        queue_.pop_front(); 
        on_pop(item);
        return std::move(item);
    }
    
    void on_push(const Item& item) {
        for (const auto& c : push_callbacks_)
            c(item);
    }

    void on_pop(const Item& item) {
        for (const auto& c : pop_callbacks_)
            c(item);
    }

    bool is_closed() const { 
        return closed_; 
    }

    bool is_empty() const {
        return queue_.empty(); 
    }

    bool is_full() const {
        return queue_.size() >= max_size_; 
    }

    const size_type         max_size_;
    volatile bool           closed_{false};
    Queue                   queue_;
    mutable std::mutex      mutex_;
    std::condition_variable push_enable_;
    std::condition_variable pop_enable_;

    Callbacks               push_callbacks_;
    Callbacks               pop_callbacks_;
};

//--------------------------------------------------------------------------

template < class T >
void SafeQueue<T>::close() {
    UniqueLocker locker(mutex_);
    closed_ = true;
    locker.unlock();           // unlock before notification to minimize mutex contention
    pop_enable_.notify_all();  // notify all waiting threads
    push_enable_.notify_all();
}

//--------------------------------------------------------------------------

template < class T >
typename SafeQueue<T>::Result SafeQueue<T>::push(const Item& item) {
    UniqueLocker locker(mutex_);
    if (is_closed()) {
        return Result::Closed;
    }
    if (is_full()) {
        return Result::Full;
    }
    push_data(item);
    locker.unlock();          // unlock before notification to minimize mutex contention
    pop_enable_.notify_one(); // notify one waiting thread
    return Result::Success;
}

//--------------------------------------------------------------------------

template < class Item >
typename SafeQueue<Item>::Result SafeQueue<Item>::blocked_push(const Item& item) {
    UniqueLocker locker(mutex_);
    if (is_closed()) {
        return Result::Closed;
    }
    while (is_full()) {
        if (is_closed()) {
            return Result::Closed;
        }
        push_enable_.wait(locker); // release lock and go join the waiting thread queue
    }
    if (is_closed()) {
        return Result::Closed;
    }
    assert(!is_full());
    push_data(item);
    locker.unlock();          // unlock before notification to minimize mutex contention
    pop_enable_.notify_one(); // notify one waiting thread
    return Result::Success;
}

//--------------------------------------------------------------------------

template < class T >
typename SafeQueue<T>::Result SafeQueue<T>::pop(Item& item) {
    UniqueLocker locker(mutex_);
    if (is_closed()) {
        return Result::Closed;
    }
    if (is_empty()) {
        return Result::Empty;
    }
    item = pop_data();
    locker.unlock();           // unlock before notification to minimize mutex contention
    push_enable_.notify_one(); // notify one waiting thread
    return Result::Success;
};

//--------------------------------------------------------------------------

template < class Item >
typename SafeQueue<Item>::Result SafeQueue<Item>::blocked_pop(Item& item) {
    UniqueLocker locker(mutex_);
    if (is_closed()) {
        return Result::Closed;
    }
    while (is_empty()) {
        if (is_closed()) {
            return Result::Closed;
        }
        pop_enable_.wait(locker); // release lock and go join the waiting thread queue
    }
    if (is_closed()) {
        return Result::Closed;
    }
    assert(!is_empty());
    item = pop_data();
    locker.unlock();            // unlock before notification to minimize mutex contention
    push_enable_.notify_one();  // notify one waiting thread
    return Result::Success;
}

//--------------------------------------------------------------------------

#endif // SAFEQUEUE_H
