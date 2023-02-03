

set grid nopolar
set grid xtics mxtics ytics mytics noztics nomztics nortics nomrtics \
nox2tics nomx2tics noy2tics nomy2tics nocbtics nomcbtics
set style data lines
set title "Températures moyennes par date/heure"
set xlabel "Date/Heure"
set ylabel "Températures moyennes"
set datafile separator ";"
set autoscale noextend
set timefmt '%Y-%m-%d %H'
set xdata time
set format x '%Y-%m-%d %H'
set xrange [*:*]
set yrange [*:*]
set xtics rotate by 45 right
plot "../output/temperature2sorted.csv" using (sprintf("%s-%s",substr(stringcolumn(1),1,10),substr(stringcolumn(1),12,14))):2 with lines notitle


pause -1 "Hit return to continue"

