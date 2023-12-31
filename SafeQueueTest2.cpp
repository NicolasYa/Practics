//
//  safe_queue_test.cpp : C++ safe queue demo test (console app)
//
//  Author: Victor V. Rudakov
//  
//  This constants can be changed in source code for testing:
//  TestQueueMaxSize      - size of tested safe queue ( >= 0 )
//  TestWorkTime          - normal work period for writer and readers (in seconds)
//  TestFinishingTime - only readers and blocked writers are working while finising queue processing (in seconds)
//
//  WriterProduceMaxDelay - Max value for randomly generated Writer message pushing (in milliseconds)
//  ReaderProcessingDelay - time for simulating readers work with popped message (in milliseconds)
//
//  DemoQueue use string as type for messages as example
//
//  In function main() number of threads and their behaviour can be changed manualy 
//  by adding/removing source code lines between section: [THREADS BEGIN 1]..[THREADS END 1]
//
//  While concurrent threads are working console output used for some animation only 
//  (text output order can depend from race conditions).
//  Accurate checks will be done after all threads are finised (based on collected test data)
//

#include <iostream>
#include <thread>
#include <vector>
#include <sstream>
#include <random>

#include "safe_queue.h"


#include "gtest/gtest.h"
#include "gmock/gmock.h"

class MockDatabase
{
public:
    MOCK_METHOD(bool, CheckMap, ((std::string), bool));
};


using namespace std;

namespace { // anonymous

//--------------------------------------------------------------------------
// Change this values for testing:

constexpr unsigned int TestQueueMaxSize = 30;  // size of tested safe queue

constexpr unsigned int TestWorkTime      = 10;  // sec, normal work period for writer and readers
constexpr unsigned int TestFinishingTime = 5;   // sec, only readers are works for finising queue processing (writres are stoped)

constexpr unsigned int WriterProduceMaxDelay = 300;  // ms
constexpr unsigned int ReaderProcessingDelay = 500;  // ms

constexpr unsigned FullTime = TestWorkTime + TestFinishingTime;

void print_to_console(const string text);

//--------------------------------------------------------------------------
// Safe queue of strings are used for example 

using DemoQueue = typename SafeQueue<string>;
using Result = typename DemoQueue::Result;
using Item = typename DemoQueue::Item;
using Messages = typename vector<Item>;

//--------------------------------------------------------------------------

static
void print_to_console(const string text) {
    static mutex s_local_mutex;

    lock_guard<mutex> locker(s_local_mutex);
    cout << text << endl;
}

//--------------------------------------------------------------------------

static
string get_unique_string_value() {
    static volatile int s_value_index{};
    static mutex        s_local_mutex;

    unique_lock<mutex> locker(s_local_mutex);
    ++s_value_index;
    ostringstream unique_value;
    unique_value << "\"String_" << s_value_index << "\"";
    return unique_value.str();
}

//--------------------------------------------------------------------------

static
unsigned get_produce_delay() {
    static random_device rd;
    static mt19937 s_gen(rd());
    static uniform_int_distribution<> distr(0, WriterProduceMaxDelay);

    return distr(s_gen);
}

//--------------------------------------------------------------------------

void print_result(ostream& out_stream, const Item& item, Result result) {
     switch (result) {
        case Result::Success: {
            out_stream << item;
            break;
        }
        case Result::Closed: {
            out_stream << " failed( Queue Closed )";
            break;
        }
        case Result::Full: {
            out_stream << " failed( Queue Full )";
            break;
        }
        case Result::Empty: {
            out_stream << " failed( Queue Empty )";
            break;
        }
        default: {
            out_stream << " error( Unknown )";
            assert(true);
            break;
        }
    }
}

//--------------------------------------------------------------------------

inline 
string get_name(const string prefix, const unsigned id) {
    ostringstream name;
    name << prefix << " (id:" << id << ")";
    return name.str();
}

//--------------------------------------------------------------------------

static
void executing_non_blocked_push(unsigned writer_id, const bool& running, DemoQueue& demo_queue) {
    string writer_name(get_name("Writer", writer_id));
    while (running) {
        this_thread::sleep_for(chrono::milliseconds(get_produce_delay()));
        const auto item{ get_unique_string_value() };
        ostringstream output;
        output << writer_name << " Non-blocked push: ";
        const auto result = demo_queue.push(item);
        print_result(output, item, result);
        print_to_console(output.str());
    }
    ostringstream output;
    output << writer_name << " Finished";
    print_to_console(output.str());
}

//--------------------------------------------------------------------------

static
void executing_blocked_push(unsigned writer_id, const bool& running, DemoQueue& demo_queue) {
    string writer_name(get_name("Writer", writer_id));
    while (running) {
        this_thread::sleep_for(chrono::milliseconds(get_produce_delay()));
        const auto item{ get_unique_string_value() };
        const auto result = demo_queue.blocked_push(item);
        ostringstream output;
        output << writer_name << " Blocked push: ";
        print_result(output, item, result);
        print_to_console(output.str());
    }
    ostringstream output;
    output << writer_name << " Finished";
    print_to_console(output.str());
}

//--------------------------------------------------------------------------

static
void executing_blocked_pop(unsigned reader_id, const bool& running, DemoQueue& demo_queue) {
    string reader_name(get_name("Reader", reader_id));
    while (running) {
        DemoQueue::Item item;
        const auto result = demo_queue.blocked_pop(item);
        ostringstream output;
        output << reader_name << " Blocked pop: ";
        print_result(output, item, result);
        print_to_console(output.str());
        this_thread::sleep_for(chrono::milliseconds(ReaderProcessingDelay));
    }
    ostringstream output;
    output << reader_name << " Finished";
    print_to_console(output.str());
}

//--------------------------------------------------------------------------

static
void executing_non_blocked_pop(unsigned reader_id, const bool& running, DemoQueue& demo_queue) {
    string reader_name(get_name("Reader", reader_id));
    while (running) {
        DemoQueue::Item item;
        const auto result = demo_queue.pop(item);
        if (result == DemoQueue::Result::Success) {
            ostringstream output;
            output << reader_name << " Non-blocked pop: ";
            print_result(output, item, result);
            print_to_console(output.str());
            this_thread::sleep_for(chrono::milliseconds(ReaderProcessingDelay));
        }
    }
    ostringstream output;
    output << reader_name << " Finished";
    print_to_console(output.str());
}

//--------------------------------------------------------------------------

void print_analized_test_results(ostream& out_stream
    , const DemoQueue& demo_queue
    , const Messages& pushed_messages
    , const Messages& popped_messages
) {
    const Messages::size_type pushed_size{ pushed_messages.size() };
    const Messages::size_type popped_size{ popped_messages.size() };
    const DemoQueue::size_type  safe_queue_size{ demo_queue.get_size() };

    out_stream << "Safe queue push/pop demo results:" << endl;
    out_stream << "Safe queue size: " << safe_queue_size << endl;
    out_stream << "Real Pushed messages: " << pushed_size << endl;
    out_stream << "Real Popped messages: " << popped_size << endl;

    bool ok = true;
    Messages::size_type lost_pushed = (pushed_size - safe_queue_size) - popped_size;
    if (lost_pushed > 0) {
        out_stream << "Lost pushed messages detected: " << lost_pushed << endl;
    }
    if (popped_size > pushed_size) {
        out_stream << "Error: popped messages count > pushed messages count" << endl;
        ok = false;
    }
    if (safe_queue_size > 0) {
        out_stream << "Warning: Non popped messages detected: " << safe_queue_size << endl;
    }
    if (ok) {
        for (auto i = 0; i < popped_size; i++) {
            if (popped_messages[i] != pushed_messages[i]) {
                out_stream << "Non FIFO behaviour detected" << endl;
                ok = false;
                break;
            }
        }
    }
    out_stream << "Safe queue push/pop test " << (ok ? "PASSED" : "FAILED") << endl;
}

//--------------------------------------------------------------------------

Messages g_pushed_messages;
Messages g_popped_messages;

static
void push_callback(const Item& item) {
    g_pushed_messages.push_back(item);
}

static
void pop_callback(const DemoQueue::Item& item) {
    g_popped_messages.push_back(item);
}

} // anonymous namespace

//--------------------------------------------------------------------------

using ThreadFunction = void(unsigned id, const bool& running, DemoQueue& queue);

void add_and_start(vector<thread>& threads, ThreadFunction Function, const bool& running, DemoQueue& queue)
{
    thread t(Function, unsigned(threads.size()), ref(running), ref(queue));
    threads.emplace_back(move(t));
}

//--------------------------------------------------------------------------

int main() {
    using namespace placeholders;
    
    cout
        << "Safe queue push/pop demo started for " << FullTime << " sec, with:" << endl
        << endl
        << "Demo full work time = " << TestWorkTime << " sec" << endl
        << "Demo finishing time = " << TestFinishingTime << " sec" << endl
        << endl
        << "Safe queue max size       = " << TestQueueMaxSize << " messages" << endl
        << "Message pushing max delay = " << WriterProduceMaxDelay << " ms" << endl
        << "Message processing delay  = " << ReaderProcessingDelay << " ms" << endl
        << endl;
    cout.flush();


    DemoQueue demo_queue(TestQueueMaxSize);
    demo_queue.register_push_callback(function(push_callback));
    demo_queue.register_pop_callback(function(pop_callback));

    vector<thread> threads;
    bool writers_running = true;
    bool readers_running = true;

    auto run_writer_thread = bind(add_and_start, ref(threads), _1, ref(writers_running), ref(demo_queue));
    auto run_reader_thread = bind(add_and_start, ref(threads), _1, ref(readers_running), ref(demo_queue));

    cout << "Starting readers and writers..." << endl;
    //  [THREADS BEGIN]
    //  writers
    run_writer_thread(executing_non_blocked_push);
    run_writer_thread(executing_non_blocked_push);
    run_writer_thread(executing_blocked_push);
    run_writer_thread(executing_blocked_push);
    //  readers
    run_reader_thread(executing_blocked_pop);
    run_reader_thread(executing_blocked_pop);
    run_reader_thread(executing_non_blocked_pop);
    //  [THREADS END]

    this_thread::sleep_for(chrono::seconds(TestWorkTime));
    print_to_console("Finishing...");

    // Stoping writers
    writers_running = false;
    // Add some time for readers and writers(with blocked push)
    this_thread::sleep_for(chrono::seconds(TestFinishingTime));

    // Stoping readers
    readers_running = false;

    // release waiting in blocked pop/push:
    demo_queue.close();
    print_to_console("Safe queue closed");

    for (auto& t : threads)
        t.join();

    cout << endl << "All readers and writers finished." << endl;

    // Print test results
    cout << endl;
    print_analized_test_results(cout, demo_queue, g_pushed_messages, g_popped_messages);
    cout << endl;
    return 0;
}
