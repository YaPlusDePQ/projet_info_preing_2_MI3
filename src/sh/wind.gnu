reset
#
set title "vecteurs vent par longitude et Latitude"
set xlabel "Longitude"
set ylabel "Latitude"

set datafile separator ";"

set xtics rotate by 90 right 
set ytics 
set xrange [*:*]
set yrange [*:*]
set autoscale noextend
set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault


plot "test.csv" using 5:4:($2*pi)/180:3 with  vectors arrowstyle 3 notitle
pause -1 "Hit return to continue"
reset
#