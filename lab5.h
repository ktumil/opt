#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <memory.h>
#include <malloc.h>
#include <papi.h>

void PAPI_init();
void start_cache_test();
void stop_cache_test();
void start_fp_ops_test();
void stop_fp_ops_test();
void start_acc_wait_test();
void stop_acc_wait_test();
static void test(char *file, int line, char *call, int retval);
