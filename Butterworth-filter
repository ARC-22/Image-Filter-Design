/*
Description of code:
1)convert image into array.
2)shift image to centre.
2)Create new image array with odd position set to 0.
3)Do FFT two times, first on rows and then on columns
4)To view spectrum take magnitude and then normalise the image in the range of 0-255.
5)Create centered Butter-worth filter. 
6)Multiply real and imaginary part of image with filter.
7)Combine real and imaginary part and do IFFT two times, first on colums and then on rows.
8)To view the image take magnitude and then do normalization. 
   

 */
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr
float *data,*output1,*output2,*output3,*output4;
float *spectrum,*norspectrum,*norImage,*outputImage;
float *real,*imaginary,*shiftimg;
float *filter,*combine,*filImage;
float *realout,*imagout;
float *output;              /* array to store output and separate real and imaginary */
int c = 0;


/*----DFT function isign=1 for dft, isign = -1 for idft----*//*--Given function--*/
void four1(float *data, int nn, int isign)
{
        int n,mmax,m,i,jstep,j;
        double wtemp,wr,wpr,wpi,wi,theta;
        float tempr,tempi;
        n=nn << 1;
        i=1;
        for (j=1;j<n;j+=2) {
                if (i > j) {
                        SWAP(data[i-1],data[j-1]);
                        SWAP(data[i],data[j]);
                }
                m=n >> 1;
                while (m >= 2 && i > m) {
                        i -= m;
                        m >>= 1;
                }
                i += m;
        }
        mmax=2;
        while (n > mmax) {
                jstep=2*mmax;
                theta=4*asin(1)/(isign*mmax);
                wtemp=sin(0.5*theta);
                wpr = -2.0*wtemp*wtemp;
                wpi=sin(theta);
                wr=1.0;
                wi=0.0;
                for (m=1;m<mmax;m+=2) {
                        for (j=m;j<=n;j+=jstep) {
                                i=j+mmax;
                                tempr=wr*data[i-1]-wi*data[i];
                                tempi=wr*data[i]+wi*data[i-1];
                                data[i-1]=data[j-1]-tempr;
                                data[i]=data[j]-tempi;
                                data[j-1] += tempr;
                                data[j] += tempi;
                        }
                        wr=(wtemp=wr)*wpr-wi*wpi+wr;
                        wi=wi*wpr+wtemp*wpi+wi;
                }
                mmax=jstep;
        }
}
 

/*-----Find maximum number from array-----*/
float maximum(float *array)
{
  int i;
  float max; 
  max=array[0];
  for(i=1;i<256*256;i++)
    {     
      if(array[i]>max)
    	max= array[i];
    }
  return(max);
} 


/*-----Find minimum number from array-----*/
float minimum(float *array)
{
  int i;
  float min; 
  min=array[0];
  for(i=1;i<256*256;i++)
    {     
      if(array[i]<min)
    	min= array[i];
    }
  return(min);
} 


/*------Normalised array between values 0-255 -------*/
normalised(float *norspectrum,float *real)
{
  int i;
  float min,max;
    min=minimum(real);
    max=maximum(real);
  for(i=0;i<256*256;i++)
    {
      norspectrum[i]=255*((real[i] - min)/(max - min));
    }
}

/*------- Store output row by row -------*/
void first(int n,float *data,float *output1)
  {
    int i;
    int b = n*2*256;
     for(i=0;i<=2*256;i++)
       {
       output1[i+b]=data[i];
       }
  }

/*------- Store output column by column --------*/
void second(int n,float *data,float *output2 )
  {
    int i;
    int c=0;
     for(i=0;i<=256*2;i+=2)
       {
	 output2[(256*2*c)+ (2*n)]=data[i];
	 output2[(256*2*c)+ (2*n) + 1]=data[i+1];
	 c++;
       }
  }


void separate(float *output )
{
  int i;
  for (i=0;i<2*256*256;i++)
      {
      if(i%2==0)
	real[i/2]=output[i];
      else
	imaginary[i/2]=output[i];
       }
}

                    /*------------  Main Function ----------------*/
int main(int argc, char *argv[])
{

  unsigned char *inputimage; 
  int i, n,j;
  unsigned levels;
  unsigned sizeX;
  unsigned sizeY;
  float D;

  n=256;

  data =(float *) calloc (2*n, sizeof (float));            /* array to store each data row of 512 elements */
  spectrum = (float *) calloc (n*n, sizeof (float));       /* array to store spectrum */
  norspectrum = (float *) calloc (n*n, sizeof (float));    /* array to store normalised spectrum */
  norImage = (float *) calloc (n*n, sizeof (float));       /* array to store normalised image */
  outputImage = (float *) calloc (n*n, sizeof (float));

  shiftimg = (float *) calloc (n*n, sizeof (float));       /* array to store centered input image */
  
  output1 = (float *) calloc (2*256*256, sizeof (float));  /* array to store output of first dft */
  output2 = (float *) calloc (2*256*256, sizeof (float));  /* array to store output of second dft */
  output3 = (float *) calloc (2*256*256, sizeof (float));  /* array to store output of first idft */
  output4 = (float *) calloc (2*256*256, sizeof (float));  /* array to store output of second idft */
  output = (float *) calloc (2*256*256, sizeof (float));
  
  real = (float *) calloc (256*256, sizeof (float));       /* array to store real part */
  imaginary = (float *) calloc (256*256, sizeof (float));  /* array to store imaginary part */
  realout = (float *) calloc (256*256, sizeof (float));    /* array to store real part of filtered image */
  imagout = (float *) calloc (256*256, sizeof (float));    /* array to store imaginary part of filtered image */
  filImage = (float *) calloc (256*256, sizeof (float));   /* array to store filtered image*/
  
  filter = (float *) calloc (256*256, sizeof (float));     /* array to store filter */
  combine = (float *) calloc (2*256*256, sizeof (float));  /* array to combine real and imaginary part*/
  //filImage = (float *) calloc (256*256, sizeof (float));
  
  float energy=0;
  unsigned char oimg[256*256];
  unsigned char spect[256*256];
  unsigned char filterImage[256*256];

        /*-----------Open files for writing images----------------*/    

  FILE *spec = fopen("spectrum.pgm","w");         /* Open empty .pgm image for writing spectrum */
  if(spec==0)                                     /*error handling*/
    { 
      printf("error opening file\n");           
      fclose(spec);
      return 1;
    }
  FILE *oi = fopen("outputImage.pgm","w");        /* Open empty .pgm image for writing output image */
  if(oi==0)                                       /*error handling*/
    { 
      printf("error opening file\n");           
      fclose(oi);
      return 1;
    }


  FILE *ii = fopen("inputImage.pgm","w");        /* Open empty .pgm image for writing input image */
  if(ii==0)                                      /*error handling*/
    { 
      printf("error opening file\n");           
      fclose(ii);
      return 1;
    }


  FILE *fi = fopen("filteredImage.pgm","w");     /* Open empty .pgm image for writing filtered image*/
  if(fi==0)                                      /*error handling*/
    { 
      printf("error opening file\n");           
      fclose(fi);
      return 1;
    }

             /*------------ Get the input image -------------------*/

  FILE *fp  = fopen(argv[1],"r");         /*pointer points to start of the file*/
  if(fp == 0)
    {
      printf("error opening file\n");    /*error handling*/
      fclose(fp);
      return 1;
    }

                 /*------- Remove the header --------*/
                 /*----------Code given by TA--------*/
 if(3!=fscanf(fp,"P5 %d %d %d",&sizeX, &sizeY, &levels)) return 1;

  inputimage= (unsigned char *)malloc (sizeX*sizeY);
  fread(inputimage,sizeof(unsigned char),sizeX*sizeY,fp);
  fclose(fp);

 
                  /*-------Shift input image to centre---------*/
  
for(i=0;i<256;i++)
    {
      for(j=0;j<256;j++)
	{
	  shiftimg[i*256 + j] = (pow(-1,(i+j))) * inputimage[i*256 + j]; 
	}  
    }

                  /*----------- Do DFT two times------------*/

/*1*/
  for(i=0;i<256;i++)
    {
      for(j=0;j<2*256;j+=2)
	{
	  data[j]=shiftimg[(i*256)+(j/2)];
	  data[j+1]=0;
	}
      

      four1(data,n,1);             /* calculate DFT of each row */
      first(i,data,output1);       /* Store each row  */
    }

/*2*/
    for(i=0;i<256;i++)
      {
         int c=0;   
       for(j=0;j<256*2;j+=2)
	 {
	   data[j]=output1[ (256*2*c) + (2*i)];
	   data[j+1]=output1[(256*2*c) +(2*i)+1];
	   c++;
	 }

       four1(data,n,1);           /* calculate DFT of each row */
       second(i,data,output2);    /* Store each row  */
      }
   
		 /*------------ separate real and imaginary -------------*/
   
   separate(output2);

		 /*-------- Get the spectrum  ----------*/
   
  for(i=0;i<256*256;i++)
     spectrum[i]=sqrt( (real[i]*real[i])+(imaginary[i]*imaginary[i]) );


	   /*-------Get the input image back by doing  IDFT 2 times --------*/

/*1*/
   for(i=0;i<256;i++)
      {
         int c=0;   
       for(j=0;j<256*2;j+=2)
	 {
	   data[j]=output2[ (256*2*c) + (2*i)];
	   data[j+1]=output2[( (256*2*c) +(2*i)+1)];
	   c++;
	 }
       four1(data,n,-1);           /* calculate IDFT of each row */
       second(i,data,output3);      /* Store each row  */
     }
   

/*2*/
   for(i=0;i<256;i++)
    {
      for(j=0;j<2*256;j++)
	{
	    data[j]=output3[(i*2*256)+j];
	}
      four1(data,n,-1);           /* calculate IDFT of each row */
      first(i,data,output4);     /* Store each row  */
    }


		   /*--------- Separate real and imaginary --------*/
 
  separate(output4);
	
		   /*---- Store the image ------*/

    for(i=0;i<256*256;i++)
      outputImage[i]=sqrt( (real[i]*real[i])+(imaginary[i]*imaginary[i]) );


/////////////////////////////////////////////////////////     PART 2      /////////////////////////////////////////////////////

		   /*----- Create the filter which is centered --------*/

     printf("Enter value of D\n");/* Ask for D value from user*/
     scanf("%f",&D);
 for(i=0;i<256;i++)
      {
	for(j=0;j<256;j++)
	  {
	    filter[i*256+j]=1/(1+pow((sqrt((i-128)*(i-128)+(j-128)*(j-128))/D),2));  
	  }
      }

     /*------- Separate real and imaginary part of frequency domain image---------*/

  for (i=0;i<2*256*256;i++)
      {
      if(i%2==0)
	real[i/2]=output2[i];
      else
	imaginary[i/2]=output2[i];
       }

      /*------Do filtering by multiplying real and imaginary part with filter in frequency domain -----*/  

for(i=0;i<256*256;i++)
    {
    realout[i]=real[i]*filter[i];
    imagout[i]=imaginary[i]*filter[i];
    }

		   /*----- Combine real and imaginary part of image --------*/

  for(i=0;i<256;i++)
      {
	for(j=0;j<2*256;j++)
	  {
	    if(j%2==0){
	      combine[i*2*256+j]=realout[(i*256)+(j/2)];
	    }
	    else{
	      combine[i*2*256+j]=imagout[(i*256)+(j/2)];
	    }

	  }
      }

		   /*-------- Do IDFT 2 times to get back filtered image in time domain  -------------*/

/*1*/
   for(i=0;i<256;i++)
      {
         int c=0;   
       for(j=0;j<256*2;j+=2)
	 {
	   data[j]=combine[ (256*2*c) + (2*i)];        
	   data[j+1]=combine[( (256*2*c) +(2*i)+1)];
	   c++;
	 }
       four1(data,n,-1);                /* calculate IDFT of each row */
	   second(i,data,output3);          /* Store each row  */
	}
   
/*2*/
   for(i=0;i<256;i++)
    {
      for(j=0;j<2*256;j++)
	{
	    data[j]=output3[(i*2*256)+j];
	}
      four1(data,n,-1);                /* calculate IDFT of each row */
      first(i,data,output4);           /* Store each row  */
    }


      /*---- Separate real and imaginary----*/
	separate(output4);

     /*------ Calculate magnitude  -------*/
    for(i=0;i<256*256;i++)
      {
		filImage[i]=sqrt( (real[i]*real[i])+(imaginary[i]*imaginary[i]) );
       }


     
       

   
   normalised(norspectrum,spectrum);                   /*Normalization of filter*/ 
    
    for(i=0;i<256*256;i++)	
      spect[i]=(unsigned char)norspectrum[i];          /*Convert spectrum image from float to unsigned char*/


    normalised(norspectrum,outputImage);               /*Normalization of outputimage*/ 
    
    for(i=0;i<256*256;i++)	
      oimg[i]=(unsigned char)norspectrum[i];           /*Convert output image from float to unsigned char*/

   
    normalised(norspectrum,filImage);                  /*Normalization of filtered image*/ 

   /*------- Calculate energy of spectrum --------*/
    for(i=0;i<256*256;i++)
      energy = energy + filImage[i]*filImage[i];  
    printf("Energy of spectrum is :%f for D= %f\n",energy,D);
    
    
    for(i=0;i<256*256;i++)
      filterImage[i]=(unsigned char)norspectrum[i];    /*convert filtered image from float to unsigned char*/
   


    /* Print input image */
    fprintf(ii, "P5 %d %d %d ",n,n, 255);              /*write header*/
    fwrite(inputimage,sizeof(unsigned char),n*n,ii);   /*write binary image*/
    fclose(ii);
	 
	 /* Print output image*/     
    fprintf(oi, "P5 %d %d %d ",n,n, 255);              /*write header*/
    fwrite(oimg,sizeof(unsigned char),n*n,oi);         /*write binary image*/
    fclose(oi);
     
    /* Print spectrum */
    fprintf(spec, "P5 %d %d %d ",n,n, 255);            /*write header*/
    fwrite(spect,sizeof(unsigned char),n*n,spec);      /*write binary image*/
    fclose(spec);
     
    /* Print filtered image*/
    fprintf(fi, "P5 %d %d %d ",n,n, 255);              /*write header*/
    fwrite(filterImage,sizeof(unsigned char),n*n,fi);  /*write binary image*/
    fclose(fi);

    return 0;
}
