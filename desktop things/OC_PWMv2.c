#include "NU32.h"
#include <stdio.h>

#define NUMSAMPS 1000 // nmumber of points in waveform 
#define PLOTPTS 200 // number of data points to plot 
#define DECIMATION 10 // plot every 10th point 

static volatile int Waveform[NUMSAMPS]; //waveform 
static volatile int ADCarray[PLOTPTS]; // measured values to plot 
static volatile int REFarray[PLOTPTS]; // reference values to plot 
static volatile int StoringData = 0; // if this flag = 1, currently storing 
static volatile int Eint = 0; 
static volatile float u = 50.0, unew = 0; 



static volatile float Kp = 0, Ki = 0; // control gains 


unsigned int adc_sample_convert(int pin) { // sample & convert the value on the given 
                                           // adc pin the pin should be configured as an 
                                           // analog input in AD1PCFG
    unsigned int elapsed = 0, finish_time = 0;
    AD1CHSbits.CH0SA = pin;                // connect chosen pin to MUXA for sampling
    AD1CON1bits.SAMP = 1;                  // start sampling
    elapsed = _CP0_GET_COUNT();
    finish_time = elapsed + 10;
    while (_CP0_GET_COUNT() < finish_time) { 
      ;                                   // sample for more than 250 ns
    }
    AD1CON1bits.SAMP = 0;                 // stop sampling and start converting
    while (!AD1CON1bits.DONE) {
      ;                                   // wait for the conversion process to finish
    }
    return ADC1BUF0;                      // read the buffer with the result
}

void makeWaveform(){

    int i = 0, center = 500, A = 300;
    for (i=0;i<NUMSAMPS; ++i){
        if(i<NUMSAMPS/2){

            Waveform[i] = center + A; 
        }
        else{
            Waveform[i] = center - A;
        }

    }

}

void __ISR(_TIMER_2_VECTOR, IPL5SOFT) Controller(void){

    static int counter = 0;
    static int plotind = 0;
    static int decctr = 0;
    static int adcval = 0;
    static int err = 0;
     

    //insert line(s) to set OC1RS
    adcval = adc_sample_convert(16);
    

    err = Waveform[counter]- adcval;

    Eint = Eint + err; 

    if (Eint > 750){

        Eint = 750;
    } else if(Eint < -750){


        Eint = -750;
    }

    u = Kp*err + Ki*Eint;

    unew = u + 50.0;
    if (unew > 100.0){

        unew = 100.0;
    }
    else if (unew < 0.0){
        unew = 0.0;
    }

    OC1RS = (unsigned int) ((unew/100.0) * PR3);

    if (StoringData){

        decctr++;
        if(decctr == DECIMATION){
            decctr = 0;
            ADCarray[plotind] = adcval;
            REFarray[plotind] = Waveform[counter]; 
            plotind++; 

        }
        if (plotind == PLOTPTS){
            plotind = 0;
            StoringData = 0;
        }

    
    }
    
    

    counter++;
    if (counter == NUMSAMPS){
        counter = 0;
    }

    
    u = unew; 

    IFS0bits.T2IF = 0;
    //NU32_WriteUART3("bingbong\r\n");
}

int main(void){

    char message[100];
    float kptemp = 0, kitemp = 0;
    int i = 0; 

    NU32_Startup();

    __builtin_disable_interrupts(); 
    // OC_PWM stufffs
    T2CONbits.TCKPS = 1; 
    PR2 = 39999; 
    TMR2 = 0;
    OC1CONbits.OCM = 0b110; 
    OC1RS = 500; 
    OC1R = 500; 
    T2CONbits.ON = 1; 
    OC1CONbits.ON = 1;
    OC1CONbits.OCTSEL = 1; 

    //Turn on the actual ADC stuff 
    //AD1PCFGbits.PCFg14 = 0; 
    AD1PCFGbits.PCFG15 = 0; 
    AD1CON3bits.ADCS = 2; 

    AD1CON1bits.ADON = 1; 

    PR3 = 3999; 
    TMR3 = 0; 
    T3CONbits.TCKPS = 0; 
    T3CONbits.TGATE = 0; 
    //T3CONbits.TCS = 0; maybe reimplement 
    T3CONbits.ON = 1; 
    /*IPC3bits.T3IP = 5; 
    IPC3bits.T3IS = 0;
    IFS0bits.T3IF = 0; 
    IEC0bits.T3IE = 1; */

    IPC2bits.T2IP = 5;
    IPC2bits.T2IS = 0; 
    IFS0bits.T2IF = 0; 
    IEC0bits.T2IE = 1;

    __builtin_enable_interrupts(); 

   /* int s[100]; 
    int i = 0; 
    char m[100]; &*/
    makeWaveform();
    while(1){

        NU32_ReadUART3(message, sizeof(message)); 
        sscanf(message, "%f %f", &kptemp, &kitemp); 
        __builtin_disable_interrupts(); 
        Kp = kptemp; 
        Ki = kitemp;
        Eint = 0; 
        __builtin_enable_interrupts();
        StoringData = 1; 
        while (StoringData) {

        }

        for (i=0; i<PLOTPTS; i++){

            sprintf(message, "%d %d %d\r\n", PLOTPTS-i, ADCarray[i], REFarray[i]);
            NU32_WriteUART3(message);
        }
        
        
        
        
        /*
        for (i = 0; i < 100; i++){

            s[i] = adc_sample_convert(16);
            _CP0_SET_COUNT(0); 
            while(_CP0_GET_COUNT() < 40000000/100){}

        }

        for(i=0; i<100; i++){
            sprintf(m, "%d\r\n", s[i]);
            NU32_WriteUART3(m); 
        }
        */
         
    }
    

    return 0; 

  

}
