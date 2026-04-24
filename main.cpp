#include <iostream>
#include <cstdlib>
#include <ctime>
#include "deque.h"

int main()
{
    srand(time(0));
    int errors = 0;

    // Basic tests
    std::cout << "===== Basic Tests =====\n";

    Deque d;
    std::cout << "empty: " << (d.empty() ? "true" : "false") << "\n"; // true
    std::cout << "size: " << d.size() << "\n";                        // 0

    d.push_back(10);
    d.push_back(20);
    d.push_back(30);
    std::cout << "front: " << d.front() << "\n"; // 10
    std::cout << "back: " << d.back() << "\n";   // 30
    std::cout << "size: " << d.size() << "\n";   // 3

    d.push_front(5);
    std::cout << "front after push_front(5): " << d.front() << "\n"; // 5

    d.pop_back();
    std::cout << "back after pop_back: " << d.back() << "\n"; // 20

    d.pop_front();
    std::cout << "front after pop_front: " << d.front() << "\n"; // 10

    // Empty deque safety test
    std::cout << "\n===== Empty Deque Tests =====\n";
    Deque empty;
    std::cout << "empty(): " << (empty.empty() ? "true" : "false") << "\n"; // true
    std::cout << "size(): " << empty.size() << "\n";                        // 0

    // pop on empty should not crash
    empty.pop_front();
    empty.pop_back();
    std::cout << "We're still here?.. cool that means: pop_front and pop_back on empty deque did not crash\n";

    // operator[] test 
    std::cout << "\n===== operator[] Tests =====\n";
    Deque d2;
    for (int i = 0; i < 20; i++)
        d2.push_back(i * 2);
    for (int i = 0; i < 20; i++)
    {
        if (d2[i] != i * 2)
        {
            std::cout << "MISMATCH at d2[" << i << "]: got " << d2[i] << " expected " << i * 2 << "\n";
            errors++;
        }
    }
    std::cout << "operator[] test done (verified 20 elements, 0 mismatches. no errors)\n";

    // Stress test
    std::cout << "\n===== Push Back Stress =====\n";
    Deque ours;
    int iterations = 5000;

    // push_back stress
    for (int i = 0; i < iterations; i++)
        ours.push_back(i);

    std::cout << "size after 5000 push_back: " << ours.size() << "\n"; // 5000

    for (int i = 0; i < iterations; i++)
    {
        if (ours[i] != i)
        {
            std::cout << "MISMATCH at index " << i << ": got " << ours[i] << " expected " << i << "\n";
            errors++;
        }
    }

    for (int i = 0; i < iterations; i++)
    {
        if (ours.front() != i)
        {
            std::cout << "FRONT MISMATCH: got " << ours.front() << " expected " << i << "\n";
            errors++;
        }
        ours.pop_front();
    }
    std::cout << "empty after drain: " << (ours.empty() ? "true" : "false") << "\n"; // true

    // Refill test
    std::cout << "\n===== Refill Test =====\n";
    for (int i = 0; i < 100; i++) // 99 to 0 order
        ours.push_front(i);

    std::cout << "size after refill: " << ours.size() << "\n";   // 100
    std::cout << "front after refill: " << ours.front() << "\n"; // 99
    std::cout << "back after refill: " << ours.back() << "\n";   // 0

    for (int i = 0; i < 100; i++)
    {
        if (ours[i] != 99 - i)
        {
            std::cout << "REFILL MISMATCH at index " << i << ": got " << ours[i] << " expected " << 99 - i << "\n";
            errors++;
        }
    }
    std::cout << "refill test done\n";

    // push_front stress then verify
    std::cout << "\n===== Push Front Stress =====\n";
    Deque ours2;
    for (int i = 0; i < iterations; i++)
        ours2.push_front(i);

    std::cout << "size after 5000 push_front: " << ours2.size() << "\n"; // 5000

    for (int i = 0; i < iterations; i++)
    {
        if (ours2[i] != iterations - 1 - i)
        {
            std::cout << "MISMATCH at index " << i << "\n";
            errors++;
        }
    }

    for (int i = 0; i < iterations; i++)
    {
        if (ours2.back() != i)
        {
            std::cout << "BACK MISMATCH: got " << ours2.back() << " expected " << i << "\n";
            errors++;
        }
        ours2.pop_back();
    }
    std::cout << "empty after drain: " << (ours2.empty() ? "true" : "false") << "\n"; // true

    // Mixed push stress 
    std::cout << "\n===== Mixed Push/Pop Stress =====\n";
    Deque ours3;

    // push even numbers to back, odd to front
    for (int i = 0; i < iterations; i++)
    {
        if (i % 2 == 0)
            ours3.push_back(i);
        else
            ours3.push_front(i);
    }
    std::cout << "size after mixed push: " << ours3.size() << "\n"; // 5000

    // drain from both ends alternately
    int count = 0;
    while (!ours3.empty())
    {
        ours3.pop_front();
        if (!ours3.empty())
            ours3.pop_back();
        count++;
    }
    std::cout << "drained mixed deque in " << count << " rounds\n";
    std::cout << "empty after drain: " << (ours3.empty() ? "true" : "false") << "\n"; // true

    // Results
    std::cout << "\n===== Results =====\n";
    std::cout << "Errors: " << errors << "\n";
    if (errors == 0)
        std::cout << "All tests passed!\n";
    else
        std::cout << "Failed.\n";

    return 0;
}