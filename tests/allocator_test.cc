extern "C" {
#include <pillar-c/allocator.h>
#include <pillar-c/status.h>
#include <pillar-c/types.h>
#include <unity.h>
}

void setUp(void) {
  // This is run before EACH TEST
}

void tearDown(void) {
  // This is run after EACH TEST
}

void test_heap_allocator_basic_alloc_dealloc(void) {
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);
  Pillar_U8 *ptr = NULL;

  struct Pillar_Status status = pillar_allocator_alloc(&allocator, layout, &ptr);

  TEST_ASSERT_TRUE(pillar_status_is_ok(status));
  TEST_ASSERT_NOT_NULL(ptr);

  status = pillar_allocator_dealloc(&allocator, ptr, layout);
  TEST_ASSERT_TRUE(pillar_status_is_ok(status));
}

void test_heap_allocator_multiple_allocations(void) {
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT(int);
  Pillar_U8 *ptr1 = NULL;
  Pillar_U8 *ptr2 = NULL;
  Pillar_U8 *ptr3 = NULL;

  struct Pillar_Status status1 = pillar_allocator_alloc(&allocator, layout, &ptr1);
  struct Pillar_Status status2 = pillar_allocator_alloc(&allocator, layout, &ptr2);
  struct Pillar_Status status3 = pillar_allocator_alloc(&allocator, layout, &ptr3);

  TEST_ASSERT_TRUE(pillar_status_is_ok(status1));
  TEST_ASSERT_TRUE(pillar_status_is_ok(status2));
  TEST_ASSERT_TRUE(pillar_status_is_ok(status3));
  TEST_ASSERT_NOT_NULL(ptr1);
  TEST_ASSERT_NOT_NULL(ptr2);
  TEST_ASSERT_NOT_NULL(ptr3);

  pillar_allocator_dealloc(&allocator, ptr1, layout);
  pillar_allocator_dealloc(&allocator, ptr2, layout);
  pillar_allocator_dealloc(&allocator, ptr3, layout);
}

void test_heap_allocator_different_sizes(void) {
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  Pillar_U8 *small_ptr = NULL;
  Pillar_U8 *medium_ptr = NULL;
  Pillar_U8 *large_ptr = NULL;

  struct Pillar_Layout small_layout = PILLAR_LAYOUT(char);
  struct Pillar_Layout medium_layout = PILLAR_LAYOUT_ARRAY(int, 100);
  struct Pillar_Layout large_layout = PILLAR_LAYOUT_ARRAY(double, 1000);

  struct Pillar_Status status1 = pillar_allocator_alloc(&allocator, small_layout, &small_ptr);
  struct Pillar_Status status2 = pillar_allocator_alloc(&allocator, medium_layout, &medium_ptr);
  struct Pillar_Status status3 = pillar_allocator_alloc(&allocator, large_layout, &large_ptr);

  TEST_ASSERT_TRUE(pillar_status_is_ok(status1));
  TEST_ASSERT_TRUE(pillar_status_is_ok(status2));
  TEST_ASSERT_TRUE(pillar_status_is_ok(status3));
  TEST_ASSERT_NOT_NULL(small_ptr);
  TEST_ASSERT_NOT_NULL(medium_ptr);
  TEST_ASSERT_NOT_NULL(large_ptr);

  pillar_allocator_dealloc(&allocator, small_ptr, small_layout);
  pillar_allocator_dealloc(&allocator, medium_ptr, medium_layout);
  pillar_allocator_dealloc(&allocator, large_ptr, large_layout);
}

void test_heap_allocator_aligned_allocation(void) {
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  Pillar_U8 *ptr = NULL;

  struct Pillar_Layout layout = {64, PILLAR_ALIGNMENT_1SHL4};

  struct Pillar_Status status = pillar_allocator_alloc(&allocator, layout, &ptr);

  TEST_ASSERT_TRUE(pillar_status_is_ok(status));
  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_EQUAL(0, ((uintptr_t)ptr) % 16);

  pillar_allocator_dealloc(&allocator, ptr, layout);
}

void test_allocator_validate_valid_allocator(void) {
  struct Pillar_Allocator heap_alloc = pillar_heap_allocator();

  TEST_ASSERT_TRUE(pillar_allocator_validate(&heap_alloc));
}

void test_allocator_validate_invalid_allocator(void) {
  struct Pillar_Allocator invalid_alloc1 = {NULL, NULL};
  struct Pillar_Allocator invalid_alloc2 = {pillar_heap_allocator().alloc, NULL};
  struct Pillar_Allocator invalid_alloc3 = {NULL, pillar_heap_allocator().dealloc};

  TEST_ASSERT_FALSE(pillar_allocator_validate(&invalid_alloc1));
  TEST_ASSERT_FALSE(pillar_allocator_validate(&invalid_alloc2));
  TEST_ASSERT_FALSE(pillar_allocator_validate(&invalid_alloc3));
}

void test_allocator_validate_null_pointer(void) {
  TEST_ASSERT_FALSE(pillar_allocator_validate(NULL));
}

void test_heap_allocator_write_and_read(void) {
  struct Pillar_Allocator allocator = pillar_heap_allocator();
  struct Pillar_Layout layout = PILLAR_LAYOUT_ARRAY(int, 10);
  Pillar_U8 *ptr = NULL;

  struct Pillar_Status status = pillar_allocator_alloc(&allocator, layout, &ptr);
  TEST_ASSERT_TRUE(pillar_status_is_ok(status));
  TEST_ASSERT_NOT_NULL(ptr);

  int *arr = (int *)ptr;
  for (int i = 0; i < 10; i++) {
    arr[i] = i * 2;
  }

  for (int i = 0; i < 10; i++) {
    TEST_ASSERT_EQUAL_INT(i * 2, arr[i]);
  }

  pillar_allocator_dealloc(&allocator, ptr, layout);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_heap_allocator_basic_alloc_dealloc);
  RUN_TEST(test_heap_allocator_multiple_allocations);
  RUN_TEST(test_heap_allocator_different_sizes);
  RUN_TEST(test_heap_allocator_aligned_allocation);
  RUN_TEST(test_allocator_validate_valid_allocator);
  RUN_TEST(test_allocator_validate_invalid_allocator);
  RUN_TEST(test_allocator_validate_null_pointer);
  RUN_TEST(test_heap_allocator_write_and_read);

  return UNITY_END();
}
