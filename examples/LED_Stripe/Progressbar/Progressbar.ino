#include <HTL_onboard.h>

#define progressDelay 250

HTL_onboard onboard;

int progressValue = 0;

void setup() {
  onboard.begin();
}

void loop() {
  onboard.writeProgress(progressValue);

  progressValue++;
  if (progressValue > 10) {
    progressValue = 0;
  }
  
  delay(progressDelay);
}