byte incomingByte;

void MIDIhardreset() {
  Serial.write(0xFF);
}

void MIDIsoftreset() {
  Serial.write(0xF0);
  Serial.write(0x7F);
  Serial.write(0x7F); //device id 7F = 127 all channels
  Serial.write(0x02);
  Serial.write(0x7F); // command format 7F = all devices
  Serial.write(0x0A); // action 0x0A= reset
  Serial.write(0xF7);
}


void setup(){
   Serial.begin(31250);
   // Send midi reset

   delay(500);

   MIDIhardreset();
   MIDIsoftreset();
   // Serial.write(0xFF);
}

  /*
void loop () {
  if (Serial.available() > 0) {   // read the incoming byte:
    incomingByte = Serial.read();
    Serial.write(incomingByte); //debugging over midi out
    
  }
}
*/

bool mute1 = false;
bool mute2 = false;
bool mute3 = false;
bool mute4 = false;
bool mute5 = false;

#define PART_LEVEL 0x07

void write (byte a, byte b, byte c) {
  Serial.write(a);
  Serial.write(b);
  Serial.write(c);
}

void loop () {
 if(Serial.available() > 2) {
   byte statusByte = Serial.read();
   byte a = Serial.read();
   byte b = Serial.read();

   if (statusByte == 0xB0){
     if (a == 0x0A) {
      // channel 8
       mute1 = !mute1;
       write(0xB8, PART_LEVEL, mute1 ? 0 : 127);
     } else if (a == 0x0B) {
       mute2 = !mute2;
       write(0xB9, PART_LEVEL, mute2 ? 0 : 127);
     } else if (a == 0x0C) {
       mute3 = !mute3;
       write(0xBA, PART_LEVEL, mute3 ? 0 : 127);
     } else if (a == 0x0D) {
       mute4 = !mute4;
       write(0xBB, PART_LEVEL, mute4 ? 0 : 127);
     } else if (a == 0x0E) {
       mute5 = !mute5;
       write(0xBC, PART_LEVEL, mute5 ? 0 : 127);
     } else {
       write(statusByte, a, b);
     }
     // playNote(0xB0, dataByte1, dataByte2);
    } else {
      write(statusByte, a, b);
    }
 }
}

