#include "data.h"

data::data()
{

}


double data::getTime(){
    return time;
}

double data::getValue(){
    return value;
}

void data::setTime(int timeInput){
    time = timeInput;
}

void data::setValue(int valueInput){
    value = valueInput;
}
