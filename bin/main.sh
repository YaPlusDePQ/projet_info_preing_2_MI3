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
            sortn="avl"
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

sed 's/,/;/g' $a > ../temp/tmp0.csv #Splitting column $10 into two columns 
a="../temp/tmp0.csv"
sed 's/,/;/g' $a > ../temp/tmp1.csv #Splitting column $10 into two columns
b="../temp/tmp1.csv"
#--------------------------------------------------LOCATIONS----------------------------------------------------
if (($arg_A == 1 ))#--------------------------------ANTILLES------------------------------------
then
    awk -F ";" '9.5<=$10 && $10<=22.1 && -76.03<=$11 && $11<=-53.03 {print $0}' $a > ../temp/Antilles.csv
    b="../temp/Antilles.csv"   
elif (($arg_F == 1))#-----------------FRANCE & CORSICA--------------------------------
then 
    awk -F ";" ' 41<=$10 && $10<=52 && -5.5<=$11 && $11<=9.4 {print $0;} ' $a   > ../temp/france.csv
    b="../temp/france.csv"
elif (($arg_G == 1)) #---------------------FRENCH GYANA---------------------------------------
then 
    awk -F ";" ' 2.1<=$10 && $10<=5.9 && -54.7<=$11 && $11<=-51 {print $0} ' $a  > ../temp/guyane.csv
    b="../temp/guyane.csv"
elif (($arg_S == 1)) #-----------------------SAINT-PIERRE ET MIQUELON --------------------------
then 
    awk -F ";" ' 46.6<=$10 && $10<=47.1 && -56.5<=$11 && $11<=-56 {print $0} ' $a  > ../temp/saint_pierre.csv
    b="../temp/saint_pierre.csv"
elif (($arg_O == 1)) #---------------------------INDIAN OCEAN---------------------------
then

    awk -F ";" ' -60.6<=$10 && $10<=8.16 && 28.3<=$11 && $11<=132.9 {print $0} ' $a  > ../temp/oc_indien.csv
    b="../temp/oc_indien.csv"
elif (($arg_Q == 1)) #------------------------------ANTARTIC----------------------
then 
    awk -F ";" ' -63.5<=$10 && $10<=-57.6 && -172<=$11 && $11<=17.4 {print $0} '  $a  > ../temp/antartique.csv
    b="../temp/antartique.csv"

fi 
#-------------DATA-------------------------
if (($arg_h == 1)) #----------------------height------------------------
then 
    cut -d ';' -f1,10,11,15 --output-delimiter ';' $b > ../temp/tmp.csv
    nt=`cat $b | wc -l`
    echo "ID OMM station;Latitude;Longitude;Altitude" > ../output/height.csv
    tail -n$((nt-1)) ../temp/tmp.csv >> ../output/height.csv
    rm ../temp/tmp.csv
    if (($arg_r == 1 ))
    then 
        ./exec --$sortn -f ../output/height.csv -o ../output/heightsorted.csv -h -r
    else 
        ./exec --$sortn -f ../output/height.csv -o ../output/heightsorted.csv -h 
    fi 

    gnuplot "height.gnu" --persist
fi   

if (($arg_m == 1)) #-----------------------moisture---------------------
then 
    cut -d ';' -f1,6,10,11 --output-delimiter ';' $b  > ../temp/tmp.csv
    nt=`cat $b | wc -l`
    echo "ID OMM station;Humidité;Latitude;Longitude" > ../output/moisture.csv
    tail -n$((nt-1)) ../temp/tmp.csv >> ../output/moisture.csv
    rm ../temp/tmp.csv
    if (($arg_r == 1 ))
    then 
        ./exec --$sortn -f ../output/moisture.csv -o ../output/moisturesorted.csv -m -r
    else 
        ./exec --$sortn -f ../output/moisture.csv -o ../output/moisturesorted.csv -m 
    fi 
    echo "test"
    gnuplot "moisture.gnu" --persist --slow
fi  
if (($arg_w == 1)) #------------------------WIND----------------------
then 
    cut -d ';' -f1,4,5,10,11 --output-delimiter ';' $b > ../temp/tmp.csv
    nt=`cat $b | wc -l`
    echo "ID OMM station;Direction du vent moyen 10 mn;Vitesse du vent moyen 10 mn;Latitude;Longitude" > ../output/wind.csv
    tail -n$((nt-1)) ../temp/tmp.csv >> ../output/wind.csv
    rm ../temp/tmp.csv
    if (($arg_r == 1)) 
    then 
        ./exec --$sortn -f ../output/wind.csv -o ../output/windsorted.csv -w -r
    else 
        ./exec --$sortn -f ../output/wind.csv -o ../output/windsorted.csv -w
    fi 
    gnuplot "wind.gnu" --persist 
fi  
if (($arg_t == 1)) #--------------------Temperature--------------------
then 
    if (($mode == 1)) #---------------------------------------MODE 1----------------------------------------------
    then 
        cut -d ';' -f1,12 --output-delimiter ';' $b  > ../temp/tmp.csv
        nt=`cat $b | wc -l`
        echo "ID OMM station;Température (°C)" > ../output/temperature1.csv
        tail -n$((nt-1)) ../temp/tmp.csv >> ../output/temperature1.csv 
        rm ../temp/tmp.csv
        if (($arg_r == 1 ))
        then 
            ./exec --$sortn -f ../output/temperature1.csv -o ../output/temperature1sorted.csv -t1 -r
        else 
            ./exec --$sortn -f ../output/temperature1.csv -o ../output/temperature1sorted.csv -t1
        fi 
        gnuplot "t1.gnu" --persist
    elif (($mode == 2)) #-------------------------------MODE 2-----------------------------------------------
    then
        cut -d ';' -f2,12 --output-delimiter ';' $b  > ../temp/tmp.csv 
        nt=`cat $b | wc -l`
        echo "Date;Température (°C)" > ../output/temperature2.csv
        tail -n$((nt-1)) ../temp/tmp.csv >> ../output/temperature2.csv 
        rm ../temp/tmp.csv
        if (( $arg_r == 1 ))
        then 
            ./exec --$sortn -f ../output/temperature2.csv -o ../output/temperature2sorted.csv -t2 -r
        else 
            ./exec --$sortn -f ../output/temperature2.csv -o ../output/temperature2sorted.csv -t2
        fi 
        gnuplot "t2.gnu" --persist
    else #-------------------------------------------MODE 3 -----------------------------------------------------
        cut -d ';' -f1,2,12 --output-delimiter ';' $b > ../temp/tmp.csv 
        nt=`cat $b | wc -l`
        echo "ID OMM station;Date;Température (°C)" > ../output/temperature3.csv
        tail -n$((nt-1)) ../temp/tmp.csv >> ../output/temperature3.csv 
        rm ../temp/tmp.csv
        if (($arg_r == 1 ))
        then 
            ./exec --$sortn -f ../output/temperature3.csv -o ../output/temperature3sorted.csv -t3 -r
        else 
            ./exec --$sortn -f ../output/temperature3.csv -o ../output/temperature3sorted.csv -t3
        fi 
        #gnuplot "t3.gnu" --persist
    fi
fi  
if (($arg_p == 1)) #----------------------------------Pression----------------------------------
then 
    if (($mode == 1)) #------------------------------------MODE 1------------------------------------------ 
    then 
        cut -d ';' -f1,3,7,8 --output-delimiter ';'  $b > ../temp/tmp.csv 
        nt=`cat $b | wc -l`
        echo "ID OMM station;Pression au niveau mer;Pression station;Variation de pression en 24 heures" > ../output/pression1.csv
        tail -n$((nt-1)) ../temp/tmp.csv >> ../output/pression1.csv 
        rm ../temp/tmp.csv
        if (($arg_r == 1 ))
        then 
            ./exec --$sortn -f ../output/pression1.csv -o ../output/pression1sorted.csv -p1 -r
        else 
            ./exec --$sortn -f ../output/pression1.csv -o ../output/pression1sorted.csv -p1
        fi 
        gnuplot "p1.gnu" --persist
    elif (($mode == 2)) #------------------------------------------MODE 2--------------------------------------------------
    then
        cut -d ';' -f2,7 --output-delimiter ';' $b > ../temp/tmp.csv 
        nt=`cat $b | wc -l`
        echo "Date;Pression station" > ../output/pression2.csv
        tail -n$((nt-1)) ../temp/tmp.csv >> ../output/pression2.csv 
        rm ../temp/tmp.csv
        if (($arg_r == 1 ))
        then 
            ./exec --$sortn -f ../output/pression2.csv -o ../output/pression2sorted.csv -p2 -r
        else 
            ./exec --$sortn -f ../output/pression2.csv -o ../output/pression2sorted.csv -p2
        fi 
        gnuplot "p2.gnu" --persist
    else #------------------------------------------MODE 3-----------------------------------------------
        cut -d ';' -f1,2,7 --output-delimiter ';' $b  > ../temp/tmp.csv 
        nt=`cat $b | wc -l`
        echo "ID OMM station;Date;Pression station" > ../output/pression3.csv
        tail -n$((nt-1)) ../temp/tmp.csv >> ../output/pression3.csv 
        rm ../temp/tmp.csv
        if (($arg_r == 1 ))
        then 
            ./exec --$sortn -f ../output/pression3.csv -o ../output/pression3sorted.csv -p3 -r
        else 
            ./exec --$sortn -f ../output/pression3.csv -o ../output/pression3sorted.csv -p3
        fi 
        #gnuplot "p3.gnu" --persist
    fi
fi
exit 0
