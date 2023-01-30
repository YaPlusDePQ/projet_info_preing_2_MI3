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
    elif (($mode==2)) # mode 2 :
        cat meteo_filtered_data_v1.csv | cut -d ';' -f1,2,11 --output-delimiter ';'  > tmp1.csv 
        head -n1 tmp1.csv > temperature2.csv
        tail -n$((a-1)) tmp1.csv >> temperature2.csv
        rm tmp1.csv
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
    elif (($mode==2)) # mode 2 :
        cat meteo_filtered_data_v1.csv | cut -d ';' -f1,2,7 --output-delimiter ';'  > tmp1.csv 
        head -n1 tmp1.csv > pression2.csv
        tail -n$((a-1)) tmp1.csv >> pression2.csv
        rm tmp1.csv
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
while getopts "FGSAOQ" opt
do 
    case $opt in 
    F) #france + corse
    head -n1 meteo_filtered_data_v1.csv > france.csv
    sed 's/,/;/g' meteo_filtered_data_v1.csv  | awk -F ";" '41<=$10 && $10<=52 && -5.5<=$11 && $11<=9.4 {print $0;}'   >> france.csv
    LOCK=1
    ;;
    G) #guyane francaise
    head -n1 meteo_filtered_data_v1.csv > guyane.csv
    sed 's/,/;/g' meteo_filtered_data_v1.csv | awk -F ";" '2.1<=$10 && $10<=5.9 && -54.7<=$11 && $11<=-51 {print $0}' >> guyane.csv
    LOCK=1
    ;;
    S) #saint pierre et miquelon : est du canada
    head -n1 meteo_filtered_data_v1.csv > saint_pierre.csv
    sed 's/,/;/g' meteo_filtered_data_v1.csv | awk -F ";" '46.6<=$10 && $10<=47.1 && -56.5<=$11 && $11<=-56 {print $0}' >> saint_pierre.csv
    LOCK=1
    ;;
    A) # Antilles
    head -n1 meteo_filtered_data_v1.csv > Antilles.csv
    sed 's/,/;/g' meteo_filtered_data_v1.csv | awk -F ";" '9.5<=$10 && $10<=22.1 && -76.03<=$11 && $11<=-53.03 {print $0}' >> Antilles.csv
    LOCK=1
    ;;
    O) #ocean indien 
    head -n1 meteo_filtered_data_v1.csv > oc_indien.csv
    sed 's/,/;/g' meteo_filtered_data_v1.csv | awk -F ";" '-60.6<=$10 && $10<=8.16 && 28.3<=$11 && $11<=132.9 {print $0}' >> oc_indien.csv
    LOCK=1
    ;;
    Q) #antartique 
    head -n1 meteo_filtered_data_v1.csv > antartique.csv
    sed 's/,/;/g' meteo_filtered_data_v1.csv | awk -F ";" '-63.5<=$10 && $10<=-57.6 && -172<=$11 && $11<=17.4 {print $0}' >> antartique.csv
    LOCK=1
    ;;
    \?) echo "ERREUR! l'option lieu n'existe pas "
    esac
    if (LOCK)
    fi 
done 

#dates 
#tris
#fichiers
exit 0