#ifndef __VSNC_STRUCTER_H_
#define __VSNC_STRUCTER_H_
#include <iostream>

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
				iNo = 0;
				iPid = 0;
				iRestartTime = 0;
				iScanningJudgmentNumber = 0;
				strProcessName = "";
				strProcessRunningPath = "";
				strProcessArg = "";
			}
		};
	}
}




#endif // !__VSNC_STRUCTER_H_

