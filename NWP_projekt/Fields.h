#pragma once
class Fields
{
public:
	POINT column[8];
	POINT row[8];
	POINT field_position;
	TCHAR* field_name;
	Fields(RECT first_Field, int hField);
	~Fields();
	POINT GetFieldPosition(POINT point, Fields* fields);
	CString GetFieldName(POINT field_position);
	RECT GetField(POINT field_position, RECT firstField);
};

