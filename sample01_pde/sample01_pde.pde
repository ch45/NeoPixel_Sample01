// sample01_pde.pde

import processing.serial.*;

Serial myPort;
final int BAUD = 57600;
final int FPS = 120;
final int LED_COUNT = 8;

void setup() {
  size(320, 240);

  String[] arrPorts = Serial.list();
  // printArray(arrPorts);
  String portName = arrPorts[2]; // COM4
  myPort = new Serial(this, portName, BAUD);
}

void draw() {
  background(255);
  ellipse(mouseX, mouseY, 20, 20);
  int val = (int)map(mouseX, 0, width, 0, LED_COUNT + 1);
  myPort.write(val);
  // println(val);
  delay(1000 / FPS);
}
