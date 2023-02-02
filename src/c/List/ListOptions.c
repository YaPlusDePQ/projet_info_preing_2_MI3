#include "../mainDefine.h"


void Option1(char * input,char * output,int r){
    FILE * file = NULL;
    file = fopen(input,"w");                //opening the returning file (have to put the path)
    if(file == NULL){                                            //verification
        printf("error from output file\n");
        printf("error code = %d \n",errno);
        printf("error message = %s \n",strerror(errno));
        exit(2);
    }
	List * plist = FileIntoList2(file,1);
	plist = DeleteAllOccurences(plist,-9999,occurence(plist,-9999));
	List * final = PreSortMinMaxAv(plist);
    if(r == 0){
        final = SortOption1(final);
    }
	else if(r == 1){
        final = SortOption1Reverse(final);
    }
    FILE * end = NULL;
    end = fopen(output,"w");                //opening the returning file (have to put the path)
    if(end == NULL){                                            //verification
        printf("error from output file\n");
        printf("error code = %d \n",errno);
        printf("error message = %s \n",strerror(errno));
        exit(3);
    }
	ListIntoFile(final,end,1);
    free(final);
    free(plist);
    fclose(file);
    fclose(end);
}

void Option2(char * input,char * output,int r){
    FILE * file = NULL;
    file = fopen(input,"w");                //opening the returning file (have to put the path)
    if(file == NULL){                                            //verification
        printf("error from output file\n");
        printf("error code = %d \n",errno);
        printf("error message = %s \n",strerror(errno));
        exit(2);
    }
    List * plist = FileIntoList2(file,2);
	plist = DeleteAllOccurences(plist,-9999,occurence(plist,-9999));
	List * final = PreSortAv(plist);
    if(r == 0){
        final = SortOption2(final);
    }
	else if(r == 1){
        final = SortOption2Reverse(final);
    }
    FILE * end = NULL;
    end = fopen(output,"w");                //opening the returning file (have to put the path)
    if(end == NULL){                                            //verification
        printf("error from output file\n");
        printf("error code = %d \n",errno);
        printf("error message = %s \n",strerror(errno));
        exit(3);
    }
	end = ListIntoFile(final,end,2);
    free(final);
    free(plist);
    fclose(file);
    fclose(end);
}

void Option3(char * input,char * output,int r){
    FILE * file = NULL;
    file = fopen(input,"w");                //opening the returning file (have to put the path)
    if(file == NULL){                                            //verification
        printf("error from output file\n");
        printf("error code = %d \n",errno);
        printf("error message = %s \n",strerror(errno));
        exit(2);
    }
    List * plist = FileIntoList3(file);
	plist = DeleteAllOccurences(plist,-9999,occurence(plist,-9999));
    if(r == 0){
        plist = SortOption3(plist);
    }
    else if(r == 1){
        plist = SortOption3Reverse(plist);
    }
    FILE * end = NULL;
    end = fopen(output,"w");                //opening the returning file (have to put the path)
    if(end == NULL){                                            //verification
        printf("error from output file\n");
        printf("error code = %d \n",errno);
        printf("error message = %s \n",strerror(errno));
        exit(3);
    }
	end = ListIntoFile2(plist,end);
    free(plist);
    fclose(file);
    fclose(end);
}

void Wind(char * input,char * output,int r){
    FILE * file = NULL;
    file = fopen(input,"w");                //opening the returning file (have to put the path)
    if(file == NULL){                                            //verification
        printf("error from output file\n");
        printf("error code = %d \n",errno);
        printf("error message = %s \n",strerror(errno));
        exit(2);
    }
    List * plist = FileIntoList5(file);
	plist = DeleteAllOccurences(plist,-9999,occurence(plist,-9999));
	List * final = PreSortWind(plist);
    if(r == 0){
        final = SortWind(final);
    }
    else if(r == 0){
        final=SortWindReverse(final);
    }
    FILE * end = NULL;
    end = fopen(output,"w");                //opening the returning file (have to put the path)
    if(end == NULL){                                            //verification
        printf("error from output file\n");
        printf("error code = %d \n",errno);
        printf("error message = %s \n",strerror(errno));
        exit(3);
    }
	end = ListIntoFile(final,end,4);
    free(final);
    free(plist);
    fclose(file);
    fclose(end);
}

void Height(char * input,char * output,int r){
    FILE * file = NULL;
    file = fopen(input,"w");                //opening the returning file (have to put the path)
    if(file == NULL){                                            //verification
        printf("error from output file\n");
        printf("error code = %d \n",errno);
        printf("error message = %s \n",strerror(errno));
        exit(2);
    }
    List * plist = FileIntoList4(file,1);
	plist = DeleteAllOccurences(plist,-9999,occurence(plist,-9999));
    if(r == 0){
        plist = SortHeight(plist);
    }
    else if(r == 1){
        plist = SortHeightReverse(plist);
    }
    FILE * end = NULL;
    end = fopen(output,"w");                //opening the returning file (have to put the path)
    if(end == NULL){                                            //verification
        printf("error from output file\n");
        printf("error code = %d \n",errno);
        printf("error message = %s \n",strerror(errno));
        exit(3);
    }
	end = ListIntoFile(plist,end,5);
    free(plist);
    fclose(file);
    fclose(end);
}

void Moisture(char * input,char * output,int r){
    FILE * file = NULL;
    file = fopen(input,"w");                //opening the returning file (have to put the path)
    if(file == NULL){                                            //verification
        printf("error from output file\n");
        printf("error code = %d \n",errno);
        printf("error message = %s \n",strerror(errno));
        exit(2);
    }
    List * plist = FileIntoList4(file,2);
	plist = DeleteAllOccurences(plist,-9999,occurence(plist,-9999));
	List * final = PreSortMax(plist);
    if(r == 0){
        final = SortMoisture(final);
    }
    else if(r == 1){
        final = SortMoistureReverse(final);
    }
    FILE * end = NULL;
    end = fopen(output,"w");                //opening the returning file (have to put the path)
    if(end == NULL){                                            //verification
        printf("error from output file\n");
        printf("error code = %d \n",errno);
        printf("error message = %s \n",strerror(errno));
        exit(3);
    }
	ListIntoFile(final, end, 6);
    free(final);
    free(plist);
    fclose(file);
    fclose(end);
}