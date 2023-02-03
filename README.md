# Folders' organisation 
## Folder bin : 
It contains :
    the gnuplot files 
    the main.sh (the shell code)
    the makefile 
    the manual (man.txt)
## Folder examples :
### Folder outputc : 
contains some .csv examples (result of the sorting)
# Folder outputpng : 
Contains some png examples (results of gnuplot) 
## src :
### AVL/ABR : 
contains all the .c files created for the sort by AVL/ABR
### TAB :
contains all the .c files created for the sort by TAB

### the main program (main.c and mainDefine.h) as well as tool.c and tool.h
## temp : 
contains the temporary files created during the execution which will be removed at the end 

## !:
we couldn't add the inputc files as examples because they are too heavy to upload on the git 

# !!:
The original file is too heavy we couldn't upload it on the git. The user should add it to the folder before any execution or add the file directory 


# SCRIPTSHELL

The script will execute the programme through the command make to execute the makefile 

Thanks to the loop while and the case the shell can look into each argument entered by the user which will allow us to know which data to filter and the original file.

Through the loop case for each argument entered by the user we will affect 1 to the corresponding variable or the type of sorting as a string the variable *sortn*

If the user entered --help he will have as an output the manual of the program 

If the user want to choose the option -p or -t he has to put a space between the letter and the number of the mode (ex: -p 2 or -t 3)

The , in the column 10 of the main file will be replaced by the ; so it will be easier to treat the datas

Through the if ()then elif() fi the data will be filtered according to the location selected by the user. the user can choose only on location at a time

then the shell will filter the data of the original file (if the user didn't select a location) or the data of the location chosen (which will be put in a temporary file)

After filtering the data the script will verify if the user chose a reverse mode for the sorting and will execute the .c program.

Then the script will execute the command gnuplot to display the graphs

The script will remove at the end the temporary files created during the execution of the main.sh (tmp0 and tmp1 where the , is replaced by ; and the files of the location) 
