/*
 * Simple calculations of half wavelengths of ham bands.
 *
 * Mike Markowski AB3AP
 * Thu Jun 28 07:01:26 EDT 2012
 */

#include <stdio.h>
#include <stdlib.h>


/*
 * For a given frequency range, calculate the half wavelength range and print
 * it.  In addition, print up to 4th multiples of each range up to the length
 * of 160m half wavelength.
 *
 * Comments are also printed out, assuming that the output will saved to a file,
 * and that file used by gnuplot for plotting.
 */
void rw(double min_kHz, double max_kHz, int band, int color) {
  double lambda0_ft, lambda1_ft;
  double loFreq_MHz = 1.8;
  double lambdaMax_ft = 2 * 150 / loFreq_MHz; /* Max wavelength in band. */
  int n;
  double qtr_ft = 150 / loFreq_MHz / 2;
  int multiples = 2*(1+160/band);

  fprintf(stderr, "# Examining %d multiples of the %d band.\n",
	 multiples, band);
  
  n = 1; /* First multiple. */
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



/*
 * Print ranges of half wavelengths for ecah ham band.
 */
void printHalfwaves(void) {
  //    rw(50000., 52000., 6,128);     /* 6m */
  rw(28000., 29700., 10,256);     /* 10m */
  rw(24890., 24990., 12,384);     /* 12m */
  rw(21000., 21450., 15,512);     /* 15m */
  rw(18068., 18168., 17,640);     /* 17m */
  rw(14000., 14350., 20,1152);     /* 20m */
  //    rw(10100., 10150., 30,1280);     /* 30m */
  rw(7000., 7200., 40,65536);       /* 40m */
  rw(3500., 3800., 80,1664);       /* 80m */
  rw(1850., 1950., 160,1792);       /* 160m */
}




int main(int argc, char **argv) {
  printHalfwaves();
}
