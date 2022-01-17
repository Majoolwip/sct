SCT - Simple C Test
-------------------
Simple C Test (SCT) is aimed at being a very straight forward testing framework
for C.

Example
---
```
SCT_Test(addTest) {
    int a = 5;
    int b = 6;
    SCT_ASSERT(a + b == 11);
}

int main(char *args) {
  (void)args;
  SCT_Test tests[] = {{.fn = addTest, .name = "addTest"}};
  return sct_run_tests(tests, sizeof(tests) / sizeof(tests[0]));
}
```