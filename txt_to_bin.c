#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "txt_bin.h"

void write_txt_to_binary(char *tx_file, char *bin_file) {
    FILE *fptr, *bptr;
    fptr = fopen(tx_file, "r");
    if (!fptr) {
        fprintf(stderr, "Error: Unable to open the text file '%s' for reading.\n", tx_file);
        return;
    }

    bptr = fopen(bin_file, "wb");
    if (!bptr) {
        fprintf(stderr, "Error: Unable to open or create the binary file '%s'.\n", bin_file);
        fclose(fptr);
        return;
    }

    char *line = (char *)malloc(sizeof(char) * MAX_LINE_LENGTH);
    while (fgets(line, MAX_LINE_LENGTH, fptr)) {
        unsigned int n = strlen(line);
        
        // Remove newline character if present
        if (line[n - 1] == '\n') {
            line[n - 1] = '\0';
            n--; // Adjust length to exclude '\n'
        }

        if (fwrite(&n, sizeof(unsigned int), 1, bptr) != 1 || fwrite(line, sizeof(char), n, bptr) != n) {
            fprintf(stderr, "Error: Writing to binary file failed.\n");
            free(line);
            fclose(fptr);
            fclose(bptr);
            return;
        }
    }
    free(line);
    fclose(fptr);
    fclose(bptr);
    printf("Content written to binary file successfully.\n");
}


char** read_from_binary(char *filepath){
    char **names;
    FILE *fptr;
    fptr=fopen(filepath,"rb");
    if(!fptr){
        fprintf(stderr,"error in reading the file");
        return NULL;
    }
    names=(char**)malloc(sizeof(char*)*MAX_NAMES);
    if (!names) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        fclose(fptr);
        return NULL;
    }
    unsigned int length;
    char* line;
    int i=0;
    while(fread(&length,sizeof(unsigned int),1,fptr)==1 && i<MAX_NAMES){
        if(length){
            line=(char *)malloc(sizeof(char)*(length+1));
            if (!line) {
                fprintf(stderr, "Error: Memory allocation failed.\n");
                fclose(fptr);
                return NULL;
            }
            if(fread(line,sizeof(char),length,fptr)!=length){
                fprintf(stderr, "Error: Reading from binary file failed.\n");
                free(line);
                fclose(fptr);
                return NULL;
            }
            line[length]='\0';
            
            names[i]=line;
            i++;
        }
    }
    fclose(fptr);
    for(int k=0;k<MAX_NAMES;k++){
        printf("%s\n",names[k]);
    }
    return names;

}



// int main(){
//     // write_txt_to_binary("data.txt","data.bin");
//     char** names=read_from_binary("data.bin");
//     for(int i=0;i<MAX_NAMES;i++){
//         printf("string is: %s\n",names[i]);
//     }
//     free(names);
//     return 0;
// }