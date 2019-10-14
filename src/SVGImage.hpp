// Project: geostuff
// File: SVGImage.hpp
//
// Simple SVG Image class. Allows creation, lines and dots, but not much more. Intended for output
//
#ifndef __GEOSTUFF_SVGIMAGE_HPP__
#define __GEOSTUFF_SVGIMAGE_HPP__

#include <string>
#include <vector>

class SVGImage
{
public:
	SVGImage(
		double dWidth_mm=297.0, double dHeight_mm=210.0, // DIN A4 Quer
		double dXMin=6.8976, double dXMax=7.7120, // Ruhrgebiet: Hagen..Recklinghausen
		double dYMin=51.3473, double dYMax=51.6461); // Ruhrgebiet: Duisburg..Unna
	virtual ~SVGImage();

	virtual void WriteToFile(std::string strFilename);
	virtual void WriteToVectorOfStrings(std::vector<std::string> &refrgLines); // Mainly intended for implementing Unit Tests

	virtual void MoveTo(double dX, double dY); // Moves virtual Cursor
	virtual void LineTo(double dX, double dY); // Adds a Line to the SVG contents and moves the virtual cursor
	virtual void DiskAt(double dX, double dY, std::string strColor="black"); // Adds a Circle/disk/dot to the contents and moves the virtual cursor
private:
	virtual std::vector<std::string> CreateHeaderLines();
	virtual std::vector<std::string> CreateFooterLines();
	double m_dCurrentPositionX;
	double m_dCurrentPositionY;
	// Data Model:
	double m_dWidth_mm;
	double m_dHeight_mm;
	double m_dXMin; 
	double m_dXMax;
	double m_dYMin;
	double m_dYMax;
	std::vector<std::string> m_rgLines;
};
#endif
