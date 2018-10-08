#include<fstream>
#include<stdio.h>
#include<iostream>

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
long long int generate_decrypted(int *pKeyPointer , int *pEncryptedData, int *pDecryptedData, long long int pSize)
{
    long long int mSize = pSize;
    long long int mIndex =0;
    while(pSize>0)
    {
        (*(pDecryptedData+mIndex)) = (*(pKeyPointer+mIndex))^(*(pEncryptedData+mIndex));
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
    inFile = fopen("enc","rb");
    keyFile = fopen("key","rb");
    outFile = fopen("d.html","wb");
    int *encryptedDataPointer = new int[268435456];
    long long int fileSize = read_file_to_memmory(inFile,encryptedDataPointer);
    int *keyDataPointer = new int[fileSize/sizeof(int) +100];
    int *decryptedDataPointer = new int[fileSize/sizeof(int) +100];
    fileSize = read_file_to_memmory(keyFile,keyDataPointer);
    fileSize = generate_decrypted(keyDataPointer,encryptedDataPointer,decryptedDataPointer,fileSize);
    fileSize = write_file_from_memmory(outFile,decryptedDataPointer,fileSize);
    fclose(inFile);
    fclose(outFile);
    fclose(keyFile);
}
