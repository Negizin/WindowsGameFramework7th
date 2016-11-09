#include	"Binary.h"
#include <fstream>

Binary::Binary() :
	m_bin(nullptr),
	m_size(0) {

};

Binary::Binary(const Binary& bin) {
	*this = bin;
}

Binary::Binary(tstring filename) {
	Load(filename);
}

Binary::~Binary() {
	SafeDelete(m_bin);
	m_size = 0;
}

bool Binary::Load(tstring fileName) {
	UnLoad();

	std::ifstream ifs(fileName, std::ifstream::in | std::ifstream::binary);

	if (ifs.fail()) {
		//DebugLog("Load Fail \n\t %s\n", fileName.c_str());
		return false;
	}
	int begin = static_cast<int>(ifs.tellg());
	ifs.seekg(0, ifs.end);

	int end = static_cast<int>(ifs.tellg());
	m_size = (end - begin);
	ifs.clear();
	ifs.seekg(0, ifs.beg);
	m_bin = new unsigned char[m_size];
	//m_bin[m_size - 1] = '\0';  
	ifs.read((char*) m_bin, m_size);

	return true;
}

void Binary::UnLoad() {
	SafeDelete(m_bin);
}
unsigned char* Binary::GetBinary()const {
	return m_bin;
}
int	Binary::GetSize()const {
	return m_size;
}

Binary Binary::operator=(const Binary& bin) {
	m_size = bin.GetSize();
	if (m_size > 0) {
		m_bin = new unsigned char[m_size];
		memcpy_s(&m_bin, m_size, bin.GetBinary(), m_size);
	}
	else
		m_bin = nullptr;

	return *this;
}

