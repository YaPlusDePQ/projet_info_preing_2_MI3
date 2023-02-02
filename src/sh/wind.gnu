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

plot "test.csv" using 5:4:($2*pi)/180:3 with  vectors arrowstyle 3 notitle
pause -1 "Hit return to continue"
reset
#