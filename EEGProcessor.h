#ifndef EEG_PROCESSOR_H
#define EEG_PROCESSOR_H

#define EEG_PIN A0
#define SAMPLE_SIZE 128
#define SAMPLE_RATE 256
#define SAMPLING_FREQUENCY 250.0

double processEEGSignal();
float EEGFilter(float input);

#endif
