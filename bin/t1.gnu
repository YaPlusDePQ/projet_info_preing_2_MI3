reset

set grid nopolar
set grid xtics mxtics ytics mytics noztics nomztics nortics nomrtics \
nox2tics nomx2tics noy2tics nomy2tics nocbtics nomcbtics
set style data lines

set title "Temperatures par ID de stations"
set xlabel "ID de la station"
set ylabel "Temperatures"

set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault
Shadecolor = "#80E0A080"
set datafile separator ";"
set autoscale noextend
set xrange [*:*]
set xtics rotate by 90 right

plot "test.csv" using 0:2:3:xticlabels(1) with filledcurve fc rgb Shadecolor title "Temperatures min et max",'' using 0:4 smooth mcspline lw 2 title "Tempesratures moyennes"
pause -1 "Hit return to continue"