#!/bin/bash
#
# Anders SM0UEI Sikvall
# 2017-03-20
# Version 1.0
#

# Call the tool with the bands listed, output to plot.dat
# You can adjust the bands here.

# Velocity factor 98%
# Using metric (change to -f for feet)
# Region 1 (also region 2 can be used)
# Include bands 10, 12, 15, 17, 20, 40 and 80
./rwa -v98 -m -r1 -b 10 12 15 17 20 40 80 > plot.dat

# Run gnuplot on the data produced to get a png file with the
# plot nicely.
gnuplot rwa.gnu

# That's it
