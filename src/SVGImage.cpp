// Project: geostuff
// File: SVGImage.cpp
//
#include "SVGImage.hpp"

SVGImage::SVGImage(double dWidth_mm, double dHeight_mm,
	double dXMin, double dXMax,
	double dYMin, double dYMax)
:m_dCurrentPositionX(0), m_dCurrentPositionY(0),
m_dWidth_mm(dWidth_mm), m_dHeight_mm(dHeight_mm),
m_dXMin(dXMin), m_dXMax(dXMax),
m_dYMin(dYMin), m_dYMax(dYMax)
{
}

SVGImage::~SVGImage()
{
	// Nothing to do
}

void SVGImage::WriteToFile(std::string strFilename)
{
	std::vector<std::string> rgHeader = CreateHeaderLines();
	std::vector<std::string> rgFooter = CreateFooterLines();
	FILE *fp= fopen(strFilename.c_str(), "w");
	if (fp)
	{
		for (auto line : rgHeader)
		{
			fprintf(fp, "%s\n", line.c_str());
		}

		for (auto line : m_rgLines)
		{
			fprintf(fp, "%s\n", line.c_str());
		}

		for (auto line : rgFooter)
		{
			fprintf(fp, "%s\n", line.c_str());
		}

		fclose(fp);
	}
}

void SVGImage::WriteToVectorOfStrings(std::vector<std::string> &refrgLines) // Mainly intended for implementing Unit Tests
{
	std::vector<std::string> rgHeader = CreateHeaderLines();
	std::vector<std::string> rgFooter = CreateFooterLines();

	for (auto line : rgHeader)
	{
		refrgLines.push_back(line);
	}

	for (auto line : m_rgLines)
	{
		refrgLines.push_back(line);
	}

	for (auto line : rgFooter)
	{
		refrgLines.push_back(line);
	}
}

std::vector<std::string> SVGImage::CreateHeaderLines()
{
	std::vector<std::string> rgErg;

	rgErg.push_back("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	rgErg.push_back("<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" version=\"1.1\" baseProfile=\"full\"");

	char buf[300] = { 0 };
	sprintf(buf, 
		"width=\"%lfmm\" height=\"%lfmm\" viewBox=\"%lf %lf %lf %lf\"", 
		m_dWidth_mm, m_dHeight_mm, 
		0, 0,
		m_dWidth_mm, m_dHeight_mm
		);
	std::string strFragment = buf;

	//  width = "800mm" height = "600mm" viewBox = "-400 -300 800 600" >

	rgErg.push_back(strFragment);
	rgErg.push_back(">");

	return rgErg;
}

std::vector<std::string> SVGImage::CreateFooterLines()
{
	std::vector<std::string> rgErg;

	rgErg.push_back("</svg>");

	return rgErg;
}

void SVGImage::MoveTo(double dX, double dY) // Moves virtual Cursor
{
	m_dCurrentPositionX = dX;
	m_dCurrentPositionY = dY;;
}

void SVGImage::LineTo(double dX, double dY) // Adds a Line to the SVG contents and moves the virtual cursor
{
	// tbd m_rgLines
	m_dCurrentPositionX = dX;
	m_dCurrentPositionY = dY;
}

void SVGImage::DiskAt(double dX, double dY, std::string strColor) // Adds a Circle/disk/dot to the contents and moves the virtual cursor
{
	double px = ((dX- m_dXMin)/(m_dXMax-m_dXMin)) * m_dWidth_mm;
	double py = m_dHeight_mm - ((dY - m_dYMin) / (m_dYMax - m_dYMin)) * m_dHeight_mm;
	// tbd m_rgLines

	char buf[200] = { 0 };
	sprintf(buf, "<circle cx=\"%lf\" cy=\"%lf\" r=\"0.02\" fill=\"%s\"/>", px, py, strColor.c_str());
	std::string strLine = buf;
	m_rgLines.push_back(strLine);

	m_dCurrentPositionX = dX;
	m_dCurrentPositionY = dY;
}

void SVGImage::TextAt(double dX, double dY, std::string strText) // Adds a Label to the contents and moves the virtual cursor
{
	double px = ((dX - m_dXMin) / (m_dXMax - m_dXMin)) * m_dWidth_mm;
	double py = m_dHeight_mm - ((dY - m_dYMin) / (m_dYMax - m_dYMin)) * m_dHeight_mm;

	char buf[200] = { 0 };
	sprintf(buf, "<text x=\"%lf\" y=\"%lf\" text-anchor=\"middle\" fill=\"black\" style=\"font-size:5\">%s</text>", px, py, strText.c_str());
	std::string strLine = buf;
	m_rgLines.push_back(strLine);

	m_dCurrentPositionX = dX;
	m_dCurrentPositionY = dY;
}
