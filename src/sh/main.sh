#!/bin/bash 


for arg in $@
do 
    case $arg in 
        --abr)
        sortn='abr'
        ;;
        --avl)
        sortn= 'avl'
        ;;
        --tab)
        sortn='tab'
        ;;
        --help)
        cat man.txt
        exit 1
        ;;
        \?) echo "ERROR"
    esac
done
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
while getopts "FAGOQShmwf:t:p:" opt
do 
case $opt in 
    f) 
        a=$OPTARG
        b=$OPTARG
    ;;
    F)arg_F=1
    ;;
    A) arg_A=1
    ;;
    G) arg_G=1
    ;;
    O) arg_O=1
    ;;
    Q)arg_Q=1
    ;;
    S)arg_S=1
    ;;
    h)arg_h=1
    ;;
    m)arg_m=1
    ;;
    w)arg_w=1
    ;;
    t)arg_t=1
    mode=$OPTARG
    ;;
    p)arg_p=1
    mode=$OPTARG
    ;;
    \?) echo "ERROR"
    esac
done 
sed 's/,/;/g' $a > tmp0.csv #Splitting column $10 into two columns 
a="tmp0.csv"
sed 's/,/;/g' $a > tmp1.csv #Splitting column $10 into two columns
b="tmp1.csv"
#------------------------------LOCATIONS----------------------------------------------------
if (($arg_A == 1 ))#--------------------------------ANTILLES------------------------------------
then
    head -n1 $a > Antilles.csv
    awk -F ";" '9.5<=$10 && $10<=22.1 && -76.03<=$11 && $11<=-53.03 {print $0}' $a >> Antilles.csv
    b="Antilles.csv"   
elif (($arg_F == 1))#-----------------FRANCE METROPOLITAINE & CORSE--------------------------------
then 
    awk -F ";" '41<=$10 && $10<=52 && -5.5<=$11 && $11<=9.4 {print $0;}' $a   > france.csv
    b="france.csv"
elif (($arg_G == 1)) #---------------------GUYANE FRANCAISE---------------------------------------
then 
    awk -F ";" '2.1<=$10 && $10<=5.9 && -54.7<=$11 && $11<=-51 {print $0}' $a  > guyane.csv
    b="guyane.csv"
elif (($arg_S == 1))#-----------------------SAINT-PIERRE ET MIQUELON --------------------------
then 
    awk -F ";" '46.6<=$10 && $10<=47.1 && -56.5<=$11 && $11<=-56 {print $0}' $a  > saint_pierre.csv
    b="saint_pierre.csv"
elif (($arg_O == 1))#---------------------------OCEAN INDIEN---------------------------
then

    awk -F ";" '-60.6<=$10 && $10<=8.16 && 28.3<=$11 && $11<=132.9 {print $0}' $a  > oc_indien.csv
    b="oc_indien.csv"
elif (($arg_Q == 1))#------------------------------ANTARTIQUE----------------------
then 
    awk -F ";" '-63.5<=$10 && $10<=-57.6 && -172<=$11 && $11<=17.4 {print $0}'  $a  > antartique.csv
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
fi  
if (($arg_m == 1))#-----------------------moisture---------------------
then 
    cut -d ';' -f1,6,10,11 --output-delimiter ';' $b  > tmp.csv
    nt=`cat $b | wc -l`
    echo "ID OMM station;Humidité;Latitude;Longitude" > moisture.csv
    tail -n$((nt-1)) tmp.csv >> moisture.csv
    rm tmp.csv
fi  
if (($arg_w == 1))#------------------------wind----------------------
then 
    cut -d ';' -f1,4,5,10,11 --output-delimiter ';' $b > tmp.csv
    nt=`cat $b | wc -l`
    echo "ID OMM station;Direction du vent moyen 10 mn;Vitesse du vent moyen 10 mn;Latitude;Longitude" > wind.csv
    tail -n$((nt-1)) tmp.csv >> wind.csv
    rm tmp.csv
fi  
if (($arg_t == 1)) #--------------------Temperature--------------------
then 
    if (($mode == 1)) #-------------------mode 1------------------------
    then 
        cut -d ';' -f1,12 --output-delimiter ';' $b  > tmp.csv
        nt=`cat $b | wc -l`
        echo "ID OMM station;Température (°C)" > temperature1.csv
        tail -n$((nt-1)) tmp.csv >> temperature1.csv 
        rm tmp.csv
    elif (($mode == 2)) #----------------mode 2----------------
    then
        cut -d ';' -f2,12 --output-delimiter ';' $b  > tmp.csv 
        nt=`cat $b | wc -l`
        echo "Date;Température (°C)" > temperature2.csv
        tail -n$((nt-1)) tmp.csv >> temperature2.csv 
        rm tmp.csv
    
    else #------------------------------mode 3--------------------------
        cut -d ';' -f1,2,12 --output-delimiter ';' $b > tmp.csv 
        nt=`cat $b | wc -l`
        echo "ID OMM station;Date;Température (°C)" > temperature3.csv
        tail -n$((nt-1)) tmp.csv >> temperature3.csv 
        rm tmp.csv
    fi
fi  
if (($arg_p == 1))#----------------------Pression---------------------
then 
    if (($mode == 1)) #---------------------mode 1---------------- 
    then 
        cut -d ';' -f1,3,7,8 --output-delimiter ';'  $b > tmp.csv 
        nt=`cat $b | wc -l`
        echo "ID OMM station;Pression au niveau mer;Pression station;Variation de pression en 24 heures" > pression1.csv
        tail -n$((nt-1)) tmp.csv >> pression1.csv 
        rm tmp.csv
    elif (($mode == 2)) #------------------mode 2----------------
    then
        cut -d ';' -f2,7 --output-delimiter ';' $b > tmp.csv 
        nt=`cat $b | wc -l`
        echo "Date;Pression station" > pression2.csv
        tail -n$((nt-1)) tmp.csv >> pression2.csv 
        rm tmp.csv
    
    else #-----------------------mode 3----------------------
        cut -d ';' -f1,2,7 --output-delimiter ';' $b  > tmp.csv 
        nt=`cat $b | wc -l`
        echo "ID OMM station;Date;Pression station" > pression3.csv
        tail -n$((nt-1)) tmp.csv >> pression3.csv 
        rm tmp.csv
    fi
fi  
exit 0
