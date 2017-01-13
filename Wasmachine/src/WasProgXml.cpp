/*
 * WasProgXml.cpp
 *
 *  Created on: Jan 13, 2017
 *      Author: hendrik
 */

#include <iostream>

#include "WasProgXml.h"

#define Attribute pugi::xml_attribute

WasProgXml::WasProgXml()
{
	try
	{
		std::cout << "loading" << std::endl;
		loadXML();
		std::cout << "done loading" << std::endl;
		for(WasProgram wp : m_wasPrograms)
		{
			std::cout << "times: " << wp.timeSpoelen << ", " << wp.timeWassing << ", " << wp.timecentrifugeren << std::endl;
			std::cout << "temp: " << wp.temp << std::endl;
			std::cout << "rpm: " << wp.RPM << std::endl;
		}
	}
	catch (uint e)
	{
		std::cout << "e: " << e << std::endl;
		if(e == -1) initXML();
		else		deleteWashProgram(e);
	}
}

void WasProgXml::setNewWashingProgram(const WasProgram &wp)
{
	Node washingPrograms = m_doc.root().child("WashingPrograms");

}

std::vector<WasProgram> WasProgXml::getWashingPrograms() const
{
	return m_wasPrograms;
}

void WasProgXml::loadXML()
{
	m_doc.load_file(m_filename.c_str());
	if(m_doc.empty()) throw -1;

	m_rootNode = m_doc.root().child("WashingPrograms");
	if(m_rootNode.empty())
	{
		throw -1;
	}

	m_currentNumberOfWashPrograms = m_rootNode.attribute("N").as_uint();

	uint index = 0;
	for(Node &currentNode : m_rootNode.children())
	{
		WasProgram wp;
		Node flushNode = currentNode.child("Flush");
		Node washNode = currentNode.child("Wash");
		Node spinNode = currentNode.child("Spin");

		if(flushNode.empty() || washNode.empty() || spinNode.empty()) throw index;

		Attribute flushTime = flushNode.attribute("Time");
		Attribute washTime = washNode.attribute("Time");
		Attribute washTemp = washNode.attribute("Temperature");
		Attribute spinTime = spinNode.attribute("Time");
		Attribute RPM = spinNode.attribute("RPM");

		if(flushTime.empty() || washTime.empty() || washTemp.empty() || spinTime.empty() || RPM.empty()) throw index;

		wp.timeSpoelen = flushTime.as_uint();
		wp.timeWassing = washTime.as_uint();
		wp.temp = washTemp.as_uint();
		wp.timecentrifugeren = spinTime.as_uint();
		wp.RPM = RPM.as_uint();

		m_wasPrograms.push_back(wp);
	}

//	for(uint i = 0; i < m_currentNumberOfWashPrograms; ++i)
//	{
//		WasProgram wp;
//		Node washing = m_rootNode.children()
//	}
}

void WasProgXml::deleteWashProgram(const uint index)
{

}

void WasProgXml::initXML()
{

}

























