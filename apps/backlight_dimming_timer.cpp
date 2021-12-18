#include "backlight_dimming_timer.h"
#include "global_preferences.h"

int nbrofrun = 0;
int brightnessLevel;
int nbrofsteps;
int nextbrightness;
float timeToSleep; // In miliseconds

BacklightDimmingTimer::BacklightDimmingTimer() :
  Timer(k_idleBeforeDimmingDuration/Timer::TickDuration)
{
}

bool BacklightDimmingTimer::fire() {
  if (nbrofrun == 0) {
    brightnessLevel = GlobalPreferences::sharedGlobalPreferences()->brightnessLevel();
    nbrofsteps = brightnessLevel / decreaseby;
    timeToSleep = decreasetime / nbrofsteps;
    m_period = timeToSleep / Timer::TickDuration;
    if (m_period == 0) {
      m_period = 1;
    }
    resetTimer();
  }
  if (nbrofrun < nbrofsteps) {
    nextbrightness = (brightnessLevel-k_dimBacklightBrightness)/nbrofsteps * (nbrofsteps-nbrofrun);
    Ion::Backlight::setBrightness(nextbrightness);
    resetTimer();
  } else if (nbrofrun == nbrofsteps) {
    Ion::Backlight::setBrightness(k_dimBacklightBrightness);
  }
  nbrofrun++;
  return false;
}

void BacklightDimmingTimer::reset() {
  nbrofrun = 0;
  m_period = k_idleBeforeDimmingDuration / Timer::TickDuration;
  resetTimer();
}

void BacklightDimmingTimer::resetTimer() {
  BacklightDimmingTimer::m_numberOfTicksBeforeFire = BacklightDimmingTimer::m_period;
}
