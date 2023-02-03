
set output 'moisture.png'

set xyplane relative 0
set title "Humidite par station"
set xlabel "Longitude"
set ylabel "Latitude"
set zlabel "Humidite"
set datafile separator ";"
set autoscale noextend
set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front noinvert bdefault
set palette rgbformulae 12,13,14
set pm3d map interpolate 6,6 flush begin nohidden3d
set pm3d map at b
set dgrid3d 50,50
splot "../output/moisturesorted.csv" using 4:3:2 with pm3d

pause -1 "Hit return to continue"
