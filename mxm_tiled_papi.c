#include<stdio.h>
#include<stdlib.h>
#include<papi.h>
#include<string.h>

#define N 10000
#define MAX( a, b ) ( ( a > b) ? a : b )
#define MIN( a, b ) ( ( a < b) ? a : b )

double x[N][N];
double y[N][N];
double z[N][N];

void handle_error(int retval)
{
  printf("PAPI error %d: %s\n", retval, PAPI_strerror(retval));
  exit(1);
}

int main(int argc, char **argv){
  int i,j,k,l;
  int ii,jj,kk;
  int B;
  double r;
  double ts,tf;
  int ret;
  float rtime, ptime, mflops;
  long long flpops;
  int event;

  if (argc < 2)
    B = 16;
  else
    B = atoi(argv[1]);

  
  /* initialize y, z */
  for (i=0;i<N;++i){
    for (j=0;j<N;++j){
      y[i][j] = 1;
      z[i][j] = 1;
    }
  }

  /* Start counting events */
  ret = PAPI_hl_region_begin("mxm_tiled");
  if ( ret != PAPI_OK )
    handle_error(1);

  for (int l=0; l<10; ++l) {
    for (jj=0;jj<N;jj+=B){
      for (kk=0;kk<N;kk+=B){
        for (i=0;i<N;++i){
          for (j=jj;j<MIN(jj+B,N);++j){
            r = 0;
            for (k=kk;k<MIN(kk+B,N);++k)
              r += y[i][k]*z[k][j];
            x[i][j] += r;
          }
        }
      }
    }
  }

  ret = PAPI_hl_region_end("mxm_tiled");
  if ( ret != PAPI_OK )
    handle_error(ret);
}