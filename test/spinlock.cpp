#include <cybozu/spinlock.hpp>

#include <mutex>
#include <thread>
#include <iostream>

alignas(CACHELINE_SIZE)
cybozu::spinlock g_lock;

alignas(CACHELINE_SIZE)
unsigned int g_counter = 0;

void accum(int n) {
    for(int i = 0; i < n; ++i) {
        std::lock_guard<cybozu::spinlock> guard(g_lock);
        ++g_counter;
    }
}

int main() {
    std::thread t1(accum, 100000);
    std::thread t2(accum, 100000);
    std::thread t3(accum, 100000);
    t1.join();
    t2.join();
    t3.join();
    std::cout << "accumulated value = " << g_counter << std::endl;
    return 0;
}
