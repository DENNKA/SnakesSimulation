#include "Button.h"

Button::Button(void (*action)(bool leftClick)) : action(action){

}

void Button::click(bool leftClick){
    action(leftClick);
}
