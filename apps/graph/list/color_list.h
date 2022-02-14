#pragma once

#include <escher/i18n.h>
#include <escher.h>
#include "color_parameter_controller.h"

namespace Graph {
    constexpr static int NumberOfColors = NUMBER_OF_COLORS_AVAILABLE;
    I18n::Message Message(int index);
    KDColor color(int index);
    I18n::Message currentColor(KDColor color);
}