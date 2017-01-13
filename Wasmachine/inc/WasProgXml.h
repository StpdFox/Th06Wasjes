/*
 * WasProgXml.h
 *
 *  Created on: Jan 13, 2017
 *      Author: hendrik
 */

#ifndef INC_WASPROGXML_H_
#define INC_WASPROGXML_H_

#include <string>
#include <vector>
#include <sys/types.h>

#include "WasProgram.h"
#include "pugixml.hpp"

#define Node pugi::xml_node

class WasProgXml
{
private:
	std::string m_filename = "WassingPrograms.xml";
	pugi::xml_document m_doc;
	std::vector<WasProgram> m_wasPrograms;
	uint m_currentNumberOfWashPrograms = 0;
	pugi::xml_node m_rootNode;

	void loadXML();
	void initXML();
	void deleteWashProgram(const uint index);
public:
	WasProgXml();
	void setNewWashingProgram(const WasProgram &wp);
	std::vector<WasProgram> getWashingPrograms() const;
};



#endif /* INC_WASPROGXML_H_ */
