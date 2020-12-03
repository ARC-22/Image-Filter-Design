/*
Computer Vision and Digital Image Processing
               Assignment 1


By:  Advait Churi
     ID: 01738336

*/


#include <stdio.h>

/*define constants */
#define inputSizeX   256
#define inputSizeY   256
#define output1SizeX 256
#define output1SizeY 256 
#define output2SizeX 128
#define output2SizeY 128
#define initialValue 0

int main(int argc, char *argv[])
{
  unsigned char inputimage   [inputSizeX * inputSizeY];       /* input image array "256*256" */
  unsigned char resultimage1 [output1SizeX * output1SizeY];   /* array for case 1 image "256*256" */
  unsigned char resultimage2 [output2SizeX * output2SizeY];   /* array for case 2 image "128*128" */
  unsigned int result2Pixel = initialValue;
  unsigned i;                                                 /*counter for looping*/
  
  
 
  FILE *input = fopen("input.pgm","w");            /* Open empty .pgm image for writing */
  if(input==0)                                     /*error handling*/
    { 
      printf("error opening file\n");           
      fclose(input);
      return 1;
    }  

  FILE *result1 = fopen("result1.pgm","w");        /* Open empty .pgm image for writing */
  if(result1==0)                                   /*error handling*/
    {
      printf("error opening file\n");            
      fclose(result1);
      return 1;
    } 

  FILE *result2 = fopen("result2.pgm","w");       /* Open empty .pgm image for writing */
  if(result2==0)                                  /*error handling*/
    { 
      printf("error opening file\n");           
      fclose(result2);
      return 1;
    }

  /************************ Code segment to get image data from image file into inputimage[] array ******************************/
 

  FILE *fp  = fopen("/pub/ComputerVision/submissions/achuri/mri.pgm","r");   /*pointer points to start of the file*/
  if(fp == 0)
    {
      printf("error opening file\n");                                    /*error handling*/
      fclose(fp);
      return 1;
    }
  for(i=0;i<inputSizeX*inputSizeY;i++)                                  /*Copy image file into image array*/
    { 	  
      inputimage[i]=fgetc(fp);	
    }

 
  /********************************************** Code segment for Part 1  ***********************************************/

   for(i=initialValue; i<=inputSizeX*inputSizeY; i++)  
     {
       if((i > 128*256) && (i%256) > 128)                   /* If pixel is in fourth quadrant then set value as 255 */
	 resultimage1[i]=255;
       else
	 resultimage1[i]=inputimage[i];                    /* Else set pixel of result image as input image */
     }



 /******************************************** Code segment for Part2  ************************************************/
 
    for (i=initialValue; i<inputSizeX*inputSizeY; i++)
      {
	if(( (i/inputSizeY) %2) == 0  &&  (i%2 == 0))               /*Enter only if row and column both are even*/ 
	  {
	    resultimage2[result2Pixel]=inputimage[i];      /*Put input image data into output image array for Part 2*/
	    result2Pixel++;   
	  }
      }


    /**** Save input image   ******/
  fprintf(input, "P5 %d %d %d ",inputSizeX,inputSizeY, 255);                     /*write header*/
  fwrite(inputimage,sizeof(unsigned char),inputSizeX*inputSizeY,input);          /*write binary image*/
  fclose(input);


   /**** Save image of Part 1  ******/
  fprintf(result1, "P5 %d %d %d ",output1SizeX,output1SizeY, 255);               /*write header*/
  fwrite(resultimage1,sizeof(unsigned char),output1SizeX*output1SizeY,result1);  /*write binary image*/
  fclose(result1);


   /**** Save  image of Part 2  ******/
  fprintf(result2, "P5 %d %d %d ",output2SizeX,output2SizeY, 255);               /*write header*/
  fwrite(resultimage2,sizeof(unsigned char),output2SizeX*output2SizeY,result2);  /*write binary image*/
  fclose(result2);


  return 0;

}
