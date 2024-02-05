#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <getopt.h>

int main(int argc, char *argv[]) {
    int opt;
    int n_procs = 1; // Default number of processes
    int simul_procs = 1; // Default number of simultaneous processes
    int iter_count = 1; // Default number of iterations

    // Parse command-line arguments
    while ((opt = getopt(argc, argv, "hn:s:t:")) != -1) {
        switch (opt) {
            case 'h':
                printf("Usage: %s -n <total_children> -s <simultaneous_children> -t <iterations>\n", argv[0]);
                exit(EXIT_SUCCESS);
            case 'n':
                n_procs = atoi(optarg);
                break;
            case 's':
                simul_procs = atoi(optarg);
                break;
            case 't':
                iter_count = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Invalid option. Use -h for help.\n");
                exit(EXIT_FAILURE);
        }
    }

    // Allocate memory for tracking child PIDs based on the number of simultaneous processes
    pid_t* children = malloc(simul_procs * sizeof(pid_t));
    if (!children) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    int active_procs = 0, launched_procs = 0;

    while (launched_procs < n_procs) {
        // Launch processes up to the limit of simul_procs
        while (active_procs < simul_procs && launched_procs < n_procs) {
            pid_t pid = fork();
            if (pid == 0) { // Child process
                char iter_str[10];
                sprintf(iter_str, "%d", iter_count);
                char *args[] = {"./user", iter_str, NULL};
                execvp("./user", args);
                perror("execvp failed");
                exit(EXIT_FAILURE); // Exit if execvp fails
            } else if (pid > 0) { // Parent process
                children[active_procs++] = pid; // Store PID
                launched_procs++;
            } else {
                perror("fork failed");
                exit(EXIT_FAILURE);
            }
        }

        // Non-blocking wait to clean up finished child processes
        int status;
		int i;
        for (i = 0; i < active_procs; i++) {
            if (waitpid(children[i], &status, WNOHANG) > 0) {
                // Shift the array of PIDs to remove the finished process
				int j;
                for (j = i; j < active_procs - 1; j++) {
                    children[j] = children[j + 1];
                }
                active_procs--;
                i--; // Adjust index to recheck the new PID at this index
            }
        }
    }

    // Final blocking wait to ensure all children are cleaned up
	int i;
    for (i = 0; i < active_procs; i++) {
        waitpid(children[i], NULL, 0);
    }

    free(children); // Clean up dynamically allocated memory
    return 0;
}
