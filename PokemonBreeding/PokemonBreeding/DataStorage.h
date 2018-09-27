#pragma once
#include <string>
#include <xmllite.h>

typedef struct parent parent;
typedef struct pokemon pokemon;

class DataStorage
{
public:
	DataStorage();
	~DataStorage();

private:
	std::string file;

	IStream* pFileStream;
	IXmlReader* pReader;
};

