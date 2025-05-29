#include <mpi.h>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    int rank, size;
    const int N = 10000000; // 100 milioane de elemente

    MPI_Init(&argc, &argv);             // Pornim MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obținem rank-ul procesului curent
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obținem numărul total de procese

    // Împărțim vectorul între procese
    int local_n = N / size;
    std::vector<int> local_vec(local_n, 0);

    double start_time = MPI_Wtime(); // Start cronometru

    // Fiecare proces incrementează propriul vector local
    for (int i = 0; i < local_n; ++i) {
        local_vec[i] += 1;
    }

    // Procesul 0 colectează rezultatele de la toate procesele
    std::vector<int> final_vec;
    if (rank == 0) {
        final_vec.resize(N);
    }

    MPI_Gather(local_vec.data(), local_n, MPI_INT,
               final_vec.data(), local_n, MPI_INT,
               0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime(); // Stop cronometru

    if (rank == 0) {
        std::cout << "Timp de executie (MPI): " << (end_time - start_time) << " secunde\n";
    }

    MPI_Finalize(); // Oprim MPI
    return 0;
}
