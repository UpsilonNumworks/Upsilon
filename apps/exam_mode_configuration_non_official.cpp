#include "exam_mode_configuration.h"

using namespace Poincare;

constexpr Shared::SettingsMessageTree ExamModeConfiguration::s_modelExamChildren[] = {
    Shared::SettingsMessageTree(I18n::Message::ExamModeModeStandard),
    Shared::SettingsMessageTree(I18n::Message::ActivateExamMode)
};

int ExamModeConfiguration::numberOfAvailableExamMode() {
    return 1; // Only one option
}

GlobalPreferences::ExamMode ExamModeConfiguration::examModeAtIndex(int index) {
    // Always return Standard Exam Mode
    return GlobalPreferences::ExamMode::Standard;
}

I18n::Message ExamModeConfiguration::examModeActivationMessage(int index) {
    return I18n::Message::ActivateExamMode;
}

I18n::Message ExamModeConfiguration::examModeActivationWarningMessage(GlobalPreferences::ExamMode mode, int line) {
    if (mode == GlobalPreferences::ExamMode::Off) {
        I18n::Message warnings[] = {I18n::Message::ExitExamMode1, I18n::Message::ExitExamMode2, I18n::Message::Default};
        return warnings[line];
    }
    assert(mode == GlobalPreferences::ExamMode::Standard || mode == GlobalPreferences::ExamMode::NoSym || mode == GlobalPreferences::ExamMode::NoSymNoText);
    I18n::Message warnings[] = {I18n::Message::ActiveExamModeMessage1, I18n::Message::ActiveExamModeMessage2, I18n::Message::ActiveExamModeMessage3};
    return warnings[line];
}

KDColor ExamModeConfiguration::examModeColor(GlobalPreferences::ExamMode mode) {
    assert(mode == GlobalPreferences::ExamMode::Standard || mode == GlobalPreferences::ExamMode::NoSym || mode == GlobalPreferences::ExamMode::NoSymNoText);
    return KDColorRed;
}

bool ExamModeConfiguration::appIsForbiddenInExamMode(App::Descriptor::ExaminationLevel appExaminationLevel, GlobalPreferences::ExamMode mode) {
    if (mode == GlobalPreferences::ExamMode::NoSymNoText) {
        return appExaminationLevel == App::Descriptor::ExaminationLevel::Basic;
    }
    return false;
}

bool ExamModeConfiguration::exactExpressionsAreForbidden(GlobalPreferences::ExamMode mode) {
    return mode == GlobalPreferences::ExamMode::NoSymNoText ? true : false;
}
