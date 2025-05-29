#include <iostream>
#include <vector>
#include <chrono>

int main() {
    const int N = 10000000;  // Dimensiunea vectorului
    std::vector<int> vec(N, 1);  // Vector de dimensiune N, inițializat cu 1

    // Măsurăm timpul de execuție
    auto start = std::chrono::high_resolution_clock::now();

    // Incrementăm fiecare element al vectorului
    for (int i = 0; i < N; ++i) {
        vec[i] += 1;  // Incrementăm fiecare element
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Timpul de execuție secvențial: " << duration.count() << " secunde\n";
    
    return 0;
}
