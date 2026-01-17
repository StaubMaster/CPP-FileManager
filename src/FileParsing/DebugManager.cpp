#include "FileParsing/DebugManager.hpp"

#include <iostream>



DebugManager::LogChange::LogChange(char data) :
	Data(data)
{ }
bool DebugManager::LogChange::operator==(const LogChange & other) const
{
	return (Data == other.Data);
}



DebugManager::LogChange DebugManager::Tabs('\t');
DebugManager::LogChange DebugManager::TabInc('\x0e');	//	Shift In	-->
DebugManager::LogChange DebugManager::TabDec('\x0f');	//	Shift Out	<--
static unsigned int TabsCount = 0;
static std::string TabsString(TabsCount, ' ');



static std::ostream StreamDump(0);
std::ostream * DebugManager::Console = &StreamDump;



void DebugManager::ChangeConsoleToDump()
{
	Console = &StreamDump;
}
void DebugManager::ChangeConsoleToCOut()
{
	Console = &std::cout;
}



std::ostream & operator<<(std::ostream & log, DebugManager::LogChange & type)
{
	if (type == DebugManager::TabInc) { TabsCount += 2; TabsString = std::string(TabsCount, ' '); }
	if (type == DebugManager::TabDec) { TabsCount -= 2; TabsString = std::string(TabsCount, ' '); }
	if (type == DebugManager::Tabs) { log << TabsString; }
	return log;
}
