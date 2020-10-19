// File: svgfromstackofsvgs.cpp
//
// Takes multiple svg files and combines them into one
// 

#include "../SVGImage.hpp"

#include <vector>
#include <string>
#include <iostream>

bool ParseCommandLine(std::string &refstrFilename1, std::string& refstrFilename2, std::string& refstrFilename3, int argc, const char**argv)
{
	bool bOk = argc == 4;
	if (bOk)
	{
		refstrFilename1 = argv[1];
		refstrFilename2 = argv[2];
		refstrFilename3 = argv[3];
	}

	return bOk;
}

void ReadTwoSVGFilesAndWriteThemToOneSVGFile(const std::string strResultSVGFile, const std::string strInputSVGFilename1, const std::string strInputSVGFilename2)
{
	SVGImage svg1;
	svg1.ReadFromFile(strInputSVGFilename1);

	SVGImage svg2;
	svg2.ReadFromFile(strInputSVGFilename2);

	svg1.AddSVG(svg2);
	svg1.WriteToFile(strResultSVGFile);
}


int main(int argc, const char** argv)
{
	int nRet = 0;

	std::string strResultSVGFile;
	std::string strInputSVGFilename1;
	std::string strInputSVGFilename2;

	bool bParsedProperly = ParseCommandLine(strResultSVGFile, strInputSVGFilename1, strInputSVGFilename2, argc, argv);

	if (bParsedProperly)
	{
		ReadTwoSVGFilesAndWriteThemToOneSVGFile(strResultSVGFile, strInputSVGFilename1, strInputSVGFilename2);
	}
	else
	{
		std::cout << "Usage: svgfromtstackofsvgs <TargetSVGFile> <InputSVGFile1> <InputSVGFile2>" << std::endl;
		nRet = 1;
	}

	return nRet;
}


