#include "pid_lib.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  PIDLib_Init(PID_HandlerType *PIDx, PID_HandlerType pidx)
{
	return PID_Init(PIDx, pidx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
float	 PIDLib_PosCalc(PID_HandlerType *PIDx, float setVal)
{
	return PID_PosCalc(PIDx, setVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
float	 PIDLib_IncCalc(PID_HandlerType *PIDx, float setVal)
{
	return PID_IncCalc(PIDx, setVal);
}