#include <iostream>
#include <thread>
#include <mutex>

std::mutex resultMutex;
int result = 1;

void calculateFactorial(int n) {
    int partialResult = 1;
    for (int i = 1; i <= n; i++) {
        partialResult *= i;
    }

    std::lock_guard<std::mutex> lock(resultMutex);
    result *= partialResult;
}

int main() {
    int n = 5;

    std::thread thread1(calculateFactorial, n/4);
    std::thread thread2(calculateFactorial, n);

    thread1.join();
    thread2.join();

    std::cout << "Factorial of " << n << " is: " << result << std::endl;

    return 0;
}
