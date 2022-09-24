#include "processMonitor.h"
#include <Windows.h>

int main()
{
	vsnc::vdc::ProcessMonitor monitor;
	std::cout << "start" << std::endl;
	std::list<vsnc::vdc::ProcessParam> lstProcessParams;
	vsnc::vdc::ProcessParam testProcess;
	testProcess.iNo = 1;
	testProcess.strProcessRunningPath = "D:/Code/qt/Btest/debug/Btest.exe";
	testProcess.strProcessName = "Btest.exe";
	lstProcessParams.push_back(testProcess);
	monitor.Init(lstProcessParams);
	monitor.RunProcessMonitor();
	std::cout << "wait over" << std::endl;
	monitor.StopAllProcess();
	std::cout << "end" << std::endl;
	return 0;
}