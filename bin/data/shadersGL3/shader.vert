#version 150

uniform mat4 modelViewProjectionMatrix;
in vec4 position;
// uniform mat4 gl_ModelViewMatrix;
// uniform mat4 gl_ProjectionMatrix;
// attribute vec4 gl_Vertex;
// uniform float time;

void main(){
  // float displacementHeight = 100;
  // float displacementY = sin(time + (position.x / 100.0)) * displacementHeight;

  // vec4 modifiedPosition = modelViewProjectionMatrix * position;
  // modifiedPosition.y += displacementY;
  // gl_Position = modifiedPosition;
  gl_Position = modelViewProjectionMatrix * position;

}
