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

//Vraća redak i stupac odabranog polja na ploči
POINT Fields::GetFieldPosition(POINT point, Fields* fields)
{
	POINT field_position = { 0 };

	for (int i = 0; i < 8; ++i)
	{
		if (point.x >= fields->column[i].x && point.x < fields->column[i].y)
		{
			field_position.x = i;
			break;
		}
	}
	for (int i = 0; i < 8; ++i)
	{
		if (point.y > fields->row[i].x && point.y <= fields->row[i].y)
		{
			field_position.y = i;
			break;
		}
	}
	return field_position;
}


void Fields::GetFieldName(POINT field_position, TCHAR* pname) 
{
	TCHAR name[4] = _T("");
	switch (field_position.x) {
	case 0:
		_tcscat_s(name, 2, _T("a"));
		break;
	case 1:
		_tcscat_s(name, 2, _T("b"));
		break;
	case 2:
		_tcscat_s(name, 2, _T("c"));
		break;
	case 3:
		_tcscat_s(name, 2, _T("d"));
		break;
	case 4:
		_tcscat_s(name, 2, _T("e"));
		break;
	case 5:
		_tcscat_s(name, 2, _T("f"));
		break;
	case 6:
		_tcscat_s(name, 2, _T("g"));
		break;
	case 7:
		_tcscat_s(name, 2, _T("h"));
	}
	
	switch (field_position.y) {
	case 0:
		_tcscat_s(name, 4, _T("1"));
		break;
	case 1:
		_tcscat_s(name, 4, _T("2"));
		break;
	case 2:
		_tcscat_s(name, 4, _T("3"));
		break;
	case 3:
		_tcscat_s(name, 4, _T("4"));
		break;
	case 4:
		_tcscat_s(name, 4, _T("5"));
		break;
	case 5:
		_tcscat_s(name, 4, _T("6"));
		break;
	case 6:
		_tcscat_s(name, 4, _T("7"));
		break;
	case 7:
		_tcscat_s(name, 4, _T("8"));
	}
	pname = name;
}

//Vraæa RECT odreðenog polja sa ploèe
RECT Fields::GetField(POINT field_position, RECT firstField)
{
	RECT rc = { 0,0,0,0 };
	if (field_position.x > 7 && field_position.y > 7) return rc;
	rc = { firstField.left + field_position.x, firstField.top - field_position.y, 
		firstField.right + field_position.x, firstField.bottom - field_position.y};
	return rc;
}

