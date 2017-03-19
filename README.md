# rwa
Random Wire Antenna calculator

It calculates resonant frequencies where the impedance is high 
for an end-fed random wire. This allows us to avoid some places
when we do not wish to use a 9:1 unun but something simpler like
the direct output from a tuner or something similar.

Based on code found in the public domain and enhanced as needed
for ease of use.

HOW TO GET STARTED

1. Compile the c code with the following command:
   gcc -o rwa rwa.c

2. Run the rwa command with arguments for the bands you wish to 
   plot, example "./rwa 20 40 80 >data.plog" will run the plots 
   for the 20,40 and 80 meter bands. Allowed bands are all ham
   bands between 6 - 160 meters 
   (6, 10, 12, 15, 17, 20, 30, 40, 80, 160)
   
3. Then run gnuplot on the file rwa.gnu
   gnuplot rwa.gnu

This should produce a f.png in the folder that shows the plot.

