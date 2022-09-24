#include "processMonitor.h"
#include <windows.h>
#include <Tlhelp32.h>

int vsnc::vdc::ProcessMonitor::RunProcessMonitor()
{
	// 检测是否有监控的程序，如果没有直接返回
	if (m_lstProcessParams.empty())
	{
		std::cout << "No Programs are added that need to be monitored,please add!";
		return -1;
	}
	size_t num = 0;
	while (true)
	{
		for (auto& processParam : m_lstProcessParams)
		{
			// 上一次检测为退出状态
			if (processParam.iPid == 0)
			{
				auto pid = GetProcessPids(processParam.strProcessName);
				if (pid == 0) //本次检测为退出状态
				{

					if (processParam.iScanningJudgmentNumber == 0) //初始未运行
					{

						RerunningProcess(processParam.strProcessRunningPath, processParam.strProcessArg);
						processParam.iPid = GetProcessPids(processParam.strProcessName);
						processParam.iScanningJudgmentNumber = 0;
						processParam.iRestartTime = 0;
						std::cout << "start exe: " << processParam.strProcessName << " path: " << processParam.strProcessRunningPath << std::endl;
					}
					else if (processParam.iScanningJudgmentNumber++ > m_iScanningJudgmentNumber) //异常退出，等待重启
					{
						RerunningProcess(processParam.strProcessRunningPath, processParam.strProcessArg);
						processParam.iPid = GetProcessPids(processParam.strProcessName);
						processParam.iScanningJudgmentNumber = m_iScanningJudgmentNumber;
						std::cout << "processParam.iScanningJudgmentNumber" << processParam.iScanningJudgmentNumber << std::endl;
						processParam.iRestartTime++;
						std::cout << "restart exe: " << processParam.strProcessName << " path: " << processParam.strProcessRunningPath << std::endl;
					}
				}
				else if (pid > 0) //本次检测为运行状态
				{
					processParam.iPid = pid;
					processParam.iRestartTime++;
					processParam.iScanningJudgmentNumber = 0;
					if (processParam.iScanningJudgmentNumber > 0 && processParam.iScanningJudgmentNumber > m_iScanningJudgmentNumber)
					{
						std::cout << "restart exe: " << processParam.strProcessName << " time , While waiting for the process to have started." << std::endl;
					}
				}
			}
			else if (processParam.iPid > 0)
			{
				auto pid = GetProcessPids(processParam.strProcessName);
				if (pid == 0)
				{
					processParam.iPid = 0;
					processParam.iScanningJudgmentNumber = 1;
					std::cout << "exe: " << processParam.strProcessName << "exception exit" << std::endl;
				}
			}
		}
		Sleep(m_iScanningTime*1000);
		std::cout << num++ << std::endl;
		/*if (num > 30)
		{
			break;
		}*/
	}

	
}

void vsnc::vdc::ProcessMonitor::StopProcessMonitor()
{
	m_bIsRunning = false;
}

void vsnc::vdc::ProcessMonitor::StopAllProcess()
{
	for (auto& processParam : m_lstProcessParams)
	{
		auto pid = GetProcessPids(processParam.strProcessName);
		if (pid != 0)
		{
			bool isExit = KillProcessById(pid);
			if (isExit)
			{
				std::cout << "exit success"<<std::endl;
			}
			else
			{
				std::cout << "exit fail" << std::endl;
			}
		}
		processParam.iScanningJudgmentNumber = 0;
	}
}

void vsnc::vdc::ProcessMonitor::FreeResource()
{
	m_lstProcessParams.clear();
}

int vsnc::vdc::ProcessMonitor::GetProcessPids(std::string strProcessName)
{
	int id = 0;
	PROCESSENTRY32 pe;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	pe.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hSnapshot, &pe)) return 0;
	while (true)
	{
		pe.dwSize = sizeof(PROCESSENTRY32);
		if (Process32Next(hSnapshot, &pe) == FALSE) break;
		char str[MAX_PATH] = { 0 };
		wcstombs(str, pe.szExeFile, MAX_PATH);
		if (strProcessName.compare(str) == 0)
		{
			id = pe.th32ProcessID;
			break;
		}
	}
	CloseHandle(hSnapshot);
	return id;
}

void vsnc::vdc::ProcessMonitor::RerunningProcess(std::string strProgramRunPath, std::string strProgramArg)
{

	wchar_t lStr[MAX_PATH] = { 0 };
	MultiByteToWideChar(CP_ACP, 0, strProgramRunPath.c_str(), static_cast<int>(strProgramRunPath.length()), lStr, static_cast<int>(strProgramRunPath.length() * 2));
	ShellExecute(NULL, L"open", lStr, NULL, NULL, SW_SHOW);
}

void vsnc::vdc::ProcessMonitor::MySleep(uint16_t sec)
{
}

bool vsnc::vdc::ProcessMonitor::GetIsRunning()
{
	return false;
}

bool vsnc::vdc::ProcessMonitor::KillProcessById(int id)
{

	HANDLE hWnd = OpenProcess(PROCESS_TERMINATE | SYNCHRONIZE, 0, id);
	if (hWnd)
	{
		if (TerminateProcess(hWnd, 0)) return true;
	}
	return false;
}
