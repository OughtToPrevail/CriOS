#ifndef OSTEST_LAYOUTPARAMS_H
#define OSTEST_LAYOUTPARAMS_H


class LayoutParams
{
public:
	explicit LayoutParams(unsigned int margin=0);

	unsigned int getMargin() const;
private:
	unsigned int _margin;
};

#endif //OSTEST_LAYOUTPARAMS_H
