#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct files {
  int fs;    // File size
  char *fn;    // File name
  int entry;    // Number of file in archive entry
} fc;

//void addFileToArchive(char *, fc *, int, char *);
void addFileToArchive(char *, char *);
void readArchive(char *);
void getFileSize(char *f);
void readText();
int main()
{
    unsigned char choice;
    while(choice!='q' && choice!='Q') {
        printf("Enter a to create an archive, x to extract its contents, s to get the size of a file, or q to quit:\n");
        scanf(" %c", &choice);
        printf("You entered %c\n", choice);
        if(choice=='a'||choice=='A') {
            printf("Enter the number of files to add to the archive:\n");
            int n;
            scanf("%d", &n);
            //fc *a = (fc *)malloc(n*sizeof(fc));
            printf("Enter a name for the archive.\n");
            char name[30];
            scanf("%s", name);
            int i;
            for(i=0; i<n; i++) {
                printf("Enter file #%d to be added: \n", i);
                char file[30];
                scanf("%s", file);
                printf("You entered %s\n", file);
                addFileToArchive(strdup(name), strdup(file));
                printf("Added...\n");
            }
            //free(a);
        }
        else if(choice=='x'||choice=='X') {
            printf("Enter the name of an archive file: ");
            char name[30];
            scanf("%s", name);
            readArchive(name);
        }
        else if(choice=='s' || choice=='S') {
            printf("Enter a file to get the size: ");
            char name[30];
            scanf("%s", name);
            getFileSize(name);
        }
        else if(choice=='t' || choice=='T') {
            readText();
        }
        else if(choice=='q' || choice=='Q')
            printf("Exiting...");
        else {
            printf("You entered an invalid choice. Try again.\n");
        }
    }
    //FILE *f1, *f2;
    // Open file from which to read
    //f1 = fopen("music.wav", "rb");
    //if(f1==NULL)
    //{
        //printf("There was a problem opening the file.");
        //exit(0);
    //}
    // Open file for writing
    //f2 = fopen("music1.wav", "wb");
    //if(f2==NULL)
    //{
        //printf("Cannot open file for writing.");
        //exit(0);
    //}
    //int data = -1;
    //int count = 0;
    //unsigned char buff[32];
    //while(data!=0) {
        //data = fread(buff, sizeof(unsigned char), 32, f1);
        //fwrite(buff, sizeof(unsigned char), 32, f2);
        //printf("Writing %d to file.\n", data);
        //count += data*sizeof(unsigned char);
    //}
    //printf("File was successfully coppied.\n");
    //printf("Size of data is %d.\n", count);
    //fclose(f1);
    //fclose(f2);
    return 0;
}

void readText() {
    FILE *f = fopen("archiveReference.txt", "rb");
    if(!f) {
        printf("Error: Could not open file.\nPossible reason, file does not exist.\n");
    }
    else {
        while(!feof(f)) {
            char name[200];
            char name1[200];
            memset(name, 0, sizeof(name));
            memset(name1, 0, sizeof(name1));
            fgets(name, 200, f);
            strncpy(name1, name, strlen(name)-1);
            //printf("%s %d\n", name1, strlen(name1));
            addFileToArchive("e.ef", name1);
        }
    }
}

void addFileToArchive(char *fn1, char *fn2) {
    int error;
    FILE *input, *output;
    output = fopen(fn1, "ab");
    if(output==NULL) {
        printf("There was an error opening the archive file for writing");
    }
    else {
        input = fopen(fn2, "rb");
        if(input==NULL) {
            printf("There was an error opening the file to be added to the archive.\n Possible cause: File does not exist\n");
        }
        else {
            fseek(input, 0, SEEK_END);
            int ifsize = (int)ftell(input);
            unsigned char *data = malloc(ifsize);
            rewind(input);
            fread(data, ifsize, 1, input);
            for(int i = 0; i < ifsize; i++) {
                if(i<3) {
                    //printf("Char num %d before op: %d\n", i+1, data[i]);
                }
                data[i] = data[i]^255;
                if(i<3) {
                    //printf("Char num %d after op: %d\n", i+1, data[i]);
                }
            }
            fwrite(data, ifsize, 1, output);
            free(data);
            fputc('e', output);
            fputc('o', output);
            fputc('f', output);
            fclose(input);
            fclose(output);
        }
    }
}

void readArchive(char *fn) {
    FILE *f;
    f = fopen(fn, "rb");
    if(f==NULL) {
        printf("There was an error opening the file for reading.\nPossible cause: File does not exist.\n");
    }
    else {
        FILE *of = fopen("c.wav", "ab");
        if(of==NULL) {
            printf("There was an error with opening or creating the file for writing.\n");
        }
        else {
            while(1) {
                
                unsigned char c;
                c = fgetc(f);
                int fsize;
                fsize = ftell(f);
                if(fsize==29776364) {
                    break;
                }
                c = c ^ 255;
                fputc(c, of);
            }
        }
        fclose(f);
        fclose(of);
    }
}

void getFileSize(char *f) {
    int c=0;
    FILE *input = fopen(f, "rb");
    if(input==NULL)
        printf("There was an error reading the input file.\nPossible Cause: File does not exist.\n");
    else {
        fseek(input, 0, SEEK_END);
        c = (int)ftell(input);
        printf("%s has a file size of %d bytes.\n", f, c);
        fclose(input);
    }
}