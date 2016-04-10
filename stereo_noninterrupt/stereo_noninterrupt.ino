/**
 * Use this to handle a 4-pin stereo jack connection
 * https://www.digikey.com/product-detail/en/cui-inc/SJ1-3514/CP1-3514-ND/738682
 * 
 * Use this when you do not have an interrupt pin to handle connection, it requires more variables
 * You should replace VAR with whatever you're actually controlling
 */
// stereo connections
const int VAR_TIP_PIN = 5;     // connect pin for stereo tip (digital or analog)
const int VAR_RING_PIN = 4;    // connect pin for stereo ring (digital or analog)
const int VAR_CONNECT_PIN = 2; // connect pin for stereo connection

// variables
// 0 = connected, 1&2 = read state, 3 = debounce
boolean var_connection_state[4] = {false, false, false, false};
unsigned long last_var_interrupt = 0;

void setup()  {
  Serial.begin(9600);
  
  setupVar();
}

void loop()  {
  checkVarConnected();
  
  if (isVarConnected()) {
    getVarTip();
    getVarSleeve();
  }
}

/**
 * Initialize the pins for var
 */
void setupVar() {
  // turn on pull-ups
  digitalWrite(VAR_TIP_PIN, HIGH);
  digitalWrite(VAR_CONNECT_PIN, HIGH);

  var_connection_state[0] = digitalRead(VAR_CONNECT_PIN);
}

/**
 * Check to see if the pin has been connected or disconnected
 */
void checkVarConnected()  {
  checkVarConnectedDiff();
  
  if (var_connection_state[3]) {
    // Debounced the connect pin
    unsigned long curtime = millis();
    if (curtime - last_var_interrupt >= 200) {
      var_connection_state[0] = var_connection_state[1];
      var_connection_state[3] = false;
      Serial.print("connected: ");
      Serial.println(var_connection_state[0]);
    }
  }               
}

/**
 * retrieve the line tip value
 */
int getVarTip() {
  return digitalRead(VAR_TIP_PIN);
}

/**
 * retrieve the line ring value
 */
int getVarSleeve() {
  return digitalRead(VAR_RING_PIN);
}

/**
 * @return boolean true if the pin is considered connected
 */
boolean isVarConnected() {
  return var_connection_state[0];
}

/**
 * handle the connect pin changing
 */
void checkVarConnectedDiff() {
  var_connection_state[1] = digitalRead(VAR_CONNECT_PIN);

  if (var_connection_state[1] != var_connection_state[2]) {
    // We've detected a change in state
    var_connection_state[2] = var_connection_state[1];
    unsigned long curtime = millis();
    last_var_interrupt = curtime;
    var_connection_state[3] = true;
  }
}

