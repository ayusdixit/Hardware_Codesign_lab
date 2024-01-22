#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <thread>
#include <mutex>
#include <chrono>
std::mutex mtx;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

double average(const std::vector<int>& numbers) {
    return round(std::accumulate(numbers.begin(), numbers.end(), 0.0) / numbers.size());
}

 
void parallelGCD(int num1, int num2, int& result) {
    std::lock_guard<std::mutex> lock(mtx);
    result = gcd(num1, num2);
}

int main() {
   
    int N;
    std::cout << "Enter the number of inputs (N): ";
    std::cin >> N;

    std::vector<int> inputs(N);
    
    for(int i = 0; i < N; ++i) {
        std::cout << "Enter input " << i+1 << ": ";
        std::cin >> inputs[i];
    }

 
    double avg = average(inputs);
    std::cout << "Average: " << avg << std::endl;

   
    int P, Q;
    
    std::cout << "Enter value for P (between 500 to 2500): ";
    std::cin >> P;
    
    std::cout << "Enter value for Q (between 1000 to 5000): ";
    std::cin >> Q;

   
    if(P < 500 || P > 2500 || Q < 1000 || Q > 5000){
        std::cerr << "P or Q is out of range." << std::endl;
        return -1;
    }

     int gcd1, gcd2;
           auto start_time = std::chrono::high_resolution_clock::now();

    std::thread thread1(parallelGCD, avg, P, std::ref(gcd1));
    std::thread thread2(parallelGCD, avg, Q, std::ref(gcd2));


    
    thread1.join();
    thread2.join();
 auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
    std::cout << "Elapsed time: " << elapsed_time.count() << " nanoseconds" << std::endl;
    
    double finalAvg = average({gcd1, gcd2});

    std::cout << "Final Average after two iterations: " << finalAvg << std::endl;

    return 0;
}
