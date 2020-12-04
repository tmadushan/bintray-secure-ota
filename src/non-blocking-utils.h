
void non_blocking_delay(unsigned int interval);


void non_blocking_delay(unsigned int interval) {
  unsigned long currentMillis = 0;

  if( millis() >= currentMillis + interval){
    currentMillis += interval;
  }
}
