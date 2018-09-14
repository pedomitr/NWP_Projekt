#pragma once
struct Field
{
	POINT position;
	bool color;
	int  pieceID;
	
public:
	Field(POINT position, bool color, int pieceID);
	~Field();
};

