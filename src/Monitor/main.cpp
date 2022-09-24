#include "processMonitor.h"
#include <Windows.h>

int main()
{
	vsnc::vdc::ProcessParam testProcess;
	testProcess.iNo = 1;
	testProcess.strProcessRunningPath = "D:/Code/qt/Btest/debug/Btest.exe";
	testProcess.strProcessName = "Btest.exe";
	
	vsnc::vdc::MonitorParams param;
	param.iScanningJudgmentNumber = 3;
	param.iScanningTime = 1;
	param.lstProcessParams.push_back(testProcess);
	vsnc::vdc::ProcessMonitor monitor(param);
	std::cout << "start" << std::endl;
	monitor.RunProcessMonitor();
	std::cout << "wait over" << std::endl;
	monitor.StopAllProcess();
	std::cout << "end" << std::endl;
	return 0;
}