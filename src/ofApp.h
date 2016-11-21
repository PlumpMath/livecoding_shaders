#pragma once

#include "ofMain.h"
#include "ofxFft.h"
#include "ofxEasyFft.h"

#define BUFFERSIZE 2048
#define SAMPLES 2
#ifdef TARGET_LINUX
#define AUDIOINPUT 0  //jackd - edit this to match your system - see console window
#endif
#ifdef TARGET_OSX
#define AUDIOINPUT 5  //builtin+soundflower combined device - edit this to match your system - see console window
#endif

class ofApp : public ofBaseApp {
    
 public:
  void setup();
  void update();
  void draw();
  void audioIn(float *input, int bufferSize, int nChannels);
  void keyPressed(int key);
  vector <float>left;
  ofSoundStream soundStream;
  ofxEasyFft fft;
  /* ofxFft* fft; */
  vector<float> drawBins, middleBins, audioBins;
  ofShader shader;
  ofPlanePrimitive plane;
  float contraFFT,bassFFT,tenorFFT,altoFFT,mezzoFFT,sopranoFFT,sopraninoFFT;
};
