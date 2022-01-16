#!/bin/bash
set echo on
module load papi/6.0
gcc -O2 -I/usr/local/papi/6.0/include -c mxm_papi.c  
gcc -O2 -o mxm_papi mxm_papi.o -L/usr/local/papi/6.0/lib -lpapi