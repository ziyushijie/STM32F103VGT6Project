#include "spi_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明： SPI的主机模式的查询方式初始化
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MHW_PollMode_Init(SPI_HandlerType *SPIx, LL_SPI_InitTypeDef SPI_InitStruct)
{
	//---恢复当前配置为初始值
	LL_SPI_DeInit(SPIx->msgSPIx);

	//---使能SPI的时钟线
	SPI_Clock(SPIx, 1);

	//---SPI初始化
	LL_SPI_Init(SPIx->msgSPIx, &(SPI_InitStruct));
	#ifndef USE_MCU_STM32F1

	//---SPI1的标准协议的支持
	LL_SPI_SetStandard(SPIx->msgSPIx, SPIx->msgStandard);
	#endif

	//---使能SPI
	LL_SPI_Enable(SPIx->msgSPIx);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 设置是高位在在前还是低位在前
//////////////////////////////////////////////////////////////////////////////
void SPI_MHW_SetTransferBitOrder(SPI_HandlerType *SPIx, UINT32_T BitOrder)
{
	LL_SPI_SetTransferBitOrder(SPIx->msgSPIx, BitOrder);
}



///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 端口初始化
//////输入参数:
//////输出参数:
//////说		明： 硬件SPI资源时的GPIO端口初始化
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MHW_GPIO_Init(SPI_HandlerType *SPIx)
{
	//---端口时钟的配置
	GPIOTask_Clock(SPIx->msgCS.msgGPIOPort, 1);
	GPIOTask_Clock(SPIx->msgSCK.msgGPIOPort, 1);
	GPIOTask_Clock(SPIx->msgMOSI.msgGPIOPort, 1);
	GPIOTask_Clock(SPIx->msgMISO.msgGPIOPort, 1);

	//---端口的配置
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---SS---设置为输出
	GPIO_InitStruct.Pin = SPIx->msgCS.msgGPIOBit;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = SPIx->msgGPIOAlternate;
	#endif
	LL_GPIO_Init(SPIx->msgCS.msgGPIOPort, &GPIO_InitStruct);

	//---SCK---设置为输出
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Pin = SPIx->msgSCK.msgGPIOBit;
	LL_GPIO_Init(SPIx->msgSCK.msgGPIOPort, &GPIO_InitStruct);

	//---MOSI---设置为输出
	GPIO_InitStruct.Pin = SPIx->msgMOSI.msgGPIOBit;
	LL_GPIO_Init(SPIx->msgMOSI.msgGPIOPort, &GPIO_InitStruct);

	//---MISO---设置为输入
	GPIO_InitStruct.Pin = SPIx->msgMISO.msgGPIOBit;
	LL_GPIO_Init(SPIx->msgMISO.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_1(SPIx->msgCS.msgGPIOPort, SPIx->msgCS.msgGPIOBit);
	GPIO_OUT_1(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit);
	GPIO_OUT_1(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	GPIO_OUT_1(SPIx->msgMISO.msgGPIOPort, SPIx->msgMISO.msgGPIOBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_GPIO_Init(SPI_HandlerType *SPIx)
{
	//---端口时钟的配置
	GPIOTask_Clock(SPIx->msgCS.msgGPIOPort, 1);
	GPIOTask_Clock(SPIx->msgSCK.msgGPIOPort, 1);
	GPIOTask_Clock(SPIx->msgMOSI.msgGPIOPort, 1);
	GPIOTask_Clock(SPIx->msgMISO.msgGPIOPort, 1);

	//---端口的配置
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---SS---设置为输出
	GPIO_InitStruct.Pin = SPIx->msgCS.msgGPIOBit;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	#endif
	LL_GPIO_Init(SPIx->msgCS.msgGPIOPort, &GPIO_InitStruct);

	//---SCK---设置为输出
	GPIO_InitStruct.Pin = SPIx->msgSCK.msgGPIOBit;
	LL_GPIO_Init(SPIx->msgSCK.msgGPIOPort, &GPIO_InitStruct);

	//---MOSI---设置为输出
	GPIO_InitStruct.Pin = SPIx->msgMOSI.msgGPIOBit;
	LL_GPIO_Init(SPIx->msgMOSI.msgGPIOPort, &GPIO_InitStruct);

	//---MISO---设置为输入
	GPIO_InitStruct.Pin = SPIx->msgMISO.msgGPIOBit;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	LL_GPIO_Init(SPIx->msgMISO.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_1(SPIx->msgCS.msgGPIOPort, SPIx->msgCS.msgGPIOBit);
	GPIO_OUT_1(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit);
	GPIO_OUT_1(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	GPIO_OUT_1(SPIx->msgMISO.msgGPIOPort, SPIx->msgMISO.msgGPIOBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_GPIO_DeInit(SPI_HandlerType *SPIx)
{
	//---端口的配置
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---SS---设置为输出
	GPIO_InitStruct.Pin = SPIx->msgCS.msgGPIOBit;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	#endif
	LL_GPIO_Init(SPIx->msgCS.msgGPIOPort, &GPIO_InitStruct);

	//---SCK---设置为输出
	GPIO_InitStruct.Pin = SPIx->msgSCK.msgGPIOBit;
	LL_GPIO_Init(SPIx->msgSCK.msgGPIOPort, &GPIO_InitStruct);

	//---MOSI---设置为输出
	GPIO_InitStruct.Pin = SPIx->msgMOSI.msgGPIOBit;
	LL_GPIO_Init(SPIx->msgMOSI.msgGPIOPort, &GPIO_InitStruct);

	//---MISO---设置为输入
	GPIO_InitStruct.Pin = SPIx->msgMISO.msgGPIOBit;
	LL_GPIO_Init(SPIx->msgMISO.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_1(SPIx->msgCS.msgGPIOPort, SPIx->msgCS.msgGPIOBit);
	GPIO_OUT_1(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit);
	GPIO_OUT_1(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	GPIO_OUT_1(SPIx->msgMISO.msgGPIOPort, SPIx->msgMISO.msgGPIOBit);
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_DeInit(SPI_HandlerType *SPIx)
{
	//---恢复当前配置为初始值
	LL_SPI_DeInit(SPIx->msgSPIx);

	//---不使能SPI的时钟线
	SPI_Clock(SPIx, 0);
	return SPI_GPIO_DeInit(SPIx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_Clock(SPI_HandlerType *SPIx, UINT8_T isEnable)
{
	//---选择SPI接口
	if (SPIx->msgSPIx == SPI1)
	{
		if (isEnable)
		{
			//---使能SPI的时钟线
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);
		}
		else
		{
			//---使能SPI的时钟线
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI1);
		}
	}
	else if (SPIx->msgSPIx == SPI2)
	{
		if (isEnable)
		{
			//---使能SPI的时钟线
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);
		}
		else
		{
			//---使能SPI的时钟线
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_SPI2);
		}
	}
	else if (SPIx->msgSPIx == SPI3)
	{
		if (isEnable)
		{
			//---使能SPI的时钟线
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI3);
		}
		else
		{
			//---使能SPI的时钟线
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_SPI3);
		}
	}
	#ifdef SPI4
	else if (SPIx->msgSPIx == SPI4)
	{
		if (isEnable)
		{
			//---使能SPI的时钟线
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI4);
		}
		else
		{
			//---使能SPI的时钟线
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI4);
		}
	}
	#endif
	#ifdef SPI5
	else if (SPIx->msgSPIx == SPI5)
	{
		if (isEnable)
		{
			//---使能SPI的时钟线
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI5);
		}
		else
		{
			//---使能SPI的时钟线
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI5);
		}
	}
	#endif
	#ifdef SPI6
	else if (SPIx->msgSPIx == SPI6)
	{
		if (isEnable)
		{
			//---使能SPI的时钟线
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI6);
		}
		else
		{
			//---使能SPI的时钟线
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI6);
		}
	}
	#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数: 0---成功，!=0---失败
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MHW_PollMode_WriteByte(SPI_HandlerType *SPIx, UINT8_T wVal, UINT8_T *pRVal)
{
	//---获取当前时间节拍
	UINT32_T nowTime = 0;
	if (SPIx->msgFuncTick != NULL)
	{
		nowTime = SPIx->msgFuncTick();
	}

	//---等待发送缓冲区为空，TXE 事件---TXE=1，开始发送下一个数据
	while (!LL_SPI_IsActiveFlag_TXE(SPIx->msgSPIx))
	{
		if (SPIx->msgFuncTick != NULL)
		{
			if ((SPIx->msgFuncTick() - nowTime) > 100)
			{
				//---发送发生超时错误
				return ERROR_2;
			}
		}
		else
		{
			nowTime++;
			if (nowTime > 100000)
			{
				//---发送发生超时错误
				return ERROR_3;
			}
		}
	}

	//---写入数据寄存器，把要写入的数据写入发送缓冲区
	LL_SPI_TransmitData8(SPIx->msgSPIx, wVal);

	//---获取当前时间节拍
	if (SPIx->msgFuncTick != NULL)
	{
		nowTime = SPIx->msgFuncTick();
	}
	else
	{
		nowTime = 0;
	}

	//---等待接收缓冲区非空，RXNE 事件---等待RXNE=1，读取收到的数据
	while (!LL_SPI_IsActiveFlag_RXNE(SPIx->msgSPIx))
	{
		if (SPIx->msgFuncTick != NULL)
		{
			if ((SPIx->msgFuncTick() - nowTime) > 100)
			{
				//---发送发生超时错误
				return ERROR_4;
			}
		}
		else
		{
			nowTime++;
			if (nowTime > 100000)
			{
				//---发送发生超时错误
				return ERROR_5;
			}
		}
	}

	//---校验读取缓存区是否为空
	if (pRVal != NULL)
	{
		//---读取数据寄存器，获取接收缓冲区数据
		*pRVal = LL_SPI_ReceiveData8(SPIx->msgSPIx);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MHW_PollMode_WriteData(SPI_HandlerType *SPIx, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;
	for (i = 0; i < length; i++)
	{
		if (pRVal == NULL)
		{
			_return = SPI_MHW_PollMode_WriteByte(SPIx, pWVal[i], NULL);
		}
		else
		{
			_return = SPI_MHW_PollMode_WriteByte(SPIx, pWVal[i], &pRVal[i]);
		}

		if (_return != OK_0)
		{
			break;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：高位在前
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_WriteBitMSB(SPI_HandlerType *SPIx, UINT8_T wVal, UINT8_T *pRVal)
{
	//---发送1bit的数据
	if ((wVal & 0x80) == 0x00)
	{
		GPIO_OUT_0(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	}
	else
	{
		GPIO_OUT_1(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	}

	//---读取1bit的数据
	if (GPIO_GET_STATE(SPIx->msgMISO.msgGPIOPort, SPIx->msgMISO.msgGPIOBit) != 0)
	{
		if (pRVal != NULL)
		{
			*pRVal |= 1;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：低位在前
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_WriteBitLSB(SPI_HandlerType *SPIx, UINT8_T wVal, UINT8_T *pRVal)
{
	//---发送1bit的数据
	if ((wVal & 0x01) == 0x00)
	{
		GPIO_OUT_0(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	}
	else
	{
		GPIO_OUT_1(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	}

	//---读取1bit的数据
	if (GPIO_GET_STATE(SPIx->msgMISO.msgGPIOPort, SPIx->msgMISO.msgGPIOBit) != 0)
	{
		if (pRVal != NULL)
		{
			*pRVal |= 0x80;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_SetClock(SPI_HandlerType *SPIx, UINT32_T clock)
{
	SPIx->msgPluseWidth = clock;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MHW_SetClock(SPI_HandlerType *SPIx, UINT32_T clock)
{
	LL_SPI_SetBaudRatePrescaler(SPIx->msgSPIx, clock);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_WriteByteMSB(SPI_HandlerType *SPIx, UINT8_T wVal, UINT8_T *pRVal)
{
	UINT8_T i = 0;
	if (pRVal != NULL)
	{
		*pRVal = 0;
	}
	for (i = 0; i < 8; i++)
	{
		if (pRVal != NULL)
		{
			*pRVal <<= 1;
		}
		if (SPI_MSW_WriteBitMSB(SPIx, wVal, pRVal) != OK_0)
		{
			return ERROR_1;
		}
		wVal <<= 1;
		GPIO_OUT_1(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit);
		if (SPIx->msgFuncDelay != NULL)
		{
			SPIx->msgFuncDelay(SPIx->msgPluseWidth);
		}
		GPIO_OUT_0(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit);
		if (SPIx->msgFuncDelay != NULL)
		{
			SPIx->msgFuncDelay(SPIx->msgPluseWidth);
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_WriteByteLSB(SPI_HandlerType *SPIx, UINT8_T wVal, UINT8_T *pRVal)
{
	UINT8_T i = 0;
	if (pRVal!=NULL)
	{
		*pRVal = 0;
	}
	for (i = 0; i < 8; i++)
	{
		if (pRVal != NULL)
		{
			*pRVal >>= 1;
		}
		if (SPI_MSW_WriteBitLSB(SPIx, wVal, pRVal) != OK_0)
		{
			return ERROR_1;
		}
		wVal >>= 1;
		GPIO_OUT_1(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit);
		if (SPIx->msgFuncDelay != NULL)
		{
			SPIx->msgFuncDelay(SPIx->msgPluseWidth);
		}
		GPIO_OUT_0(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit);
		if (SPIx->msgFuncDelay != NULL)
		{
			SPIx->msgFuncDelay(SPIx->msgPluseWidth);
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：高位在前
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_WriteDataMSB(SPI_HandlerType *SPIx, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;
	for (i = 0; i < length; i++)
	{
		//---判断数据是否有效
		if (pRVal == NULL)
		{
			_return = SPI_MSW_WriteByteMSB(SPIx, pWVal[i], NULL);
		}
		else
		{
			_return = SPI_MSW_WriteByteMSB(SPIx, pWVal[i], &pRVal[i]);
		}

		//---判断读取正确性
		if (_return != OK_0)
		{
			break;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：低位在前
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_WriteDataLSB(SPI_HandlerType *SPIx, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;
	for (i = 0; i < length; i++)
	{
		//---判断数据是否有效
		if (pRVal == NULL)
		{
			_return = SPI_MSW_WriteByteLSB(SPIx, pWVal[i], NULL);
		}
		else
		{
			_return = SPI_MSW_WriteByteLSB(SPIx, pWVal[i], &pRVal[i]);
		}

		//---判断读取正确性
		if (_return != OK_0)
		{
			break;
		}
	}
	return _return;
}