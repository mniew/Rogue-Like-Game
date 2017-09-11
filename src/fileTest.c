#include"fileTest.h"

int fileTest(char **argv)
{
    FILE* fileData;  //creats file pointer called file data

    fileData = fopen(argv[1], "r");  //opens file for reading

    if (fileData == NULL)  // if it doesnt open do the following
    {
        printf("Cannot find Data file, exiting program.\n");
        exit(1);
    }

    fclose(fileData); //if it opens close it and return 0

    return(0);
}
