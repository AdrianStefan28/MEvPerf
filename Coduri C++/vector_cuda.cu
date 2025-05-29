#include <iostream>
#include <cuda_runtime.h>

__global__ void increment_vector(int* vec, int n) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < n) {
        vec[idx] += 1;
    }
}

int main() {
    const int N = 10000000; // 100 milioane
    size_t size = N * sizeof(int);

    int* h_vec = (int*)malloc(size);
    int* d_vec;

    // Inițializăm vectorul pe host
    for (int i = 0; i < N; i++) h_vec[i] = 0;

    cudaMalloc(&d_vec, size);
    cudaMemcpy(d_vec, h_vec, size, cudaMemcpyHostToDevice);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start);

    // Rulăm kernelul CUDA
    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;
    increment_vector<<<blocksPerGrid, threadsPerBlock>>>(d_vec, N);

    cudaMemcpy(h_vec, d_vec, size, cudaMemcpyDeviceToHost);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);

    std::cout << "Timp de executie (CUDA): " << milliseconds / 1000.0f << " secunde\n";

    cudaFree(d_vec);
    free(h_vec);

    return 0;
}
