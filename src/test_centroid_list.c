#include "unity.h"
#include "centroid_list.h"
#include "centroid.h"

void setUp() {}
void tearDown() {}

void test_init_free() {
  CentroidList* cl = centroid_list_init();

  TEST_ASSERT_NOT_NULL(cl);
  TEST_ASSERT_EQUAL_INT(0, centroid_list_getSize(cl));
  TEST_ASSERT_NULL(centroid_list_getNext(cl));

  centroid_list_free(cl);
}

void test_append() {
  CentroidList* cl = centroid_list_init();
  TEST_ASSERT_NOT_NULL(cl);

  Centroid c1 = {
    .color = {255, 255, 255},
    .point = {1, 1}
  };

  Centroid c2 = {
    .color = {255, 255, 255},
    .point = {2, 2}
  };

  centroid_list_append(cl, c1);
  centroid_list_append(cl, c2);

  TEST_ASSERT_EQUAL_INT(2, centroid_list_getSize(cl));

  Centroid* cp = centroid_list_getNext(cl);
  TEST_ASSERT_NOT_NULL(cp);
  TEST_ASSERT_EQUAL_INT(1, cp->point.x);

  cp = centroid_list_getNext(cl);
  TEST_ASSERT_NOT_NULL(cp);
  TEST_ASSERT_EQUAL_INT(2, cp->point.x);

  cp = centroid_list_getNext(cl);
  TEST_ASSERT_NULL(cp);

  centroid_list_free(cl);
}

void test_remove() {
  CentroidList* cl = centroid_list_init();
  TEST_ASSERT_NOT_NULL(cl);

  Centroid c1 = {
    .color = {255, 255, 255},
    .point = {1, 1}
  };

  Centroid c2 = {
    .color = {255, 255, 255},
    .point = {2, 2}
  };

  Centroid c3 = {
    .color = {255, 255, 255},
    .point = {3, 3}
  };

  centroid_list_append(cl, c1);
  centroid_list_append(cl, c2);
  centroid_list_append(cl, c3);

  // remove the middle
  centroid_list_remove(cl, 1);
  TEST_ASSERT_EQUAL_INT(2, centroid_list_getSize(cl));

  Centroid* cp = centroid_list_getNext(cl);
  TEST_ASSERT_NOT_NULL(cp);
  TEST_ASSERT_EQUAL_INT(1, cp->point.x);

  cp = centroid_list_getNext(cl);
  TEST_ASSERT_NOT_NULL(cp);
  TEST_ASSERT_EQUAL_INT(3, cp->point.x);

  cp = centroid_list_getNext(cl);
  TEST_ASSERT_NULL(cp);

  // remove the tail
  centroid_list_remove(cl, 1);
  centroid_list_resetIterator(cl);
  TEST_ASSERT_EQUAL_INT(1, centroid_list_getSize(cl));

  cp = centroid_list_getNext(cl);
  TEST_ASSERT_NOT_NULL(cp);
  TEST_ASSERT_EQUAL_INT(1, cp->point.x);

  cp = centroid_list_getNext(cl);
  TEST_ASSERT_NULL(cp);

  // remove the head
  centroid_list_remove(cl, 0);
  centroid_list_resetIterator(cl);
  TEST_ASSERT_EQUAL_INT(0, centroid_list_getSize(cl));

  cp = centroid_list_getNext(cl);
  TEST_ASSERT_NULL(cp);

  centroid_list_free(cl);
}

void test_setIterator() {
  CentroidList* cl = centroid_list_init();
  TEST_ASSERT_NOT_NULL(cl);

  Centroid c1 = {
    .color = {255, 255, 255},
    .point = {1, 1}
  };

  Centroid c2 = {
    .color = {255, 255, 255},
    .point = {2, 2}
  };

  Centroid c3 = {
    .color = {255, 255, 255},
    .point = {3, 3}
  };

  centroid_list_append(cl, c1);
  centroid_list_append(cl, c2);
  centroid_list_append(cl, c3);

  centroid_list_setIterator(cl, 2);
  Centroid* cp = centroid_list_getNext(cl);

  TEST_ASSERT_EQUAL_INT(3, cp->point.x);
}

void test_removeClosest() {
  CentroidList* cl = centroid_list_init();
  TEST_ASSERT_NOT_NULL(cl);

  Centroid c1 = {
    .color = {255, 255, 255},
    .point = {100, 100}
  };

  Centroid c2 = {
    .color = {255, 255, 255},
    .point = {1, 1}
  };

  Centroid c3 = {
    .color = {255, 255, 255},
    .point = {500, 500}
  };

  centroid_list_append(cl, c1);
  centroid_list_append(cl, c2);
  centroid_list_append(cl, c3);

  centroid_list_removeClosest(cl, (Point) {0, 0}, 1000);
  TEST_ASSERT_EQUAL_INT(2, centroid_list_getSize(cl));

  Centroid* cp = centroid_list_getNext(cl);
  TEST_ASSERT_NOT_NULL(cp);
  TEST_ASSERT_EQUAL_INT(100, cp->point.x);

  cp = centroid_list_getNext(cl);
  TEST_ASSERT_NOT_NULL(cp);
  TEST_ASSERT_EQUAL_INT(500, cp->point.x);

  cp = centroid_list_getNext(cl);
  TEST_ASSERT_NULL(cp);
}

void test_getNth() {
  CentroidList* cl = centroid_list_init();
  TEST_ASSERT_NOT_NULL(cl);

  Centroid c1 = {
    .color = {255, 255, 255},
    .point = {100, 100}
  };

  Centroid c2 = {
    .color = {255, 255, 255},
    .point = {1, 1}
  };

  Centroid c3 = {
    .color = {255, 255, 255},
    .point = {500, 500}
  };

  centroid_list_append(cl, c1);
  centroid_list_append(cl, c2);
  centroid_list_append(cl, c3);

  Centroid* c = centroidListGetNth(cl, 1);
  TEST_ASSERT_EQUAL_INT(1, c->point.x);
}

// NB:
// - Centroid* centroid_list_getNext(CentroidList* pl)
// - void centroid_list_resetIterator(CentroidList* pl)
// - size_t centroid_list_getSize(CentroidList* cl)
// are tested implicitly

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_init_free);
  RUN_TEST(test_append);
  RUN_TEST(test_remove);
  RUN_TEST(test_setIterator);
  RUN_TEST(test_removeClosest);
  RUN_TEST(test_getNth);

  return UNITY_END();
}
