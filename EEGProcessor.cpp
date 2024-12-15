#include "EEGProcessor.h"
#include <Arduino.h>
#include <arduinoFFT.h>

double vReal[SAMPLE_SIZE];
double vImag[SAMPLE_SIZE];

ArduinoFFT FFT = ArduinoFFT(vReal, vImag, SAMPLE_SIZE, SAMPLING_FREQUENCY);

double processEEGSignal() {
    for (int i = 0; i < SAMPLE_SIZE; i++) {
    float sensor_value = analogRead(EEG_PIN);  
    vReal[i] = EEGFilter(sensor_value);  
    vImag[i] = 0;  
    delayMicroseconds(1000000 / SAMPLE_RATE);
  }

  FFT.windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD); 
  FFT.compute(FFT_FORWARD);                       
  FFT.complexToMagnitude();                       
  return FFT.majorPeak(); 
}


float EEGFilter(float input) {
	float output = input;
	{
		static float z1, z2; // filter section state
		float x = output - -0.95391350*z1 - 0.25311356*z2;
		output = 0.00735282*x + 0.01470564*z1 + 0.00735282*z2;
		z2 = z1;
		z1 = x;
	}
	{
		static float z1, z2; // filter section state
		float x = output - -1.20596630*z1 - 0.60558332*z2;
		output = 1.00000000*x + 2.00000000*z1 + 1.00000000*z2;
		z2 = z1;
		z1 = x;
	}
	{
		static float z1, z2; // filter section state
		float x = output - -1.97690645*z1 - 0.97706395*z2;
		output = 1.00000000*x + -2.00000000*z1 + 1.00000000*z2;
		z2 = z1;
		z1 = x;
	}
	{
		static float z1, z2; // filter section state
		float x = output - -1.99071687*z1 - 0.99086813*z2;
		output = 1.00000000*x + -2.00000000*z1 + 1.00000000*z2;
		z2 = z1;
		z1 = x;
	}
	return output;
}