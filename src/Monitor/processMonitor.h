#ifndef __PROCESS_MONITOR_H__
#define __PROCESS_MONITOR_H__

#include <iostream>
#include <list>
#include <mutex>
namespace vsnc
{
	namespace vdc
	{
		enum class Status
		{
			VSNC_PROCESS_NONE,
			VSNC_PROCESS_RUNNING,
			VSNC_PROCESS_SLEEP,
			VSNC_PROCESS_ZOMBIE,
			VSNC_PROCESS_EXIT,
		};

		struct ProcessParam
		{
			int iNo;
			int iPid;
			int iRestartTime;
			int iScanningJudgmentNumber;
			std::string strProcessName;
			std::string strProcessRunningPath;
			std::string strProcessArg;

			ProcessParam()
			{
				iNo                     = 0;
				iPid                    = 0;
				iRestartTime            = 0;
				iScanningJudgmentNumber = 0;
				strProcessName          = "";
				strProcessRunningPath   = "";
				strProcessArg           = "";
			}
		};

		class ProcessMonitor
		{
		public:
			ProcessMonitor() :m_bIsRunning(true),
				m_iScanningJudgmentNumber(0),
				m_iScanningTime(0) {}
			~ProcessMonitor() {}

			void Init(std::list<ProcessParam>& lstProcessParams);
			int RunProcessMonitor();
			void StopProcessMonitor();
			void StopAllProcess();
		private:
			void FreeResource();
			int  GetProcessPids(std::string strProcessName);
			void RerunningProcess(std::string strProgramRunPath, std::string strProgramArg);

			void MySleep(uint16_t sec);
			bool GetIsRunning();
			bool KillProcessById(int id);

		private:
			bool m_bIsRunning;
			int  m_iScanningTime;
			int  m_iScanningJudgmentNumber;
			std::list<ProcessParam> m_lstProcessParams;
		};
	}
}

#endif // !__PROCESS_MONITOR_H__