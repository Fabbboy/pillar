extern "C" {
#include <pillar-c/intrin.h>
#include <pillar-c/types.h>
#include <unity.h>
}

void setUp(void) {
  // This is run before EACH TEST
}

void tearDown(void) {
  // This is run after EACH TEST
}

void test_trailing_zeros_zero_input(void) {
  Pillar_Usize result = pillar_trailing_zeros(0);
  TEST_ASSERT_EQUAL(sizeof(Pillar_Usize) * 8, result);
}

void test_trailing_zeros_one(void) {
  Pillar_Usize result = pillar_trailing_zeros(1);
  TEST_ASSERT_EQUAL(0, result);
}

void test_trailing_zeros_power_of_two(void) {
  TEST_ASSERT_EQUAL(1, pillar_trailing_zeros(2));
  TEST_ASSERT_EQUAL(2, pillar_trailing_zeros(4));
  TEST_ASSERT_EQUAL(3, pillar_trailing_zeros(8));
  TEST_ASSERT_EQUAL(4, pillar_trailing_zeros(16));
  TEST_ASSERT_EQUAL(5, pillar_trailing_zeros(32));
  TEST_ASSERT_EQUAL(6, pillar_trailing_zeros(64));
}

void test_trailing_zeros_arbitrary_values(void) {
  TEST_ASSERT_EQUAL(0, pillar_trailing_zeros(7));
  TEST_ASSERT_EQUAL(2, pillar_trailing_zeros(12));
  TEST_ASSERT_EQUAL(3, pillar_trailing_zeros(24));
  TEST_ASSERT_EQUAL(4, pillar_trailing_zeros(48));
}

void test_leading_zeros_zero_input(void) {
  Pillar_Usize result = pillar_leading_zeros(0);
  TEST_ASSERT_EQUAL(sizeof(Pillar_Usize) * 8, result);
}

void test_leading_zeros_one(void) {
  Pillar_Usize result = pillar_leading_zeros(1);
  TEST_ASSERT_EQUAL(sizeof(Pillar_Usize) * 8 - 1, result);
}

void test_leading_zeros_power_of_two(void) {
  Pillar_Usize bits = sizeof(Pillar_Usize) * 8;

  TEST_ASSERT_EQUAL(bits - 2, pillar_leading_zeros(2));
  TEST_ASSERT_EQUAL(bits - 3, pillar_leading_zeros(4));
  TEST_ASSERT_EQUAL(bits - 4, pillar_leading_zeros(8));
  TEST_ASSERT_EQUAL(bits - 5, pillar_leading_zeros(16));
  TEST_ASSERT_EQUAL(bits - 6, pillar_leading_zeros(32));
  TEST_ASSERT_EQUAL(bits - 7, pillar_leading_zeros(64));
}

void test_leading_zeros_max_value(void) {
  Pillar_Usize max_val = (Pillar_Usize)-1;
  TEST_ASSERT_EQUAL(0, pillar_leading_zeros(max_val));
}

void test_popcount_zero(void) {
  TEST_ASSERT_EQUAL(0, pillar_popcount(0));
}

void test_popcount_one(void) {
  TEST_ASSERT_EQUAL(1, pillar_popcount(1));
}

void test_popcount_all_bits_set(void) {
  Pillar_Usize max_val = (Pillar_Usize)-1;
  TEST_ASSERT_EQUAL(sizeof(Pillar_Usize) * 8, pillar_popcount(max_val));
}

void test_popcount_single_bit(void) {
  TEST_ASSERT_EQUAL(1, pillar_popcount(1));
  TEST_ASSERT_EQUAL(1, pillar_popcount(2));
  TEST_ASSERT_EQUAL(1, pillar_popcount(4));
  TEST_ASSERT_EQUAL(1, pillar_popcount(8));
  TEST_ASSERT_EQUAL(1, pillar_popcount(16));
}

void test_popcount_multiple_bits(void) {
  TEST_ASSERT_EQUAL(2, pillar_popcount(3));
  TEST_ASSERT_EQUAL(3, pillar_popcount(7));
  TEST_ASSERT_EQUAL(4, pillar_popcount(15));
  TEST_ASSERT_EQUAL(5, pillar_popcount(31));
  TEST_ASSERT_EQUAL(2, pillar_popcount(5));
  TEST_ASSERT_EQUAL(3, pillar_popcount(14));
}

void test_npow2_zero(void) {
  TEST_ASSERT_EQUAL(1, pillar_npow2(0));
}

void test_npow2_one(void) {
  TEST_ASSERT_EQUAL(1, pillar_npow2(1));
}

void test_npow2_power_of_two(void) {
  TEST_ASSERT_EQUAL(2, pillar_npow2(2));
  TEST_ASSERT_EQUAL(4, pillar_npow2(4));
  TEST_ASSERT_EQUAL(8, pillar_npow2(8));
  TEST_ASSERT_EQUAL(16, pillar_npow2(16));
  TEST_ASSERT_EQUAL(32, pillar_npow2(32));
}

void test_npow2_non_power_of_two(void) {
  TEST_ASSERT_EQUAL(4, pillar_npow2(3));
  TEST_ASSERT_EQUAL(8, pillar_npow2(5));
  TEST_ASSERT_EQUAL(8, pillar_npow2(6));
  TEST_ASSERT_EQUAL(8, pillar_npow2(7));
  TEST_ASSERT_EQUAL(16, pillar_npow2(9));
  TEST_ASSERT_EQUAL(16, pillar_npow2(15));
  TEST_ASSERT_EQUAL(32, pillar_npow2(17));
  TEST_ASSERT_EQUAL(32, pillar_npow2(31));
  TEST_ASSERT_EQUAL(64, pillar_npow2(33));
}

void test_ppow2_zero(void) {
  TEST_ASSERT_EQUAL(1, pillar_ppow2(0));
}

void test_ppow2_one(void) {
  TEST_ASSERT_EQUAL(1, pillar_ppow2(1));
}

void test_ppow2_power_of_two(void) {
  TEST_ASSERT_EQUAL(2, pillar_ppow2(2));
  TEST_ASSERT_EQUAL(4, pillar_ppow2(4));
  TEST_ASSERT_EQUAL(8, pillar_ppow2(8));
  TEST_ASSERT_EQUAL(16, pillar_ppow2(16));
  TEST_ASSERT_EQUAL(32, pillar_ppow2(32));
  TEST_ASSERT_EQUAL(64, pillar_ppow2(64));
}

void test_ppow2_non_power_of_two(void) {
  TEST_ASSERT_EQUAL(2, pillar_ppow2(3));
  TEST_ASSERT_EQUAL(4, pillar_ppow2(5));
  TEST_ASSERT_EQUAL(4, pillar_ppow2(6));
  TEST_ASSERT_EQUAL(4, pillar_ppow2(7));
  TEST_ASSERT_EQUAL(8, pillar_ppow2(9));
  TEST_ASSERT_EQUAL(8, pillar_ppow2(10));
  TEST_ASSERT_EQUAL(8, pillar_ppow2(15));
  TEST_ASSERT_EQUAL(16, pillar_ppow2(17));
  TEST_ASSERT_EQUAL(16, pillar_ppow2(31));
  TEST_ASSERT_EQUAL(32, pillar_ppow2(33));
}

void test_npow2_and_ppow2_relationship(void) {
  for (Pillar_Usize i = 2; i < 100; i++) {
    Pillar_Usize next = pillar_npow2(i);
    Pillar_Usize prev = pillar_ppow2(i);

    TEST_ASSERT_TRUE(next >= i);
    TEST_ASSERT_TRUE(prev <= i);

    if ((i & (i - 1)) == 0) {
      TEST_ASSERT_EQUAL(i, next);
      TEST_ASSERT_EQUAL(i, prev);
    }
  }
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_trailing_zeros_zero_input);
  RUN_TEST(test_trailing_zeros_one);
  RUN_TEST(test_trailing_zeros_power_of_two);
  RUN_TEST(test_trailing_zeros_arbitrary_values);

  RUN_TEST(test_leading_zeros_zero_input);
  RUN_TEST(test_leading_zeros_one);
  RUN_TEST(test_leading_zeros_power_of_two);
  RUN_TEST(test_leading_zeros_max_value);

  RUN_TEST(test_popcount_zero);
  RUN_TEST(test_popcount_one);
  RUN_TEST(test_popcount_all_bits_set);
  RUN_TEST(test_popcount_single_bit);
  RUN_TEST(test_popcount_multiple_bits);

  RUN_TEST(test_npow2_zero);
  RUN_TEST(test_npow2_one);
  RUN_TEST(test_npow2_power_of_two);
  RUN_TEST(test_npow2_non_power_of_two);

  RUN_TEST(test_ppow2_zero);
  RUN_TEST(test_ppow2_one);
  RUN_TEST(test_ppow2_power_of_two);
  RUN_TEST(test_ppow2_non_power_of_two);

  RUN_TEST(test_npow2_and_ppow2_relationship);

  return UNITY_END();
}
