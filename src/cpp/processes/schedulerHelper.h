#ifndef CRIOS_SCHEDULERHELPER_H
#define CRIOS_SCHEDULERHELPER_H
extern "C"
{
unsigned int scheduler_getEBP();
unsigned int scheduler_getESP();

unsigned int scheduler_getEIP();

void scheduler_contextSwitch(unsigned int eip, unsigned int esp, unsigned int ebp);
}
#endif //CRIOS_SCHEDULERHELPER_H
