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
#include <getopt.h>


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



int main (int argc, char **argv)
{
  int c;
  int verbose;
  int region = 1; // Default EU region

  while (1)
    {
      static struct option long_options[] =
        {
	  {"quiet",   no_argument,       0, 'q'},
	  {"verbose", no_argument,       0, 'v'},
	  {"band",    required_argument, 0, 'b'},
	  {"help",    no_argument,       0, 'h'},
	  {"region",  required_argument, 0, 'r'},
          {0, 0, 0, 0} // No more args
        };
      
      /* getopt_long stores the option index here. */
      int option_index = 0;
      c = getopt_long (argc, argv, "qvr:b:h",
                       long_options, &option_index);

      /* Detect the end of the options. */
      if (c == -1)
        break;
      switch (c)
        {
	case 'h':
	  puts("Simple gnuplot generator for detecting lengths to avoid on a random wire\n"
	       "if the impedance should be low enought to be end fed using a standard\n"
	       "tuner with 1:4 unun, for high impedance feed you need 1:9 unun which\n"
	       "together with the tuner is yet another thing to carry around.\n\n"
	       "USAGE: rwa [-v] [-q] [-h] [-r <region>] -b <band1> ... <bandN>\n\n"
	       "-v, --verbose     Prints more information of what goes on.\n\n"
	       "-q, --quiet       Prints less informaton of what goes on.\n\n"
	       "-h, --help        Prints this text and offers helpful information.\n\n"
	       "-b, --band <args> Sets the bands you are interested in viewing information\n\n"
	       "                  about. The bands can be 160, 80, 60, 40, 30, 20, 17, 15, 12, 10\n"
	       "                  and 6, which corresponds to their wavelengths in meters.\n"
	       "                  You can give more than one argument, -b 80 40 20 is valid as\n"
	       "                  an example. Only include the bands you are interested in working\n"
	       "                  as that gives you a good chart.\n\n"
	       "-r, --region [r]  Set region for band edges to region 1-3.\n"
	       "                  Region 1: Europe, Africa, Russia, Middle East etc.\n"
	       "                  Region 2: The Americas, Greenland etc.\n"
	       "                  Region 3: Far East, Australia etc.\n"
	       "                  For now only region 1 is working.\n"
	       "                  If no argument is given, it defaults to region 1.\n"
	       );
	  
	  break;
        case 'q':
	  verbose = 0;
          break;
        case 'v':
	  verbose = 1;
          break;
	case 'r':
	  region = atoi(optarg);
	  if(region < 1 || region > 3) {
	    puts("Error: Region must be 1-3, and we only have data for regions 1-2 at this moment.\n");
	    exit(10);
	  }
	  if(region == 2) {
	    puts("Region 2 data missing at this time. Sorry. \n");
	    exit(0);
	  }
	  if(region == 3) {
	    puts("Region 3 data missing at this time. Sorry. \n");
	    exit(0);
	  }
	  if(region == 1)
	    puts("Region 1 selected, Europe, Africa, Russia and Middle East.\n");
	  break;
        case 'b':
	  for(optind--; optind < argc && *argv[optind] != '-'; optind++) {
	    int band = atoi(argv[optind]);
	    switch(band) {
	    case 160:
	      if(verbose)
		printf("Band %d considered.\n", band);
	      rw(1850, 1950, 160);
		break;
	    case 80:
	      if(verbose)
		printf("Band %d considered.\n", band);
	      rw(3500, 3800, 80);
	      break;
	    case 40:
	      if(verbose)
		printf("Band %d considered.\n", band);
	      rw(7000,7200, 40);
	      break;
	    case 30:
	      if(verbose)
		printf("Band %d considered.\n", band);
	      rw(10100, 10150, 30);
	      break;
	    case 20:
	      if(verbose)
		printf("Band %d considered.\n", band);
	      rw(14000, 14350, 20);
	      break;
	    case 17:
	      if(verbose)
		printf("Band %d considered.\n", band);
	      rw(18068, 18168, 17);
	      break;
	    case 15:
	      if(verbose)
		printf("Band %d considered.\n", band);
	      rw(21000, 21450, 15);
	      break;
	    case 12:
	      if(verbose)
		printf("Band %d considered.\n", band);
	      rw(24890, 24990, 12);
	      break;
	    case 10:
	      if(verbose)
		printf("Band %d considered.\n", band);
	      rw(28000, 29700, 10);
	      break;
	    case 6:
	      if(verbose)
		printf("Band %d considered.\n", band);
	      rw(50000, 52000, 6);
	      break;
	    default:
	      printf("Band %d not found.\n", band);
	      break;
	    }
	  }
          break;
        default:
	  exit(10);
        }
    }
  
  return 0;
}
