#pragma once
static class LoadPng
{
public:
	LoadPng();
	~LoadPng();
	HRESULT LoadPI(CImage pngImage, CString pngPath);
};

