/******************** (C) COPYRIGHT 2017 STMicroelectronics ********************
* File Name          :
* Author             : AMS KOREA
* Version            : V0.07
* Date               : 5th of December, 2018
* Description        : Reference code for FST1 and FTM5
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdlib.h>
#include "fts_lgd.h"

/** @addtogroup FTS_Private_Variables
  * @{
  */
static	uint8_t fts_fifo_addr[2] = {FTS_FIFO_ADDR, 0};

uint8_t		sysInfo_buf[SYS_INFO_SIZE];
SysInfo		*pSysInfo;

/**
  * @}
  */

/** @addtogroup FTS_Functions
  * @{
  */

/**
  * @brief  fts_delay
  *         Internal milli-second delay function
  * @param  msCount : specifies the delay time length
  * @retval None
  */
void fts_delay(uint32_t msCount)
{
	/* 
	 *Implement function for milli-second delay time
	 */
}

/**
  * @brief  Supply a voltage for analog (3.3V)
  * @param  None
  * @retval None
  */
void analog_3V3_power_onoff(int on_off)
{
	if (on_off == ENABLE)
	{
		/*
		 * user code - Power on
		 */
	}
	else
	{
		/*
		 * user code - Power off
		 */
	}
}

/**
  * @brief  Supply a voltage for digital (1.8V)
  * @param  None
  * @retval None
  */
void digital_1V8_power_onoff(int on_off)
{
	if (on_off == ENABLE)
	{
		/*
		 * user code - Power on
		 */
	}
	else
	{
		/*
		 * user code - Power off
		 */
	}
}

/**
  * @brief  Supply a voltage to FTS
  * @note	Have to turn on 1.8V earlier than 3.3V or 3.3V and 1.8V at the same time.
  * @param  None
  * @retval None
  */
void power_on(void)
{
	/* Please turn on 1.8V earlier than 3.3V */
	digital_1V8_power_onoff(ENABLE);
	fts_delay(10);

	analog_3V3_power_onoff(ENABLE);
	fts_delay(10);

	print("\r\n[FTS]Power On.");
}

/**
  * @brief  Supply a voltage to FTS
  * @note	Once the power off run, voltages (1.8V and 3.3V) MUST immediately fall to the ground level (auto-discharge function).
  * @param  None
  * @retval None
  */
void power_off(void)
{
	/*
	 * Important !!
	 *     Once the power off run, voltages (1.8V and 3.3V) MUST immediately fall to the ground level (auto-discharge function).
	 */
	digital_1V8_power_onoff(DISABLE);
	analog_3V3_power_onoff(DISABLE);

	print("\r\n[FTS]Power Off.");
}

#if	1

/**
  * @brief  Write data to target registers.
  * @param  pInBuf  : A pointer of the buffer to be sending to target.
  * @param  inCnt   : The count of pInBuf to be writing.
  * @retval OK if all operations done correctly, FAIL if not
  */
int fts_write_reg(uint8_t *pInBuf, int InCnt)
{
#ifdef	I2C_INTERFACE

	/* Implement user's fts_write_reg depend on your system using I2C communication. */

#else

	/* Implement user's fts_write_reg depend on your system using SPI 4-WIRE communication. */

#endif
	
	return	(FTS_NO_ERR);
}

/**
  * @brief  Read data from the device registers.
  * @note	It has to use reStart transaction when read data.
  * @param  pInBuf  : A pointer of the target register adress.
  * @param  inCnt   : The count of pInBuf for sending.
  * @param  pOutBuf : A pointer of the buffer containing the read bytes.
  * @param  outBuf  : The count of bytes to be reading from taget.
  * @retval OK if all operations done correctly. FAIL if error.
  */
int fts_read_reg(uint8_t *pInBuf, int inCnt, uint8_t *pOutBuf, int outCnt)
{
	int		err_flag = FTS_NO_ERR;
#ifdef	I2C_INTERFACE

	/* 
	 * Implement user's fts_read_reg depend on your system using I2C communication.
	 */
	 
#else

	/*
	 * 
	 * Implement user's fts_read_reg depend on your system using I2C communication.
	 *
	 * IMPOTANT!!!
	 *     There is one dummy byte before reading valid data.
	 *     In other words, first byte of read data is dummy and valid data is from second byte.
	 */
	 
#endif
	
	return	err_flag;
}

/**
  * @brief  Write a command to target
  * @param  cmd		: A command
  * @retval OK if all operations done correctly, FAIL if not
  */
int fts_command(uint8_t cmd)
{
	uint8_t	regAdd = 0;

	regAdd = cmd;
	if (fts_write_reg(&regAdd, 1) != 0)
		return	(FTS_ERR | FTS_ERR_COMM);

	return	FTS_NO_ERR;
}

/**
  * @brief  Write the data to target
  * @param  cmd       : a command
  * @param  reg_addr  : address of a register
  * @param  addr_size : size of address
  * @param  data      : position of data to write
  * @param  data_size : size of data
  * @retval OK if all operations done correctly, FAIL if not
  */
int fts_write_regU32(uint8_t cmd, uint32_t reg_addr, int addr_size, uint8_t *data, int data_size)
{
	uint8_t	regAdd[32];
	int		i;

	regAdd[0] = cmd;
	for (i = 0; i < addr_size; i++)
	{
		regAdd[i + 1] = (uint8_t) ((reg_addr >> ((addr_size - 1 - i) * 8)) & 0xFF);
	}
	for (i = 0; i < data_size; i++)
	{
		regAdd[i + 1 + addr_size] = data[i];
	}
	if (fts_write_reg(regAdd, addr_size + data_size + 1) != 0)
		return	(FTS_ERR | FTS_ERR_COMM);

	return	FTS_NO_ERR;
}

/**
  * @brief  Read the data from target
  * @param  cmd       : a command
  * @param  reg_addr  : address of a register
  * @param  addr_size : size of address
  * @param  data      : position of a buffer to save what read data
  * @param  data_size : size of data
  * @retval OK if all operations done correctly, FAIL if not
  */
int fts_read_regU32(uint8_t cmd, uint32_t reg_addr, int addr_size, uint8_t *pOutBuf, int outCnt)
{
	uint8_t	regAdd[16];
	int		i;

	regAdd[0] = cmd;
	for (i = 0; i < addr_size; i++)
	{
		regAdd[i + 1] = (uint8_t) ((reg_addr >> ((addr_size - 1 - i) * 8)) & 0xFF);
	}
	if (fts_read_reg(regAdd, addr_size + 1, pOutBuf, outCnt) != 0)
		return	(FTS_ERR | FTS_ERR_COMM);

	return	FTS_NO_ERR;
}

/**
  * @brief  Check error event message
  * @param  val  : a position of a event message
  * @retval OK if all operations done correctly, FAIL if not
  */
int fts_err_event_handler(uint8_t *val)
{
	int		err_type = FTS_NO_ERR;

	if (val[0] != EVTID_ERROR_REPORT)
		return	err_type;

	printf("\r\n[err_check]ERROR [%02x %02x %02x %02x %02x %02x %02x %02x]",
							val[0], val[1], val[2], val[3], val[4], val[5], val[6], val[7]);

	switch (val[1] & 0xF0)
	{
	case	EVTID_ERR_TYPE_SYSTEM1:
	case	EVTID_ERR_TYPE_SYSTEM2:
		err_type |= (FTS_ERR | FTS_ERR_SYSTEM);
		break;
	case	EVTID_ERR_TYPE_CRC:
		if ((val[1] >= 0x24) && (val[1] <= 0x27))
		{
			err_type |= (FTS_ERR | FTS_ERR_CRC_CORRUPT);
		}
		if ((val[1] == 0x29) || (val[1] == 0x2A))
		{
			err_type |= (FTS_ERR | FTS_ERR_CRC_CORRUPT);
		}
		if ((val[1] == 0x20) || (val[1] == 0x21))
		{
			err_type |= (FTS_ERR | FTS_ERR_CRC_CFG);
		}
	#ifdef MACHINE_OQC_INSPECTION
		if ((val[1] == 0x22) || (val[1] == 0x28))
		{
			err_type |= (FTS_ERR | FTS_ERR_MISS_FINAL);
		}
	#endif
		break;
#if	0
	case	EVTID_ERR_TYPE_MS_TUNE:
			break;
	case	EVTID_ERR_TYPE_SS_TUNE:
		break;
#endif
	case	EVTID_ERR_TYPE_LOCKDOWN_CODE:
		err_type |= (FTS_ERR | FTS_ERR_LOCKDOWN_ERR | (val[1] & 0x0F));
		break;
#if	defined (FTS_METHOD_GOLDEN_VALUE) || defined(MACHINE_OQC_INSPECTION)
	case	EVTID_ERR_TYPE_CX:
		err_type |= (FTS_ERR | FTS_ERR_CRC_CX);
		break;
#endif
	case	0xC0:
		break;
	default:
		err_type |= FTS_ERR;
		break;
	}

	return err_type;
}

/**
  * @brief  Parse and process received events.
  * @note	Reporting of finger data when the presence of fingers is detected.
  * @param  data		: The buffer of event saved.
  * @param	LeftEvent	: Count of events
  * @retval OK if all operations done correctly, FAIL if not
  */
int fts_event_handler_type_b(uint8_t *data, uint8_t LeftEvent)
{
	uint8_t 	EventNum = 0;
	uint8_t		TouchID = 0, EventID = 0;
	uint16_t	x = 0, y = 0, z = 0;

	for (EventNum = 0; EventNum < LeftEvent; EventNum++)
	{
		EventID = data[EventNum * FTS_EVENT_SIZE];
		if ((EventID == EVTID_ENTER_POINTER) || (EventID == EVTID_MOTION_POINTER) || (EventID == EVTID_LEAVE_POINTER))
		{
			TouchID = (data[1 + EventNum * FTS_EVENT_SIZE] >> 4) & 0x0F;
			x = (data[2 + EventNum * FTS_EVENT_SIZE] & 0x00FF) + ((data[3 + EventNum * FTS_EVENT_SIZE] << 8) & 0x0F00);
			y = ((data[3 + EventNum * FTS_EVENT_SIZE] >> 4) & 0x000F) + ((data[4 + EventNum * FTS_EVENT_SIZE] << 4) & 0x0FF0);

			switch (EventID)
			{
			case	EVTID_ENTER_POINTER:
				printf("\r\n[FTS]ENTER  : %d [x:%d][y:%d][z:%d]", TouchID, x, y, z);
				break;
			case	EVTID_MOTION_POINTER:
				printf("\r\n[FTS] MOTION : %d [x:%d][y:%d][z:%d]", TouchID, x, y, z);
				break;
			case	EVTID_LEAVE_POINTER:
				printf("\r\n[FTS] LEAVE  : %d [x:%d][y:%d][z:%d]", TouchID, x, y, z);
				break;
			}
		}
	}

	return	FTS_NO_ERR;
}

/**
  * @brief  Called by the ISR or the kernel when occurs an interrupt.
  * @note	This function handles the acquisition of finger data.
  * @param  None
  * @retval OK if all operations done correctly, FAIL if not
  */
int fts_event_handler(void)
{
	uint8_t		data[FTS_EVENT_SIZE * FTS_FIFO_MAX];
	int			evtcount = 0, remain_evtcnt = 0;

	do	{
		fts_read_reg(fts_fifo_addr, 1, (uint8_t *) data + (evtcount * FTS_EVENT_SIZE), FTS_EVENT_SIZE);
		remain_evtcnt = data[(evtcount * FTS_EVENT_SIZE) + 7] & 0x1F;
		evtcount++;
	}	while (remain_evtcnt);

	fts_event_handler_type_b(data, evtcount);

	return	FTS_NO_ERR;
}

/**
  * @brief  Check event messages for commands
  * @param  event_id   : type of event
  * @param	rpt_type   : status report type
  * @param	system_cmd : echo of command code
  * @param	length     : size of command code
  * @param	timeout    : count of timeout
  * @retval OK if all operations done correctly, FAIL if not
  */
int fts_cmd_completion_check(uint8_t event_id, uint8_t rpt_type, uint8_t *system_cmd, uint8_t length, int timeout)
{
	uint8_t val[8];
	int 	retry;
	int		i;
	int		err_type = FTS_NO_ERR, res = TRUE;

	retry = timeout;
	while (retry--)
	{
		fts_delay(50);
		fts_read_reg(fts_fifo_addr, 1, val, FTS_EVENT_SIZE);
		switch (val[0])
		{
		case	EVTID_CONTROLLER_READY:
			if (val[0] == event_id)
			{
				printf("\r\n[cmd_check]OK [%02x %02x %02x %02x %02x %02x %02x %02x]",
										val[0], val[1], val[2], val[3], val[4], val[5], val[6], val[7]);

				if ((err_type & (FTS_ERR_CRC_CX | FTS_ERR_CRC_CFG | FTS_ERR_SYSTEM | FTS_ERR_CRC_CORRUPT)) != 0)
				{
					printf("\r\n[cmd_check]ERROR-there is system or crc error.");
					return	err_type;
				}
			#ifdef MACHINE_OQC_INSPECTION
				if ((err_type & FTS_ERR_MISS_FINAL) != 0)
				{
					printf("\r\n[cmd_check]ERROR-It seems like this sample was not gone through the final inspection process.");
					return	err_type;
				}
			#endif
				return	FTS_NO_ERR;
			}
			break;
		case	EVTID_STATUS_REPORT:
			if ((val[0] == event_id) && (val[1] == rpt_type))
			{
				res = TRUE;
				for (i = 0; i < length; i++)
				{
					if (val[i + 2] != system_cmd[i])
						res = FALSE;
				}
				if (res == TRUE)
				{
					printf("\r\n[cmd_check]OK [%02x %02x %02x %02x %02x %02x %02x %02x]",
											val[0], val[1], val[2], val[3], val[4], val[5], val[6], val[7]);
					return	err_type;
				}
				else
				{
					printf("\r\n[cmd_check]INVALID [%02x %02x %02x %02x %02x %02x %02x %02x]",
											val[0], val[1], val[2], val[3], val[4], val[5], val[6], val[7]);
				}
			}
			else
			{
				printf("\r\n[cmd_check]INVALID [%02x %02x %02x %02x %02x %02x %02x %02x]",
										val[0], val[1], val[2], val[3], val[4], val[5], val[6], val[7]);
			}
			break;
		case	EVTID_ERROR_REPORT:
			err_type |= fts_err_event_handler(val);
			break;
		default:
			break;
		}
	}

	if (retry <= 0)
	{
		err_type |= (FTS_ERR | FTS_ERR_EVT_TIMEOVER);
		printf("\r\n[cmd_check]Time Over");
	}

	if (err_type != FTS_NO_ERR)
	{
		printf("\r\n[cmd_check]Error event generated.");
	}
	
	return err_type;
}

/**
  * @brief  System Reset
  * @param  mode       : Software/Hardware system reset
  * @param	echo_check : whether echo event will check or not
  * @retval OK if all operations done correctly, FAIL if not
  */
int fts_systemreset(int mode, int echo_check)
{
	uint8_t	regAdd[8] = {CMD_SYSTEM, CMD_SYS_SPECIAL, CMD_SYS_SPECIAL_SYSTEMRESET, 0x00};
	uint8_t	val[4] = {SYSTEM_RESET_VALUE, };
	int		reg_leng = 3;
	int		err_code = FTS_NO_ERR;

	if (mode == SYSTEM_RESET_SOFT)
	{
		fts_write_reg(regAdd, reg_leng);
	}
	else
	{
		fts_write_regU32(FTS_CMD_HW_REG_W, FTS_ADDR_SYSTEM_RESET, BITS_32, val, 1);
	}

	if (echo_check == ENABLE)
	{
		err_code = fts_cmd_completion_check(EVTID_CONTROLLER_READY, EVTID_RPTTYPE_CMD_ECHO, regAdd, reg_leng, 50);
		if (err_code != FTS_NO_ERR)
		{
			err_code |= (err_code | FTS_ERR_SYS_RST);
		}
	}

	return	err_code;
}

/**
  * @brief  Clear Event FIFO
  * @param  None
  * @retval OK if all operations done correctly, FAIL if not
  */
int fts_clear_FIFO(void)
{
	uint8_t	regAdd[8] = {CMD_SYSTEM, CMD_SYS_SPECIAL, CMD_SYS_SPECIAL_CLEAR_FIFO, 0x00};
	int		reg_leng = 3;
	int		err_code = FTS_NO_ERR;

	fts_write_reg(regAdd, reg_leng);
	err_code = fts_cmd_completion_check(EVTID_STATUS_REPORT, EVTID_RPTTYPE_CMD_ECHO, regAdd, reg_leng, 50);

	return	err_code;
}

/**
  * @brief  Interrupt enable or disable
  * @param  onoff	: ENABLE or DISABLE
  * @retval OK if all operations done correctly, FAIL if not
  */
int fts_interrupt_control(int onoff)
{
	uint8_t	regAdd[8] = {CMD_SYSTEM, CMD_SYS_INTB, 0x00, 0x00};
	int		reg_leng = 3;
	int		err_code = FTS_NO_ERR;

	if (onoff == ENABLE)
		regAdd[2] |= 0x01;

	fts_write_reg(regAdd, reg_leng);
	err_code = fts_cmd_completion_check(EVTID_STATUS_REPORT, EVTID_RPTTYPE_CMD_ECHO, regAdd, reg_leng, 50);

	return	err_code;
}

/**
  * @brief  Read chip id
  * @param  None
  * @retval OK if all operations done correctly, FAIL if not
  */
int fts_read_chip_id(void)
{
	uint8_t	val[8] = {0};
	int		retry = 5;
	int		err_code = FTS_NO_ERR;

	while (retry--)
	{
		fts_delay(20);
		fts_read_regU32(FTS_CMD_HW_REG_R, FTS_ADDR_CHIP_ID, BITS_32, val, FTS_EVENT_SIZE);
		if ((val[0] == FTS_ID0) && (val[1] == FTS_ID1))
		{
			if ((val[4] == 0x00) && (val[5] == 0x00))
			{
				printf("\r\n[ChipID]No FW [%02x %02x %02x %02x %02x %02x %02x %02x]",
							val[0], val[1], val[2], val[3], val[4], val[5], val[6], val[7]);
				err_code |= (FTS_ERR | FTS_ERR_CHIPID);
				return	err_code;
			}
			else
			{
				printf("\r\n[ChipID]OK [%02x %02x %02x %02x %02x %02x %02x %02x]",
							val[0], val[1], val[2], val[3], val[4], val[5], val[6], val[7]);
				return	err_code;
			}
		}
	}

	if (retry <= 0)
	{
		err_code |= (FTS_ERR | FTS_ERR_EVT_TIMEOVER);
	}

	return	err_code;
}

#ifdef	FTS_SUPPORT_FW_DOWNLOAD

/**
  * @brief  Poll the status of flash if the Flash becomes ready within a timeout.
  * @param  type
  * @retval TRUE if all operation done correctly, FALSE if not..
  */
int wait_for_flash_ready(uint8_t type)
{
    uint8_t	cmd[8] = {FTS_CMD_HW_REG_R, 0x20, 0x00, 0x00, type};
    uint8_t	readData[2] = {0};
    int		i, retry = 1000;

    while (retry > 0)
    {
    	fts_delay(50);
    	fts_read_reg(cmd, 5, readData, 2);
	#ifdef I2C_INTERFACE
    	if ((readData[0] & 0x80) == 0)
	#else
    	if ((readData[0] & 0x80) == 0)
	#endif
    	{
    		return	FTS_NO_ERR;
    	}
    	retry--;
    }
   	printf("\r\n[flash]Ready Timeout!");


    return	(FTS_ERR | FTS_ERR_EVT_TIMEOVER);
}

/**
  * @brief  Put the M3 in hold.
  * @param  None
  * @retval
  */
int hold_m3(void)
{
    uint8_t	cmd[4] = {SYSTEM_HOLD_M3_VALUE, 0};
    int	ret = FTS_NO_ERR;

	ret = fts_write_regU32(FTS_CMD_HW_REG_W, FTS_ADDR_SYSTEM_RESET, BITS_32, cmd, 1);
	if (ret != FTS_NO_ERR)
	{
		printf("\r\n[flash]Error[%08X]-hold_m3", ret);
		return ret;
	}
	fts_delay(10);

#if !defined(I2C_INTERFACE) && defined(SPI4_WIRE)
	cmd[0] = 0x10;
	ret = fts_write_regU32(FTS_CMD_HW_REG_W, ADDR_GPIO_DIRECTION, BITS_32, cmd, 1);
	if (ret != FTS_NO_ERR)
	{
		printf("\r\n[flash]Error[%08X]-hold_m3,DIR", ret);
		return ret;
	}

	fts_delay(1);
	cmd[0] = 0x02;
	ret = fts_write_regU32(FTS_CMD_HW_REG_W, ADDR_GPIO_PULLUP, BITS_32, cmd, 1);
	if (ret != FTS_NO_ERR)
	{
		printf("\r\n[flash]Error[%08X]-hold_m3,Pullup", ret);
		return ret;
	}

	fts_delay(1);
	cmd[0] = 0x07;
	ret = fts_write_regU32(FTS_CMD_HW_REG_W, ADDR_GPIO_CONFIG_REG2, BITS_32, cmd, 1);
	if (ret != FTS_NO_ERR)
	{
		printf("\r\n[flash]Error[%08X]-hold_m3,Config", ret);
		return ret;
	}

	fts_delay(1);
	cmd[0] = 0x30;
	ret = fts_write_regU32(FTS_CMD_HW_REG_W, ADDR_GPIO_CONFIG_REG0, BITS_32, cmd, 1);
	if (ret != FTS_NO_ERR)
	{
		printf("\r\n[flash]Error[%08X]-hold_m3,Config", ret);
		return ret;
	}

	fts_delay(1);
	cmd[0] = SPI4_MASK;
	ret = fts_write_regU32(FTS_CMD_HW_REG_W, ADDR_ICR, BITS_32, cmd, 1);
	if (ret != FTS_NO_ERR)
	{
		printf("\r\n[flash]Error[%08X]-hold_m3,Mode", ret);
		return ret;
	}
	fts_delay(10);
#endif

    return	FTS_NO_ERR;
}

/**
  * @brief  dma operation.
  * @param  None
  * @retval TRUE if all operation done correctly, FALSE if not..
  */
int start_flash_dma()
{
    int		status = FTS_NO_ERR;
    uint8_t	cmd[6] = {FTS_CMD_HW_REG_W, 0x20, 0x00, 0x00, FLASH_DMA_CODE0, FLASH_DMA_CODE1};

    fts_write_reg(cmd, 6);

    status = wait_for_flash_ready(FLASH_DMA_CODE0);
    if (status != FTS_NO_ERR)
    {
        return	status;
    }

    return	status;
}

/**
  * @brief  Fill the flash
  * @param  address		: Start address to fill
  * @param	data		: A pointer of binary file
  * @param	size		: Size of data to fill
  * @retval TRUE if all operation done correctly, FALSE if not..
  */
int fillFlash(uint32_t address, uint8_t *data, int size)
{
    int		remaining, index = 0;
    int		toWrite = 0;
    int		byteBlock = 0;
    int		wheel = 0;
    uint32_t	addr = 0;
    int		res = FTS_NO_ERR;
    int		delta;

    uint8_t		buff[DMA_CHUNK + 5] = {0};
    uint8_t		buff2[12] = {0};

    remaining = size;
    while (remaining > 0)
    {
		byteBlock = 0;
		addr = 0x00100000;
		printf("\r\n[flash]Write to memory [%d]", wheel);
        while (byteBlock < FLASH_CHUNK && remaining > 0)
        {
        	index = 0;
            if (remaining >= DMA_CHUNK)
            {
                if ((byteBlock + DMA_CHUNK) <= FLASH_CHUNK)
                {
                    toWrite = DMA_CHUNK;
                    remaining -= DMA_CHUNK;
                    byteBlock += DMA_CHUNK;
                }
                else
                {
                    delta = FLASH_CHUNK - byteBlock;
                    toWrite = delta;
                    remaining -= delta;
                    byteBlock += delta;
                }
            }
            else
            {
                if ((byteBlock + remaining) <= FLASH_CHUNK)
                {
                    toWrite = remaining;
                    byteBlock += remaining;
                    remaining = 0;

                }
                else
                {
                    delta = FLASH_CHUNK - byteBlock;
                    toWrite = delta;
                    remaining -= delta;
                    byteBlock += delta;
                }
            }

			buff[index++] = FTS_CMD_HW_REG_W;
			buff[index++] = (uint8_t) ((addr & 0xFF000000) >> 24);
			buff[index++] = (uint8_t) ((addr & 0x00FF0000) >> 16);
			buff[index++] = (uint8_t) ((addr & 0x0000FF00) >> 8);
            buff[index++] = (uint8_t) (addr & 0x000000FF);
            memcpy(&buff[index], data, toWrite);
            fts_write_reg(buff, index + toWrite);
            fts_delay(1);

            addr += toWrite;
            data += toWrite;
        }

        //configuring the DMA
		printf("\r\n[flash]Configure DMA [%d]", wheel);
        byteBlock = (byteBlock / 4) - 1;
        index = 0;

        buff2[index++] = FTS_CMD_HW_REG_W;
		buff2[index++] = 0x20;
        buff2[index++] = 0x00;
		buff2[index++] = 0x00;
        buff2[index++] = FLASH_DMA_CONFIG;
        buff2[index++] = 0x00;
        buff2[index++] = 0x00;
		addr = address + ((wheel * FLASH_CHUNK) / 4);
        buff2[index++] = (uint8_t) ((addr & 0x000000FF));
        buff2[index++] = (uint8_t) ((addr & 0x0000FF00) >> 8);
        buff2[index++] = (uint8_t) (byteBlock & 0x000000FF);
        buff2[index++] = (uint8_t) ((byteBlock & 0x0000FF00) >> 8);
		buff2[index++] = 0x00;

        fts_write_reg(buff2, index);
        fts_delay(10);

        printf("\r\n[flash]Start flash DMA [%d]", wheel);
        res = start_flash_dma();
        if (res != FTS_NO_ERR)
        {
        	printf("\r\n[flash]Error flashing DMA!");
            return	res;
        }
        fts_delay(100);
		printf("\r\n[flash]DMA done [%d]", wheel);


        wheel++;
    }
    return	res;
}

/**
  * @brief  Download a firmware to flash.
  * @param  pFilename	: A pointer of buffer for a read file.
  * @param	block_type
  * @param	system_reset
  * @retval None
  */
int fw_download(uint8_t *pFilename, FW_FTB_HEADER *fw_Header)
{
	uint32_t	FTS_TOTAL_SIZE = (256 * 1024);
	int			HEADER_DATA_SIZE = 32;

	int			err_flag = FTS_NO_ERR;
	uint8_t		regAdd[8] = {0};

	printf("\r\n[flash]1. System Reset");
	if ((err_flag = fts_systemreset(SYSTEM_RESET_HARD, DISABLE)) != FTS_NO_ERR)
	{
		printf("\r\n[flash]FAILED - system reset");
		return	err_flag;
	}
	fts_delay(50);

	printf("\r\n[flash]2. Hold M3");
	hold_m3();

	printf("\r\n[flash]3. Set Zero");
	regAdd[0] = FTS_CMD_HW_REG_W;	regAdd[1] = 0x20;	regAdd[2] = 0x00;	regAdd[3] = 0x00;	regAdd[4] = FLASH_UNLOCK_CODE0;	regAdd[5] = FLASH_UNLOCK_CODE1;
	fts_write_reg(regAdd, 6);
	fts_delay(50);

	printf("\r\n[flash]4. Flash Erase Unlock");
	regAdd[0] = FTS_CMD_HW_REG_W;	regAdd[1] = 0x20;	regAdd[2] = 0x00;	regAdd[3] = 0x00;	regAdd[4] = FLASH_ERASE_UNLOCK_CODE0;	regAdd[5] = FLASH_ERASE_UNLOCK_CODE1;
	fts_write_reg(regAdd, 6);
	fts_delay(30);

	printf("\r\n[flash]5. Flash Erase");
	regAdd[0] = FTS_CMD_HW_REG_W;	regAdd[1] = 0x20;	regAdd[2] = 0x00;	regAdd[3] = 0x00;	regAdd[4] = FLASH_ERASE_CODE0 + 1;	regAdd[5] = 0x00;
	fts_write_reg(regAdd, 6);
	fts_delay(10);

	regAdd[0] = FTS_CMD_HW_REG_W;	regAdd[1] = 0x20;	regAdd[2] = 0x00;	regAdd[3] = 0x00;	regAdd[4] = FLASH_ERASE_CODE0;	regAdd[5] = FLASH_ERASE_CODE1;
	fts_write_reg(regAdd, 6);
	fts_delay(10);

	err_flag = wait_for_flash_ready(FLASH_ERASE_CODE0);
	if (err_flag != FTS_NO_ERR)
	{
        err_flag |= (FTS_ERR_FLASH_ERASE);
		printf("\r\n[flash]Error - Flash Erase");


        return	err_flag;
    }
	fts_delay(200);

	printf("\r\n[flash]Program sec0:%d", fw_Header->sec0_size);
	err_flag = fillFlash(FLASH_ADDR_CODE, (pFilename + FW_HEADER_SIZE), fw_Header->sec0_size);
	if (err_flag != FTS_NO_ERR)
	{
		err_flag |= (FTS_ERR | FTS_ERR_FLASH_BURN);
		printf("\r\n[flash]Error - sec0");
		return	err_flag;
	}
	fts_delay(100);
	printf("\r\n[flash]load sec0 program DONE!");


	printf("\r\n[flash]Program sec1:%d", fw_Header->sec1_size);
	err_flag = fillFlash(FLASH_ADDR_CONFIG, (pFilename + FW_HEADER_SIZE + fw_Header->sec0_size), fw_Header->sec1_size);
	if (err_flag != FTS_NO_ERR)
	{
		err_flag |= (FTS_ERR | FTS_ERR_FLASH_BURN);
		printf("\r\n[flash]Error - sec1");


		return	err_flag;
	}
	fts_delay(100);
	printf("\r\n[flash]load sec1 program DONE!");


	printf("\r\n[flash]Program sec2:%d", fw_Header->sec2_size);
	if (fw_Header->sec2_size !=0)
	{
		err_flag = fillFlash(FLASH_ADDR_CX, (pFilename + FW_HEADER_SIZE + fw_Header->sec0_size + fw_Header->sec1_size), fw_Header->sec2_size);
		if (err_flag != FTS_NO_ERR)
		{
			err_flag |= (FTS_ERR | FTS_ERR_FLASH_BURN);
			printf("\r\n[flash]Error - sec2");

			return	err_flag;
		}
		fts_delay(100);
		printf("\r\n[flash]load sec2 program DONE!");
	}

	printf("\r\n[flash]6. System Reset");
	err_flag = fts_systemreset(SYSTEM_RESET_HARD, ENABLE);
	if (err_flag != FTS_NO_ERR)
	{
		err_flag |= (FTS_ERR | FTS_ERR_SYS_RST | FTS_ERR_FLASH_BURN);
		printf("\r\n[flash]Error - System Reset");
		return	err_flag;
	}

	printf("\r\n[flash]8. Read SysInfo");
	err_flag = fts_read_sysInfo();
	if (err_flag != FTS_NO_ERR)
	{
		err_flag |= (FTS_ERR | FTS_ERR_FLASH_BURN);
		printf("\r\n[flash]Error - Read sysInfo [%08X]", err_flag);
	}
	/*
	 * Need to check the version information.
	 */

	return	err_flag;
}

/**
  * @brief  Parsing the header of firmware binary file
  * @param  data		: A pointer of binary file
  * @param	fw_size		: Size of binary file
  * @param	fw_header	: A pointer of header parsing
  * @param	keep_cx		: Always '0'
  * @retval TRUE if all operation done correctly, FALSE if not..
  */
int parseBinFile(uint8_t *data, int fw_size, FW_FTB_HEADER *fw_header, int keep_cx)
{
	int			dimension;
	uint32_t	temp;
	int			res, file_type;
	int			err_code = FTS_NO_ERR;

	memcpy(fw_header, &data[0], FW_HEADER_SIZE);

	if (fw_header->signature != FW_HEADER_FTB_SIGNATURE)
	{
		printf("\r\n[parseBinFile] Wrong FW Signature %08X", fw_header->signature);
		err_code |= (FTS_ERR | FTS_ERR_BIN_TYPE);
		return	err_code;
	}

	if (fw_header->target != FW_HEADER_TARGET_ID)
	{
		printf("\r\n[parseBinFile] Wrong target version %08X ... ERROR", fw_header->target);
		err_code |= (FTS_ERR | FTS_ERR_BIN_TYPE);
		return	err_code;
	}

    if (!keep_cx)
    {
    	dimension = fw_header->sec0_size + fw_header->sec1_size + fw_header->sec2_size + fw_header->sec3_size;
    	temp = fw_size;
    }
    else
    {
    	//sec2 may contain cx data (future implementation) sec3 atm not used
		dimension = fw_header->sec0_size + fw_header->sec1_size;
		temp = fw_size - fw_header->sec2_size - fw_header->sec3_size;
    }

    if (dimension + FW_HEADER_SIZE + FW_BYTES_ALLIGN != temp)
    {
    	printf("\r\n[parseBinFile] Read only %d instead of %d... ERROR", fw_size, dimension + FW_HEADER_SIZE + FW_BYTES_ALLIGN);
		err_code |= (FTS_ERR | FTS_ERR_BIN_TYPE);
		return	err_code;
    }

	return	err_code;
}

/**
  * @brief  A buffer for saving a binary file (firmware)
  */
//const	uint8_t	fw_bin_data[105136] = {0, 1};

/**
  * @brief  Manage flash update procedure.
  * @param  force		: Always '0'
  * @param	keep_cx		: Always '0'
  * @retval TRUE if all operation done correctly, FALSE if not.
  */
int flashProcedure(int force, int keep_cx)
{
	uint8_t			*pFilename = NULL;
	int				fw_size;
	int				err_code;

	FW_FTB_HEADER	fw_ftbHeader;

	/* A pointer and size of buffer for binary file */
	pFilename = (uint8_t *) fw_bin_data;
	fw_size = sizeof(fw_bin_data);

	err_code = parseBinFile(pFilename, fw_size, &fw_ftbHeader, keep_cx);
	if (err_code != FTS_NO_ERR)
	{
		printf("\r\n[flash]ERROR-FW is not appreciate");

		return	err_code;
	}
	printf("\r\n[flash]Ver,E:%04X,F:%04X,C:%04X", fw_ftbHeader.ext_ver, fw_ftbHeader.fw_ver, fw_ftbHeader.cfg_ver);
	printf("\r\n[flash]Size,Sec0:%d,Sec1:%d", fw_ftbHeader.sec0_size, fw_ftbHeader.sec1_size);
	printf("\r\n[flash]Size,Sec2:%d,Sec3:%d", fw_ftbHeader.sec2_size, fw_ftbHeader.sec3_size);

	err_code = fw_download(pFilename, &fw_ftbHeader);
	if (err_code != FTS_NO_ERR)
	{
		printf("\r\n[flash]ERROR-Firmware update is not completed.");
		return	err_code;
	}
	printf("\r\n[flash]Firmware update is done successfully.");

	return	FTS_NO_ERR;
}

#endif

#ifdef FTS_SUPPORT_LOCKDOWN_CODE

/**
  * @brief	Calculates CRC8 value of an array of bytes & return 8-bit CRC value
  * @param	u8_srcBuff[]	: input array of bytes
  * @param	u32_len			: the number of input bytes
  * @return	CRC8 result
  * @note	The CRC Polynomial and initial CRC value are fixed, as following:
 */
uint8_t CalculateCRC8(uint8_t* u8_srcBuff, uint32_t u32_len)
{
	uint8_t		u8_polynomial = 0x9B;		// WCDMA standard
	uint8_t		u8_initCRCValue = 0x00;		// WCDMA standard.
	uint8_t 	u8_remainder;
	uint32_t	u32_i;
	uint8_t		bit;

	u8_remainder = u8_initCRCValue;
	// Perform modulo-2 division, a byte at a time.
	for (u32_i = 0; u32_i < u32_len; u32_i++)
	{
		//Bring the next byte into the remainder.
		u8_remainder ^= u8_srcBuff[u32_i];

		//Perform modulo-2 division, a bit at a time.
		for (bit = 8; bit > 0; --bit)
		{
			//Try to divide the current data bit.
			if (u8_remainder & (0x1 << 7)) // MSB is 1
			{
				u8_remainder = (u8_remainder << 1) ^ u8_polynomial;
			}
			else // MSB is 0
			{
				u8_remainder = (u8_remainder << 1);
			}
		}
	}
	// The final remainder is the CRC result.
	return (u8_remainder);
}

/**
  * @brief  Write lockdown code (OTP)
  * @param  mem_rec_id		Record ID of lockdown code (mainly, LOAD_LOCKDOWN_CODE_REC_ID0)
  * @param	wr_data			position of the lockdown code buffer
  * @param	nlength			Length of the lockdown code
  * @retval None
  */
int fts_lockdown_write(uint8_t mem_rec_id, uint8_t *wr_data, int nlength)
{
	uint8_t	regAdd[8] = {0x5A, 0x00, 0x00, 0x00};
	int		reg_leng = 4;
	int		err_code = FTS_NO_ERR;
	uint8_t	lockdown_Buf[4 + FTS_LOCKDOWN_CODE_LENGTH];

	memcpy(lockdown_Buf + 4, wr_data, nlength);
	lockdown_Buf[0] = nlength;
	lockdown_Buf[1] = CalculateCRC8(wr_data, nlength);
	lockdown_Buf[2] = mem_rec_id;
	lockdown_Buf[3] = CalculateCRC8(lockdown_Buf, 3);

	printf("\r\n[fts_lockdown_write]Command for the header");
	regAdd[1] = mem_rec_id;
	fts_write_regU32(CMD_FRM_BUFF_W, ADDR_FRAMEBUFFER, BITS_16, regAdd, reg_leng);
	fts_delay(10);

	printf("\r\n[fts_lockdown_write]Command for the payload");
	fts_write_regU32(CMD_FRM_BUFF_W, ADDR_FRAMEBUFFER + 0x10, BITS_16, lockdown_Buf, nlength + 4);
	fts_delay(10);

	printf("\r\n[fts_lockdown_write]Command to upload the data to flash");
	regAdd[0] = CMD_SYSTEM; regAdd[1] = CMD_SYS_SPECIAL; regAdd[2] = CMD_SYS_SPECIAL_UPLOAD_HOST_DATA;
	reg_leng = 3;
	fts_write_reg(regAdd, reg_leng);
	err_code = fts_cmd_completion_check(EVTID_STATUS_REPORT, EVTID_RPTTYPE_CMD_ECHO, regAdd, reg_leng, 50);
	if (err_code != FTS_NO_ERR)
	{
		if ((err_code & FTS_ERR_LOCKDOWN_ERR) && ((err_code & 0xF) == 0x1))
			printf("\r\n[fts_lockdown_write]Error[%08X]-CRC Error.", err_code);
		else if ((err_code & FTS_ERR_LOCKDOWN_ERR) && ((err_code & 0xF) == 0x3))
			printf("\r\n[fts_lockdown_write]Error[%08X]-There is no enough space in flash for new record.", err_code);
		else
			printf("\r\n[fts_lockdown_write]Error[%08X]", err_code);
	}

	return	err_code;
}

/**
  * @brief  Read lockdown code (OTP)
  * @param  mem_rec_id		Record ID of lockdown code  (mainly, LOAD_LOCKDOWN_CODE_REC_ID0)
  * @param	rd_data			position of the lockdown code buffer
  * @param	nlength			Length of the lockdown code
  * @retval None
  */
int fts_lockdown_read(uint8_t mem_rec_id, uint8_t *rd_data, int nlength)
{
	uint8_t	regAdd[8] = {CMD_SYSTEM, CMD_SYS_LOAD_DATA_MEM, 0x00, 0x00};
	int		reg_leng = 3;
	int		err_code = FTS_NO_ERR;
	uint8_t	rec_cnt = 0;

	printf("\r\n[fts_lockdown_read]Request the lockdown code");
	regAdd[2] = mem_rec_id;
	fts_write_reg(regAdd, reg_leng);
	err_code = fts_cmd_completion_check(EVTID_STATUS_REPORT, EVTID_RPTTYPE_CMD_ECHO, regAdd, reg_leng, 50);
	if (err_code != FTS_NO_ERR)
	{
		if ((err_code & FTS_ERR_LOCKDOWN_ERR) && ((err_code & 0xF) == 0x0))
			printf("\r\n[fts_lockdown_read]Error[%08X]-Lockdown code error.", err_code);
		else if ((err_code & FTS_ERR_LOCKDOWN_ERR) && ((err_code & 0xF) == 0x2))
			printf("\r\n[fts_lockdown_read]Error[%08X]-There is no data of this id in flash.", err_code);
		else
			printf("\r\n[fts_lockdown_read]Error[%08X]", err_code);

		return	err_code;
	}

	printf("\r\n[fts_lockdown_read]Command to download the data");
	fts_delay(10);
	fts_read_regU32(CMD_FRM_BUFF_R, ADDR_FRAMEBUFFER, BITS_16, regAdd, 8);
	if ((regAdd[0] == 0xA5) && (regAdd[1] == mem_rec_id))
	{
		rec_cnt = regAdd[5];		// Writing count of lock downn code.
		fts_read_regU32(CMD_FRM_BUFF_R, ADDR_FRAMEBUFFER + 0x14, BITS_16, rd_data, nlength);
		fts_delay(1);
		printf("\r\n[fts_lockdown_read]OK-Done successfully.");
	}
	else
	{
		printf("\r\n[fts_lockdown_read]Error-Can't load the data due to different ID");
		err_code = FTS_ERR;
	}

	return	err_code;
}

#endif

/**
  * @brief  Read system information
  * @param  None
  * @retval None
  */
int fts_read_sysInfo(void)
{
	uint8_t	regAdd[8] = {CMD_SYSTEM, CMD_SYS_LOAD_DATA_MEM, LOAD_SYS_INFO, 0x00};
	int		reg_leng = 3;
	int		err_code = FTS_NO_ERR;

	pSysInfo = (SysInfo *) sysInfo_buf;

	fts_write_reg(regAdd, reg_leng);
	err_code = fts_cmd_completion_check(EVTID_STATUS_REPORT, EVTID_RPTTYPE_CMD_ECHO, regAdd, reg_leng, 50);
	if (err_code != FTS_NO_ERR)
	{
		err_code |= (FTS_ERR | FTS_ERR_HOSTDATA_ID_HD);
		return	err_code;
	}

	fts_read_regU32(CMD_FRM_BUFF_R, ADDR_FRAMEBUFFER, BITS_16, sysInfo_buf, SYS_INFO_SIZE);
	if ((pSysInfo->header != HEADER_SIGNATURE) || (pSysInfo->host_data_mem_id != LOAD_SYS_INFO))
	{
		err_code |= (FTS_ERR | FTS_ERR_HOSTDATA_ID_HD);
		return	err_code;
	}

	return	err_code;
}

/**
  * @brief	Get the mutual compensation data
  * @param  memory_id : type of compensation data
  * @param	pbuf_data : position of a buffer to save the data
  * @retval TRUE if all operation done correctly, FALSE if not.
  */
int fts_get_ms_comp_data(uint8_t memory_id, int8_t *pbuf_data)
{
	uint8_t	regAdd[8] = {CMD_SYSTEM, CMD_SYS_LOAD_DATA_MEM, 0x00, 0x00};
	int		reg_leng = 3;
	int		err_code = FTS_NO_ERR;
	uint8_t	temp_header[COMP_DATA_HEADER_SIZE];
	int8_t	*temp_buf;
	MsCompHeader	*ptHeader;

	regAdd[2] = memory_id;
	/* Write the command and check the echo event */
	fts_write_reg(regAdd, reg_leng);
	fts_delay(10);
	if ((err_code = fts_cmd_completion_check(EVTID_STATUS_REPORT, EVTID_RPTTYPE_CMD_ECHO, regAdd, reg_leng, 50)) != FTS_NO_ERR)
	{
		err_code  |= (FTS_ERR | FTS_ERR_HOSTDATA_ID_HD);
		printf("\r\n[fts_get_ms_comp_data]FAILED[%08X]-Invalid echo event for command", err_code);
		return	err_code;
	}

	/* Read the header of compensation data */
	fts_read_regU32(CMD_FRM_BUFF_R, ADDR_FRAMEBUFFER, BITS_16, temp_header, COMP_DATA_HEADER_SIZE);
	ptHeader = (MsCompHeader *) temp_header;
	if ((ptHeader->header != HEADER_SIGNATURE) || (ptHeader->host_data_mem_id != memory_id))
	{
		err_code |= (FTS_ERR | FTS_ERR_HOSTDATA_ID_HD);
		printf("\r\n[fts_get_ms_comp_data]FAILED[%08X]-Incorrect header", err_code);
		return	err_code;
	}
	printf("\r\n[fts_get_ms_comp_data]LENGTH : TX[%02X], RX:[%02X]", ptHeader->force_leng, ptHeader->sense_leng);

	temp_buf = (int8_t *) malloc(ptHeader->force_leng * ptHeader->sense_leng * sizeof(int8_t));
	if (temp_buf == NULL)
	{
		err_code |= (FTS_ERR | FTS_ERR_MEM_ALLC);
		printf("\r\n[fts_get_ms_comp_data]FAILED[%08X]-Memory Allocation", err_code);
		free(temp_buf);
		return	err_code;
	}

	/* Read the data and copy to destination buffer */
	fts_read_regU32(CMD_FRM_BUFF_R, ADDR_FRAMEBUFFER + COMP_DATA_HEADER_SIZE, BITS_16, temp_buf, ptHeader->force_leng * ptHeader->sense_leng * sizeof(int8_t));
	memcpy(pbuf_data, temp_buf, ptHeader->force_leng * ptHeader->sense_leng * sizeof(int8_t));

	free(temp_buf);

	return	err_code;
}

/**
  * @brief	Get the self compensation data
  * @param  memory_id : type of compensation data
  * @param	pbuf_tx and pbuf_rx : position of a buffer to save the data
  * @retval	TRUE if all operation done correctly, FALSE if not.
  */
int fts_get_ss_totalcomp_data(uint8_t memory_id, uint16_t *pbuf_tx, uint16_t *pbuf_rx)
{
	uint8_t		regAdd[8] = {CMD_SYSTEM, CMD_SYS_LOAD_DATA_MEM, 0x00, 0x00};
	int			reg_leng = 3, tempAddr;
	int			i = 0, err_code = FTS_NO_ERR;
	uint8_t		temp_header[COMP_DATA_HEADER_SIZE];
	uint8_t		*temp_buf_tx, *temp_buf_rx;
	SsCompHeader	*ptHeader;

	regAdd[2] = memory_id;
	fts_write_reg(regAdd, reg_leng);
	fts_delay(10);
	if ((err_code = fts_cmd_completion_check(EVTID_STATUS_REPORT, EVTID_RPTTYPE_CMD_ECHO, regAdd, reg_leng, 50)) != FTS_NO_ERR)
	{
		err_code  |= (FTS_ERR | FTS_ERR_HOSTDATA_ID_HD);
		printf("\r\n[fts_get_ss_totalcomp_data]FAILED[%08X]-Invalid echo event for command", err_code);
		return	err_code;
	}

	/* Read the header of compensation data */
	tempAddr = ADDR_FRAMEBUFFER;
	fts_read_regU32(CMD_FRM_BUFF_R, tempAddr, BITS_16, temp_header, COMP_DATA_HEADER_SIZE);
	ptHeader = (SsCompHeader *) temp_header;
	if ((ptHeader->header != HEADER_SIGNATURE) || (ptHeader->host_data_mem_id != memory_id))
	{
		err_code |= (FTS_ERR | FTS_ERR_HOSTDATA_ID_HD);
		printf("\r\n[fts_get_ss_totalcomp_data]FAILED[%08X]-Incorrect header", err_code);
		return	err_code;
	}
	printf("\r\n[fts_get_ss_totalcomp_data]LENGTH : TX[%02X], RX:[%02X]", ptHeader->force_leng, ptHeader->sense_leng);

	if (pbuf_tx != NULL)
	{
		temp_buf_tx = (uint8_t *) malloc(ptHeader->force_leng * sizeof(uint16_t));
		if (temp_buf_tx == NULL)
		{
			err_code |= (FTS_ERR | FTS_ERR_MEM_ALLC);
			printf("\r\n[fts_get_ss_totalcomp_data]FAILED[%08X]-Memory Allocation", err_code);
			free(temp_buf_tx);
			return	err_code;
		}
	}
	if (pbuf_rx != NULL)
	{
		temp_buf_rx = (uint8_t *) malloc(ptHeader->sense_leng * sizeof(uint16_t));
		if (temp_buf_rx == NULL)
		{
			err_code |= (FTS_ERR | FTS_ERR_MEM_ALLC);
			printf("\r\n[fts_get_ss_totalcomp_data]FAILED[%08X]-Memory Allocation", err_code);
			free(temp_buf_rx);
			return	err_code;
		}
	}

	/* Load the tx data */
	tempAddr += COMP_DATA_HEADER_SIZE;
	if (pbuf_tx != NULL)
	{
		fts_read_regU32(CMD_FRM_BUFF_R, tempAddr, BITS_16, temp_buf_tx, ptHeader->force_leng * sizeof(uint16_t));
		for (i = 0; i < ptHeader->force_leng; i++)
		{
			pbuf_tx[i] = ((uint16_t) temp_buf_tx[i * 2 + 1] << 8) | (uint16_t) temp_buf_tx[i * 2];
		}
		free(temp_buf_tx);
	}
	/* Load the rx data */
	tempAddr += ptHeader->force_leng * sizeof(uint16_t);
	if (pbuf_rx != NULL)
	{
		fts_read_regU32(CMD_FRM_BUFF_R, tempAddr, BITS_16, temp_buf_rx, ptHeader->sense_leng * sizeof(uint16_t));
		for (i = 0; i < ptHeader->sense_leng; i++)
		{
			pbuf_rx[i] = ((uint16_t) temp_buf_rx[i * 2 + 1] << 8) | (uint16_t) temp_buf_rx[i * 2];
		}
		free(temp_buf_rx);
	}

	return	err_code;
}

/**
  * @brief	Get the MS capacitance (uncompensated Cm)
  * @param  memory_id : host data memory id
  * @param	pbuf_data : position of a buffer to save the data
  * @retval TRUE if all operation done correctly, FALSE if not.
  */
int fts_get_ms_capacitance(uint8_t memory_id, uint16_t *pbuf_data)
{
	uint8_t	regAdd[8] = {CMD_SYSTEM, CMD_SYS_LOAD_DATA_MEM, 0x00, 0x00};
	int		reg_leng = 3;
	int		err_code = FTS_NO_ERR;
	int		i;
	uint8_t	temp_header[COMP_DATA_HEADER_SIZE];
	uint8_t	*temp_buf;
	CapFormHeader	*ptHeader;

	regAdd[2] = memory_id;
	/* Write the command and check the echo event */
	fts_write_reg(regAdd, reg_leng);
	fts_delay(10);
	if ((err_code = fts_cmd_completion_check(EVTID_STATUS_REPORT, EVTID_RPTTYPE_CMD_ECHO, regAdd, reg_leng, 50)) != FTS_NO_ERR)
	{
		err_code  |= (FTS_ERR | FTS_ERR_HOSTDATA_ID_HD);
		printf("\r\n[fts_get_ms_capacitance]FAILED[%08X]-Invalid echo event for command", err_code);
		return	err_code;
	}

	/* Read the header of compensation data */
	fts_read_regU32(CMD_FRM_BUFF_R, ADDR_FRAMEBUFFER, BITS_16, temp_header, COMP_DATA_HEADER_SIZE);
	ptHeader = (CapFormHeader *) temp_header;
	if ((ptHeader->header != HEADER_SIGNATURE) || (ptHeader->host_data_mem_id != memory_id))
	{
		err_code |= (FTS_ERR | FTS_ERR_HOSTDATA_ID_HD);
		printf("\r\n[fts_get_ms_capacitance]FAILED[%08X]-Incorrect header", err_code);
		return	err_code;
	}
	printf("\r\n[fts_get_ms_capacitance]LENGTH : TX[%02X], RX:[%02X]", ptHeader->force_leng, ptHeader->sense_leng);

	temp_buf = (uint8_t *) malloc(ptHeader->force_leng * ptHeader->sense_leng * sizeof(uint16_t));
	if (temp_buf == NULL)
	{
		err_code |= (FTS_ERR | FTS_ERR_MEM_ALLC);
		printf("\r\n[fts_get_ms_capacitance]FAILED[%08X]-Memory Allocation", err_code);
		free(temp_buf);
		return	err_code;
	}

	/* Read the data and save to a buffer */
	fts_read_regU32(CMD_FRM_BUFF_R, ADDR_FRAMEBUFFER + COMP_DATA_HEADER_SIZE, BITS_16, temp_buf, ptHeader->force_leng * ptHeader->sense_leng * sizeof(uint16_t));
	for (i = 0; i < ptHeader->force_leng * ptHeader->sense_leng; i++)
	{
		pbuf_data[i] = ((uint16_t) temp_buf[i * 2 + 1] << 8) | (uint16_t) temp_buf[i * 2];
	}
	free(temp_buf);

	return	err_code;
}

/**
  * @brief	Get the SS capacitance (uncompensated Cp)
  * @param  memory_id : host data memory id
  * @param	pbuf_tx and pbuf_rx : position of a buffer to save the data
  * @retval	TRUE if all operation done correctly, FALSE if not.
  */
int fts_get_ss_capacitance(uint8_t memory_id, uint16_t *pbuf_tx, uint16_t *pbuf_rx)
{
	uint8_t		regAdd[8] = {CMD_SYSTEM, CMD_SYS_LOAD_DATA_MEM, 0x00, 0x00};
	int			reg_leng = 3, tempAddr;
	int			i = 0, err_code = FTS_NO_ERR;
	uint8_t		temp_header[COMP_DATA_HEADER_SIZE];
	uint8_t		*temp_buf_tx, *temp_buf_rx;
	CapFormHeader	*ptHeader;

	regAdd[2] = memory_id;
	fts_write_reg(regAdd, reg_leng);
	fts_delay(10);
	if ((err_code = fts_cmd_completion_check(EVTID_STATUS_REPORT, EVTID_RPTTYPE_CMD_ECHO, regAdd, reg_leng, 50)) != FTS_NO_ERR)
	{
		err_code  |= (FTS_ERR | FTS_ERR_HOSTDATA_ID_HD);
		printf("\r\n[fts_get_ss_capacitance]FAILED[%08X]-Invalid echo event for command", err_code);
		return	err_code;
	}

	/* Read the header of compensation data */
	tempAddr = ADDR_FRAMEBUFFER;
	fts_read_regU32(CMD_FRM_BUFF_R, tempAddr, BITS_16, temp_header, COMP_DATA_HEADER_SIZE);
	ptHeader = (CapFormHeader *) temp_header;
	if ((ptHeader->header != HEADER_SIGNATURE) || (ptHeader->host_data_mem_id != memory_id))
	{
		err_code |= (FTS_ERR | FTS_ERR_HOSTDATA_ID_HD);
		printf("\r\n[fts_get_ss_capacitance]FAILED[%08X]-Incorrect header", err_code);
		return	err_code;
	}
	printf("\r\n[fts_get_ss_capacitance]LENGTH : TX[%02X], RX:[%02X]", ptHeader->force_leng, ptHeader->sense_leng);

	if (pbuf_tx != NULL)
	{
		temp_buf_tx = (uint8_t *) malloc(ptHeader->force_leng * sizeof(uint16_t));
		if (temp_buf_tx == NULL)
		{
			err_code |= (FTS_ERR | FTS_ERR_MEM_ALLC);
			printf("\r\n[fts_get_ss_totalcomp_data]FAILED[%08X]-Memory Allocation", err_code);
			free(temp_buf_tx);
			return	err_code;
		}
	}
	if (pbuf_rx != NULL)
	{
		temp_buf_rx = (uint8_t *) malloc(ptHeader->sense_leng * sizeof(uint16_t));
		if (temp_buf_rx == NULL)
		{
			err_code |= (FTS_ERR | FTS_ERR_MEM_ALLC);
			printf("\r\n[fts_get_ss_totalcomp_data]FAILED[%08X]-Memory Allocation", err_code);
			free(temp_buf_rx);
			return	err_code;
		}
	}

	/* Load the tx data */
	tempAddr += COMP_DATA_HEADER_SIZE;
	if (pbuf_tx != NULL)
	{
		fts_read_regU32(CMD_FRM_BUFF_R, tempAddr, BITS_16, temp_buf_tx, ptHeader->force_leng * sizeof(uint16_t));
		for (i = 0; i < ptHeader->force_leng; i++)
		{
			pbuf_tx[i] = ((uint16_t) temp_buf_tx[i * 2 + 1] << 8) | (uint16_t) temp_buf_tx[i * 2];
		}
		free(temp_buf_tx);
	}
	/* Load the rx data */
	tempAddr += ptHeader->force_leng * sizeof(uint16_t);
	if (pbuf_rx != NULL)
	{
		fts_read_regU32(CMD_FRM_BUFF_R, tempAddr, BITS_16, temp_buf_rx, ptHeader->sense_leng * sizeof(uint16_t));
		for (i = 0; i < ptHeader->sense_leng; i++)
		{
			pbuf_rx[i] = ((uint16_t) temp_buf_rx[i * 2 + 1] << 8) | (uint16_t) temp_buf_rx[i * 2];
		}
		free(temp_buf_rx);
	}

	return	err_code;
}

/**
  * @brief	Get synchronized data
  * @param  memory_id  : type of compensation data
  * @param	pbuf_ms    : position of a buffer -> Mutual
  * @param	pbuf_ss_tx : position of a buffer -> SS TX
  * @param	pbuf_ss_rx : position of a buffer -> SS RX
  * @param	pbuf_key   : position of a buffer -> KEY
  * @retval	TRUE if all operation done correctly, FALSE if not.
  */
int fts_get_SyncFrame_data(uint8_t memory_id, int16_t *pbuf_ms, int16_t *pbuf_ss_tx, int16_t *pbuf_ss_rx, int16_t *pbuf_key)
{
	uint8_t		regAdd[8] = {CMD_SYSTEM, CMD_SYS_LOAD_DATA_MEM, 0x00, 0x00};
	int			reg_leng = 3, tempAddr;
	int			i = 0, retry = 10, err_code = FTS_NO_ERR;
	uint8_t		temp_header[COMP_DATA_HEADER_SIZE];
	uint8_t		*tmp_buf_ms, *tmp_buf_ss_tx, *tmp_buf_ss_rx, *tmp_buf_key;
	SyncFrameHeader	*ptHeader;
	static int	frameCount = 0;

	regAdd[2] = memory_id;
	fts_write_reg(regAdd, reg_leng);
	fts_delay(50);

	/* Read the header of compensation data */
	tempAddr = ADDR_FRAMEBUFFER;
	ptHeader = (SyncFrameHeader *) temp_header;
	for (i = 0; i < retry; i++)
	{
		fts_delay(50);
		fts_read_regU32(CMD_FRM_BUFF_R, tempAddr, BITS_16, temp_header, COMP_DATA_HEADER_SIZE);
		if ((ptHeader->header == HEADER_SIGNATURE) && (ptHeader->host_data_mem_id == memory_id) && (ptHeader->cnt != frameCount))
		{
			frameCount = ptHeader->cnt;
			break;
		}
	}
	if (i >= retry)
	{
		err_code |= (FTS_ERR | FTS_ERR_HOSTDATA_ID_HD);
		printf("\r\n[SyncFrame]FAILED[%08X]-Incorrect header", err_code);
		return	err_code;
	}
	printf("\r\n[SyncFrame]MS LENGTH : TX[%02X], RX:[%02X], KEY[%02X]", ptHeader->ms_force_leng, ptHeader->ms_sense_leng, ptHeader->key_leng);
	printf("\r\n[SyncFrame]SS LENGTH : TX[%02X], RX:[%02X]", ptHeader->ss_force_leng, ptHeader->ss_sense_leng);

	tempAddr += COMP_DATA_HEADER_SIZE + ptHeader->dbg_frm_leng;
	if (((ptHeader->ms_force_leng > 0) || (ptHeader->ms_sense_leng > 0)) && (pbuf_ms != NULL))
	{
		tmp_buf_ms = (uint8_t *) malloc(ptHeader->ms_force_leng * ptHeader->ms_sense_leng * sizeof(uint16_t));
		if (tmp_buf_ms == NULL)
		{
			err_code |= (FTS_ERR | FTS_ERR_MEM_ALLC);
			printf("\r\n[SyncFrame]FAILED[%08X]-MS Memory Allocation", err_code);
			free(tmp_buf_ms);
			return	err_code;
		}
		fts_read_regU32(CMD_FRM_BUFF_R, tempAddr, BITS_16, tmp_buf_ms, ptHeader->ms_force_leng * ptHeader->ms_sense_leng * sizeof(uint16_t));
		for (i = 0; i < ptHeader->ms_force_leng * ptHeader->ms_sense_leng; i++)
		{
			pbuf_ms[i] = ((uint16_t) tmp_buf_ms[i * 2 + 1] << 8) | (uint16_t) tmp_buf_ms[i * 2];
		}
		free(tmp_buf_ms);
	}

	/* Load self raw data of tx */
	tempAddr += ptHeader->ms_force_leng * ptHeader->ms_sense_leng * sizeof(uint16_t);
	if ((ptHeader->ss_force_leng > 0) && (pbuf_ss_tx != NULL))
	{
		tmp_buf_ss_tx = (uint8_t *) malloc(ptHeader->ss_force_leng * sizeof(uint16_t));
		if (tmp_buf_ss_tx == NULL)
		{
			err_code |= (FTS_ERR | FTS_ERR_MEM_ALLC);
			printf("\r\n[SyncFrame]FAILED[%08X]-SS Memory Allocation", err_code);
			free(tmp_buf_ss_tx);
			return	err_code;
		}
		fts_read_regU32(CMD_FRM_BUFF_R, tempAddr, BITS_16, tmp_buf_ss_tx, ptHeader->ss_force_leng * sizeof(uint16_t));
		for (i = 0; i < ptHeader->ss_force_leng; i++)
		{
			pbuf_ss_tx[i] = ((uint16_t) tmp_buf_ss_tx[i * 2 + 1] << 8) | (uint16_t) tmp_buf_ss_tx[i * 2];
		}
		free(tmp_buf_ss_tx);
	}

	/* Load self raw data of rx */
	tempAddr += ptHeader->ss_force_leng * sizeof(uint16_t);
	if ((ptHeader->ss_sense_leng > 0) && (pbuf_ss_rx != NULL))
	{
		tmp_buf_ss_rx = (uint8_t *) malloc(ptHeader->ss_sense_leng * sizeof(uint16_t));
		if (tmp_buf_ss_rx == NULL)
		{
			err_code |= (FTS_ERR | FTS_ERR_MEM_ALLC);
			printf("\r\n[SyncFrame]FAILED[%08X]-SS Memory Allocation", err_code);
			free(tmp_buf_ss_rx);
			return	err_code;
		}
		fts_read_regU32(CMD_FRM_BUFF_R, tempAddr, BITS_16, tmp_buf_ss_rx, ptHeader->ss_sense_leng * sizeof(uint16_t));
		for (i = 0; i < ptHeader->ss_sense_leng; i++)
		{
			pbuf_ss_rx[i] = ((uint16_t) tmp_buf_ss_rx[i * 2 + 1] << 8) | (uint16_t) tmp_buf_ss_rx[i * 2];
		}
		free(tmp_buf_ss_rx);
	}

	/* Load key raw data */
	tempAddr += ptHeader->ss_sense_leng * sizeof(uint16_t);
	if ((ptHeader->key_leng > 0) && (pbuf_key != NULL))
	{
		tmp_buf_key = (uint8_t *) malloc(ptHeader->key_leng * sizeof(uint16_t));
		if (tmp_buf_key == NULL)
		{
			err_code |= (FTS_ERR | FTS_ERR_MEM_ALLC);
			printf("\r\n[SyncFrame]FAILED[%08X]-KEY Memory Allocation", err_code);
			free(tmp_buf_key);
			return	err_code;
		}
		fts_read_regU32(CMD_FRM_BUFF_R, tempAddr, BITS_16, tmp_buf_key, ptHeader->key_leng * sizeof(uint16_t));
		for (i = 0; i < ptHeader->key_leng; i++)
		{
			pbuf_key[i] = ((uint16_t) tmp_buf_key[i * 2 + 1] << 8) | (uint16_t) tmp_buf_key[i * 2];
		}
		free(tmp_buf_key);
	}

	return	err_code;
}

/**
  * @brief	Get MS frame data
  * @param  ms_type   : type of the data
  * @param	pbuf_data : position of a buffer to save the data
  * @param	tx_cnt    : count of tx
  * @param	rx_cnt    : count of rx
  * @param	pbuf_key   : position of a buffer -> KEY
  * @retval	TRUE if all operation done correctly, FALSE if not.
  */
int fts_get_ms_frame_data(MSFrameType ms_type, int16_t *pbuf_data, int tx_cnt, int rx_cnt)
{
	int			err_code = FTS_NO_ERR;
	int			i;
	uint8_t		*temp_buf;
	uint16_t	tempOffsetAddr;

	switch (ms_type)
	{
	case MS_RAW:
		tempOffsetAddr = pSysInfo->msTchRawAddr;
		break;
	case MS_FILTER:
		tempOffsetAddr = pSysInfo->msTchFilterAddr;
		break;
	case MS_STRENGHT:
		tempOffsetAddr = pSysInfo->msTchStrenAddr;
		break;
	case MS_BASELINE:
		tempOffsetAddr = pSysInfo->msTchBaselineAddr;
		break;
	case MS_KEY_RAW:
		tempOffsetAddr = pSysInfo->keyRawAddr;
		break;
	case MS_KEY_FILTER:
		tempOffsetAddr = pSysInfo->keyFilterAddr;
		break;
	case MS_KEY_STRENGHT:
		tempOffsetAddr = pSysInfo->keyStrenAddr;
		break;
	case MS_KEY_BASELINE:
		tempOffsetAddr = pSysInfo->keyBaselineAddr;
		break;
	case FRC_RAW:
		tempOffsetAddr = pSysInfo->frcRawAddr;
		break;;
	case FRC_FILTER:
		tempOffsetAddr = pSysInfo->frcFilterAddr;
		break;;
	case FRC_STRENGHT:
		tempOffsetAddr = pSysInfo->frcStrenAddr;
		break;;
	case FRC_BASELINE:
		tempOffsetAddr = pSysInfo->frcBaselineAddr;
		break;
	default:
		break;
	}

	temp_buf = (uint8_t *) malloc(tx_cnt * rx_cnt * sizeof(int16_t));
	if (temp_buf == NULL)
	{
		err_code |= (FTS_ERR | FTS_ERR_MEM_ALLC);
		printf("\r\n[fts_get_ms_frame_data]FAILED[%08X]-Memory Allocation", err_code);
		free(temp_buf);
		return	err_code;
	}
	memset(temp_buf, 0x00, tx_cnt * rx_cnt * sizeof(int16_t));

	/* Load the frame data */
	fts_read_regU32(CMD_FRM_BUFF_R, tempOffsetAddr, BITS_16, temp_buf, tx_cnt * rx_cnt * sizeof(int16_t));
	for (i = 0; i < tx_cnt * rx_cnt; i++)
	{
		pbuf_data[i] = ((uint16_t) temp_buf[i * 2 + 1] << 8) | (uint16_t) temp_buf[i * 2];
	}
	free(temp_buf);

	return	err_code;
}

/**
  * @brief	Get MS frame data
  * @param  ms_type   : type of the data
  * @param	pbuf_tx : position of a buffer to save the data
  * @param	pbuf_rx : position of a buffer to save the data
  * @param	tx_cnt    : count of tx
  * @param	rx_cnt    : count of rx
  * @param	pbuf_key   : position of a buffer -> KEY
  * @retval TRUE if all operation done correctly, FALSE if not.
  */
int fts_get_ss_frame_data(SSFrameType ss_type, int16_t *pbuf_tx, int16_t *pbuf_rx, int tx_cnt, int rx_cnt)
{
	int			err_code = FTS_NO_ERR;
	int			i;
	uint8_t		*tmp_buf_tx, *tmp_buf_rx;
	uint16_t	tmpOffsetForce, tmpOffsetSense;

	switch (ss_type)
	{
	case SS_RAW:
		tmpOffsetForce = pSysInfo->ssTchTxRawAddr;
		tmpOffsetSense = pSysInfo->ssTchRxRawAddr;
		break;
	case SS_FILTER:
		tmpOffsetForce = pSysInfo->ssTchTxFilterAddr;
		tmpOffsetSense = pSysInfo->ssTchRxFilterAddr;
		break;
	case SS_STRENGHT:
		tmpOffsetForce = pSysInfo->ssTchTxStrenAddr;
		tmpOffsetSense = pSysInfo->ssTchRxStrenAddr;
		break;
	case SS_BASELINE:
		tmpOffsetForce = pSysInfo->ssTchTxBaselineAddr;
		tmpOffsetSense = pSysInfo->ssTchRxBaselineAddr;
		break;
	case SS_HVR_RAW:
		tmpOffsetForce = pSysInfo->ssHvrTxRawAddr;
		tmpOffsetSense = pSysInfo->ssHvrRxRawAddr;
		break;
	case SS_HVR_FILTER:
		tmpOffsetForce = pSysInfo->ssHvrTxFilterAddr;
		tmpOffsetSense = pSysInfo->ssHvrRxFilterAddr;
		break;
	case SS_HVR_STRENGHT:
		tmpOffsetForce = pSysInfo->ssHvrTxStrenAddr;
		tmpOffsetSense = pSysInfo->ssHvrRxStrenAddr;
		break;
	case SS_HVR_BASELINE:
		tmpOffsetForce = pSysInfo->ssHvrTxBaselineAddr;
		tmpOffsetSense = pSysInfo->ssHvrRxBaselineAddr;
		break;
	case SS_PRX_RAW:
		tmpOffsetForce = pSysInfo->ssPrxTxRawAddr;
		tmpOffsetSense = pSysInfo->ssPrxRxRawAddr;
		break;
	case SS_PRX_FILTER:
		tmpOffsetForce = pSysInfo->ssPrxTxFilterAddr;
		tmpOffsetSense = pSysInfo->ssPrxRxFilterAddr;
		break;
	case SS_PRX_STRENGHT:
		tmpOffsetForce = pSysInfo->ssPrxTxStrenAddr;
		tmpOffsetSense = pSysInfo->ssPrxRxStrenAddr;
		break;
	case SS_PRX_BASELINE:
		tmpOffsetForce = pSysInfo->ssPrxTxBaselineAddr;
		tmpOffsetSense = pSysInfo->ssPrxRxBaselineAddr;
		break;
	case SS_DET_RAW:
		tmpOffsetForce = pSysInfo->ssDetRawAddr;
		break;
	default:
		break;
	}

	if (pbuf_tx != NULL)
	{
		tmp_buf_tx = (uint8_t *) malloc(tx_cnt * sizeof(uint16_t));
		if (tmp_buf_tx == NULL)
		{
			err_code |= (FTS_ERR | FTS_ERR_MEM_ALLC);
			printf("\r\n[fts_get_ss_frame_data]FAILED[%08X]-Memory Allocation", err_code);
			free(tmp_buf_tx);
			return	err_code;
		}
		/* Load the frame data */
		fts_read_regU32(CMD_FRM_BUFF_R, tmpOffsetForce, BITS_16, tmp_buf_tx, tx_cnt * sizeof(uint16_t));
		for (i = 0; i < tx_cnt; i++)
		{
			pbuf_tx[i] = ((uint16_t) tmp_buf_tx[i * 2 + 1] << 8) | (uint16_t) tmp_buf_tx[i * 2];
		}
		free(tmp_buf_tx);
	}

	if (pbuf_rx != NULL)
	{
		tmp_buf_rx = (uint8_t *) malloc(rx_cnt * sizeof(uint16_t));
		if (tmp_buf_rx == NULL)
		{
			err_code |= (FTS_ERR | FTS_ERR_MEM_ALLC);
			printf("\r\n[fts_get_ss_frame_data]FAILED[%08X]-Memory Allocation", err_code);
			free(tmp_buf_rx);
			return	err_code;
		}
		/* Load the frame data */
		fts_read_regU32(CMD_FRM_BUFF_R, tmpOffsetSense, BITS_16, tmp_buf_rx, rx_cnt * sizeof(uint16_t));
		for (i = 0; i < rx_cnt; i++)
		{
			pbuf_rx[i] = ((uint16_t) tmp_buf_rx[i * 2 + 1] << 8) | (uint16_t) tmp_buf_rx[i * 2];
		}
		free(tmp_buf_rx);
	}

	return	err_code;
}

/**
  * @brief
  * @param  None
  * @retval TRUE if all operation done correctly, FALSE if not
  */
int fts_do_LPTimeCalib(void)
{
	uint8_t	regAdd[8] = {CMD_SYSTEM, CMD_SYS_SPECIAL_TUNE_CMD, CMD_SYS_SPECIAL_TUNE_CMD_LPTIMER_CAL, 0x00};
	int		reg_leng = 4;
	int		err_code = FTS_NO_ERR;

	fts_write_reg(regAdd, reg_leng);
	if ((err_code = fts_cmd_completion_check(EVTID_STATUS_REPORT, EVTID_RPTTYPE_CMD_ECHO, regAdd, reg_leng, 100)) != FTS_NO_ERR)
	{
		return	err_code;
	}

	return	err_code;
}

/**
  * @brief
  * @param  None
  * @retval TRUE if all operation done correctly, FALSE if not
  */
int fts_do_Ioffset(void)
{
	uint8_t	regAdd[8] = {CMD_SYSTEM, CMD_SYS_SPECIAL_TUNE_CMD, CMD_SYS_SPECIAL_TUNE_CMD_IOFFSET_TUNE, 0x00};
	int		reg_leng = 4;
	int		err_code = FTS_NO_ERR;

	fts_write_reg(regAdd, reg_leng);
	fts_delay(300);
	if ((err_code = fts_cmd_completion_check(EVTID_STATUS_REPORT, EVTID_RPTTYPE_CMD_ECHO, regAdd, reg_leng, 100)) != FTS_NO_ERR)
	{
		return	err_code;
	}

	return	err_code;
}

/**
  * @brief	LPTimer calibration and Ioffset tune.
  * @param  None
  * @retval TRUE if all operation done correctly, FALSE if not
  */
int fts_do_SpecialCalib(void)
{
	uint8_t	regAdd[8] = {CMD_SYSTEM, CMD_SYS_SPECIAL_TUNE_CMD, 0x00, 0x00};
	int		reg_leng = 4;
	int		err_code = FTS_NO_ERR;

	regAdd[2] = CMD_SYS_SPECIAL_TUNE_CMD_LPTIMER_CAL + CMD_SYS_SPECIAL_TUNE_CMD_IOFFSET_TUNE;
	fts_write_reg(regAdd, reg_leng);
	fts_delay(300);
	if ((err_code = fts_cmd_completion_check(EVTID_STATUS_REPORT, EVTID_RPTTYPE_CMD_ECHO, regAdd, reg_leng, 100)) != FTS_NO_ERR)
	{
		return	err_code;
	}

	return	err_code;
}

/**
  * @brief  Full panel initialization included auto-tune and saving flash.
  * @param  None
  * @retval TRUE if all operation done correctly, FALSE if not
  */
int fts_do_FullPanelInit(void)
{
	uint8_t	regAdd[8] = {CMD_SYSTEM, CMD_SYS_SPECIAL, CMD_SYS_SPECIAL_FULLPANEL_INIT, 0x00};
	int		reg_leng = 3;
	int		err_code = FTS_NO_ERR;

	fts_write_reg(regAdd, reg_leng);
	fts_delay(500);
	if ((err_code = fts_cmd_completion_check(EVTID_STATUS_REPORT, EVTID_RPTTYPE_CMD_ECHO, regAdd, reg_leng, 600)) != FTS_NO_ERR)
	{
		return	err_code;
	}

	return	err_code;
}

/**
  * @brief  Panel initialization.
  * @param  None
  * @retval TRUE if all operation done correctly, FALSE if not
  */
int fts_do_PanelInit(void)
{
	uint8_t	regAdd[8] = {CMD_SYSTEM, CMD_SYS_SPECIAL, CMD_SYS_SPECIAL_PANEL_INIT, 0x00};
	int		reg_leng = 3;
	int		err_code = FTS_NO_ERR;

	fts_write_reg(regAdd, reg_leng);
	fts_delay(500);
	if ((err_code = fts_cmd_completion_check(EVTID_STATUS_REPORT, EVTID_RPTTYPE_CMD_ECHO, regAdd, reg_leng, 300)) != FTS_NO_ERR)
	{
		return	err_code;
	}

	return	err_code;
}

/**
  * @brief  Auto-tune with necessary commands
  * @param  None
  * @retval TRUE if all operation done correctly, FALSE if not
  */
int fts_do_autotune(void)
{
	uint8_t	regAdd[8] = {CMD_SYSTEM, CMD_SYS_ATUNE, 0x00, 0x00};
	int		reg_leng = 4;
	int		err_code = FTS_NO_ERR;

	err_code = fts_do_LPTimeCalib();
	if (err_code != FTS_NO_ERR)
	{
		printf("\r\n[fts_do_autotune]FAILED[%08X]-LPTImer Calibration", err_code);
		return	err_code;
	}
	
	err_code = fts_do_Ioffset();
	if (err_code != FTS_NO_ERR)
	{
		printf("\r\n[fts_do_autotune]FAILED[%08X]-Ioffset", err_code);
		return	err_code;
	}
	
	regAdd[2] = ((CMD_SYS_SCANTYPE_MUTUAL | CMD_SYS_SCANTYPE_MUTUAL_LP) >> 8) & 0xFF;
	regAdd[3] = (CMD_SYS_SCANTYPE_MUTUAL | CMD_SYS_SCANTYPE_MUTUAL_LP) & 0xFF;
	fts_write_reg(regAdd, reg_leng);
	fts_delay(500);
	if ((err_code = fts_cmd_completion_check(EVTID_STATUS_REPORT, EVTID_RPTTYPE_CMD_ECHO, regAdd, reg_leng, 300)) != FTS_NO_ERR)
	{
		printf("\r\n[fts_do_autotune]FAILED[%08X]-MUTUAL", err_code);
		return	err_code;
	}

#ifdef	FTS_SUPPORT_SELF_SENSE
	regAdd[2] = ((CMD_SYS_SCANTYPE_SELF | CMD_SYS_SCANTYPE_SELF_LP) >> 8) & 0xFF;
	regAdd[3] = (CMD_SYS_SCANTYPE_SELF | CMD_SYS_SCANTYPE_SELF_LP) & 0xFF;
	fts_write_reg(regAdd, reg_leng);
	fts_delay(500);
	if ((err_code = fts_cmd_completion_check(EVTID_STATUS_REPORT, EVTID_RPTTYPE_CMD_ECHO, regAdd, reg_leng, 300)) != FTS_NO_ERR)
	{
		printf("\r\n[fts_do_autotune]FAILED[%08X]-SELF", err_code);
		return	err_code;
	}
#endif

	return	err_code;
}

/**
  * @brief  Save the config to Flash.
  * @param  None
  * @retval TRUE if all operation done correctly, FALSE if not
  */
int fts_save_config(void)
{
	uint8_t	regAdd[8] = {CMD_SYSTEM, CMD_SYS_SAVE2FLASH, CMD_SYS_SAVE2FLASH_FWCONFIG, 0x00};
	int		reg_leng = 3;
	int		status = FTS_NO_ERR;

	fts_write_reg(regAdd, reg_leng);
	fts_delay(200);
	if ((status = fts_cmd_completion_check(EVTID_STATUS_REPORT, EVTID_RPTTYPE_CMD_ECHO, regAdd, reg_leng, 100)) != FTS_NO_ERR)
	{
		status |= (FTS_ERR_SAVE_COMP | FTS_ERR);
		return	status;
	}

	return	status;
}

#ifdef FTS_SUPPORT_SAVE_COMP

/**
  * @brief  Save the compensation data to Flash.
  * @param  None
  * @retval None
  */
int fts_save2flash_compensation(void)
{
	uint8_t	regAdd[8] = {CMD_SYSTEM, CMD_SYS_SAVE2FLASH, CMD_SYS_SAVE2FLASH_CX, 0x00};
	int		reg_leng = 3;
	int		status = FTS_NO_ERR;

	fts_write_reg(regAdd, reg_leng);
	fts_delay(200);
	if ((status = fts_cmd_completion_check(EVTID_STATUS_REPORT, EVTID_RPTTYPE_CMD_ECHO, regAdd, reg_leng, 100)) != FTS_NO_ERR)
	{
		status |= (FTS_ERR_SAVE_COMP | FTS_ERR);
		return	status;
	}

	return	status;
}

#endif

/**
  * @brief  Control scan mode
  * @param  mode_sel     : scan mode
  * @param  mode_setting : selection of scan mode
  * @param  onoff        : on or off
  * @retval None
  */
int fts_scan_mode_control(uint8_t mode_sel, uint8_t mode_setting, int onoff)
{
	uint8_t	regAdd[8] = {CMD_SCAN_MODE, 0x00, 0x00, 0x00};
	int		reg_leng = 3;
	int		err_code = FTS_NO_ERR;

	if (mode_sel == CMD_SCAN_LPMODE)
		reg_leng = 2;

	regAdd[1] = mode_sel;
	if (onoff == ENABLE)
		regAdd[2] = mode_setting;

	fts_write_reg(regAdd, reg_leng);
	fts_delay(10);
	if ((err_code = fts_cmd_completion_check(EVTID_STATUS_REPORT, EVTID_RPTTYPE_CMD_ECHO, regAdd, reg_leng, 50)) != FTS_NO_ERR)
	{
		return	err_code;
	}

	return	err_code;
}

/**
  * @brief  Check hw reset pin when jig is able to control this pin.
  * @param	None
  * @retval None
  */
int fts_hw_reset_pin_check()
{
	uint8_t	regAdd[4] = {CMD_SYSTEM, CMD_SYS_SPECIAL, CMD_SYS_SPECIAL_SYSTEMRESET, 0x00};
	int		reg_leng = 3;
	int		err_code = FTS_NO_ERR;

	printf("\r\n[HW PIN CHECK] RESET PIN ...");
	if (fts_clear_FIFO() != FTS_NO_ERR)
	{
		printf("\r\n[fts_hw_reset_pin_check]Error-FIFO is not cleared");
		return	FTS_ERR;
	}

	{
		/*
		 * Notice!!
		 *		Drive the reset pin to "LOW" and keep for 10ms over, then drive it to "HIGH".
		 */
	}

	err_code = fts_cmd_completion_check(EVTID_CONTROLLER_READY, EVTID_RPTTYPE_CMD_ECHO, regAdd, reg_leng, 50);
	if (err_code != FTS_NO_ERR)
	{
		printf("\r\n[fts_hw_reset_pin_check]Error[%08X]-Not ready Reset Pin", err_code);
	}

	return	err_code;
}

/**
  * @brief  Check interrupt pin
  * @param	None
  * @retval None
  */
int fts_interrupt_pin_check()
{
	uint8_t	regAdd[8] = {CMD_SYSTEM, CMD_SYS_INTB, 0x01, 0x00};
	int		reg_leng = 3;
	int		err_code = FTS_NO_ERR;

	printf("\r\n[HW PIN CHECK] INTERRUPT PIN ...");
	if ((err_code = fts_systemreset(SYSTEM_RESET_SOFT, DISABLE)) != FTS_NO_ERR)
	{
		printf("\r\n[fts_interrupt_pin_check]Error[%08X]-System Reset", err_code);
		return	err_code;
	}
	fts_delay(50);
	fts_write_reg(regAdd, reg_leng);
	fts_delay(5);

	{
		/*
		 * Check interrupt pin whether it is low or not.
		 *     If not low, return ERROR.
		 */
	}

	if ((err_code = fts_clear_FIFO()) != FTS_NO_ERR)
	{
		printf("\r\n[fts_interrupt_pin_check]Error[%08X]-FIFO is not cleared", err_code);
		return	err_code;
	}
	fts_delay(5);

	{
		/*
		 * Check interrupt pin whether it is high or not.
		 *     If not high, return ERROR.
		 */
	}

	return	FTS_NO_ERR;
}

/**
  * @brief  Check I2C interface under SPI interface
  * @param	None
  * @retval None
  */
int fts_i2c_interface_check()
{
	uint8_t	regAdd[8] = {CMD_SYSTEM, CMD_SYS_INTB, 0x01, 0x00};
	int		reg_leng = 3;
	int		err_code = FTS_NO_ERR;

	/*
	 * IMPORTANT!!!
	 *     Communication by SPI 4-WIRE interface.
	 */
	{
		/*
		 * GPI2 Pin Control to HIGH
		 */
	}

	if ((err_code = fts_systemreset(SYSTEM_RESET_SOFT, DISABLE)) != FTS_NO_ERR)
	{
		printf("\r\n[fts_interrupt_pin_check]Error-System Reset");
		return	err_code;
	}
	fts_delay(50);

	/*
	 *  IMPORTANT!!!
	 *    Read the system information by I2C interface.
	 *      If can't treat the information by I2C or Version is not correct
	 *      retrun error.
	 */
	printf("\r\n[FTS]System Information");
	if ((err_code = fts_read_sysInfo()) != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR[%08X]-sysInfo", err_code);
		return	err_code;
	}
	printf("\r\n[FTS] Version Information.");
	printf("\r\n      Version : FW [%04X], Config [%04X], Extenal [%4X]", pSysInfo->fwVer, pSysInfo->cfgVer, pSysInfo->releaseInfo[0] | (pSysInfo->releaseInfo[1] << 8));
	printf("\r\n      Channel : TX [%04X], RX [%04X]", pSysInfo->scrTxLen, pSysInfo->scrRxLen);

	/*
	 *     If version is not correct, retrun error.
	 */

	return	FTS_NO_ERR;
}

#ifdef	FTS_SUPPORT_ITOTEST

/**
  * @brief  Proceed the ITO TEST
  * @param	None
  * @retval None
  */
int fts_panel_ito_command(void)
{
	uint8_t	cmd_data[18] = {0x89, 0x86, 0x1A, 0x1F, 0x04, 0xD8, 0x08, 0x20, 0x00, 0x02, 0x00, 0x1F, 0x00, 0x24, 0x60, 0x06, 0x00, 0x00};
	int		data_leng = 18;
	int		err_flag = FTS_NO_ERR;

	if ((err_flag = fts_write_regU32(CMD_CONFIG_W, 0x00C8, BITS_16, cmd_data, data_leng)) != FTS_NO_ERR)
	{
		return	err_flag;
	}
	return	err_flag;
}

#ifdef FTS_SUPPORT_MICRO_SHORT
/*
  * @brief  Pre-saved reference MsRaw Gap data for the micro short test.
  *         Please should get the reference data (Reference_LF_MsRaw_Gap) to LG Display.
 */
const int16_t Reference_LF_MsRaw_Gap[FTS_TX_LENGTH][FTS_RX_LENGTH - 1] =
		{
			{-1896, 872, -448, -410, -51, 69, -26, 141, -102, 184, 2, -227, 355, -313, -9, 185, -122, -128, 28, -49, 343, -362, 362, -148, -261, -91, 156, 292, -313, 8, 2015},
			{-507, 988, -454, -429, -118, -63, 116, 17, -118, 347, -5, -345, 521, -492, 104, 175, -261, 46, 59, -138, 859, -613, 674, -589, -421, -29, 56, 861, -859, 60, 969},
			{-526, 973, -445, -439, -121, -59, 125, 20, -126, 341, -7, -333, 535, -503, 102, 197, -283, 52, 39, -136, 918, -674, 674, -586, -395, -37, 32, 864, -869, 66, 972},
			{-541, 970, -444, -438, -121, -59, 151, -6, -136, 348, -7, -321, 554, -515, 100, 184, -269, 45, 41, -114, 884, -674, 674, -587, -391, -34, 26, 803, -829, 96, 966},
			{-562, 972, -446, -428, -123, -58, 145, 4, -137, 359, -24, -312, 552, -511, 124, 150, -255, 32, 48, -113, 871, -613, 613, -587, -384, -23, 15, 857, -893, 61, 1002},
			{-572, 980, -458, -423, -114, -65, 152, 4, -136, 357, -22, -302, 561, -523, 116, 173, -269, 25, 31, -102, 875, -674, 613, -530, -401, 7, 38, 825, -847, 99, 994},
			{-599, 982, -455, -427, -108, -65, 150, -1, -156, 360, -6, -312, 554, -507, 123, 173, -281, 23, 43, -90, 865, -674, 613, -567, -379, -10, 42, 853, -870, 78, 1038},
			{-616, 993, -472, -415, -112, -48, 142, 14, -154, 365, -25, -300, 563, -520, 123, 161, -277, 60, 22, -70, 887, -735, 613, -542, -390, -5, 47, 829, -841, 111, 983},
			{-634, 984, -471, -415, -117, -40, 142, 19, -152, 359, -25, -279, 574, -509, 120, 121, -258, 37, 51, -132, 859, -674, 613, -527, -378, -7, 30, 821, -874, 75, 1050},
			{-638, 990, -464, -413, -96, -46, 137, 0, -144, 351, -4, -299, 585, -509, 109, 145, -264, 70, 0, -144, 871, -674, 613, -504, -361, -22, 11, 815, -884, 81, 1052},
			{-663, 1013, -451, -427, -95, -43, 136, 15, -152, 342, -4, -291, 567, -505, 95, 184, -258, 12, 33, -168, 895, -674, 674, -563, -361, -19, -1, 822, -882, 62, 1072},
			{-684, 1027, -459, -401, -93, -57, 129, 9, -146, 371, -25, -298, 553, -490, 95, 143, -270, 50, -4, -131, 913, -674, 674, -564, -373, -26, 23, 818, -879, 76, 1058},
			{-705, 1044, -490, -397, -92, -14, 115, -11, -140, 364, -5, -318, 545, -524, 86, 186, -285, 40, 27, -132, 879, -613, 613, -567, -378, -7, 32, 798, -863, 84, 1094},
			{-647, 1044, -482, -407, -117, -43, 130, 1, -134, 359, -2, -331, 520, -502, 105, 205, -290, 39, 20, -129, 890, -674, 674, -571, -384, -12, 46, 799, -863, 84, 1102},
			{-1904, 846, -391, -412, -110, -65, 114, -6, -125, 360, -28, -288, 548, -502, 96, 181, -260, 45, 12, -125, 886, -674, 674, -596, -382, -10, 40, 826, -858, 162, 2272}
		};

/**
  * @brief  Do the micro short test.
  * @param	None
  * @retval None
  */
int fts_panel_micro_short_test(int16_t *pbuf_lfRaw, int16_t *pbuf_data)
{
	uint8_t	val[8], regAdd[8] = {CMD_SYSTEM, CMD_SYS_ITO_TEST, 0x00, 0x08};
	int		reg_leng = 4;
	int		cnt = 100;
	int		err_flag = FTS_NO_ERR;
	int		row, col, offset;

	int16_t	lf_MsRaw_Gap[FTS_TX_LENGTH][FTS_RX_LENGTH - 1];
	int16_t	diff_data[FTS_TX_LENGTH][FTS_RX_LENGTH - 1], res_data[FTS_TX_LENGTH][FTS_RX_LENGTH - 1];
	int16_t	AvgColVal[FTS_RX_LENGTH - 1];
	int32_t	SumColVal[FTS_RX_LENGTH - 1];

	printf("\r\n[Micro Short Test]System Reset");
	err_flag = fts_systemreset(SYSTEM_RESET_SOFT, ENABLE);
	if (err_flag != FTS_NO_ERR)
	{
		printf("\r\n[Micro Short Test]ERROR-System Reset");
		return	err_flag;
	}
	printf("\r\n[Micro Short Test]Special Calibration");
	if ((err_flag = fts_do_SpecialCalib()) != FTS_NO_ERR)
	{
		printf("\r\n[Micro Short Test]ERROR-Special Calibration");
		return	err_flag;
	}
	printf("\r\n[Micro Short Test]Command for micro short test");
	fts_write_reg(regAdd, reg_leng);
	fts_delay(200);
	err_flag = fts_cmd_completion_check(EVTID_STATUS_REPORT, EVTID_RPTTYPE_CMD_ECHO, regAdd, reg_leng, 100);
	if (err_flag != FTS_NO_ERR)
	{
		printf("\r\n[Micro Short Test]Error[%08X]-Not echo event for micro short command", err_flag);
		return	err_flag;
	}

	memset(pbuf_lfRaw, 0x00, pSysInfo->scrTxLen * pSysInfo->scrRxLen * sizeof(int16_t));
	err_flag = fts_get_ms_frame_data(MS_RAW, pbuf_lfRaw, pSysInfo->scrTxLen, pSysInfo->scrRxLen);
	if (err_flag != FTS_NO_ERR)
	{
		printf("\r\n[Micro Short Test]ERROR-raw data for micro short");
		return	err_flag;
	}

	/* Calculate the horizontal adjacent matrix of lf_MsRaw */
	memset(SumColVal, 0, (pSysInfo->scrRxLen - 1) * sizeof(int32_t));
	for (row = 0; row < pSysInfo->scrTxLen; row++)
	{
		offset = row * pSysInfo->scrRxLen;
		for (col = 0; col < (pSysInfo->scrRxLen - 1); col++)
		{
			lf_MsRaw_Gap[row][col] = pbuf_lfRaw[offset + col] - pbuf_lfRaw[offset + col + 1];
			diff_data[row][col] = lf_MsRaw_Gap[row][col] - Reference_LF_MsRaw_Gap[row][col];
			SumColVal[col] += diff_data[row][col];
		}
	}

	/* Calculate the average in Rx channel */
	for (col = 0; col < (pSysInfo->scrRxLen - 1); col++)
	{
		AvgColVal[col] = SumColVal[col] / pSysInfo->scrTxLen;
	}

	/*
	 * Acquire the final data (res_data) by difference of diff_data and AvgColVal.
	 *     - Check the res_data if there is out of limits.
	 */
	for (row = 0; row < pSysInfo->scrTxLen; row++)
	{
		offset = row * (pSysInfo->scrRxLen - 1);
		for (col = 0; col < (pSysInfo->scrRxLen - 1); col++)
		{
			pbuf_data[offset + col] = diff_data[row][col] - AvgColVal[col];
		}
	}

	return	err_flag;
}

#endif

/**
  * @brief  Proceed the ITO TEST
  * @param	None
  * @retval None
  */
int fts_panel_ito_test(void)
{
	uint8_t	val[8], regAdd[8] = {CMD_SYSTEM, CMD_SYS_ITO_TEST, 0xFF, 0x01};
	int		reg_leng = 4;
	int		cnt = 100;
	int		res = TRUE, err_flag = FTS_NO_ERR;
	int		i;
	uint8_t	*errortypes[9] = {"Short - Force to GND", "Short - Sense to GND", "Short - Force to VDD", "Short - Sense to VDD",
								"Short - Force to Force", "Short - Sense to Sense", "Open - Force", "Open-Sense", "Open-KeyS2S"};

#ifdef	FTS_SUPPORT_HF_RAW_ADJ
	int16_t	hf_raw[FTS_TX_LENGTH * FTS_RX_LENGTH], hf_raw_gap_vert[FTS_TX_LENGTH * FTS_RX_LENGTH], hf_raw_gap_horiz[FTS_TX_LENGTH * FTS_RX_LENGTH];
	int		j, offset1, offset2;
#endif

	/*
	 * ITO SHORT TEST
	 */
	printf("\r\n[ITO_TEST]System Reset");
	if ((err_flag = fts_systemreset(SYSTEM_RESET_SOFT, ENABLE)) != FTS_NO_ERR)
	{
		printf("\r\n[ITO_TEST]ERROR-System Reset");
		return	err_flag;
	}
	printf("\r\n[ITO_TEST]Special Calibration");
	if ((err_flag = fts_do_SpecialCalib()) != FTS_NO_ERR)
	{
		printf("\r\n[ITO_TEST]ERROR-Special Calibration");
		return	err_flag;
	}
	printf("\r\n[ITO_TEST]Command for ito test");
	fts_write_reg(regAdd, reg_leng);
	fts_delay(200);
	while (cnt--)
	{
		fts_delay(10);
		fts_read_reg(fts_fifo_addr, 1, val, FTS_EVENT_SIZE);
		if ((val[0] == EVTID_STATUS_REPORT) && (val[1] == EVTID_RPTTYPE_CMD_ECHO))
		{
			res = TRUE;
			for (i = 0; i < reg_leng; i++)
			{
				if (val[i + 2] != regAdd[i])
					res = FALSE;
			}
			if (res == TRUE)
			{
				printf("\r\n[ITO_TEST]Finished [%02x %02x %02x %02x %02x %02x %02x %02x]",
							val[0], val[1], val[2], val[3], val[4], val[5], val[6], val[7]);
				break;
			}
			else
			{
				printf("\r\n[ITO_TEST]INVALID [%02x %02x %02x %02x %02x %02x %02x %02x]",
							val[0], val[1], val[2], val[3], val[4], val[5], val[6], val[7]);
			}
		}
		else if (val[0] == EVTID_ERROR_REPORT)
		{
			switch (val[1])
			{
				case ITO_FORCE_SHRT_GND:
				case ITO_SENSE_SHRT_GND:
				case ITO_FORCE_SHRT_VDD:
				case ITO_SENSE_SHRT_VDD:
				case ITO_FORCE_SHRT_FORCE:
				case ITO_SENSE_SHRT_SENSE:
				case ITO_FORCE_OPEN:
				case ITO_SENSE_OPEN:
				case ITO_KEY_OPEN:
					err_flag |= (FTS_ERR | FTS_ERR_ITO_TEST);
					printf("\r\n[ITO_TEST]DETECTED-Error Type : %s, Channel : %d", errortypes[val[1]-0x60], val[2]);
					break;
				default:
					printf("\r\n[ITO_TEST]INVALID [%02x %02x %02x %02x %02x %02x %02x %02x]",
								val[0], val[1], val[2], val[3], val[4], val[5], val[6], val[7]);
					break;
			}
		}

	}

	if (cnt <= 0)
	{
		printf("\r\n[ITO_TEST] Time Over");
		err_flag |= (FTS_ERR | FTS_ERR_EVT_TIMEOVER);
	}

/*
 * Collect HF Raw and Calculate the gap of HF Raw.
 * Definitely this process has to be started after ITO SHORT test without any additional instruction.
 */
#ifdef	FTS_SUPPORT_HF_RAW_ADJ
	printf("\r\n[HF_RAW_GAP]Collect HF Raw data");
	memset(hf_raw, 0x00, pSysInfo->scrTxLen * pSysInfo->scrRxLen * sizeof(int16_t));
	if (fts_get_ms_frame_data(MS_RAW, hf_raw, pSysInfo->scrTxLen, pSysInfo->scrRxLen) != FTS_NO_ERR)
	{
		printf("\r\n[HF_RAW]ERROR- HF raw data");
	}

	// Calculate the horizontal adjacent matrix of HF Raw
	for (i = 0; i < pSysInfo->scrTxLen; i++)
	{
		offset1 = i * pSysInfo->scrRxLen;
		for (j = 0; j < (pSysInfo->scrRxLen - 1); j++)
		{
			hf_raw_gap_horiz[offset1 + j] = abs(hf_raw[offset1 + j] - hf_raw[offset1 + j + 1]);
		}
	}

	// Calculate the vertical adjacent matrix of HF Raw
	for (i = 0; i < (pSysInfo->scrTxLen - 1); i++)
	{
		offset1 = i * pSysInfo->scrRxLen;
		offset2 = (i + 1) * pSysInfo->scrRxLen;
		for (j = 0; j < pSysInfo->scrRxLen; j++)
		{
			hf_raw_gap_vert[offset1 + j] = abs(hf_raw[offset1 + j] - hf_raw[offset2 + j]);
		}
	}
#endif

	return	err_flag;
}

#endif

#ifdef SPECIAL_COMMAND_FOR_EVT1A

/**
  * @brief  Special command to resolve self idle auto-tune fail.
  * 		This function will be applied for EVT1-A event.
  * @param	None
  * @retval None
  */
int fts_special_cmd_for_evt1A(void)
{
	uint8_t	regAdd[8] = {FTS_CMD_HW_REG_W, 0x20, 0x01, 0xF7, 0x6A, 0x20};
	int		reg_leng = 6;
	int		err_flag = FTS_NO_ERR;

	printf("\r\n[COMMAND_EVT1A]Special command for evt1-A");
	fts_write_reg(regAdd, reg_leng);
	fts_delay(50);

	printf("\r\n[COMMAND_EVT1A]Save Config");
	if ((err_flag = fts_save_config()) != FTS_NO_ERR)
	{
		printf("\r\n[COMMAND_EVT1A]ERROR-Save Config");
		return	err_flag;
	}

	printf("\r\n[COMMAND_EVT1A]System Reset");
	if ((err_flag = fts_systemreset(SYSTEM_RESET_HARD, ENABLE)) != FTS_NO_ERR)
	{
		printf("\r\n[COMMAND_EVT1A]ERROR-System Reset");
		return	err_flag;
	}

	return	err_flag;
}

#endif

/**
  * @brief  To inspect and check test items of the panel.
  * @param  None
  * @retval None
  */
int fts_panel_test(void)
{
	int			i, res;
	int16_t		ms_raw[FTS_TX_LENGTH * FTS_RX_LENGTH], ms_jitter[FTS_TX_LENGTH * FTS_RX_LENGTH];
	int16_t		ss_raw_tx[FTS_TX_LENGTH], ss_raw_rx[FTS_RX_LENGTH];

#ifdef FTS_METHOD_PRE_SAVED
	int8_t		ms_cx[FTS_TX_LENGTH * FTS_RX_LENGTH];
	uint16_t	ss_ix_tx[FTS_TX_LENGTH], ss_ix_rx[FTS_RX_LENGTH];
#endif
#ifdef FTS_SUPPORT_CM_CP_CAPACITANCE
	uint16_t	ms_cap[FTS_TX_LENGTH * FTS_RX_LENGTH], ss_cap_tx[FTS_TX_LENGTH], ss_cap_rx[FTS_RX_LENGTH];
#endif
#ifdef FTS_SUPPORT_LP_SS_COMP
	uint16_t	ss_ix_idle_tx[FTS_TX_LENGTH];
#endif
#ifdef FTS_SUPPORT_LP_SS_RAW
	uint16_t	ss_lp_raw_tx[FTS_TX_LENGTH];
#endif
#ifdef FTS_SUPPORT_LP_MS_RAW
	int16_t		ms_lp_raw[FTS_TX_LENGTH];
#endif
#ifdef FTS_SUPPORT_MICRO_SHORT
	int16_t		micro_short_buf[FTS_TX_LENGTH * (FTS_RX_LENGTH - 1)];
	int16_t		ms_raw_lf[FTS_TX_LENGTH * FTS_RX_LENGTH];
#endif
#ifdef	FTS_GET_SERIALNUM
	uint8_t		serial_num[DIE_INFO_SIZE];
#endif

	power_on();
	fts_delay(50);

#ifdef	FTS_SUPPORT_FW_DOWNLOAD
	flashProcedure(0, 0);
#endif

#ifdef	FTS_SUPPORT_HW_PIN_CHECK
	fts_hw_reset_pin_check();
	fts_interrupt_pin_check();
#endif

	printf("\r\n[FTS]#System Reset");
	if ((res = fts_systemreset(SYSTEM_RESET_SOFT, ENABLE)) != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR[%08X]-System Reset", res);
		return	res;
	}

#ifdef SPECIAL_COMMAND_FOR_EVT1A
	printf("\r\n[FTS]#Special command for EVT1-A");
	if ((res = fts_special_cmd_for_evt1A()) != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR[%08X]-Special command for EVT1-A", res);
		return	res;
	}
#endif

	printf("\r\n[FTS]#Read Chip ID");
	if ((res = fts_read_chip_id()) != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR[%08X]-read chip id", res);
		return	res;
	}

	printf("\r\n[FTS]#Interrupt Disable");
	if ((res = fts_interrupt_control(DISABLE)) != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR[%08X]-Interrupt Disable", res);
		return	res;
	}

	printf("\r\n[FTS]#System Information");
	if ((res = fts_read_sysInfo()) != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR[%08X]-sysInfo", res);
		return	res;
	}
	printf("\r\n    Version : FW [%04X], Config [%04X], Extenal [%04X]", pSysInfo->fwVer, pSysInfo->cfgVer, pSysInfo->releaseInfo[0] | (pSysInfo->releaseInfo[1] << 8));
	printf("\r\n    Channel : TX [%04X], RX [%04X]", pSysInfo->scrTxLen, pSysInfo->scrRxLen);

#ifdef	FTS_GET_SERIALNUM
	printf("\r\n    Serial Number : ");
	for (i = 0; i < DIE_INFO_SIZE; i++)
	{
		serial_num[i] = pSysInfo->dieInfo[DIE_INFO_SIZE - i - 1];
		printf("%02X", serial_num[i]);
	}
#endif

#ifdef	FTS_SUPPORT_ITOTEST
	printf("\r\n[FTS]#PANEL ITO TEST");
	if ((res = fts_panel_ito_test()) != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR[%08X]-ITO TEST", res);
		return	res;
	}
 #ifdef FTS_SUPPORT_MICRO_SHORT
	/* Please save "ms_raw_lf" to log to make the Reference_LF_MsRaw_Gap */
	printf("\r\n[FTS]#PANEL MICRO SHORT TEST\r\n");
	res = fts_panel_micro_short_test(ms_raw_lf, micro_short_buf);
	if (res != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR[%08X]-MICRO SHORT TEST", res);
		return	res;
	}
 #endif
#endif

#if defined (FTS_METHOD_PRE_SAVED) || defined (MACHINE_OTHERS)

	printf("\r\n[FTS]#System Reset");
	if ((res = fts_systemreset(SYSTEM_RESET_SOFT, ENABLE)) != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR[%08X]-System Reset", res);
		return	res;
	}

 #ifdef FTS_SEL_AUTOTUNE_FULLINIT
	printf("\r\n[FTS]#Full Panel Init.");
	if ((res = fts_do_FullPanelInit()) != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR[%08X]-Full Panel Init", res);
		return	res;
	}
 #else
  #ifdef FTS_SEL_AUTOTUNE_ONLY
	printf("\r\n[FTS]#Auto-tune procedures");
	if ((res = fts_do_autotune()) != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR[%08X]-Auto-tune procedures", res);
		return	res;
	}
  #endif

  #ifdef FTS_SUPPORT_SAVE_COMP
	printf("\r\n[FTS]#Save to Flash");
	if ((res = fts_save2flash_compensation()) != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR[%08X]-Save to Flash", res);
		return	res;
	}
  #endif
 #endif

	printf("\r\n[FTS]#Read MS CX");
	res = fts_get_ms_comp_data(LOAD_CX_MS_LOW_POWER, ms_cx);
	if (res != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR[%08X]-Read MS CX", res);
		return	res;
	}

	printf("\r\n[FTS]#Read SS IX of Active mode");
	res = fts_get_ss_totalcomp_data(LOAD_PANEL_CX_TOT_SS_TOUCH, ss_ix_tx, ss_ix_rx);
	if (res != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR[%08X]-Read SS IX of Active mode", res);
		return	res;
	}

 #ifdef FTS_SUPPORT_LP_SS_COMP
	printf("\r\n[FTS]#Read SS IX of Idle mode");
	res = fts_get_ss_totalcomp_data(LOAD_PANEL_CX_TOT_SS_TOUCH_IDLE, ss_ix_idle_tx, NULL);
	if (res != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR[%08X]-Read SS IX of Idle mode", res);
		return	res;
	}
 #endif

 #ifdef FTS_SUPPORT_CM_CP_CAPACITANCE
	printf("\r\n[FTS]#Read MS Capacitance");
	res = fts_get_ms_capacitance(LOAD_CM_CAPACITANCE, ms_cap);
	if (res != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR[%08X]-Read MS Capacitance", res);
		return	res;
	}

	printf("\r\n[FTS]#Read SS Capacitance");
	res = fts_get_ss_capacitance(LOAD_CP_CAPACITANCE, ss_cap_tx, ss_cap_rx);
	if (res != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR[%08X]-Read SS Capacitance", res);
		return	res;
	}
 #endif

#endif

#ifdef FTS_METHOD_GOLDEN_VALUE

 #if defined (MACHINE_FINAL_INSPECTION) || defined (MACHINE_OQC_INSPECTION)
	printf("\r\n[FTS]#System Reset");
	if ((res = fts_systemreset(SYSTEM_RESET_SOFT, ENABLE)) != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR[%08X]-System Reset", res);
		return	res;
	}

	printf("\r\n[FTS]#Interrupt Disable");
	if ((res = fts_interrupt_control(DISABLE)) != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR[%08X]-Interrupt Disable", res);
		return	res;
	}

  #ifdef MACHINE_FINAL_INSPECTION
	printf("\r\n[FTS]#Panel Init.");
	if((res = fts_do_PanelInit()) != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR[%08X]-Panel Init", res);
		return	res;
	}
  #endif
 #endif

#endif

	/*
	 * Sense On
	 */
	printf("\r\n[FTS]#Sense On");
	if ((res = fts_scan_mode_control(CMD_SCAN_ACTIVE, CMD_SCAN_ACTIVE_MULTI, ENABLE)) != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR[%08X]-Sense On", res);
		return	res;
	}

#ifdef FTS_SUPPORT_CURRENT_MEASUREMENT_IDLE
	{
		fts_delay(500);
		/*
		 * CURRENT MEASUREMENT : Idle mode.
		 */
	}
#endif

	/*
	 * Locked Active Mode
	 */
	printf("\r\n[FTS]#Locked active mode");
	if ((res = fts_scan_mode_control(CMD_SCAN_LOCKED, CMD_SCAN_LOCKED_ACTIVE, ENABLE)) != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR[%08X]-Locked active", res);
		return	res;
	}
	fts_delay(500);

#ifdef FTS_SUPPORT_CURRENT_MEASUREMENT_ACTIVE
	{
		/*
		 * CURRENT MEASUREMENT : Active mode.
		 */
	}
#endif

#if	0
	printf("\r\n[FTS]#Sense Off");
	if (fts_scan_mode_control(CMD_SCAN_ACTIVE, CMD_SCAN_ACTIVE_MULTI, DISABLE) != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR-Sense Off");
		return	FALSE;
	}
#endif

	printf("\r\n[FTS]#Read all of raw data");
	res = fts_get_SyncFrame_data(LOAD_SYNC_FRAME_RAW, ms_raw, ss_raw_tx, ss_raw_rx, NULL);
	if (res != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR[%08X]-Read Raw data", res);
		return	res;
	}

	printf("\r\n[FTS]#Read all of jitter (strength) data");
	res = fts_get_SyncFrame_data(LOAD_SYNC_FRAME_STRENGTH, ms_jitter, NULL, NULL, NULL);
	if (res != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR[%08X]-Read jitter (strength) data", res);
		return	res;
	}

#if 0
	/* Enter the LP mode */
	printf("\r\n[FTS]#Enter LP mode");
	if ((res = fts_scan_mode_control(CMD_SCAN_LPMODE, 0x00, DISABLE)) != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR-LP mode");
		return	res;
	}
#endif

#ifdef FTS_SUPPORT_LP_SS_RAW
	/*
	 * Change LP detect mode and Get self raw data of LP detect mode.
	 */
	printf("\r\n[FTS]#Locked LP detect");
	if ((res = fts_scan_mode_control(CMD_SCAN_LOCKED, CMD_SCAN_LOCKED_LP_DETECT, ENABLE)) != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR-Locked LP detect");
		return	res;
	}
	fts_delay(500);

 #ifdef FTS_SUPPORT_CURRENT_MEASUREMENT_LP_DETECT
	{
		/*
		 * CURRENT MEASUREMENT : Low Power Idle mode.
		 */
	}
 #endif

	printf("\r\n[FTS]#Collect LP Detect SS force raw data");
	if (fts_get_ss_frame_data(SS_DET_RAW, ss_lp_raw_tx, NULL, pSysInfo->scrTxLen, pSysInfo->scrRxLen) != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR-LP SS Raw_Tx");
		return	FALSE;
	}
#endif

#ifdef FTS_SUPPORT_LP_MS_RAW
	/*
	 * Change LP Active mode and Get mutual raw data of LP active mode.
	 */
	printf("\r\n[FTS]#Locked LP Active");
	if ((res = fts_scan_mode_control(CMD_SCAN_LOCKED, CMD_SCAN_LOCKED_LP_ACTIVE, ENABLE)) != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR-Locked LP detect");
		return	res;
	}
	fts_delay(500);

 #ifdef FTS_SUPPORT_CURRENT_MEASUREMENT_LP_ACTIVE
	{
		/*
		 * CURRENT MEASUREMENT : Low Power Active mode.
		 */
	}
 #endif

	printf("\r\n[FTS]#Collect LP Active MS Raw");
	if ((res = fts_get_SyncFrame_data(LOAD_SYNC_FRAME_RAW, ms_lp_raw, NULL, NULL, NULL)) != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR-LP Active MS Raw");
		return	FALSE;
	}
 #endif

#ifdef FTS_SUPPORT_CURRENT_MEASUREMENT_SLEEP
	{
		printf("\r\n[FTS]#Sense Off for current measurement of sleep mode");
		if (fts_scan_mode_control(CMD_SCAN_ACTIVE, CMD_SCAN_ACTIVE_MULTI, DISABLE) != FTS_NO_ERR)
		{
			printf("\r\n[FTS]ERROR-Sense Off");
			return	FALSE;
		}
		fts_delay(200);

		/*
		 * CURRENT MEASUREMENT : Sleep mode.
		 */
	}
#endif

#ifdef FTS_SUPPORT_I2C_INTERFACE_CHECK
	printf("\r\n[FTS]I2C interface check");
	if ((res = fts_i2c_interface_check()) != FTS_NO_ERR)
	{
		printf("\r\n[FTS]ERROR[%08X]-I2C INTERFACE CHECK", res);
		return	res;
	}
#endif

	power_off();

	printf("\r\n[FTS]Test finished.");

	return	FTS_NO_ERR;
}

/**
  * @brief  Initialize with Auto-tune sequence only for touch operation.
  * @param  None
  * @retval None
  */
int fts_init(void)
{
	power_on();
	fts_delay(50);

	if (fts_systemreset(SYSTEM_RESET_SOFT, ENABLE) != FTS_NO_ERR)
	{
		printf("\r\n[FTS]FAILED-System Reset");
		return	FTS_ERR;
	}

	if (fts_read_chip_id() != FTS_NO_ERR)
	{
		printf("\r\n[FTS]FAILED-read chip id");
		return	FTS_ERR;
	}

	fts_interrupt_control(DISABLE);
	fts_delay(1);

	if (fts_do_autotune() != FTS_NO_ERR)
	{
		printf("\r\n[FTS]FAILED-Auto-tune");
		return	FTS_ERR;
	}

	if (fts_scan_mode_control(CMD_SCAN_ACTIVE, CMD_SCAN_ACTIVE_MULTI, ENABLE) != FTS_NO_ERR)
	{
		printf("\r\n[FTS]FAILED-Sense On");
		return	FTS_ERR;
	}

	fts_interrupt_control(ENABLE);
	printf("\r\n[FTS]Interrupt Enable.");

	return	FTS_ERR;
}

/**
  * @}
  */

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/

