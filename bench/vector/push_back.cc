#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "trivial_vector.h"

#define ITERS 10000000 /* 10 million */
#define SIZE 256
#define SIZE_ (SIZE - 1)

#define STD 1
#define TRIVIAL 1

/*
 * Time per push_back:
 * 1. E5-2683-v3 at 3 GHz: std::vector: 1.99 ns, trivial_vector: .2 ns
 */
using namespace std;

static inline uint32_t hrd_fastrand(uint64_t *seed) {
  *seed = *seed * 1103515245 + 12345;
  return (uint32_t)(*seed >> 32);
}

int main() {
  uint64_t seed = 0xdeadbeef;

  int sum = 0;
  int iter;
  struct timespec start, end;
  double nanoseconds;

#if TRIVIAL == 1
  // Trivial vector
  trivial_vector<int> tV;
  tV.init(2, SIZE);
  clock_gettime(CLOCK_REALTIME, &start);

  for (iter = 0; iter < ITERS; iter++) {
    // asm("xxx");
    for (int i = 0; i < SIZE; i++) {
      tV.push_back(iter + i); /* This is bad, but it's fine here. */
    }
    // asm("xxx");

    asm volatile("" ::: "memory");

    /*
     * Access a random array element to prevent any compiler tricks.
     * Do this once every @SIZE time to save cycles.
     */
    int rand_index = hrd_fastrand(&seed) & SIZE_;
    sum += tV[rand_index];
    tV.clear();
  }

  clock_gettime(CLOCK_REALTIME, &end);

  nanoseconds =
      (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);

  printf("Time per push_back (trivial vector) = %f ns, sum = %d\n",
         nanoseconds / ((long long)iter * SIZE), sum);
#endif

#if STD == 1
  // Std vector
  std::vector<int> V;
  V.reserve(SIZE);

  clock_gettime(CLOCK_REALTIME, &start);
  for (iter = 0; iter < ITERS; iter++) {
    for (int i = 0; i < SIZE; i++) {
      V.push_back(i);
    }
    V.clear();
  }
  clock_gettime(CLOCK_REALTIME, &end);

  nanoseconds =
      (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);

  printf("Time per push_back (std::vector) = %f ns\n",
         nanoseconds / ((long long)iter * SIZE));
#endif
}
