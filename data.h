#ifndef DATA_H
#define DATA_H


class data
{
public:
    data();
    double getTime();
    double getValue();
    void setTime(int timeInput);
    void setValue(int valueInput);

private:
    double time;
    double value;
};

#endif // DATA_H
