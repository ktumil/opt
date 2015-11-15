#include "lab5.h"

const PAPI_hw_info_t *hwinfo = NULL;

int data_cache_events[2] = { PAPI_L2_DCH, PAPI_L2_DCM };
long long data_cache_values[2];

int fp_ops_events[1] = { PAPI_FP_OPS };
long long fp_ops_values[1];
///*
int mem_acc_wait_events[1] = { PAPI_MEM_SCY };
long long mem_acc_wait_values[1] = { PAPI_MEM_SCY };
//*/
void PAPI_init() {
  int retval;
  if ((retval = PAPI_library_init(PAPI_VER_CURRENT)) != PAPI_VER_CURRENT){
    printf("Error in papi version\n");
    exit(-1);
  }

  if ((hwinfo = PAPI_get_hardware_info()) == NULL) {
    printf("Error PAPI_get_hardware_info\n");
    exit(-1);
  }
}

void start_cache_test() {
  int retval = 0;
  retval = PAPI_start_counters(data_cache_events, 2);
  if (retval !=  PAPI_OK) {
    test(__FILE__, __LINE__, "PAPI_cache", retval);
  }
}

void stop_cache_test() {
  int retval = 0;
  retval = PAPI_stop_counters(data_cache_values, 2);
  if (retval != PAPI_OK) {
    test(__FILE__, __LINE__, "PAPI_cache", retval);
  } else {
    printf("hits: %lld\n", data_cache_values[0]);
    printf("misses: %lld\n", data_cache_values[1]);
  }
}

void start_fp_ops_test() {
  int retval = 0;
  retval = PAPI_start_counters(fp_ops_events, 1);
  if (retval !=  PAPI_OK) {
    test(__FILE__, __LINE__, "PAPI_flops", retval);
  }
}

void stop_fp_ops_test() {
  int retval = 0;
  retval = PAPI_stop_counters(fp_ops_values, 1);
  if (retval != PAPI_OK) {
    test(__FILE__, __LINE__, "PAPI_flops", retval);
  } else {
    printf("fp operations: %lld\n", fp_ops_values[0]);
  }
}
///*
 void start_acc_wait_test() {
   int retval = 0;
   retval = PAPI_start_counters(mem_acc_wait_events, 1);
   if (retval != PAPI_OK) {
     test(__FILE__, __LINE__, "PAPI_memacc", retval);
   }
 }

 void stop_acc_wait_test() {
   int retval = 0;
   retval = PAPI_stop_counters(mem_acc_wait_values, 1);
   if (retval != PAPI_OK) {
     test(__FILE__, __LINE__, "PAPI_memacc", retval);
   } else {
     printf("mem_acc_waiting: %lld\n", fp_ops_values[0]);
   }
 }
//*/
static void test(char *file, int line, char *call, int retval){
    printf("%s\tFAILED\nLine # %d\n", file, line);
    if ( retval == PAPI_ESYS ) {
        char buf[128];
        memset( buf, '\0', sizeof(buf) );
        sprintf(buf, "Sys error in %s:", call );
        perror(buf);
    }
    else if ( retval > 0 ) {
        printf("Error calc: %s\n", call );
    }
    else {
        printf("Error in %s: %s\n", call, PAPI_strerror(retval) );
    }
    printf("\n");
    exit(1);
}
