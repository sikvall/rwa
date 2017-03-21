/***********************************************************************
 * Adapted from orignal code by
 * Mike Markowski AB3AP
 * Thu Jun 28 07:01:26 EDT 2012
 *
 * Refined and added to by SM0UEI
 * 2017 and onwards, various options added, code cleanup and conversion
 * to the metric system instead
 *
 * Code is in public domain
 *
 ***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>


#define METER_TO_FT 3.2808399

// Globals used sparingly :)
int feet_flg = 0;
float vf = 98.0;


void print_help(void)
{
  puts("RWA - Simple gnuplot generator for random wire antennas\n"
       "Written by SM0UEI with code adapted from AB3AP released 2012\n"
       "Public Domain Software 2017 and forward.\n\n"
       
       "USAGE: rwa [-v] [-q] [-h] [-f] [-r <region>] -b <band1> ... <bandN>\n\n"

       "-h, --help        Prints this text and offers helpful information.\n\n"

       "-v, --velocity    Set the velocity factor as a percentage of free space.\n"
       "                  useful settings for random wire would be 98 for thin wire\n"
       "                  and up to 95 for very thick wires. Default value is 98%.\n\n"

       "-r, --region [r]  Set region for band edges to region 1-3.\n"
       "                  Region 1: Europe, Africa, Russia, Middle East etc.\n"
       "                  Region 2: The Americas, Greenland etc.\n"
       "                  Region 3: Far East, Australia etc.\n"
       "                  For now only region 1 is working.\n"
       "                  If no argument is given, it defaults to region 1.\n\n"

       "-f, --feet        Output distance in feet instead of meters which is the default.\n\n"

       "-m, --meters      Has no real effect other than ensure it will be metric.\n\n"

       "-b, --band <args> Sets the bands you are interested in viewing information\n"
       "                  about. The bands can be 160, 80, 60, 40, 30, 20, 17, 15, 12, 10\n"
       "                  and 6, which corresponds to their wavelengths in meters.\n"
       "                  You can give more than one argument, -b 80 40 20 is valid as\n"
       "                  an example. Only include the bands you are interested in working\n"
       "                  as that gives you a good chart. This should be the last option\n"
       "                  on the command line for all switches to take effect before the\n"
       "                  band information is being processed\n\n"
       );
}  

/***********************************************************************
 * For a given range in kHz (start-stop) print the half-wave resonant
 * frequency and all multiples up to 160 meter band.
 ***********************************************************************/
void rw(double min_kHz, double max_kHz, int band) {
  double lambda0_ft, lambda1_ft;
  int i;
  int multiples = 2*(160/band);

  fprintf(stderr, "# Examining %d multiples of the %d band.\n",
	 multiples, band);
  
  // First multiple.
  for(i = 1; i <= multiples; i++) {
    lambda0_ft = i * 150 * vf / (max_kHz * 1e-3);
    lambda1_ft = i * 150 * vf / (min_kHz * 1e-3);

    // If in feet do simple conversion here
    if(feet_flg) {
      lambda0_ft = METER_TO_FT * lambda0_ft;
      lambda1_ft = METER_TO_FT * lambda1_ft;
    }
    
    // Print in format gnuplot expects.
    printf("# %.3f to %.3f kHz, multiple %d\n",
	   min_kHz, max_kHz, i);
    
    printf("%.3f 0 %d\n%.3f 1 %d\n%.3f 1 %d\n%.3f 0 %d\n\n",
	   lambda0_ft-(1e-3), band, lambda0_ft, band,
	   lambda1_ft, band, lambda1_ft+(1e-3), band );
  } 
}




int main (int argc, char **argv)
{
  int c;
  int region = 1; // Default EU region

  // If no arguments, then print help and exit
  if(argc < 2) {
    printf("# Missing arguments, use -h for help.\n");
    exit(5);
  }

  while (1)
    {
      static struct option long_options[] =
        {
	  {"help",     no_argument,       0, 'h'},
	  {"feet",     no_argument,       0, 'f'},
	  {"meter",    no_argument,       0, 'm'},
	  {"velocity", required_argument, 0, 'v'},
	  {"region",   required_argument, 0, 'r'},
	  {"band",     required_argument, 0, 'b'},
          {0, 0, 0, 0} // No more args
        };
      
      /* getopt_long stores the option index here. */
      int option_index = 0;
      c = getopt_long (argc, argv, "hfv:r:b:",
                       long_options, &option_index);

      /* Detect the end of the options. */
      if (c == -1)
        break;
      switch (c)
        {
	case 'f':
	  feet_flg = 1;
	  break;

	case 'm':
	  feet_flg = 0;
	  break;
	  
	case 'h':
	  print_help();
	  exit(0);
	  break;

	case 'v':
	  // Get velocity factor
	  vf = atof(optarg);
	  printf("# VF is considered to be %f\n", vf);

	  // Sane range would be 50 to 100 (free space). Actually 50 is pushing it
	  // not really useful but hey let's allow it anyways.
	  if(vf < 50 || vf > 100) {
	    printf("# Velocity factor must be in range 50 < vf < 100\n");
	    exit(20);
	  }

	  // Convert from percentage to factor
	  vf = vf/100; 
          break;

	case 'r':
	  region = atoi(optarg);
	  if(region < 1 || region > 3) {
	    puts("# Error: Region must be 1-3, and we only have data for regions 1-2 at this moment.\n");
	    exit(10);
	  }
	  if(region == 3) {
	    puts("# Region 3 data missing at this time. Sorry. \n");
	    exit(0);
	  }
	  printf("# Considering data for region %d\n", region);
	  break;

	case 'b':
	  for(optind--; optind < argc && *argv[optind] != '-'; optind++) {
	    int band = atoi(argv[optind]);
	    switch(band) {
	    case 160:
	      printf("# Band %d considered region %d\n", band, region);
	      rw(1800, 2000, 160);
		break;
	    case 80:
	      printf("# Band %d considered region %d\n", band, region);
	      if(region == 1) rw(3500, 3800, 80);
	      if(region == 2) rw(3500, 4000, 80);
	      break;
	    case 60:
	      printf("# Band %d considered region %d\n", band, region);
	      rw(5351, 5367, 60);
	      break;
	    case 40:
	      printf("# Band %d considered region %d\n", band, region);
	      if(region == 1) rw(7000, 7200, 40);
	      if(region == 2) rw(7000, 7300, 40);
	      break;
	    case 30:
	      printf("# Band %d considered region %d\n", band, region);
	      rw(10100, 10150, 30);
	      break;
	    case 20:
	      printf("# Band %d considered region %d\n", band, region);
	      rw(14000, 14350, 20);
	      break;
	    case 17:
	      printf("# Band %d considered region %d\n", band, region);
	      rw(18068, 18168, 17);
	      break;
	    case 15:
	      printf("# Band %d considered region %d\n", band, region);
	      rw(21000, 21450, 15);
	      break;
	    case 12:
	      printf("# Band %d considered region %d\n", band, region);
	      rw(24890, 24990, 12);
	      break;
	    case 10:
	      printf("# Band %d considered region %d\n", band, region);
	      rw(28000, 29700, 10);
	      break;
	    case 6:
	      printf("# Band %d considered region %d\n", band, region);
	      if(region == 1) rw(50000, 52000, 6);
	      if(region == 2) rw(50000, 54000, 6);
	      break;
	    default:
	      printf("# Band %d not found.\n", band);
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
