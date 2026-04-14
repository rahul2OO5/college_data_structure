#include <arm_neon.h>
#include <pthread.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define IDX(row, column, size) (((row) * (size)) + (column))
#define BLOCK_SIZE 64
#define NUM_THREAD 4
#define BUFFER 40
#define BASE 10

typedef int32_t i32;

typedef struct {
  i32 *matrix_1;
  i32 *matrix_2;
  i32 *result;
  i32 size;
  i32 start_row;
  i32 end_row;
} ThreadData;
static void *multipleWorker(void *arg) {
  ThreadData *data = (ThreadData *)arg;
  i32 size = data->size;

  for (i32 i = data->start_row; i < data->end_row; i += BLOCK_SIZE) {
    for (i32 k = 0; k < size; k += BLOCK_SIZE) {
      for (i32 j = 0; j < size; j += BLOCK_SIZE) {

        i32 i_limit =
            (i + BLOCK_SIZE < data->end_row) ? (i + BLOCK_SIZE) : data->end_row;

        for (i32 ii = i; ii < i_limit; ii++) {
          for (i32 kk = k; kk < k + BLOCK_SIZE && kk < size; kk++) {
            i32 matrix_1_val = data->matrix_1[IDX(ii, kk, size)];

            int32x4_t matrix_1_vec = vdupq_n_s32(matrix_1_val);
            i32 jj = j;
            i32 j_limit = (j + BLOCK_SIZE < size) ? (j + BLOCK_SIZE) : size;

            for (; jj <= j_limit - 4; jj += 4) {
              int32x4_t matrix_2_vec =
                  vld1q_s32(&data->matrix_2[IDX(kk, jj, size)]);
              int32x4_t result_vec =
                  vld1q_s32(&data->result[IDX(ii, jj, size)]);

              result_vec = vmlaq_s32(result_vec, matrix_2_vec, matrix_1_vec);
              vst1q_s32(&data->result[IDX(ii, jj, size)], result_vec);
            }
            for (; jj < j_limit; jj++) {
              data->result[IDX(ii, jj, size)] +=
                  matrix_1_val * data->matrix_2[IDX(kk, jj, size)];
            }
          }
        }
      }
    }
  }
  return NULL;
}

static int Sscan() {
  char buffer[BUFFER];
  if ((fgets(buffer, BUFFER, stdin)) == NULL) {
    return 0;
  }
  return (i32)strtol(buffer, NULL, BASE);
}

static void fillArr(i32 *const matrix_1, const i32 size) {
  printf("Ente the element or %d x %d matrix\n", size, size);
  for (i32 counter = 0; counter < size * size; counter++) {
    printf("Enter the element %d: ", counter + 1);
    matrix_1[counter] = Sscan();
  }
}

static void display(const i32 *const result, const i32 size) {
  for (i32 inner_counter = 0; inner_counter < size; inner_counter++) {
    for (i32 outer_counter = 0; outer_counter < size; outer_counter++) {
      printf("%d\t", result[IDX(inner_counter, outer_counter, size)]);
    }
    printf("\n");
  }
}

int main() {
  i32 size = 0;
  printf("Enter the size of the matrix(N X N):");
  size = Sscan();
  if (size < 0) {
    return 0;
  }

  if (size <= 0) {
    return 0;
  }

  i32 *matrix_1 = (i32 *)malloc((size_t)size * size * sizeof(i32));
  if (matrix_1 == NULL) {
    return 0;
  }

  i32 *matrix_2 = (i32 *)malloc((size_t)size * size * sizeof(i32));
  if (matrix_2 == NULL) {
    free(matrix_1);
    return 0;
  }
  i32 *result = (i32 *)calloc((size_t)size * size, sizeof(i32));
  if (result == NULL) {
    free(matrix_1);
    free(matrix_2);
    return 0;
  }

  printf("\n");
  printf("\nFirst matrix\n");
  fillArr(matrix_1, size);
  printf("\n");
  printf("\nSecond matrix\n");
  fillArr(matrix_2, size);
  printf("\n");

  pthread_t threads[NUM_THREAD];
  ThreadData thread_arg[NUM_THREAD];

  i32 row_per_thread = size / NUM_THREAD;

  for (i32 i = 0; i < NUM_THREAD; i++) {
    thread_arg[i].matrix_1 = matrix_1;
    thread_arg[i].matrix_2 = matrix_2;
    thread_arg[i].result = result;
    thread_arg[i].size = size;
    thread_arg[i].start_row = i * row_per_thread;

    thread_arg[i].end_row =
        (i == NUM_THREAD - 1) ? size : (i + 1) * row_per_thread;
    pthread_create(&threads[i], NULL, multipleWorker, &thread_arg[i]);
  }

  for (i32 i = 0; i < NUM_THREAD; i++) {
    pthread_join(threads[i], NULL);
  }
  printf("\nResult\n");
  display(result, size);
  free(matrix_1);
  free(matrix_2);
  free(result);
  return 0;
}
