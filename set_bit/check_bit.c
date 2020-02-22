#include <stdio.h>
#define SET     1
#define NOT_SET 0

//function to check nth bit
int isNthBitSet(unsigned int data,unsigned int pos)
{
    return ((data & (1 << pos))? SET : NOT_SET);
}
int main()
{
    //Given data
    unsigned int cData=0xFF;
    unsigned int pos =0;
    unsigned int isBitSet = 0;
    printf("Initially cData = 0x%x\n\n",cData);
    printf("Enter the position which you want check = ");
    scanf("%u",&pos);
    //Check bit set or not
    isBitSet  = isNthBitSet(cData,pos);
    if(isBitSet)
    {
        printf("\nBit is One\n");
    }
    else
    {
        printf("\nBit is zero\n");
    }
    return 0;
}
