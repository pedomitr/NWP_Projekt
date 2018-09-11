#include "stdafx.h"
#include "Fields.h"


Fields::Fields(RECT first_Field, int hField)
{
	int i = 0;
	while (i < 8) {
		column[i] = { (first_Field.left + i) * hField, (first_Field.right + i) * hField };
		++i;
	}

	i = 0;
	while (i < 8) {
		row[i] = { (first_Field.top - i) * hField, (first_Field.bottom - i) * hField };
		++i;
	}
}


Fields::~Fields()
{
}
