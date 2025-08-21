// Test code for the mavlink interface stuff
// Basically stuff from https://discuss.ardupilot.org/t/mavlink-and-arduino-step-by-step/25566
//
// Connect to the serial port via Mission Planner (115200 baud) and it should connect and send parameters

#include <mavlink.h> 
#define  LED_BUILTIN  2
#define  Fuel_L1_Detect_Pin 4

#define  Fuel_L2_Detect_Pin 18
// Hardware ports
COMMS_MAVLINK mavlink(Serial);
void send_param(void);
// Global variables
unsigned long _1Hz_timer = 0;
uint16_t _counter = 0;
// --- Your new custom parameter variable ---
float param_fuel_level_1 = 0.0;
float param_fuel_level_2 = 0.0;



void setup()
{
  // Initialise the UART ports
  Serial.begin(115200);  // Open the mavlink port

  // LEDs
  pinMode(LED_BUILTIN,OUTPUT);

  // Fuel Line Detect
  pinMode(Fuel_L1_Detect_Pin,INPUT_PULLUP);

  pinMode(Fuel_L2_Detect_Pin,INPUT_PULLUP);

  // Set up the mavlink connection
  mavlink.init();

}

void loop()
{
  // Handle any data we're being sent
  mavlink.update();

  // Send a heartbeat at 2 Hz
  if (millis() - _1Hz_timer > 500) {
    // Update timer
    _1Hz_timer = millis();
    // Send some data and a heartbeat
     char buf[50];
    if(digitalRead(Fuel_L1_Detect_Pin) == 0){
      sprintf(buf, "Fuel Level OK ");
      param_fuel_level_1 = 0;
    }else{  
      sprintf(buf, "Fuel Level Low (Aprox 1 liter) | Timestamp: %3d", _counter++);
      param_fuel_level_1=1;
    }
     if(digitalRead(Fuel_L2_Detect_Pin) == 0){
       //sprintf(buf, "Fuel Level Below | Timestamp: %3d", _counter++);
       param_fuel_level_2 = 0;
       
    }else{ 
            param_fuel_level_2=1;
            sprintf(buf, "Fuel Level Critcal Low [Below 1 liter] ");
    }
    //  if (_counter % 2 == 0) { // 50 * 100ms = 5 seconds
    //     fuel_line = !fuel_line;
    // }
    mavlink.send_heartbeat();
    mavlink.send_string(buf,sizeof(buf));

    // my_param = (float)random(0, 100) / 10.0; // Example: sending a random value
     send_param();
  }
}
// --- New function to send your custom parameter ---
void send_param(void) {

 mavlink_message_t msg;


 mavlink_msg_named_value_float_pack(mavlink.computer.system_id, mavlink.computer.component_id, &msg,
     millis(), "Fuel_Lvl_Low", param_fuel_level_1);


 // Update LED
    digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));

  mavlink.broadcast(msg);
  delay(100);

  mavlink_msg_named_value_float_pack(mavlink.computer.system_id, mavlink.computer.component_id, &msg,
     millis(), "Fuel_Lvl_Crtcl", param_fuel_level_2);

  mavlink.broadcast(msg);

  return;
}
