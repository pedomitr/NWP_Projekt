#include "stdafx.h"
#include "Fields.h"


Fields::Fields(RECT first_Field)
{
	int i = 0;
	while (i < 8) {
		column[i] = { first_Field.left + i, first_Field.right + i };
		++i;
	}

	i = 0;
	while (i < 8) {
		row[i] = { first_Field.top - i, first_Field.bottom - i };
		++i;
	}
}


Fields::~Fields()
{
}
