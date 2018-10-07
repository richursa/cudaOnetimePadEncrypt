#include<iostream>
#include<stdio.h>
#include<fstream>
#include<time.h>
using namespace std;
int main()
{
    
    FILE *infile;
    infile = fopen("file.txt","rb");
    FILE *outfile;
    FILE *xorFile;
    xorFile = fopen("xor.txt","wb");
    outfile = fopen("enc.txt","wb");
    int *buffer  = new int;
    int *xorVal = new int;
    time_t t;
    int size;
    srand((unsigned) time(&t));
    if(infile!= NULL)
    {
     size =fread(buffer,1,sizeof(int),infile);
        while(size!=0)
        {   
            *xorVal = rand();
            *buffer = (*buffer)^(*xorVal);
            fwrite(buffer ,1,size,outfile);
            fwrite(xorVal,1,size,xorFile);
            size = fread(buffer,1,sizeof(int),infile);
        }
    }
    fclose(infile);
    fclose(outfile);
    fclose(xorFile);
    FILE * xorInFile;
    xorInFile = fopen("xor.txt","rb");
    FILE *inxfile;
    FILE *outxfile;
    inxfile = fopen("enc.txt","rb");
    outxfile = fopen("dec.txt","wb");
    if(inxfile!= NULL)
    {
        size = fread(xorVal,1,sizeof(int),xorInFile);
        while(size!=0)
        {
            size = fread(buffer,1,size,inxfile);
            *xorVal = (*xorVal)^(*buffer);
            fwrite(xorVal,1,size,outxfile);
            size = fread(xorVal,1,sizeof(int),xorInFile);
        }
    }
    fclose(inxfile);
    fclose(outxfile);
    fclose(xorInFile);
}
