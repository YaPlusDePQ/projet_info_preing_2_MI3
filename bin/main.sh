#!/bin/bash 
make -f makefile

#initialization

arg_F=0 #for the arg -F
arg_A=0 #for the arg -A
arg_S=0 #for the arg -S
arg_Q=0 #for the arg -Q
arg_G=0 #for the arg -G
arg_O=0 #for the arg -O
arg_h=0 #for the arg -h
arg_m=0 #for the arg -m
arg_w=0 #for the arg -w
arg_t=0 #for the arg -t
arg_p=0 #for the arg -p
arg_d=0 #for the arg -d
arg_f=0 #for the arg -f
arg_r=0 #for the arg -r

while [ $# -ne 0 ] # look over all the arguments entered by the user
do 
    case $1 in # discussing the first argument 
        --abr) # sorting using abr
            sortn="abr"
            shift # to shift to the next argument 
            ;;
        --avl) # sorting using avl
            sortn="avl"
            shift # to shift to the next argument 
            ;;
        --tab) #sorting using tab 
            sortn="tab"
            shift # to shift to the next argument 
        ;;
        --help) #help
            less man.txt
            shift # to shift to the next argument 
            ;;
        -f)
            arg_f=1
            a="$2" #retrieval of the file's name
            b="$2"  #retrieval of the file's name
            shift # to shift to the next argument 
            shift # to shift to the next argument 
            ;;
        -F) #argument for the location : france and corse
            arg_F=1
            shift # to shift to the next argument 
            ;;
        -A) #argument for the location: west indies (antilles)
            arg_A=1
            shift # to shift to the next argument 
            ;;
        -G) #argument for the location : french guyana
            arg_G=1
            shift # to shift to the next argument 
            ;;
        -O) # argument for the location : indian ocean
            arg_O=1
            shift # to shift to the next argument 
            ;;
        -Q) #argument for the location Antartic
            arg_Q=1
            shift # to shift to the next argument 
            ;;
        -S) #argument for the location Saint-Pierre et Miquelon
            arg_S=1
            shift # to shift to the next argument 
            ;;
        -h) #argument for the height 
            arg_h=1
            shift # to shift to the next argument 
        ;;
        -m) #argument for the moisture
            arg_m=1
            shift # to shift to the next argument 
            ;;
        -w) # argument for the wind
            arg_w=1
            shift # to shift to the next argument 
            ;;
        -t) #argument for the temperature
            arg_t=1
            mode=$2
            if (($mode != 1 || $mode!=2 || $mode!=3))
            then 
                exit(2)
            fi 
            shift # to shift to the next argument 
            shift # to shift to the next argument 
            ;;
        -p) # argument for pressure
            arg_p=1 
            mode=$2 #mode choice
            if (($mode != 1 || $mode!=2 || $mode!=3))
            then 
                exit(2)
            fi 
            shift # to shift to the next argument 
            shift # to shift to the next argument 
            ;;
        -r) #argument for sorting by reverse
            arg_r=1
            shift # to shift to the next argument 
            ;;
        *) echo "ERROR! Command not found($1). Use command --help for the man"
            exit 1
            ;;
    esac
done 

if [ $arg_f -eq 0 ] #if the user didn't enter -f 
then
    echo "ERROR! file not found. Use command --help for the man"
    exit 1
fi

sed 's/,/;/g' $a > ../temp/tmp0.csv #Splitting column $10 into two columns by replacing the , by ; 
a="../temp/tmp0.csv"
sed 's/,/;/g' $a > ../temp/tmp1.csv #Splitting column $10 into two columns by replacing the , by ;
b="../temp/tmp1.csv"
#--------------------------------------------------LOCATIONS----------------------------------------------------
if (($arg_A == 1 )) #--------------------------------ANTILLES------------------------------------
then
    awk -F ";" '9.5<=$10 && $10<=22.1 && -76.03<=$11 && $11<=-53.03 {print $0}' $a > ../temp/Antilles.csv #to sample the main data file to the datas of west indies
    b="../temp/Antilles.csv"   #affecting to the variable b the name of the new file 
elif (($arg_F == 1)) #-----------------FRANCE & CORSICA--------------------------------
then 
    awk -F ";" ' 41<=$10 && $10<=52 && -5.5<=$11 && $11<=9.4 {print $0;} ' $a   > ../temp/france.csv #to sample the main data file to the datas of france+corse
    b="../temp/france.csv" #affecting to the variable b the name of the new file 
elif (($arg_G == 1)) #---------------------FRENCH GYANA---------------------------------------
then 
    awk -F ";" ' 2.1<=$10 && $10<=5.9 && -54.7<=$11 && $11<=-51 {print $0} ' $a  > ../temp/guyane.csv #to sample the main data file to the datas of French Gyana
    b="../temp/guyane.csv" #affecting to the variable b the name of the new file 
elif (($arg_S == 1)) #-----------------------SAINT-PIERRE ET MIQUELON --------------------------
then 
    awk -F ";" ' 46.6<=$10 && $10<=47.1 && -56.5<=$11 && $11<=-56 {print $0} ' $a  > ../temp/saint_pierre.csv #to sample the main data file to the datas of saint-pierre et miquelon
    b="../temp/saint_pierre.csv" #affecting to the variable b the name of the new file 
elif (($arg_O == 1)) #---------------------------INDIAN OCEAN---------------------------
then

    awk -F ";" ' -60.6<=$10 && $10<=8.16 && 28.3<=$11 && $11<=132.9 {print $0} ' $a  > ../temp/oc_indien.csv #to sample the main data file to the datas of indian ocean 
    b="../temp/oc_indien.csv" #affecting to the variable b the name of the new file 
elif (($arg_Q == 1)) #------------------------------ANTARTIC----------------------
then 
    awk -F ";" ' -100<=$10 && $10<=-58 {print $0} '  $a  > ../temp/antartique.csv #to sample the main data file to the datas of antartic
    b="../temp/antartique.csv" #affecting to the variable b the name of the new file 

fi 
#-------------DATA-------------------------
if (($arg_h == 1)) #----------------------height------------------------
then 
    cut -d ';' -f1,10,11,15 --output-delimiter ';' $b > ../temp/tmp.csv #taking only the needed coloumns from the main file 
    nt=`cat $b | wc -l` #calculating the number of lines in the file 
    echo "ID OMM station;Latitude;Longitude;Altitude" > ../output/height.csv #changing the header of the new file
    tail -n$((nt-1)) ../temp/tmp.csv >> ../output/height.csv #copy the data from tmp without the header in the height file
    rm ../temp/tmp.csv #removing the temporary file 
    if (($arg_r == 1 )) # looking if the user chose the reverse mode
    then 
        ./exec --$sortn -f ../output/height.csv -o ../output/heightsorted.csv -h -r #command to execute the .c program
    else 
        ./exec --$sortn -f ../output/height.csv -o ../output/heightsorted.csv -h #command to execute the .c program 
    fi 

    gnuplot "height.gnu" --persist  #command to execute gnuplot 
fi   

if (($arg_m == 1)) #-----------------------moisture---------------------
then 
    cut -d ';' -f1,6,10,11 --output-delimiter ';' $b  > ../temp/tmp.csv #taking only the needed coloumns from the main file 
    nt=`cat $b | wc -l` #calculating the number of lines in the file 
    echo "ID OMM station;Humidité;Latitude;Longitude" > ../output/moisture.csv # creating a new header
    tail -n$((nt-1)) ../temp/tmp.csv >> ../output/moisture.csv #copy the data without the original header
    rm ../temp/tmp.csv #removing the temporary file
    if (($arg_r == 1 )) #looking if the user chose the reverse mode 
    then 
        ./exec --$sortn -f ../output/moisture.csv -o ../output/moisturesorted.csv -m -r #command to execute the .c program
    else 
        ./exec --$sortn -f ../output/moisture.csv -o ../output/moisturesorted.csv -m #command to execute the .c program
    fi 
    gnuplot "moisture.gnu" --persist #command to execute the gnuplot 
fi  
if (($arg_w == 1)) #------------------------WIND----------------------
then 
    cut -d ';' -f1,4,5,10,11 --output-delimiter ';' $b > ../temp/tmp.csv #taking only the needed coloumns from the main file 
    nt=`cat $b | wc -l` #calculating the number of lines in the file 
    echo "ID OMM station;Direction du vent moyen 10 mn;Vitesse du vent moyen 10 mn;Latitude;Longitude" > ../output/wind.csv # creating a new header
    tail -n$((nt-1)) ../temp/tmp.csv >> ../output/wind.csv #copy the data without the original header
    rm ../temp/tmp.csv #removing the temporary file
    if (($arg_r == 1)) #looking if the user chose the reverse mode
    then 
        ./exec --$sortn -f ../output/wind.csv -o ../output/windsorted.csv -w -r #command to execute the .c program
    else 
        ./exec --$sortn -f ../output/wind.csv -o ../output/windsorted.csv -w #command to execute the .c program
    fi 
    gnuplot "wind.gnu" --persist #command to execute the gnuplot 
fi  
if (($arg_t == 1)) #--------------------Temperature--------------------
then 
    if (($mode == 1)) #---------------------------------------MODE 1----------------------------------------------
    then 
        cut -d ';' -f1,12 --output-delimiter ';' $b  > ../temp/tmp.csv #taking only the needed coloumns from the main file 
        nt=`cat $b | wc -l` #calculating the number of lines in the file 
        echo "ID OMM station;Température (°C)" > ../output/temperature1.csv # creating a new header
        tail -n$((nt-1)) ../temp/tmp.csv >> ../output/temperature1.csv #copy the data without the original header
        rm ../temp/tmp.csv #removing the temporary file
        if (($arg_r == 1 )) #looking if the user chose the reverse mode
        then 
            ./exec --$sortn -f ../output/temperature1.csv -o ../output/temperature1sorted.csv -t1 -r #command to execute the .c program
        else 
            ./exec --$sortn -f ../output/temperature1.csv -o ../output/temperature1sorted.csv -t1 #command to execute the .c program
        fi 
        gnuplot "t1.gnu" --persist #command to execute the gnuplot 
    elif (($mode == 2)) #-------------------------------MODE 2-----------------------------------------------
    then
        cut -d ';' -f2,12 --output-delimiter ';' $b  > ../temp/tmp.csv #taking only the needed coloumns from the main file 
        nt=`cat $b | wc -l` #calculating the number of lines in the file 
        echo "Date;Température (°C)" > ../output/temperature2.csv # creating a new header
        tail -n$((nt-1)) ../temp/tmp.csv >> ../output/temperature2.csv #copy the data without the original header
        rm ../temp/tmp.csv #removing the temporary file
        if (( $arg_r == 1 )) #looking if the user chose the reverse mode
        then 
            ./exec --$sortn -f ../output/temperature2.csv -o ../output/temperature2sorted.csv -t2 -r #command to execute the .c program
        else 
            ./exec --$sortn -f ../output/temperature2.csv -o ../output/temperature2sorted.csv -t2 #command to execute the .c program
        fi 
        gnuplot "t2.gnu" --persist #command to execute the gnuplot 
    else #-------------------------------------------MODE 3 -----------------------------------------------------
        cut -d ';' -f1,2,12 --output-delimiter ';' $b > ../temp/tmp.csv  #taking only the needed coloumns from the main file 
        nt=`cat $b | wc -l` #calculating the number of lines in the file 
        echo "ID OMM station;Date;Température (°C)" > ../output/temperature3.csv # creating a new header
        tail -n$((nt-1)) ../temp/tmp.csv >> ../output/temperature3.csv #copy the data without the original header
        rm ../temp/tmp.csv #removing the temporary file
        if (($arg_r == 1 )) #looking if the user chose the reverse mode
        then 
            ./exec --$sortn -f ../output/temperature3.csv -o ../output/temperature3sorted.csv -t3 -r #command to execute the .c program
        else 
            ./exec --$sortn -f ../output/temperature3.csv -o ../output/temperature3sorted.csv -t3 #command to execute the .c program
        fi 
        #gnuplot "t3.gnu" --persist # couldn't create the gnuplot for mode 3
    fi
fi  
if (($arg_p == 1)) #----------------------------------Pression----------------------------------
then 
    if (($mode == 1)) #------------------------------------MODE 1------------------------------------------ 
    then 
        cut -d ';' -f1,3,7,8 --output-delimiter ';'  $b > ../temp/tmp.csv #taking only the needed coloumns from the main file 
        nt=`cat $b | wc -l` #calculating the number of lines in the file 
        echo "ID OMM station;Pression au niveau mer;Pression station;Variation de pression en 24 heures" > ../output/pression1.csv # creating a new header
        tail -n$((nt-1)) ../temp/tmp.csv >> ../output/pression1.csv #copy the data without the original header
        rm ../temp/tmp.csv #removing the temporary file
        if (($arg_r == 1 )) #looking if the user chose the reverse mode
        then 
            ./exec --$sortn -f ../output/pression1.csv -o ../output/pression1sorted.csv -p1 -r #command to execute the .c program
        else 
            ./exec --$sortn -f ../output/pression1.csv -o ../output/pression1sorted.csv -p1 #command to execute the .c program
        fi 
        gnuplot "p1.gnu" --persist #command to execute the gnuplot 
    elif (($mode == 2)) #------------------------------------------MODE 2--------------------------------------------------
    then
        cut -d ';' -f2,7 --output-delimiter ';' $b > ../temp/tmp.csv #taking only the needed coloumns from the main file 
        nt=`cat $b | wc -l` #calculating the number of lines in the file 
        echo "Date;Pression station" > ../output/pression2.csv # creating a new header
        tail -n$((nt-1)) ../temp/tmp.csv >> ../output/pression2.csv #copy the data without the original header
        rm ../temp/tmp.csv #removing the temporary file
        if (($arg_r == 1 )) #looking if the user chose the reverse mode
        then 
            ./exec --$sortn -f ../output/pression2.csv -o ../output/pression2sorted.csv -p2 -r #command to execute the .c program
        else 
            ./exec --$sortn -f ../output/pression2.csv -o ../output/pression2sorted.csv -p2 #command to execute the .c program
        fi 
        gnuplot "p2.gnu" --persist #command to execute the gnuplot 
    else #------------------------------------------MODE 3-----------------------------------------------
        cut -d ';' -f1,2,7 --output-delimiter ';' $b  > ../temp/tmp.csv #taking only the needed coloumns from the main file 
        nt=`cat $b | wc -l` #calculating the number of lines in the file 
        echo "ID OMM station;Date;Pression station" > ../output/pression3.csv # creating a new header
        tail -n$((nt-1)) ../temp/tmp.csv >> ../output/pression3.csv #copy the data without the original header
        rm ../temp/tmp.csv #removing the temporary file
        if (($arg_r == 1 )) #looking if the user chose the reverse mode
        then 
            ./exec --$sortn -f ../output/pression3.csv -o ../output/pression3sorted.csv -p3 -r #command to execute the .c program
        else 
            ./exec --$sortn -f ../output/pression3.csv -o ../output/pression3sorted.csv -p3 #command to execute the .c program
        fi 
        #gnuplot "p3.gnu" --persist #couldn't create the gnuplot for mode 3
    fi
fi
#removing the temporary files in the folder temp
cd ../temp
rm *.csv
exit 0
