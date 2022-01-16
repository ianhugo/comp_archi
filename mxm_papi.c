#include<stdio.h>
#include<stdlib.h>
#include<papi.h>
#include<string.h>

#define N 10000

double c[N][N];
double a[N][N];
double b[N][N];

void handle_error(int retval)
{
  printf("PAPI error %d: %s\n", retval, PAPI_strerror(retval));
  exit(1);
}

int main(int argc, char **argv){
  int i,j,k,l;
  double r;
  double ts,tf;
  float rtime, ptime, mflops;
  long long flpops;
  int event, ret;

  
  /* initialize y, z */
  for (i=0;i<N;++i){
    for (j=0;j<N;++j){
      a[i][j] = 1;
      b[i][j] = 1;
    }
  }

  /* Start counting events */
  ret = PAPI_hl_region_begin("mxm");
  if ( ret != PAPI_OK )
    handle_error(1);

  for (int l=0; l<10; ++l) {
    for (k=0; k<10; k++) {
      for (i=0;i<N;++i){
        for (j=0;j<N;++j) {
          c[i][j] += a[i][j] * b[i][j];
        }
      }
    }
  }

  /* Save events */
  ret = PAPI_hl_region_end("mxm");
  if ( ret != PAPI_OK )
    handle_error(ret);

}