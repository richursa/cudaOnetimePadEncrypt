#include<fstream>
#include<stdio.h>
#include "random.h"
long long int  read_file_to_memmory(FILE *pInfile , int *pPointer)
{
    if(pInfile != NULL)
    {
        
        int mIndex =0;
        int mSize = fread(pPointer+mIndex,1,sizeof(int),pInfile);
        long long int mFileSize=0;
        while(mSize!= 0)
        {
            mFileSize = mFileSize +mSize;
            mIndex++;
            mSize = fread(pPointer+mIndex,1,mSize,pInfile);
        }
        return mFileSize;
    }
    return 0;
}
long long int write_file_from_memmory(FILE *pOutFile , int *pPointer,long long int pFileSize)
{
    if(pOutFile!=NULL)
    {
        pFileSize = fwrite(pPointer,1,pFileSize,pOutFile);
        return pFileSize;
    }
    return 0;
}
long long int generate_random_bits(int  *pPointer , long long int pSize)
{
    long long int mSize = pSize;
    while(pSize!=0)
    {
        (*pPointer ) = rand();
        pSize = pSize - sizeof(int);
    }
    return mSize;
}
long long int generate_encrypted(int *pDataPointer , int *pRandomData, int *pEncyptedData, long long int pSize)
{
    long long int mSize = pSize;
    while(pSize!=0)
    {
        (*pEncryptedData) = (*pDataPointer)^(*pRandomData);
        pSize = pSize - sizeof(int);
    }
    return mSize;
}
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
    int size;
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
