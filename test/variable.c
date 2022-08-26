#include "test.h"

int g1, g2[4];

int main() {
  // [10] 支持单字母变量
  ASSERT(3, ({ int a; a=3; a; }));
  ASSERT(3, ({ int a=3; a; }));
  ASSERT(8, ({ int a=3; int z=5; a+z; }));

  // [11] 支持多字母变量
  ASSERT(3, ({ int a=3; a; }));
  ASSERT(8, ({ int a=3; int z=5; a+z; }));
  ASSERT(6, ({ int a; int b; a=b=3; a+b; }));
  ASSERT(3, ({ int foo=3; foo; }));
  ASSERT(8, ({ int foo123=3; int bar=5; foo123+bar; }));

  // [30] 支持 sizeof
  ASSERT(8, ({ int x; sizeof(x); }));
  ASSERT(8, ({ int x; sizeof x; }));
  ASSERT(8, ({ int *x; sizeof(x); }));
  ASSERT(32, ({ int x[4]; sizeof(x); }));
  ASSERT(96, ({ int x[3][4]; sizeof(x); }));
  ASSERT(32, ({ int x[3][4]; sizeof(*x); }));
  ASSERT(8, ({ int x[3][4]; sizeof(**x); }));
  ASSERT(9, ({ int x[3][4]; sizeof(**x) + 1; }));
  ASSERT(9, ({ int x[3][4]; sizeof **x + 1; }));
  ASSERT(8, ({ int x[3][4]; sizeof(**x + 1); }));
  ASSERT(8, ({ int x=1; sizeof(x=2); }));
  ASSERT(1, ({ int x=1; sizeof(x=2); x; }));

  ASSERT(0, g1);
  ASSERT(3, ({ g1=3; g1; }));
  ASSERT(0, ({ g2[0]=0; g2[1]=1; g2[2]=2; g2[3]=3; g2[0]; }));
  ASSERT(1, ({ g2[0]=0; g2[1]=1; g2[2]=2; g2[3]=3; g2[1]; }));
  ASSERT(2, ({ g2[0]=0; g2[1]=1; g2[2]=2; g2[3]=3; g2[2]; }));
  ASSERT(3, ({ g2[0]=0; g2[1]=1; g2[2]=2; g2[3]=3; g2[3]; }));

  ASSERT(8, sizeof(g1));
  ASSERT(32, sizeof(g2));

  // [33] 支持char类型
  ASSERT(1, ({ char x=1; x; }));
  ASSERT(1, ({ char x=1; char y=2; x; }));
  ASSERT(2, ({ char x=1; char y=2; y; }));

  ASSERT(1, ({ char x; sizeof(x); }));
  ASSERT(10, ({ char x[10]; sizeof(x); }));

  // [44] 处理域
  ASSERT(2, ({ int x=2; { int x=3; } x; }));
  ASSERT(2, ({ int x=2; { int x=3; } int y=4; x; }));
  ASSERT(3, ({ int x=2; { x=3; } x; }));

  // [51] 对齐局部变量
  ASSERT(15, ({ int x; int y; char z; char *a=&y; char *b=&z; b-a; }));
  ASSERT(1, ({ int x; char y; int z; char *a=&y; char *b=&z; b-a; }));

  printf("OK\n");
  return 0;
}