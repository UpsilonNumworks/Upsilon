#include "color_list.h"
#include "apps/i18n.h"

namespace Graph {
    namespace FunctionColors {
        I18n::Message Message(int index) {
            static constexpr I18n::Message message[NumberOfColors] = {
            I18n::Message::FunctionColorBlack,
            I18n::Message::FunctionColorBlue,
            I18n::Message::FunctionColorRed,
            I18n::Message::FunctionColorPurple,
            I18n::Message::FunctionColorGreen,
            I18n::Message::FunctionColorOrange,
            I18n::Message::FunctionColorYellow,
            I18n::Message::FunctionColorWhite
        };
        return message[index];
        }
        KDColor color(int index) {
            switch(index) {
                case 0: return KDColorBlack;
                case 1: return KDColorBlue;
                case 2: return KDColorRed;
                case 3: return KDColorPurple;
                case 4: return KDColorGreen;
                case 5: return KDColorOrange;
                case 6: return KDColorYellow;
                case 7: return KDColorWhite;
                default: return KDColorRed;
            }
        }
        I18n::Message currentColor(KDColor color) {
            if(color == KDColorBlack) return Message(0);
            if(color == KDColorBlue) return Message(1);
            if(color == KDColorRed) return Message(2);
            if(color == KDColorPurple) return Message(3);
            if(color == KDColorGreen) return Message(4);
            if(color == KDColorOrange) return Message(5);
            if(color == KDColorYellow) return Message(6);
            if(color == KDColorWhite) return Message(7);
            return Message(2);
        }
    }
}