#include <stdlib.h> // to be able to use malloc function
#include <unistd.h> // to be able to use sleep function


//multiplication calculation method --> and creation of result matrix
void m_multi(int **m1, int **m2, int **result, int m1_r, int m1_c, int m2_c) {
    for (int i = 0; i < m1_r; i++) { // matrix1_rows
        for (int j = 0; j < m2_c; j++) { //matrix2_columns
            result[i][j] = 0;   // Initialize all elements to 0
            for (int z = 0; z < m1_c; z++) {
                result[i][j] += m1[i][z] * m2[z][j]; // element-wise multiplication calculation
            }
        }
    }
}
int matrix() {
    int m1_r, m1_c, m2_r, m2_c; // initialise all variables to be used in do-while loop
    bool valid_input = false; // condition to get out of loop
    do {
        printf("Enter number of rows for matrix 1: "); // rows_matrix1
        scanf("%d", &m1_r);
        printf("Enter number of columns for matrix 1: ");// columns_matrix1
        scanf("%d", &m1_c);

        printf("Enter number of rows for matrix 2: "); // rows_matrix2
        scanf("%d", &m2_r);
        printf("Enter number of columns for matrix 2: "); // columns_matrix2
        scanf("%d", &m2_c);

        // Validate matrix sizes --> in case user inputs matrices of incompatible sizes
        if (m1_c != m2_r) {
            printf("ERROR Occurred :( \nIncompatible matrix sizes!!\n");
            valid_input = false; // keep validation false
            sleep(1);  // Pause for 1 second
            printf("Reloading...\n");
            usleep(500000); // Pause for 0.5 seconds
            printf("\n");
        } else
            valid_input = true; // make validation true
            printf("Loading...\n");
        sleep(1);  // Pause for 1 seconds

    } while (!valid_input);

    // Allocating memory for matrices using malloc function
    // Allocating memory for m1
    int **m1 = malloc(m1_r * sizeof(int *));
    for (int i = 0; i < m1_r; i++) { // For each row in m1
        m1[i] = malloc(m1_c * sizeof(int)); // Allocating memory for each column in m1
    }

    // Same as above but for m2
    int **m2 = malloc(m2_r * sizeof(int *));
    for (int i = 0; i < m2_r; i++) {
        m2[i] = malloc(m2_c * sizeof(int));
    }

    // Allocating memory for result matrix
    int **result = malloc(m1_r * sizeof(int *));
    for (int i = 0; i < m1_r; i++) {
        result[i] = malloc(m2_c * sizeof(int));
    }

    // User inputs elements of matrix1
    printf("\nEnter elements for matrix 1:\n");
    for (int i = 0; i < m1_r; i++) { // m1_rows
        for (int j = 0; j < m1_c; j++) { //m1_columns
            printf("Enter element (%d, %d): ", i, j); // displays the position of the matrix
            scanf("%d", &m1[i][j]);
        }
    }

    // User inputs elements of matrix2
    printf("Enter elements for matrix 2:\n");
    for (int i = 0; i < m2_r; i++) { // m2_rows
        for (int j = 0; j < m2_c; j++) { // m2_columns
            printf("Enter element (%d, %d): ", i, j);
            scanf("%d", &m2[i][j]);
        }
    }

    // Perform matrix multiplication by calling corresponding method
    m_multi(m1, m2, result, m1_r, m1_c, m2_c);

    // Print result matrix
    printf("\nMatrix Multiplication:\n");
    for (int i = 0; i < m1_r; i++) {
        for (int j = 0; j < m2_c; j++) {
            printf("%d ", result[i][j]);
        }
        sleep(1); // Pause for 1 second
        printf("\n");
    }
    sleep(1); // Pause for 1 second
    printf("\n");

    // Free memory using free function (to free memory post using malloc function)
    // Free memory for matrix 1
    for (int i = 0; i < m1_r; i++) {
        free(m1[i]);
    }
    free(m1);

    // Free memory for matrix 2
    for (int i = 0; i < m2_r; i++) {
        free(m2[i]);
    }
    free(m2);

    // Free memory for result matrix
    for (int i = 0; i < m1_r; i++) {
        free(result[i]);
    }
    free(result);

    return 0;
}