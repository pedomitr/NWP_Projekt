#include "stdafx.h"
#include "LoadPng.h"

LoadPng::LoadPng()
{

}


LoadPng::~LoadPng()
{

}

HRESULT LoadPng::LoadPI(CImage pngImage, CString pngPath)
{
	return pngImage.Load(pngPath);
}
