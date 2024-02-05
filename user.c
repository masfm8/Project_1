#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s NUM_ITERATIONS\n", argv[0]);
        return 1;
    }

    char *endptr;
    long iter_count = strtol(argv[1], &endptr, 10);

    // Check for errors: no digits found, long overflow or underflow, or part of the input is non-numeric
    if (endptr == argv[1] || *endptr != '\0' || errno == ERANGE || iter_count > INT_MAX || iter_count < INT_MIN) {
        fprintf(stderr, "Error: Invalid number of iterations: %s\n", argv[1]);
        return 1;
    }

    // Check for non-positive iteration count
    if (iter_count <= 0) {
        fprintf(stderr, "Error: Number of iterations must be positive: %ld\n", iter_count);
        return 1;
    }

    for (int i = 0; i < iter_count; ++i) {
        printf("USER PID:%d PPID:%d Iteration:%d before sleeping\n", getpid(), getppid(), i + 1);
        sleep(1); // Sleep for one second
        printf("USER PID:%d PPID:%d Iteration:%d after sleeping\n", getpid(), getppid(), i + 1);
    }

    return 0;
}
