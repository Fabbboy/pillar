extern "C" {
#include <pillar-c/status.h>
#include <unity.h>
}

void setUp(void) {
  // This is run before EACH TEST
}

void tearDown(void) {
  // This is run after EACH TEST
}

void test_status_ok_creates_ok_status(void) {
  struct Pillar_Status status = pillar_status_ok();

  TEST_ASSERT_EQUAL_UINT16(PILLAR_STATUS_OK, status.domain);
  TEST_ASSERT_EQUAL_UINT16(PILLAR_STATUS_OK, status.code);
}

void test_status_ok_is_recognized_as_ok(void) {
  struct Pillar_Status status = pillar_status_ok();

  TEST_ASSERT_TRUE(pillar_status_is_ok(status));
}

void test_status_init_creates_status_with_domain_and_code(void) {
  Pillar_U16 domain = 100;
  Pillar_U16 code = 200;

  struct Pillar_Status status = pillar_status_init(domain, code);

  TEST_ASSERT_EQUAL_UINT16(domain, status.domain);
  TEST_ASSERT_EQUAL_UINT16(code, status.code);
}

void test_status_init_creates_error_status(void) {
  struct Pillar_Status status = pillar_status_init(1, 1);

  TEST_ASSERT_FALSE(pillar_status_is_ok(status));
}

void test_status_is_ok_checks_code_field(void) {
  struct Pillar_Status ok_status1 = {0, 0};
  struct Pillar_Status ok_status2 = {1, 0};
  struct Pillar_Status ok_status3 = {100, 0};
  struct Pillar_Status error_status1 = {0, 1};
  struct Pillar_Status error_status2 = {1, 1};
  struct Pillar_Status error_status3 = {100, 200};

  TEST_ASSERT_TRUE(pillar_status_is_ok(ok_status1));
  TEST_ASSERT_TRUE(pillar_status_is_ok(ok_status2));
  TEST_ASSERT_TRUE(pillar_status_is_ok(ok_status3));
  TEST_ASSERT_FALSE(pillar_status_is_ok(error_status1));
  TEST_ASSERT_FALSE(pillar_status_is_ok(error_status2));
  TEST_ASSERT_FALSE(pillar_status_is_ok(error_status3));
}

void test_status_size_is_32_bits(void) {
  TEST_ASSERT_EQUAL_size_t(sizeof(Pillar_U32), sizeof(struct Pillar_Status));
}

void test_status_constants_have_correct_values(void) {
  TEST_ASSERT_EQUAL(0, PILLAR_STATUS_OK);
  TEST_ASSERT_EQUAL(1, PILLAR_STATUS_START);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_status_ok_creates_ok_status);
  RUN_TEST(test_status_ok_is_recognized_as_ok);
  RUN_TEST(test_status_init_creates_status_with_domain_and_code);
  RUN_TEST(test_status_init_creates_error_status);
  RUN_TEST(test_status_is_ok_checks_code_field);
  RUN_TEST(test_status_size_is_32_bits);
  RUN_TEST(test_status_constants_have_correct_values);

  return UNITY_END();
}
