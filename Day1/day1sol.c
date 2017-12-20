#include <stdio.h>
#include <stdlib.h>

int *data;

int* readFromFile(char *filename){
    FILE *fp = fopen(filename, "r");
    fseek(fp, 0, SEEK_END);
    int fileSize = ftell(fp);

    fseek(fp, 0, SEEK_SET);
    char buffer[fileSize];
    //Last entry in buffer holds '\n'
    for(int i = 0; i < fileSize; i++){
        fread(&buffer[i], 1, 1, fp);
    }

    fclose(fp);

    //Make fileData same size as buffer but hold size in spot 0
    int *fileData = malloc(sizeof(int) * (fileSize));
    for(int i = 1; i < fileSize; i++){
        fileData[i] = (int)buffer[i - 1] - '0';
    }

    fileData[0] = fileSize;
    return fileData;
}

int main(int argc, char *argv[]){
    if(argc == 2){
        data = readFromFile(argv[1]);
    }else{
        printf("To read from file: \n    %s filename\n", argv[0]);
    }

    int sum = 0;
    //Array starts at spot 1 since size is held at spot 0
    for(int i = 1; i < data[0]; i++){
        if(i == (data[0] - 1)){
            if(data[i] == data[1]){
                sum += data[i];
            }
        }else{
            if(data[i] == data[i + 1]){
                sum += data[i];
            }
        }
    }

    printf("Answer: %d\n", sum);

    return 0;
}