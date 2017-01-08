/**
* LICENSE PLACEHOLDER
*
* @file mbn_reader.cpp
* @class OpenPST::QC::MbnHeader
* @package OpenPST
* @brief Reads and parses various MBN information from a binary on disk
*
* @author Gassan Idriss <ghassani@gmail.com>
*/

#include "qualcomm/mbn_reader.h"

using namespace OpenPST::QC;


MbnReader::MbnReader(std::string filePath) : filePath(filePath)
{
	std::stringstream ss;
	std::ifstream file(filePath.c_str(), std::ios::in | std::ios::binary);
				

	if (!file.is_open()) {
		ss << "Could Not Open File " << filePath;
		throw std::invalid_argument(ss.str());
	}

	file.seekg(0, file.end);
	fileSize = (size_t)file.tellg();
	file.seekg(0, file.beg);

	if (fileSize < sizeof(header.header80)) {
		ss << "Invalid File Type. File is smaller than header. " << filePath;
		throw std::invalid_argument(ss.str());
	}

	file.read(reinterpret_cast<char*>(&header.header80), sizeof(header.header80));

	header.is80byte = header.header80.magic == MBN_EIGHTY_BYTE_MAGIC;
	
	file.close();
}

MbnReader::~MbnReader()
{

}

const MbnHeader& MbnReader::getHeader()
{
	return header;
}

int MbnReader::getHeaderSize()
{
	return header.is80byte ? 
		sizeof(MbnHeader80byte) : sizeof(MbnHeader40byte);
}