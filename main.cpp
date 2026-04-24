#include <iostream>
#include <deque>
#include <cstdlib>
#include <ctime>
#include "deque.h"

int main()
{
    srand(time(0));

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

    // operator[] test
    std::cout << "\n===== operator[] Tests =====\n";
    Deque d2;
    for (int i = 0; i < 20; i++)
        d2.push_back(i * 2);
    for (int i = 0; i < 20; i++)
        std::cout << "d2[" << i << "] = " << d2[i] << "\n"; // 0,2,4,...,38

    // Stress test
    std::cout << "\n===== Stress Test =====\n";
    Deque ours;
    std::deque<int> ref;

    int mismatches = 0;
    int iterations = 5000;

    for (int i = 0; i < iterations; i++)
    {
        int op = rand() % 4;
        int val = rand() % 10000;

        if (op == 0)
        {
            ours.push_back(val);
            ref.push_back(val);
        }
        else if (op == 1)
        {
            ours.push_front(val);
            ref.push_front(val);
        }
        else if (op == 2)
        {
            if (!ref.empty())
            {
                if (ours.front() != ref.front())
                    mismatches++;
                ours.pop_front();
                ref.pop_front();
            }
        }
        else
        {
            if (!ref.empty())
            {
                if (ours.back() != ref.back())
                    mismatches++;
                ours.pop_back();
                ref.pop_back();
            }
        }
    }

    // checks for mismatches using deque library as a reference
    for (int i = 0; i < (int)ref.size(); i++)
    {
        if (ours[i] != ref[i])
            mismatches++;
    }

    std::cout << "Iterations: " << iterations << "\n";
    std::cout << "Mismatches: " << mismatches << "\n";
    if (mismatches == 0)
        std::cout << "All tests passed!\n";
    else
        std::cout << "Failed.\n";

    return 0;
}