#ifndef __PROCESS_MONITOR_H__
#define __PROCESS_MONITOR_H__

#include <list>
#include <mutex>

#include "structer.h"
namespace vsnc
{
	namespace vdc
	{
		
		struct MonitorParams
		{
			int iScanningJudgmentNumber;
			int iScanningTime;
			std::list<ProcessParam> lstProcessParams;

		};

		class ProcessMonitor
		{
		public:
			ProcessMonitor(MonitorParams param) :m_bIsRunning(true),
				m_iScanningJudgmentNumber(param.iScanningJudgmentNumber),
				m_iScanningTime(param.iScanningTime),
				m_lstProcessParams(param.lstProcessParams){}
			~ProcessMonitor() {}

			int  RunProcessMonitor();
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
