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


void ReadSVGFilesAndWriteThemToOneSVGFile(const std::string strResultSVGFile, const std::vector<std::string>& refrgInputFilenames)
{
	SVGImage svgCombiniedImage;

	for (auto fn : refrgInputFilenames)
	{
		SVGImage svgNextImage;
		svgNextImage.ReadFromFile(fn);
		svgCombiniedImage.AddSVG(svgNextImage);
	}

	svgCombiniedImage.WriteToFile(strResultSVGFile);

}

int main(int argc, const char** argv)
{
	int nRet = 0;

	if (argc>=2)
	{
		std::string strResultSVGFile = argv[1];
		std::vector<std::string> rgInputFilenames;
		for (size_t i = 2; i < argc; i++)
		{
			std::string strInputFilename = argv[i];
			rgInputFilenames.push_back(strInputFilename);
		}
		ReadSVGFilesAndWriteThemToOneSVGFile(strResultSVGFile, rgInputFilenames);
	}
	else
	{
		std::cout << "Usage: svgfromtstackofsvgs <TargetSVGFile> {<InputSVGFile>}" << std::endl;
		nRet = 1;
	}

	return nRet;
}


