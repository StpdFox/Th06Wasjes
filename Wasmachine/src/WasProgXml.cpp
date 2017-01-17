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
		if(e == 0) initXML();
	}
}

void WasProgXml::saveXML()
{
	m_doc.save_file(m_filename.c_str());
}

void WasProgXml::addNewWashProgram(const WasProgram &wp)
{
	++m_currentNumberOfWashPrograms;
	m_rootNode.attribute("N") = m_currentNumberOfWashPrograms;
	Node newWashingNode = m_rootNode.append_child("Washing");

	Node newFlushNode = newWashingNode.append_child("Flush");
	newFlushNode.append_attribute("Time") = wp.timeSpoelen;

	Node newWashNode = newWashingNode.append_child("Wash");
	newWashNode.append_attribute("Time") = wp.timeWassing;
	newWashNode.append_attribute("Temperature") = wp.temp;

	Node newSpinNode = newWashingNode.append_child("Spin");
	newSpinNode.append_attribute("Time") = wp.timecentrifugeren;
	newSpinNode.append_attribute("RPM") = wp.RPM;
	saveXML();
}

std::vector<WasProgram> WasProgXml::getWashingPrograms() const
{
	return m_wasPrograms;
}

void WasProgXml::loadXML()
{
	m_doc.load_file(m_filename.c_str());
	if(m_doc.empty()) throw (uint(0));

	m_rootNode = m_doc.root().child("WashingPrograms");
	if(m_rootNode.empty())
	{
		throw (uint(0));
	}

	m_currentNumberOfWashPrograms = m_rootNode.attribute("N").as_uint();

	for(Node &currentNode : m_rootNode.children())
	{
		WasProgram wp;
		Node flushNode = currentNode.child("Flush");
		Node washNode = currentNode.child("Wash");
		Node spinNode = currentNode.child("Spin");

		if(flushNode.empty() || washNode.empty() || spinNode.empty())
		{
			deleteWashProgram(currentNode);
			throw (uint(1));
		}

		Attribute flushTime = flushNode.attribute("Time");
		Attribute washTime = washNode.attribute("Time");
		Attribute washTemp = washNode.attribute("Temperature");
		Attribute spinTime = spinNode.attribute("Time");
		Attribute RPM = spinNode.attribute("RPM");

		if(flushTime.empty() || washTime.empty() || washTemp.empty() || spinTime.empty() || RPM.empty())
		{
			deleteWashProgram(currentNode);
			throw (uint(1));
		}

		wp.timeSpoelen = flushTime.as_uint();
		wp.timeWassing = washTime.as_uint();
		wp.temp = washTemp.as_uint();
		wp.timecentrifugeren = spinTime.as_uint();
		wp.RPM = RPM.as_uint();

		m_wasPrograms.push_back(wp);
	}
}

void WasProgXml::deleteWashProgram(const Node &node)
{
	m_rootNode.remove_child(node);
	--m_currentNumberOfWashPrograms;
}

void WasProgXml::deleteWashProgram(const WasProgram &wp)
{
	for(Node &currentNode : m_rootNode.children())
	{
		Node flushNode = currentNode.child("Flush");
		Node washNode = currentNode.child("Wash");
		Node spinNode = currentNode.child("Spin");

		Attribute flushTime = flushNode.attribute("Time");
		Attribute washTime = washNode.attribute("Time");
		Attribute washTemp = washNode.attribute("Temperature");
		Attribute spinTime = spinNode.attribute("Time");
		Attribute RPM = spinNode.attribute("RPM");

		if(wp.timeSpoelen == flushTime.as_uint() && wp.timeWassing == washTime.as_uint() && wp.temp == washTemp.as_uint() &&
		   wp.timecentrifugeren == spinTime.as_uint() && wp.RPM == RPM.as_uint())
		{
			deleteWashProgram(currentNode);
			saveXML();
			break;
		}
	}
}

void WasProgXml::initXML()
{
	m_rootNode = m_doc.append_child("WashingPrograms");
	m_rootNode.append_attribute("N") = 0;
	saveXML();
}

























