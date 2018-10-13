// richu shaji abraham
#include<fstream>
#include<stdio.h>
#include<iostream>
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
            ++mIndex;
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
    long long int mIndex =0;
    while(pSize>0)
    {
        (*(pPointer+mIndex)) = rand();
        ++mIndex;
        pSize = pSize - sizeof(int);
    }
    return mSize;
}
long long int generate_encrypted(int *pDataPointer , int *pRandomData, int *pEncryptedData, long long int pSize)
{
    long long int mSize = pSize;
    long long int mIndex =0;
    while(pSize>0)
    {
        (*(pEncryptedData+mIndex)) = (*(pDataPointer+mIndex))^(*(pRandomData+mIndex));
        ++mIndex;
        pSize = pSize - sizeof(int);
    }
    return mSize;
}
int main(int argc , char *argv[])
{
    FILE *inFile;
    FILE *outFile;
    FILE *keyFile;
    inFile = fopen("c.html","rb");
    outFile = fopen("enc","wb");
    keyFile = fopen("key","wb");
    int *dataPointer = new int[268435456];
    std::cout<<"yo";
    long long int fileSize = read_file_to_memmory(inFile,dataPointer);
    std::cout<<fileSize;
    int *randomBytePointer = new int[fileSize/sizeof(int) + 100];
    fileSize = generate_random_bits(randomBytePointer , fileSize);
    std::cout<<"hello2";
    int *encryptedPointer = new int[fileSize/sizeof(int) +100];
    fileSize = generate_encrypted(dataPointer,randomBytePointer,encryptedPointer,fileSize);
    std::cout<<"hello";
    fileSize =write_file_from_memmory(outFile,encryptedPointer,fileSize);
    fileSize =write_file_from_memmory(keyFile,randomBytePointer,fileSize);
    fclose(inFile);
    fclose(outFile);
    fclose(keyFile);
}
