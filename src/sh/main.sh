#!/bin/bash
#type de données
a=`cat meteo_filtered_data_v1.csv | wc -l`

while getopts "mhwt:p:" opt
do 
    case $opt in
    h) #height 
        cat meteo_filtered_data_v1.csv | cut -d ';' -f1,14 --output-delimiter ';' > tmp.csv
        head -n1 tmp.csv > height.csv
        tail -n$((a-1)) tmp.csv >> height.csv
        rm tmp.csv
    ;;
    m) # moisture 
        cat meteo_filtered_data_v1.csv | cut -d ';' -f1,6 --output-delimiter ';'  > tmp1.csv
        head -n1 tmp1.csv > moisture.csv 
        tail -n$((a-1)) tmp1.csv >> moisture.csv 
        rm tmp1.csv
    ;;
    w) #wind 
        cat meteo_filtered_data_v1.csv | cut -d ';' -f1,4,5 --output-delimiter ';' > tmp1.csv
        head -n1 tmp1.csv > wind.csv
        tail -n$((a-1)) tmp1.csv >> wind.csv
        rm tmp1.csv
    ;;
    t) #temperature 
    mode=$OPTARG
    if (($mode==1)) # mode 1 : max, min and average temperatures
    then 
        cat meteo_filtered_data_v1.csv | cut -d ';' -f1,11,12,13 --output-delimiter ';'  > tmp1.csv
        head -n1 tmp1.csv > temperature1.csv 
        tail -n$((a-1)) tmp1.csv >> temperature1.csv 
        rm tmp1.csv
    elif (($mode==2)) # mode 2 : ?? 
    then
    else #mode 3 : temperatures per date/hour 
        cat meteo_filtered_data_v1.csv | cut -d ';' -f1,2,11 --output-delimiter ';'  > tmp1.csv 
        head -n1 tmp1.csv > temperature3.csv
        tail -n$((a-1)) tmp1.csv >> temperature3.csv
        rm tmp1.csv
    fi
    ;;
    p) #pression 
    mode=$OPTARG
    if (($mode==1)) # mode 1 : max, min and average pressions 
    then 
        cat meteo_filtered_data_v1.csv | cut -d ';' -f1,3,7,8 --output-delimiter ';'  > tmp1.csv 
        head -n1 tmp1.csv > pression1.csv
        tail -n$((a-1)) tmp1.csv >> pression1.csv
        rm tmp1.csv
    elif (($mode==2)) # mode 2 : ??
    then
    else #mode 3 : pressions per date/hour 
        cat meteo_filtered_data_v1.csv | cut -d ';' -f1,2,7 --output-delimiter ';'  > tmp1.csv 
        head -n1 tmp1.csv > pression3.csv
        tail -n$((a-1)) tmp1.csv >> pression3.csv
        rm tmp1.csv
    fi
    ;;
    \?) echo "ERREUR! L'option saisie n'existe pas"
    esac
done
#lieux 

#dates 
#tris
#fichiers