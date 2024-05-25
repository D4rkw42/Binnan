#include <iostream>
#include <chrono>
#include <thread>

using namespace std::this_thread;
using namespace std::chrono;

int main(void) {
    std::cout << "Antes de 3 segundos..." << "\n";
    sleep_for(seconds(3));
    std::cout << "Depois de 3 segundos..." << "\n";

    return 0;
}
