reset

set xyplane relative 0
set title "Altitude par station"
set xlabel "Longitude"
set ylabel "Latitude"
set zlabel "Altitude"
set datafile separator ";"
set autoscale noextend
set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front noinvert bdefault
set palette rgbformulae 12,13,14
set pm3d map interpolate 5,5 flush begin nohidden3d
set dgrid3d 80,80
splot "test.csv" u 4:2:3 w pm3d

pause -1 "Hit return to continue"