extern "C" {
#include <pillar-c/allocator.h>
#include <pillar-c/status.h>
#include <pillar-c/types.h>
#include <pillar-c/vec.h>
#include <unity.h>
}

void setUp(void) {
  // This is run before EACH TEST
}

void tearDown(void) {
  // This is run after EACH TEST
}

void test_raw_vec_init_with_creates_vector(void) {
  struct Pillar_RawVec vec;
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);

  struct Pillar_Status status = pillar_raw_vec_init_with(&vec, layout, allocator, 10);

  TEST_ASSERT_TRUE(pillar_status_is_ok(status));
  TEST_ASSERT_NOT_NULL(vec.data);
  TEST_ASSERT_EQUAL(0, vec.len);
  TEST_ASSERT_EQUAL(10, vec.cap);

  pillar_raw_vec_deinit(&vec);
}

void test_raw_vec_init_with_null_pointer(void) {
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);

  struct Pillar_Status status = pillar_raw_vec_init_with(NULL, layout, allocator, 10);

  TEST_ASSERT_FALSE(pillar_status_is_ok(status));
  TEST_ASSERT_EQUAL(PILLAR_VEC_DOMAIN, status.domain);
  TEST_ASSERT_EQUAL(PILLAR_VEC_CODE_INVALID_ARGUMENT, status.code);
}

void test_raw_vec_init_with_invalid_allocator(void) {
  struct Pillar_RawVec vec;
  struct Pillar_Allocator invalid_allocator = {NULL, NULL};
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);

  struct Pillar_Status status = pillar_raw_vec_init_with(&vec, layout, invalid_allocator, 10);

  TEST_ASSERT_FALSE(pillar_status_is_ok(status));
}

void test_raw_vec_deinit_null_pointer(void) {
  struct Pillar_Status status = pillar_raw_vec_deinit(NULL);

  TEST_ASSERT_FALSE(pillar_status_is_ok(status));
  TEST_ASSERT_EQUAL(PILLAR_VEC_CODE_INVALID_ARGUMENT, status.code);
}

void test_raw_vec_append_single_element(void) {
  struct Pillar_RawVec vec;
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);

  pillar_raw_vec_init_with(&vec, layout, allocator, 10);

  int value = 42;
  struct Pillar_Status status = pillar_raw_vec_append(&vec, (Pillar_U8 *)&value);

  TEST_ASSERT_TRUE(pillar_status_is_ok(status));
  TEST_ASSERT_EQUAL(1, vec.len);

  int *data = (int *)vec.data;
  TEST_ASSERT_EQUAL(42, data[0]);

  pillar_raw_vec_deinit(&vec);
}

void test_raw_vec_append_multiple_elements(void) {
  struct Pillar_RawVec vec;
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);

  pillar_raw_vec_init_with(&vec, layout, allocator, 10);

  for (int i = 0; i < 5; i++) {
    struct Pillar_Status status = pillar_raw_vec_append(&vec, (Pillar_U8 *)&i);
    TEST_ASSERT_TRUE(pillar_status_is_ok(status));
  }

  TEST_ASSERT_EQUAL(5, vec.len);

  int *data = (int *)vec.data;
  for (int i = 0; i < 5; i++) {
    TEST_ASSERT_EQUAL(i, data[i]);
  }

  pillar_raw_vec_deinit(&vec);
}

void test_raw_vec_append_grows_when_full(void) {
  struct Pillar_RawVec vec;
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);

  pillar_raw_vec_init_with(&vec, layout, allocator, 4);

  for (int i = 0; i < 10; i++) {
    struct Pillar_Status status = pillar_raw_vec_append(&vec, (Pillar_U8 *)&i);
    TEST_ASSERT_TRUE(pillar_status_is_ok(status));
  }

  TEST_ASSERT_EQUAL(10, vec.len);
  TEST_ASSERT_TRUE(vec.cap >= 10);

  int *data = (int *)vec.data;
  for (int i = 0; i < 10; i++) {
    TEST_ASSERT_EQUAL(i, data[i]);
  }

  pillar_raw_vec_deinit(&vec);
}

void test_raw_vec_append_null_vec(void) {
  int value = 42;
  struct Pillar_Status status = pillar_raw_vec_append(NULL, (Pillar_U8 *)&value);

  TEST_ASSERT_FALSE(pillar_status_is_ok(status));
  TEST_ASSERT_EQUAL(PILLAR_VEC_CODE_INVALID_ARGUMENT, status.code);
}

void test_raw_vec_append_null_item(void) {
  struct Pillar_RawVec vec;
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);

  pillar_raw_vec_init_with(&vec, layout, allocator, 10);

  struct Pillar_Status status = pillar_raw_vec_append(&vec, NULL);

  TEST_ASSERT_FALSE(pillar_status_is_ok(status));
  TEST_ASSERT_EQUAL(PILLAR_VEC_CODE_INVALID_ARGUMENT, status.code);

  pillar_raw_vec_deinit(&vec);
}

void test_raw_vec_pop_single_element(void) {
  struct Pillar_RawVec vec;
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);

  pillar_raw_vec_init_with(&vec, layout, allocator, 10);

  int value = 42;
  pillar_raw_vec_append(&vec, (Pillar_U8 *)&value);

  int result;
  struct Pillar_Status status = pillar_raw_vec_pop(&vec, (Pillar_U8 *)&result);

  TEST_ASSERT_TRUE(pillar_status_is_ok(status));
  TEST_ASSERT_EQUAL(42, result);
  TEST_ASSERT_EQUAL(0, vec.len);

  pillar_raw_vec_deinit(&vec);
}

void test_raw_vec_pop_multiple_elements(void) {
  struct Pillar_RawVec vec;
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);

  pillar_raw_vec_init_with(&vec, layout, allocator, 10);

  for (int i = 0; i < 5; i++) {
    pillar_raw_vec_append(&vec, (Pillar_U8 *)&i);
  }

  for (int i = 4; i >= 0; i--) {
    int result;
    struct Pillar_Status status = pillar_raw_vec_pop(&vec, (Pillar_U8 *)&result);
    TEST_ASSERT_TRUE(pillar_status_is_ok(status));
    TEST_ASSERT_EQUAL(i, result);
  }

  TEST_ASSERT_EQUAL(0, vec.len);

  pillar_raw_vec_deinit(&vec);
}

void test_raw_vec_pop_from_empty(void) {
  struct Pillar_RawVec vec;
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);

  pillar_raw_vec_init_with(&vec, layout, allocator, 10);

  int result;
  struct Pillar_Status status = pillar_raw_vec_pop(&vec, (Pillar_U8 *)&result);

  TEST_ASSERT_FALSE(pillar_status_is_ok(status));
  TEST_ASSERT_EQUAL(PILLAR_VEC_CODE_OUT_OF_BOUNDS, status.code);

  pillar_raw_vec_deinit(&vec);
}

void test_raw_vec_pop_null_vec(void) {
  int result;
  struct Pillar_Status status = pillar_raw_vec_pop(NULL, (Pillar_U8 *)&result);

  TEST_ASSERT_FALSE(pillar_status_is_ok(status));
  TEST_ASSERT_EQUAL(PILLAR_VEC_CODE_INVALID_ARGUMENT, status.code);
}

void test_raw_vec_pop_null_out(void) {
  struct Pillar_RawVec vec;
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);

  pillar_raw_vec_init_with(&vec, layout, allocator, 10);

  int value = 42;
  pillar_raw_vec_append(&vec, (Pillar_U8 *)&value);

  struct Pillar_Status status = pillar_raw_vec_pop(&vec, NULL);

  TEST_ASSERT_FALSE(pillar_status_is_ok(status));
  TEST_ASSERT_EQUAL(PILLAR_VEC_CODE_INVALID_ARGUMENT, status.code);

  pillar_raw_vec_deinit(&vec);
}

void test_raw_vec_prepend_single_element(void) {
  struct Pillar_RawVec vec;
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);

  pillar_raw_vec_init_with(&vec, layout, allocator, 10);

  int value = 42;
  struct Pillar_Status status = pillar_raw_vec_prepend(&vec, (Pillar_U8 *)&value);

  TEST_ASSERT_TRUE(pillar_status_is_ok(status));
  TEST_ASSERT_EQUAL(1, vec.len);

  int *data = (int *)vec.data;
  TEST_ASSERT_EQUAL(42, data[0]);

  pillar_raw_vec_deinit(&vec);
}

void test_raw_vec_prepend_multiple_elements(void) {
  struct Pillar_RawVec vec;
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);

  pillar_raw_vec_init_with(&vec, layout, allocator, 10);

  for (int i = 0; i < 5; i++) {
    struct Pillar_Status status = pillar_raw_vec_prepend(&vec, (Pillar_U8 *)&i);
    TEST_ASSERT_TRUE(pillar_status_is_ok(status));
  }

  TEST_ASSERT_EQUAL(5, vec.len);

  int *data = (int *)vec.data;
  for (int i = 0; i < 5; i++) {
    TEST_ASSERT_EQUAL(4 - i, data[i]);
  }

  pillar_raw_vec_deinit(&vec);
}

void test_raw_vec_prepend_grows_when_full(void) {
  struct Pillar_RawVec vec;
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);

  pillar_raw_vec_init_with(&vec, layout, allocator, 4);

  for (int i = 0; i < 10; i++) {
    struct Pillar_Status status = pillar_raw_vec_prepend(&vec, (Pillar_U8 *)&i);
    TEST_ASSERT_TRUE(pillar_status_is_ok(status));
  }

  TEST_ASSERT_EQUAL(10, vec.len);
  TEST_ASSERT_TRUE(vec.cap >= 10);

  pillar_raw_vec_deinit(&vec);
}

void test_raw_vec_shift_single_element(void) {
  struct Pillar_RawVec vec;
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);

  pillar_raw_vec_init_with(&vec, layout, allocator, 10);

  int value = 42;
  pillar_raw_vec_prepend(&vec, (Pillar_U8 *)&value);

  int result;
  struct Pillar_Status status = pillar_raw_vec_shift(&vec, (Pillar_U8 *)&result);

  TEST_ASSERT_TRUE(pillar_status_is_ok(status));
  TEST_ASSERT_EQUAL(42, result);
  TEST_ASSERT_EQUAL(0, vec.len);

  pillar_raw_vec_deinit(&vec);
}

void test_raw_vec_shift_multiple_elements(void) {
  struct Pillar_RawVec vec;
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);

  pillar_raw_vec_init_with(&vec, layout, allocator, 10);

  for (int i = 0; i < 5; i++) {
    pillar_raw_vec_append(&vec, (Pillar_U8 *)&i);
  }

  for (int i = 0; i < 5; i++) {
    int result;
    struct Pillar_Status status = pillar_raw_vec_shift(&vec, (Pillar_U8 *)&result);
    TEST_ASSERT_TRUE(pillar_status_is_ok(status));
    TEST_ASSERT_EQUAL(i, result);
  }

  TEST_ASSERT_EQUAL(0, vec.len);

  pillar_raw_vec_deinit(&vec);
}

void test_raw_vec_shift_from_empty(void) {
  struct Pillar_RawVec vec;
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);

  pillar_raw_vec_init_with(&vec, layout, allocator, 10);

  int result;
  struct Pillar_Status status = pillar_raw_vec_shift(&vec, (Pillar_U8 *)&result);

  TEST_ASSERT_FALSE(pillar_status_is_ok(status));
  TEST_ASSERT_EQUAL(PILLAR_VEC_CODE_OUT_OF_BOUNDS, status.code);

  pillar_raw_vec_deinit(&vec);
}

void test_raw_vec_grow_increases_capacity(void) {
  struct Pillar_RawVec vec;
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);

  pillar_raw_vec_init_with(&vec, layout, allocator, 10);

  struct Pillar_Status status = pillar_raw_vec_grow(&vec, 20);

  TEST_ASSERT_TRUE(pillar_status_is_ok(status));
  TEST_ASSERT_EQUAL(20, vec.cap);

  pillar_raw_vec_deinit(&vec);
}

void test_raw_vec_grow_preserves_data(void) {
  struct Pillar_RawVec vec;
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);

  pillar_raw_vec_init_with(&vec, layout, allocator, 10);

  for (int i = 0; i < 5; i++) {
    pillar_raw_vec_append(&vec, (Pillar_U8 *)&i);
  }

  struct Pillar_Status status = pillar_raw_vec_grow(&vec, 20);

  TEST_ASSERT_TRUE(pillar_status_is_ok(status));
  TEST_ASSERT_EQUAL(5, vec.len);
  TEST_ASSERT_EQUAL(20, vec.cap);

  int *data = (int *)vec.data;
  for (int i = 0; i < 5; i++) {
    TEST_ASSERT_EQUAL(i, data[i]);
  }

  pillar_raw_vec_deinit(&vec);
}

void test_raw_vec_grow_with_smaller_cap_does_nothing(void) {
  struct Pillar_RawVec vec;
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);

  pillar_raw_vec_init_with(&vec, layout, allocator, 10);

  struct Pillar_Status status = pillar_raw_vec_grow(&vec, 5);

  TEST_ASSERT_TRUE(pillar_status_is_ok(status));
  TEST_ASSERT_EQUAL(10, vec.cap);

  pillar_raw_vec_deinit(&vec);
}

void test_raw_vec_shrink_reduces_capacity(void) {
  struct Pillar_RawVec vec;
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);

  pillar_raw_vec_init_with(&vec, layout, allocator, 20);

  for (int i = 0; i < 5; i++) {
    pillar_raw_vec_append(&vec, (Pillar_U8 *)&i);
  }

  struct Pillar_Status status = pillar_raw_vec_shrink(&vec);

  TEST_ASSERT_TRUE(pillar_status_is_ok(status));
  TEST_ASSERT_EQUAL(5, vec.len);
  TEST_ASSERT_EQUAL(5, vec.cap);

  int *data = (int *)vec.data;
  for (int i = 0; i < 5; i++) {
    TEST_ASSERT_EQUAL(i, data[i]);
  }

  pillar_raw_vec_deinit(&vec);
}

void test_raw_vec_shrink_when_len_equals_cap(void) {
  struct Pillar_RawVec vec;
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);

  pillar_raw_vec_init_with(&vec, layout, allocator, 5);

  for (int i = 0; i < 5; i++) {
    pillar_raw_vec_append(&vec, (Pillar_U8 *)&i);
  }

  struct Pillar_Status status = pillar_raw_vec_shrink(&vec);

  TEST_ASSERT_TRUE(pillar_status_is_ok(status));
  TEST_ASSERT_EQUAL(5, vec.len);
  TEST_ASSERT_EQUAL(5, vec.cap);

  pillar_raw_vec_deinit(&vec);
}

void test_raw_vec_shrink_when_empty(void) {
  struct Pillar_RawVec vec;
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);

  pillar_raw_vec_init_with(&vec, layout, allocator, 10);

  struct Pillar_Status status = pillar_raw_vec_shrink(&vec);

  TEST_ASSERT_TRUE(pillar_status_is_ok(status));
  TEST_ASSERT_EQUAL(0, vec.len);
  TEST_ASSERT_EQUAL(0, vec.cap);
  TEST_ASSERT_NULL(vec.data);

  pillar_raw_vec_deinit(&vec);
}

void test_raw_vec_at_valid_index(void) {
  struct Pillar_RawVec vec;
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);

  pillar_raw_vec_init_with(&vec, layout, allocator, 10);

  for (int i = 0; i < 5; i++) {
    pillar_raw_vec_append(&vec, (Pillar_U8 *)&i);
  }

  for (Pillar_Usize i = 0; i < 5; i++) {
    Pillar_U8 *ptr;
    struct Pillar_Status status = pillar_raw_vec_at(&vec, i, &ptr);

    TEST_ASSERT_TRUE(pillar_status_is_ok(status));
    TEST_ASSERT_NOT_NULL(ptr);
    TEST_ASSERT_EQUAL((int)i, *(int *)ptr);
  }

  pillar_raw_vec_deinit(&vec);
}

void test_raw_vec_at_out_of_bounds(void) {
  struct Pillar_RawVec vec;
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);

  pillar_raw_vec_init_with(&vec, layout, allocator, 10);

  for (int i = 0; i < 5; i++) {
    pillar_raw_vec_append(&vec, (Pillar_U8 *)&i);
  }

  Pillar_U8 *ptr;
  struct Pillar_Status status = pillar_raw_vec_at(&vec, 5, &ptr);

  TEST_ASSERT_FALSE(pillar_status_is_ok(status));
  TEST_ASSERT_EQUAL(PILLAR_VEC_CODE_OUT_OF_BOUNDS, status.code);

  pillar_raw_vec_deinit(&vec);
}

void test_raw_vec_at_null_vec(void) {
  Pillar_U8 *ptr;
  struct Pillar_Status status = pillar_raw_vec_at(NULL, 0, &ptr);

  TEST_ASSERT_FALSE(pillar_status_is_ok(status));
  TEST_ASSERT_EQUAL(PILLAR_VEC_CODE_INVALID_ARGUMENT, status.code);
}

void test_raw_vec_at_null_out(void) {
  struct Pillar_RawVec vec;
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);

  pillar_raw_vec_init_with(&vec, layout, allocator, 10);

  int value = 42;
  pillar_raw_vec_append(&vec, (Pillar_U8 *)&value);

  struct Pillar_Status status = pillar_raw_vec_at(&vec, 0, NULL);

  TEST_ASSERT_FALSE(pillar_status_is_ok(status));
  TEST_ASSERT_EQUAL(PILLAR_VEC_CODE_INVALID_ARGUMENT, status.code);

  pillar_raw_vec_deinit(&vec);
}

void test_raw_vec_complex_sequence(void) {
  struct Pillar_RawVec vec;
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);

  pillar_raw_vec_init_with(&vec, layout, allocator, 4);

  for (int i = 0; i < 5; i++) {
    int value = i * 10;
    pillar_raw_vec_append(&vec, (Pillar_U8 *)&value);
  }

  TEST_ASSERT_EQUAL(5, vec.len);

  int value = 999;
  pillar_raw_vec_prepend(&vec, (Pillar_U8 *)&value);
  TEST_ASSERT_EQUAL(6, vec.len);

  int result;
  pillar_raw_vec_shift(&vec, (Pillar_U8 *)&result);
  TEST_ASSERT_EQUAL(999, result);
  TEST_ASSERT_EQUAL(5, vec.len);

  pillar_raw_vec_pop(&vec, (Pillar_U8 *)&result);
  TEST_ASSERT_EQUAL(40, result);
  TEST_ASSERT_EQUAL(4, vec.len);

  Pillar_U8 *ptr;
  pillar_raw_vec_at(&vec, 2, &ptr);
  TEST_ASSERT_EQUAL(20, *(int *)ptr);

  pillar_raw_vec_shrink(&vec);
  TEST_ASSERT_EQUAL(4, vec.cap);

  pillar_raw_vec_deinit(&vec);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_raw_vec_init_with_creates_vector);
  RUN_TEST(test_raw_vec_init_with_null_pointer);
  RUN_TEST(test_raw_vec_init_with_invalid_allocator);
  RUN_TEST(test_raw_vec_deinit_null_pointer);

  RUN_TEST(test_raw_vec_append_single_element);
  RUN_TEST(test_raw_vec_append_multiple_elements);
  RUN_TEST(test_raw_vec_append_grows_when_full);
  RUN_TEST(test_raw_vec_append_null_vec);
  RUN_TEST(test_raw_vec_append_null_item);

  RUN_TEST(test_raw_vec_pop_single_element);
  RUN_TEST(test_raw_vec_pop_multiple_elements);
  RUN_TEST(test_raw_vec_pop_from_empty);
  RUN_TEST(test_raw_vec_pop_null_vec);
  RUN_TEST(test_raw_vec_pop_null_out);

  RUN_TEST(test_raw_vec_prepend_single_element);
  RUN_TEST(test_raw_vec_prepend_multiple_elements);
  RUN_TEST(test_raw_vec_prepend_grows_when_full);

  RUN_TEST(test_raw_vec_shift_single_element);
  RUN_TEST(test_raw_vec_shift_multiple_elements);
  RUN_TEST(test_raw_vec_shift_from_empty);

  RUN_TEST(test_raw_vec_grow_increases_capacity);
  RUN_TEST(test_raw_vec_grow_preserves_data);
  RUN_TEST(test_raw_vec_grow_with_smaller_cap_does_nothing);

  RUN_TEST(test_raw_vec_shrink_reduces_capacity);
  RUN_TEST(test_raw_vec_shrink_when_len_equals_cap);
  RUN_TEST(test_raw_vec_shrink_when_empty);

  RUN_TEST(test_raw_vec_at_valid_index);
  RUN_TEST(test_raw_vec_at_out_of_bounds);
  RUN_TEST(test_raw_vec_at_null_vec);
  RUN_TEST(test_raw_vec_at_null_out);

  RUN_TEST(test_raw_vec_complex_sequence);

  return UNITY_END();
}
