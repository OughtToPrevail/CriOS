#ifndef CRIOS_USERMODE_H
#define CRIOS_USERMODE_H


extern "C"
{
void jumpUsermode();
}


class Usermode
{
public:
	static void jumpIntoUsermode();
};


#endif //CRIOS_USERMODE_H
