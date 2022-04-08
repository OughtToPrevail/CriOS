#ifndef CRIOS_IDENTITYPAGING_H
#define CRIOS_IDENTITYPAGING_H

#include "Paging.h"

class IdentityPaging : public Paging
{
public:
	void setupPaging() override;
};


#endif //CRIOS_IDENTITYPAGING_H
