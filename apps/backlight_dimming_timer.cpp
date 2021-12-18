#include "backlight_dimming_timer.h"
#include "global_preferences.h"

BacklightDimmingTimer::BacklightDimmingTimer() :
  Timer(k_idleBeforeDimmingDuration/Timer::TickDuration)
{
}

bool BacklightDimmingTimer::fire() {
  if (m_dimerExecutions == 0) {
    m_brightnessLevel = GlobalPreferences::sharedGlobalPreferences()->brightnessLevel();
    m_nbrofsteps = m_brightnessLevel / decreaseby;
    m_timeToSleep = decreasetime / m_nbrofsteps;
    m_period = m_timeToSleep / Timer::TickDuration;
    if (m_period == 0) {
      m_period = 1;
    }
    resetTimer();
  }
  if (m_dimerExecutions < m_nbrofsteps) {
    m_nextbrightness = (m_brightnessLevel-k_dimBacklightBrightness)/m_nbrofsteps * (m_nbrofsteps-m_dimerExecutions);
    Ion::Backlight::setBrightness(m_nextbrightness);
    resetTimer();
  } else if (m_dimerExecutions == m_nbrofsteps) {
    Ion::Backlight::setBrightness(k_dimBacklightBrightness);
  }
  m_dimerExecutions++;
  return false;
}

void BacklightDimmingTimer::reset() {
  m_dimerExecutions = 0;
  m_period = k_idleBeforeDimmingDuration / Timer::TickDuration;
  resetTimer();
}

void BacklightDimmingTimer::resetTimer() {
  BacklightDimmingTimer::m_numberOfTicksBeforeFire = BacklightDimmingTimer::m_period;
}
