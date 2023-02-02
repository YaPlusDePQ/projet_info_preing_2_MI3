#!/bin/bash 
make -f makefile
#initialization
arg_F=0
arg_A=0
arg_S=0
arg_Q=0
arg_G=0
arg_O=0
arg_h=0
arg_m=0
arg_w=0
arg_t=0
arg_p=0
arg_d=0
arg_f=0
arg_r=0
while [ $# -ne 0 ]
do 
    case $1 in
        --abr)
            sortn="abr"
            shift
            ;;
        --avl)
            sortn= "avl"
            shift
            ;;
        --tab)
            sortn="tab"
            shift 
        ;;
        --help)
            less man.txt
            shift
            ;;
        -f)
            arg_f=1
            a="$2"
            b="$2"  
            shift
            shift
            ;;
        -F)
            arg_F=1
            shift
            ;;
        -A) 
            arg_A=1
            shift
            ;;
        -G) 
            arg_G=1
            shift
            ;;
        -O) 
            arg_O=1
            shift 
            ;;
        -Q)
            arg_Q=1
            shift
            ;;
        -S)
            arg_S=1
            shift
            ;;
        -h)
            arg_h=1
            shift
        ;;
        -m)
            arg_m=1
            shift
            ;;
        -w)
            arg_w=1
            shift
            ;;
        -t)
            arg_t=1
            mode=$2
            shift
            shift
            ;;
        -p)
            arg_p=1
            mode=$2
            shift
            shift
            ;;
        -r)
            arg_r=1
            shift
            ;;
        *) echo "ERROR! Command not found($1). Use command --help for the man"
            exit 1
            ;;
    esac
done 

if [ $arg_f -eq 0 ]
then
    echo "ERROR! file not found. Use command --help for the man"
    exit 1
fi

sed 's/,/;/g' $a > tmp0.csv #Splitting column $10 into two columns 
a="tmp0.csv"
sed 's/,/;/g' $a > tmp1.csv #Splitting column $10 into two columns
b="tmp1.csv"
#--------------------------------------------------LOCATIONS----------------------------------------------------
if (($arg_A == 1 ))#--------------------------------ANTILLES------------------------------------
then
    awk -F ";" '9.5<=$10 && $10<=22.1 && -76.03<=$11 && $11<=-53.03 {print $0}' $a >> Antilles.csv
    b="Antilles.csv"   
elif (($arg_F == 1))#-----------------FRANCE & CORSICA--------------------------------
then 
    awk -F ";" ' 41<=$10 && $10<=52 && -5.5<=$11 && $11<=9.4 {print $0;} ' $a   > france.csv
    b="france.csv"
elif (($arg_G == 1)) #---------------------FRENCH GYANA---------------------------------------
then 
    awk -F ";" ' 2.1<=$10 && $10<=5.9 && -54.7<=$11 && $11<=-51 {print $0} ' $a  > guyane.csv
    b="guyane.csv"
elif (($arg_S == 1))#-----------------------SAINT-PIERRE ET MIQUELON --------------------------
then 
    awk -F ";" ' 46.6<=$10 && $10<=47.1 && -56.5<=$11 && $11<=-56 {print $0} ' $a  > saint_pierre.csv
    b="saint_pierre.csv"
elif (($arg_O == 1))#---------------------------INDIAN OCEAN---------------------------
then

    awk -F ";" ' -60.6<=$10 && $10<=8.16 && 28.3<=$11 && $11<=132.9 {print $0} ' $a  > oc_indien.csv
    b="oc_indien.csv"
elif (($arg_Q == 1))#------------------------------ANTARTIC----------------------
then 
    awk -F ";" ' -63.5<=$10 && $10<=-57.6 && -172<=$11 && $11<=17.4 {print $0} '  $a  > antartique.csv
    b="antartique.csv"

fi 
#-------------DATA-------------------------
if (($arg_h == 1)) #----------------------height------------------------
then 
    cut -d ';' -f1,10,11,15 --output-delimiter ';' $b > tmp.csv
    nt=`cat $b | wc -l`
    echo "ID OMM station;Latitude;Longitude;Altitude" > height.csv
    tail -n$((nt-1)) tmp.csv >> height.csv
    rm tmp.csv
    if ("$sortn"="abr")
    then
        if [$arg_r -eq 1 ]
        then 
            ./exec --abr -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -h -r
        else 
            ./exec --abr -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -h 
        fi 
        gnuplot "test.csv" -persist
    elif ("$sortn"="avl")
    then 
        if [$arg_r -eq 1 ]
        then 
            ./exec --avl -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -h -r
        else 
            ./exec --avl -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -h 
        fi 
        gnuplot "test.csv" -persist
    else 
        if [$arg_r -eq 1 ]
        then 
            ./exec --tab -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -h -r
        else 
            ./exec --tab -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -h 
        fi 
        gnuplot "test.csv" -persist
    fi 
fi   

if (($arg_m == 1))#-----------------------moisture---------------------
then 
    cut -d ';' -f1,6,10,11 --output-delimiter ';' $b  > tmp.csv
    nt=`cat $b | wc -l`
    echo "ID OMM station;Humidité;Latitude;Longitude" > moisture.csv
    tail -n$((nt-1)) tmp.csv >> moisture.csv
    rm tmp.csv
    if ("$sortn"="abr")
    then
        if [$arg_r -eq 1 ]
        then 
            ./exec --abr -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -m -r
        else 
            ./exec --abr -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -m 
        fi 
        gnuplot "test.csv" -persist
    elif ("$sortn"="avl")
    then 
        if [$arg_r -eq 1 ]
        then 
            ./exec --avl -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -m -r
        else 
            ./exec --avl -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -m 
        fi 
        gnuplot "test.csv" -persist
    else 
        if [$arg_r -eq 1 ]
        then 
            ./exec --tab -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -m -r
        else 
            ./exec --tab -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -m 
        fi 
        gnuplot "test.csv" -persist
    fi 
fi  
if (($arg_w == 1))#------------------------WIND----------------------
then 
    cut -d ';' -f1,4,5,10,11 --output-delimiter ';' $b > tmp.csv
    nt=`cat $b | wc -l`
    echo "ID OMM station;Direction du vent moyen 10 mn;Vitesse du vent moyen 10 mn;Latitude;Longitude" > wind.csv
    tail -n$((nt-1)) tmp.csv >> wind.csv
    rm tmp.csv
    if ("$sortn"="abr")
    then
        if [$arg_r -eq 1 ]
        then 
            ./exec --abr -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -w -r
        else 
            ./exec --abr -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -w
        fi 
        gnuplot "test.csv" -persist
    elif ("$sortn"="avl")
    then 
        if [$arg_r -eq 1 ]
        then 
            ./exec --avl -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -w -r
        else 
            ./exec --avl -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -w
        fi 
        gnuplot "test.csv" -persist
    else 
        if [$arg_r -eq 1 ]
        then 
            ./exec --tab -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -w -r
        else 
            ./exec --tab -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -w 
        fi 
        gnuplot "test.csv" -persist
    fi 
fi  
if (($arg_t == 1)) #--------------------Temperature--------------------
then 
    if (($mode == 1)) #---------------------------------------MODE 1----------------------------------------------
    then 
        cut -d ';' -f1,12 --output-delimiter ';' $b  > tmp.csv
        nt=`cat $b | wc -l`
        echo "ID OMM station;Température (°C)" > temperature1.csv
        tail -n$((nt-1)) tmp.csv >> temperature1.csv 
        rm tmp.csv
        if ("$sortn"="abr")
        then
            if [$arg_r -eq 1 ]
            then 
                ./exec --abr -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -t1 -r
            else 
                ./exec --abr -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -t1
            fi 
            gnuplot "test.csv" -persist
        elif ("$sortn"="avl")
        then 
            if [$arg_r -eq 1 ]
            then 
                ./exec --avl -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -t1 -r
            else 
                ./exec --avl -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -t1
            fi 
            gnuplot "test.csv" -persist
        else 
            if [$arg_r -eq 1 ]
            then 
                ./exec --tab -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -t1 -r
            else 
                ./exec --tab -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -t1 
            fi 
            gnuplot "test.csv" -persist
        fi 
    elif (($mode == 2)) #-------------------------------MODE 2-----------------------------------------------
    then
        cut -d ';' -f2,12 --output-delimiter ';' $b  > tmp.csv 
        nt=`cat $b | wc -l`
        echo "Date;Température (°C)" > temperature2.csv
        tail -n$((nt-1)) tmp.csv >> temperature2.csv 
        rm tmp.csv
        if ("$sortn"="abr")
        then
            if [$arg_r -eq 1 ]
            then 
                ./exec --abr -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -t2 -r
            else 
                ./exec --abr -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -t2
            fi
            gnuplot "test.csv" -persist 
        elif ("$sortn"="avl")
        then 
            if [$arg_r -eq 1 ]
            then 
                ./exec --avl -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -t2 -r
            else 
                ./exec --avl -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -t2
            fi 
            gnuplot "test.csv" -persist
        else 
            if [$arg_r -eq 1 ]
            then 
                ./exec --tab -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -t2 -r
            else 
                ./exec --tab -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -t2 
            fi 
            gnuplot "test.csv" -persist
        fi 
    else #-------------------------------------------MODE 3 -----------------------------------------------------
        cut -d ';' -f1,2,12 --output-delimiter ';' $b > tmp.csv 
        nt=`cat $b | wc -l`
        echo "ID OMM station;Date;Température (°C)" > temperature3.csv
        tail -n$((nt-1)) tmp.csv >> temperature3.csv 
        rm tmp.csv
        if ("$sortn"="abr")
        then
            if [$arg_r -eq 1 ]
            then 
                ./exec --abr -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -t3 -r
            else 
                ./exec --abr -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -t3
            fi 
            gnuplot "test.csv" -persist
        elif ("$sortn"="avl")
        then 
            if [$arg_r -eq 1 ]
            then 
                ./exec --avl -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -t3 -r
            else 
                ./exec --avl -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -t3
            fi 
            gnuplot "test.csv" -persist
        else 
            if [$arg_r -eq 1 ]
            then 
                ./exec --tab -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -t3 -r
            else 
                ./exec --tab -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -t3
            fi 
            gnuplot "test.csv" -persist
        fi 
    fi
fi  
if (($arg_p == 1))#----------------------------------Pression----------------------------------
then 
    if (($mode == 1)) #------------------------------------MODE 1------------------------------------------ 
    then 
        cut -d ';' -f1,3,7,8 --output-delimiter ';'  $b > tmp.csv 
        nt=`cat $b | wc -l`
        echo "ID OMM station;Pression au niveau mer;Pression station;Variation de pression en 24 heures" > pression1.csv
        tail -n$((nt-1)) tmp.csv >> pression1.csv 
        rm tmp.csv
        if ("$sortn"="abr")
        then
            if [$arg_r -eq 1 ]
            then 
                ./exec --abr -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -p1 -r
            else 
                ./exec --abr -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -p1
            fi 
            gnuplot "test.csv" -persist
        elif ("$sortn"="avl")
        then 
            if [$arg_r -eq 1 ]
            then 
                ./exec --avl -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -p1 -r
            else 
                ./exec --avl -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -p1
            fi 
            gnuplot "test.csv" -persist
        else 
            if [$arg_r -eq 1 ]
            then 
                ./exec --tab -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -p1 -r
            else 
                ./exec --tab -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -p1 
            fi 
            gnuplot "test.csv" -persist
        fi 
    elif (($mode == 2)) #------------------------------------------MODE 2--------------------------------------------------
    then
        cut -d ';' -f2,7 --output-delimiter ';' $b > tmp.csv 
        nt=`cat $b | wc -l`
        echo "Date;Pression station" > pression2.csv
        tail -n$((nt-1)) tmp.csv >> pression2.csv 
        rm tmp.csv
        if ("$sortn"="abr")
        then
            if [$arg_r -eq 1 ]
            then 
                ./exec --abr -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -p2 -r
            else 
                ./exec --abr -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -p2
            fi 
            gnuplot "test.csv" -persist
        elif ("$sortn"="avl")
        then 
            if [$arg_r -eq 1 ]
            then 
                ./exec --avl -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -p2 -r
            else 
                ./exec --avl -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -p2
            fi 
            gnuplot "test.csv" -persist
        else 
            if [$arg_r -eq 1 ]
            then 
                ./exec --tab -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -p2 -r
            else 
                ./exec --tab -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -p2 
            fi 
            gnuplot "test.csv" -persist
        fi 
    else #------------------------------------------MODE 3-----------------------------------------------
        cut -d ';' -f1,2,7 --output-delimiter ';' $b  > tmp.csv 
        nt=`cat $b | wc -l`
        echo "ID OMM station;Date;Pression station" > pression3.csv
        tail -n$((nt-1)) tmp.csv >> pression3.csv 
        rm tmp.csv
        if ("$sortn"="abr")
        then
            if [$arg_r -eq 1 ]
            then 
                ./exec --abr -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -p3 -r
            else 
                ./exec --abr -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -p3
            fi 
            gnuplot "test.csv" -persist
        elif ("$sortn"="avl")
        then 
            if [$arg_r -eq 1 ]
            then 
                ./exec --avl -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -p3 -r
            else 
                ./exec --avl -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -p3
            fi 
            gnuplot "test.csv" -persist
        else 
            if [$arg_r -eq 1 ]
            then 
                ./exec --tab -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -p3 -r
            else 
                ./exec --tab -f source/meteo_filtered_data_v1.csv -o PROJET_INFO_PREING2_MI3/sh/test.csv -p3 
            fi 
            gnuplot "test.csv" -persist
        fi 
    fi
fi
exit 0
