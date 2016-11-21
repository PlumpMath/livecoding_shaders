#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

  // ofSetupOpenGL(1024,768, OF_WINDOW);
  ofGLFWWindowSettings settings;
  settings.setGLVersion(3, 0);
  settings.width = 512;
  settings.height = 384;
  ofCreateWindow(settings);
  
  ofRunApp( new ofApp());

}
