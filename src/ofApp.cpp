#include "ofApp.h"

void ofApp::setup() {
  soundStream.printDeviceList();
  // soundStream.setDeviceID(AUDIOINPUT);
  soundStream.setDeviceID(1);
  // ofLog(OF_LOG_NOTICE, "AUDIOINPUT: " + ofToString(AUDIOINPUT));
  left.assign(BUFFERSIZE, 0.0);
  soundStream.setup(this, 0, 1, 44100, BUFFERSIZE, SAMPLES);
  shader.load("shadersGL3/shader");
  // fft = ofxFft::create(BUFFERSIZE, OF_FFT_WINDOW_HAMMING);
  // fft = ofxFft::create(BUFFERSIZE, OF_FFT_WINDOW_HAMMING, OF_FFT_FFTW);
  fft.setup(BUFFERSIZE);

  
  
  // drawBins.resize(fft->getBinSize());
  // middleBins.resize(fft->getBinSize()); 
  // audioBins.resize(fft->getBinSize());

  // int a = fft.getBins();
  
  // std::cout << "Length of array = " << sizeof(buffer) << std::endl;
}

void ofApp::update() {
  // FFT
  fft.update();
  vector<float> buffer = fft.getBins();
  contraFFT = fft.getBins()[0];
  float avgContra,avgBass,avgTenor,avgAlto,avgMezzo,avgSoprano,avgSopranino = 0;
  for(unsigned int i = 0; i < 1024; i++ )
    {
      if (i < 128) {avgContra += buffer[i];}
      else if (i < 256) {avgBass += buffer[i];}
      else if (i < 384) {avgTenor += buffer[i];}
      else if (i < 512) {avgAlto += buffer[i];}
      else if (i < 640) {avgMezzo += buffer[i];}
      else if (i < 768) {avgSoprano += buffer[i];}
      else { avgSopranino += buffer[i];}
    }
  contraFFT = avgContra/128;
  bassFFT=avgBass/128;
  tenorFFT=avgTenor/128;
  altoFFT=avgAlto/128;
  mezzoFFT=avgMezzo/128;
  sopranoFFT=avgSoprano/128;
  sopraninoFFT=avgSopranino/256;
}

void ofApp::draw() {
  // ofSetWindowTitle(ofToString(ofGetFrameRate()));
  
  std::string windowTitle = "FPS: ";
  windowTitle += ofToString(ofGetFrameRate());
  // ofSetWindowTitle(ofToString(ofGetElapsedTimef()));
  ofSetWindowTitle(windowTitle);
  ofSetColor(255);
  shader.begin(); 
  ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
  // ofDrawRectangle(0, 0, 512, 384);
  shader.setUniform3f("iResolution", ofGetWidth(), ofGetHeight(), 0.0);  
  shader.setUniform1f("iGlobalTime", ofGetElapsedTimef());
  shader.setUniform1f("iContra", contraFFT);
  shader.setUniform1f("iBass", bassFFT);
  shader.setUniform1f("iTenor", tenorFFT);
  shader.setUniform1f("iAlto", altoFFT);
  shader.setUniform1f("iMezzo", mezzoFFT);
  shader.setUniform1f("iSoprano", sopranoFFT);
  shader.setUniform1f("iSopranino", sopraninoFFT);
  // AUDIO IN
  for(unsigned int i= 0; i<BUFFERSIZE; i++) {
    float sample= left[i];
    shader.setUniform1f("iAmp", sample);
  }

  shader.end();

  // ofClear(0);
  // std::string fftvals = ofToString(contraFFT);
  // ofDrawBitmapString(fftvals, 1, 100);

  
  // //wave1 - draw using shape and vertices
  // ofTranslate(0, ofGetWindowHeight()*0.333);
  // ofBeginShape();
  // for(unsigned int i= 0; i<BUFFERSIZE; i++) {
  //   float sample= left[i];
  //   //and here draw whatever
  //   ofVertex(i, sample*500.0);
  // }
  // ofEndShape();
    
  // //wave2 - draw plain lines instead
  // ofTranslate(0, ofGetWindowHeight()*0.333);
  // for(unsigned int i= 1; i<BUFFERSIZE; i++) {
  //   ofDrawLine(i, left[i]*500.0, i-1, left[i-1]);
  // }
}

void ofApp::audioIn(float *input, int bufferSize, int nChannels) {
  float maxValue = 0;
  for(int i = 0; i < bufferSize; i++) {
    if(abs(input[i]) > maxValue) {
      maxValue = abs(input[i]);
      }
    }
  
    for(int i= 0; i<bufferSize; i++) {
      left[i]= input[i];
    }

  
    // fft->setSignal(input);
	
    // float* curFft = fft->getAmplitude();
    // memcpy(&audioBins[0], curFft, sizeof(float) * fft->getBinSize());

    // fft->setSignal(input);
    // middleBins = audioBins;

    // maxValue = 0;
    // for(int i = 0; i < fft->getBinSize(); i++) {
    //   if(abs(audioBins[i]) > maxValue) {
    //     maxValue = abs(audioBins[i]);
    //   }
    //  }
    // for(int i = 0; i < fft->getBinSize(); i++) {
    //   audioBins[i] /= maxValue;
    //  }
  }



  void ofApp::keyPressed(int key){
    switch (key) {
    case 'f':
      ofToggleFullscreen();
      break;
    }
  }
