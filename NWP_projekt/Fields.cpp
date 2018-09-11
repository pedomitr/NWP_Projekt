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


POINT GetFieldPosition(POINT point, Fields* fields)
{
	POINT field_position;
	for (int i = 0; i < 8; ++i)
	{
		if (point.x >= fields->column[i].x && point.x <= fields->column[i].y)
			field_position.x = i;
	}
	for (int i = 0; i < 8; ++i)
	{
		if (point.y >= fields->row[i].x && point.y <= fields->row[i].y)
			field_position.y = i;
	}
}


TCHAR* GetFieldName(POINT field_position) 
{
	TCHAR* name;
	switch (field_position.x) {
	case 0:
		name = _T("a");
		break;
	case 1:
		name = _T("b");
		break;
	case 2:
		name = _T("c");	
		break;
	case 3:
		name = _T("d");
		break;
	case 4:
		name = _T("e");
		break;
	case 5:
		name = _T("f");
		break;
	case 6:
		name = _T("g");
		break;
	case 7:
		name = _T("h");
	}
	
	switch (field_position.y) {
	case 0:
		name += '1';
		break;
	case 1:
		name += '2';
		break;
	case 2:
		name += '3';
		break;
	case 3:
		name += '4';
		break;
	case 4:
		name += '5';
		break;
	case 5:
		name += '6';
		break;
	case 6:
		name += '7';
		break;
	case 7:
		name += '8';
	}
	return name;
}

