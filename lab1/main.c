/*
  memlab/main.c
  Build: gcc -g -O0 -fno-omit-frame-pointer -Wall -Wextra -std=c11 main.c -o memlab
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* --------- Globals / literals ---------- */
int g_int = 12345;
int g_arr[5] = {10,20,30,40,50};
static int g_static = 777;

const char *g_cstr = "GLOBAL_CONST_STRING";
const int g_const_int = 42;

/* --------- Helpers ---------- */
static void marker(const char *tag) {
  // Place breakpoint here occasionally if you want a consistent stop-point.
  printf("[marker] %s\n", tag);
}

/* 1) Where does this live? */
void part1_locations(void) {
  int local = 7;
  static int local_static = 88;
  const char *lit = "LITERAL_IN_CODE_SECTION";
  int *heap = (int*)malloc(sizeof(int));
  *heap = 999;

  marker("part1");
  printf("local=%d local_static=%d lit=%s heap=%d\n", local, local_static, lit, *heap);

  free(heap);
}

/* 2-4) Stack usage / reorder locals / caller vs callee */

void part2_stack_measure(int param) {
  char a = 'A';
  int  b = 0x11223344;
  double c = 3.14159;
  long long d = 0x0102030405060708LL;
  int arr[7] = {0,1,2,3,4,5,6};

  marker("part2");
  printf("%d %c %f %lld %d\n", param, a, c, d, arr[0]);
}

/* 3) Reordered locals (same data, different order) */

void part3_reorder(int param) {
  double c = 3.14159;
  long long d = 0x0102030405060708LL;
  int arr[7] = {0,1,2,3,4,5,6};
  int  b = 0x11223344;
  char a = 'A';

  marker("part3");
  printf("%d %c %f %lld %d\n", param, a, c, d, arr[0]);
}

/* 5-6) Raw stack memory (endianness) + disassembly mapping */

void part5_endianness(void) {
  uint32_t x = 0xA1B2C3D4;
  uint16_t y = 0x1122;
  marker("part5");
  printf("x=%08X y=%04X\n", x, y);
}

/* 7) Prove const strings and globals are not on the stack */

void part7_not_stack(void) {
  int local = 1;
  const char *s1 = "HELLO";
  const char *s2 = g_cstr;
  marker("part7");
  printf("%d %s %s\n", local, s1, s2);
}

/* 8) Watchpoints */

void part8_watchpoints(void) {
  int counter = 0;
  marker("part8_before");
  counter += 1;
  counter += 2;
  counter += 3;
  marker("part8_after");
  printf("counter=%d\n", counter);
}

/* 9) Recursion */

int part9_recurse(int n) {
  int local = 100 + n;
  marker("part9");
  if (n <= 0) return local;
  return local + part9_recurse(n-1);
}

/* 10) Stack vs heap growth direction */

void part10_growth(void) {
  int local1 = 1;
  int *heap1 = malloc(4);
  int local2 = 2;
  int *heap2 = malloc(4);
  marker("part10");
  printf("locals: %p %p  heaps: %p %p\n", (void*)&local1, (void*)&local2, (void*)heap1, (void*)heap2);
  free(heap1); free(heap2);
}

/* 11) Struct padding */
typedef struct {
  char  c1;
  int   i;
  char  c2;
  short s;
} Padded;


void part11_struct(void) {
  Padded p = { .c1='X', .i=0x12345678, .c2='Y', .s=0x2222 };
  marker("part11");
  printf("%c %X %c %X\n", p.c1, p.i, p.c2, (unsigned)p.s);
}

/* 12) Pointer aliasing */

void part12_alias(void) {
  int value = 10;
  int *p = &value;
  int *q = &value;
  marker("part12_before");
  *p = 99;
  marker("part12_after");
  printf("%d %d\n", *p, *q);
}

/* 13) Array decay vs &array */

void part13_decay(void) {
  int a[4] = {11,22,33,44};
  int *p = a;
  int (*pa)[4] = &a;
  marker("part13");
  printf("%p %p %d\n", (void*)p, (void*)pa, a[0]);
}

/* 14) Call by value vs call by pointer */

void inc_by_value(int x) { x += 1; marker("inc_by_value"); }

void inc_by_ptr(int *x)  { (*x) += 1; marker("inc_by_ptr"); }


void part14_calls(void) {
  int v = 5;
  marker("part14_before");
  inc_by_value(v);
  inc_by_ptr(&v);
  marker("part14_after");
  printf("v=%d\n", v);
}

/* 15) Use-after-return (safe demo of stack reuse) */

int* bad_return_addr(void) {
  int local = 123;
  marker("bad_return_addr");
  int* volatile p = &local;  
  return p; // UB: DO NOT dereference in C; only observe in debugger.
}

void reuse_stack_slot(void) {
  int another = 999;
  marker("reuse_stack_slot");
  printf("%d\n", another);
}

/* 16) String literal vs stack buffer */

void part16_str_literal_vs_array(void) {
  char *s1 = "hi";
  char s2[] = "hi";
  marker("part16");
  printf("%s %s\n", s1, s2);
}

/* 17) Instruction memory vs data memory */

void part17_pc_sp(void) {
  int local = 7;
  marker("part17");
  printf("%d %d\n", local, g_int);
}

/* 18) Observe a 1D array */

void part18_array1d(void) {
  uint32_t a[6] = {0x11111111,0x22222222,0x33333333,0x44444444,0x55555555,0x66666666};
  marker("part18");
  printf("%u\n", a[0]);
}

/* 19) Out-of-bounds array write (controlled) */

void part19_oob_controlled(void) {
  int guard1 = 1111;
  int a[4] = {1,2,3,4};
  int guard2 = 2222;
  marker("part19_before");
  a[4] = 9999; // ONE element past end (UB). Only for debugger observation.
  marker("part19_after");
  printf("%d %d %d\n", guard1, a[0], guard2);
}

/* 20-25) String buffer observation + edits */

void part20_string_buffer(void) {
  char buf[16] = "ABCDEFGHIJKLMNO";
  marker("part20");
  printf("%s\n", buf);
}

/* 26) strlen vs sizeof */

void part26_strlen_sizeof(void) {
  char s[] = "hello";
  char *p = "hello";
  marker("part26");
  printf("%zu %zu %zu %zu\n", sizeof(s), strlen(s), sizeof(p), strlen(p));
}

/* 27-28) 2D contiguous layout and passing */
#define R 3
#define C 4

void takes_2d(int a[][C]) { marker("takes_2d"); a[2][3] += 1; }


void part27_2d_contig(void) {
  int a[R][C] = {
    { 1, 2, 3, 4 },
    { 5, 6, 7, 8 },
    { 9,10,11,12 }
  };
  marker("part27_before");
  takes_2d(a);
  marker("part27_after");
  printf("%d\n", a[2][3]);
}

/* 29) Jagged array */

void part29_jagged(void) {
  int *rows[R];
  for (int i=0;i<R;i++) {
    rows[i] = (int*)malloc(C * sizeof(int));
    for (int j=0;j<C;j++) rows[i][j] = 100*i + j;
  }
  marker("part29");
  printf("%d\n", rows[2][3]);
  for (int i=0;i<R;i++) free(rows[i]);
}

/* 30) Dynamic 2D: contiguous vs jagged */

void part30_dynamic2d_compare(void) {
  int *contig = (int*)malloc(R*C*sizeof(int));
  int **jag = (int**)malloc(R*sizeof(int*));
  for (int i=0;i<R;i++) {
    jag[i] = (int*)malloc(C*sizeof(int));
  }
  marker("part30");
  printf("%p %p %p\n", (void*)contig, (void*)jag, (void*)jag[0]);

  for (int i=0;i<R;i++) free(jag[i]);
  free(jag);
  free(contig);
}

int main(void) {
  part1_locations();
  part2_stack_measure(1);
  part3_reorder(2);
  part5_endianness();
  part7_not_stack();
  part8_watchpoints();
  (void)part9_recurse(3);
  part10_growth();
  part11_struct();
  part12_alias();
  part13_decay();
  part14_calls();

  int *addr = bad_return_addr();
  reuse_stack_slot();
  // do NOT dereference addr in C; debugger-only observation is allowed.
  printf("addr=%p\n", (void*)addr);

  part16_str_literal_vs_array();
  part17_pc_sp();
  part18_array1d();
  part19_oob_controlled();
  part20_string_buffer();
  part26_strlen_sizeof();
  part27_2d_contig();
  part29_jagged();
  part30_dynamic2d_compare();
  return 0;
}