#include "test.h"

TEST_START("reopen test", "reopen")
  char* result = NULL;

  /* reopen empty database */
  assert(bp__close(&db) == BP_OK);
  assert(bp__open(&db, __db_file) == BP_OK);
  assert(bp_get_s(&db, "key-1", &result) == BP_ENOTFOUND);

  /* write some stuff */
  assert(bp_set_s(&db, "key-1", "val-1") == BP_OK);
  assert(bp_get_s(&db, "key-1", &result) == BP_OK);
  assert(strncmp(result, "val-1", 5) == 0);
  free(result);
  result = NULL;

  /* reopen database */
  assert(bp__close(&db) == BP_OK);
  assert(bp__open(&db, __db_file) == BP_OK);

  /* ensure that stuff is still in */
  assert(bp_get_s(&db, "key-1", &result) == BP_OK);
  assert(strncmp(result, "val-1", 5) == 0);
  free(result);
  result = NULL;

  /* add another stuff */
  assert(bp_set_s(&db, "key-2", "val-2") == BP_OK);
  assert(bp_get_s(&db, "key-2", &result) == BP_OK);
  assert(strncmp(result, "val-2", 5) == 0);
  free(result);
  result = NULL;
TEST_END("reopen test", "reopen")
