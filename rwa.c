/***********************************************************************
 * Adapted from orignal code by
 * Mike Markowski AB3AP
 * Thu Jun 28 07:01:26 EDT 2012
 *
 * Refined and added to by SM0UEI
 * 2017 and onwards
 *
 * Code is in public domain
 *
 ***********************************************************************/
#include <stdio.h>
#include <stdlib.h>


/***********************************************************************
 * For a given range in kHz (start-stop) print the half-wave resonant
 * frequency and all multiples up to 160 meter band.
 ***********************************************************************/
void rw(double min_kHz, double max_kHz, int band) {
  double lambda0_ft, lambda1_ft;
  double loFreq_MHz = 1.8;
  double lambdaMax_ft = 2 * 150 / loFreq_MHz; /* Max wavelength in band. */
  int n;
  double qtr_ft = 150 / loFreq_MHz / 2;
  int multiples = 2*(160/band);

  /* For debug only */
  fprintf(stderr, "# Examining %d multiples of the %d band.\n",
	 multiples, band);
  
  /* First multiple. */
  n = 1; 
  do {
    lambda0_ft = n * 150 / (max_kHz * 1e-3);
    lambda1_ft = n * 150 / (min_kHz * 1e-3);
    
    /* Print in format gnuplot expects. */
    printf("# %.3f to %.3f kHz, multiple %d\n",
	   min_kHz, max_kHz, n);


    
    printf("%.3f 0 %d\n%.3f 1 %d\n%.3f 1 %d\n%.3f 0 %d\n\n",
	   lambda0_ft-(1e-3), band, lambda0_ft, band,
	   lambda1_ft, band, lambda1_ft+(1e-3), band );
    
    /* Prepare for next multiple. */
    n++;

    /* Change the last number in next line to max number of multiples to calculate. */
  } while (lambda1_ft < lambdaMax_ft && n < multiples);
}



/***********************************************************************
 * Print ranges of half wavelengths for ecah ham band.
 * Edit any frequency ranges here!
 ***********************************************************************/
void printHalfwaves(int bandmask) {
  //  rw(50000., 52000., 6);     /* 6m */
  //  rw(28000., 29700., 10);     /* 10m */
  //  rw(24890., 24990., 12);     /* 12m */
  //rw(21000., 21450., 15);     /* 15m */
  //  rw(18068., 18168., 17);     /* 17m */
  //rw(14000., 14350., 20);     /* 20m */
  //  rw(10100., 10150., 30);     /* 30m */
  rw(7000., 7200., 40);       /* 40m */
  //rw(3500., 3800., 80);       /* 80m */
  //rw(1850., 1950., 160);       /* 160m */
}

int main(int argc, char *argv[]) {
  int i = 0;
  for( i = 0; i<argc; i++) {
    if(160 == atoi(argv[i]))
      rw(1850, 1950, 160);
    if(80 == atoi(argv[i]))
      rw(3500, 3800, 80);
    if(40 == atoi(argv[i]))
      rw(7000, 7200, 40);
    if(30 == atoi(argv[i]))
      rw(10100, 10150, 30);
    if(20 == atoi(argv[i]))
      rw(14000, 14350, 20);
    if(17 == atoi(argv[i]))
      rw(18068, 18168, 17);
    if(15 == atoi(argv[i]))
      rw(21000, 21450, 15);
    if(12 == atoi(argv[i]))
      rw(24890, 24990, 12);
    if(10 == atoi(argv[i]))
      rw(28000, 29700, 10);
    if(6 == atoi(argv[i]))
      rw(50000, 52000, 6);
  }
}



