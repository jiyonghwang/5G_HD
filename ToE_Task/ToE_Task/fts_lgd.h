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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef	__FTS_LGD_H__
#define	__FTS_LGD_H__

/* Global typedef -----------------------------------------------------------*/
typedef unsigned int	uint_t;
#if	1
 typedef unsigned short	uint16_t;
 typedef unsigned char	uint8_t;

 typedef unsigned long	uint32_t;
 typedef char			int8_t;
 typedef short			int16_t;
 typedef long			int32_t;
#endif

/** @addtogroup FTS_Standard_Driver
  * @{
  */

/**
  * @brief  FTS Configuration definitions
  */
#define	FST1
#define	LGD_TOE

#if	defined (FST1)
 #define FTS_ID0							0x36
 #define FTS_ID1							0x39
#endif

/**
 * @brief	Select the interface for touch
 */
//#define	I2C_INTERFACE
#ifdef	I2C_INTERFACE
 #define FTS_I2C_ADDR						0x92
 #define I2C_TIMEOUT						3000
#else
 #define SPI4_WIRE
 #define SPI_DELAY_CS						10
 //#define SPI_CLOCK_FREQ						7000000
 #define SPI_TIMEOUT						3000
#endif

#define FTS_FIFO_MAX						32
#define FTS_EVENT_SIZE						8

#ifdef	I2C_INTERFACE
 #define FTS_FIFO_ADDR						0x86
 #define FTS_FIFO_READALL					0x86
#else
 #define FTS_FIFO_ADDR						0x87
 #define FTS_FIFO_READALL					0x87
#endif

#ifdef I2C_INTERFACE
 #define DUMMY								0
 #define DUMMY_HW_REG						0
 #define DUMMY_FRAMEBUFFER					0
 #define DUMMY_CONFIG						0
 #define DUMMY_FIFO							0
#else
 #define DUMMY								1
 #define DUMMY_HW_REG						1
 #define DUMMY_FRAMEBUFFER					1
 #define DUMMY_CONFIG						1
 #define DUMMY_FIFO							1
#endif

/**
  * @brief  Definitions for Inspection Machine.
  */
#define MACHINE_OTHERS
//#define MACHINE_FINAL_INSPECTION
//#define MACHINE_OQC_INSPECTION

//#define FTS_METHOD_GOLDEN_VALUE
#ifndef FTS_METHOD_GOLDEN_VALUE
 #define FTS_METHOD_PRE_SAVED
#endif

#if	defined (MACHINE_OTHERS)
 #define FTS_SEL_AUTOTUNE_ONLY
#elif defined (MACHINE_FINAL_INSPECTION) || defined (MACHINE_OQC_INSPECTION)
 #if defined (MACHINE_FINAL_INSPECTION) && defined (FTS_METHOD_PRE_SAVED)
  #define FTS_SEL_AUTOTUNE_FULLINIT
 #endif
#endif

//#define SPECIAL_COMMAND_FOR_EVT1A

/**
  * @brief  Definitions for FTS Features and Test items
  */
//#define FTS_SUPPORT_FW_DOWNLOAD
#define FTS_SUPPORT_SELF_SENSE
#define FTS_SUPPORT_HW_PIN_CHECK
//#define FTS_GET_SERIALNUM

#define FTS_SUPPORT_ITOTEST
#ifdef FTS_SUPPORT_ITOTEST
 #define FTS_SUPPORT_HF_RAW_ADJ
 #ifdef LGD_TOE
  #define FTS_SUPPORT_MICRO_SHORT
 #endif
#endif

#if defined (FTS_METHOD_PRE_SAVED) || defined (MACHINE_OTHERS)
 #define FTS_SUPPORT_LP_SS_COMP
#endif
#define FTS_SUPPORT_CM_CP_CAPACITANCE
#define FTS_SUPPORT_LP_SS_RAW
//#define FTS_SUPPORT_LP_MS_RAW

#define	FTS_SUPPORT_LOCKDOWN_CODE
#ifdef	FTS_SUPPORT_LOCKDOWN_CODE
 #define FTS_LOCKDOWN_CODE_LENGTH			8
#endif

#define FTS_SUPPORT_I2C_INTERFACE_CHECK
//#define FTS_SUPPORT_CURRENT_CHECK
#ifdef FTS_SUPPORT_CURRENT_CHECK
 #define FTS_SUPPORT_CURRENT_MEASUREMENT_ACTIVE
 #define FTS_SUPPORT_CURRENT_MEASUREMENT_IDLE
 #define FTS_SUPPORT_CURRENT_MEASUREMENT_LP_DETECT
 #define FTS_SUPPORT_CURRENT_MEASUREMENT_LP_ACTIVE
 #define FTS_SUPPORT_CURRENT_MEASUREMENT_SLEEP
#endif

/**
  * @brief  Definitions for number of sensor (panel)
  */
#define FTS_TX_LENGTH						15
#define FTS_RX_LENGTH						32

/**
  * @brief  FTS command definitions
  */
#define CMD_SCAN_MODE							0xA0
#define CMD_FEATURE								0xA2
#define CMD_SYSTEM								0xA4

#ifdef I2C_INTERFACE
 #define CMD_FRM_BUFF_W							0xA6
 #define CMD_FRM_BUFF_R							0xA6
 #define CMD_CONFIG_R							0xA8
 #define CMD_CONFIG_W							0xA8
 #define FTS_CMD_HW_REG_W						0xFA
 #define FTS_CMD_HW_REG_R						0xFA
#else
 #define CMD_FRM_BUFF_W							0xA6
 #define CMD_FRM_BUFF_R							0xA7
 #define CMD_CONFIG_R							0xA9
 #define CMD_CONFIG_W							0xA8
 #define FTS_CMD_HW_REG_W						0xFA
 #define FTS_CMD_HW_REG_R						0xFB
#endif

/**
  * @brief  Scan mode selection of Scan mode Command (0xA0)
  */
#define CMD_SCAN_ACTIVE							0x00
#define	CMD_SCAN_LPMODE							0x01
#define	CMD_SCAN_TUNING_WIZARD					0x02
#define	CMD_SCAN_LOCKED							0x03

/**
  * @brief  Scan mode Setting of Scan mode Command (0xA0 - 0x00)
  */
#define CMD_SCAN_ACTIVE_MULTI					0x01
#define	CMD_SCAN_ACTIVE_KEY						0x02
#define	CMD_SCAN_ACTIVE_HOVER					0x04
#define	CMD_SCAN_ACTIVE_PROXIMITY				0x08
#define	CMD_SCAN_ACTIVE_FORCE					0x10
#define CMD_SCAN_ACTIVE_SIDETOUCH				0x20
/**
 * @brief  Scan mode Setting of Scan mode Command (0xA0 - 0x03)
 */
#define CMD_SCAN_LOCKED_ACTIVE					0x00
#define CMD_SCAN_LOCKED_NOTOUCH					0x01
#define CMD_SCAN_LOCKED_IDLE					0x02
#define CMD_SCAN_LOCKED_LP_DETECT				0x10
#define CMD_SCAN_LOCKED_LP_ACTIVE				0x11

/**
  * @brief  Command Type of System Command (0xA4)
  */
#define CMD_SYS_SPECIAL							0x00
#define	CMD_SYS_INTB							0x01
#define	CMD_SYS_FCAL							0x02
#define	CMD_SYS_ATUNE							0x03
#define	CMD_SYS_ITO_TEST						0x04
#define	CMD_SYS_SAVE2FLASH						0x05
#define	CMD_SYS_LOAD_DATA_MEM					0x06
#define CMD_SYS_CX_COMMON_CORRECTION			0x07
#define CMD_SYS_SPECIAL_TUNE_CMD				0x08

/**
  * @brief  Operation Setting of Special Commands (0xA4 - 0x00)
  */
#define CMD_SYS_SPECIAL_SYSTEMRESET				0x00
#define CMD_SYS_SPECIAL_CLEAR_FIFO				0x01
#define CMD_SYS_SPECIAL_PANEL_INIT				0x02
#define CMD_SYS_SPECIAL_FULLPANEL_INIT			0x03
#define	CMD_SYS_SPECIAL_UPLOAD_HOST_DATA		0x04

/**
  * @brief  Operation Setting of Auto Tune Commands (0xA4 - 0x02 and 0x03)
  */
#define CMD_SYS_SCANTYPE_MUTUAL					0x0100
#define CMD_SYS_SCANTYPE_MUTUAL_LP				0x0200
#define CMD_SYS_SCANTYPE_SELF					0x0400
#define CMD_SYS_SCANTYPE_SELF_LP				0x0800
#define CMD_SYS_SCANTYPE_MSKEY					0x1000
#define CMD_SYS_SCANTYPE_SSKEY					0x2000
#define CMD_SYS_SCANTYPE_MS_FORCE				0x4000
#define CMD_SYS_SCANTYPE_SS_FORCE				0x8000

/**
  * @brief  Operation Setting of Save to Flash Commands (0xA4 - 0x05)
  */
#define CMD_SYS_SAVE2FLASH_FWCONFIG				0x01
#define CMD_SYS_SAVE2FLASH_CX					0x02
#define CMD_SYS_SAVE2FLASH_PANELCONFIG			0x04

/**
  * @brief  Operation Setting of Host Data Memory (0xA4 - 0x06)
  * 		Host Data Memory ID
  */
#define LOAD_SYS_INFO							0x01								///< Load System Info
#define LOAD_CX_MS_TOUCH						0x10								///< Load MS Init Data for Active Mode
#define LOAD_CX_MS_LOW_POWER					0x11								///< Load MS Init Data for Low Power Mode
#define LOAD_CX_SS_TOUCH						0x12								///< Load SS Init Data for Active Mode
#define LOAD_CX_SS_TOUCH_IDLE					0x13								///< Load SS Init Data for Low Power Mode
#define LOAD_CX_MS_KEY							0x14								///< Load MS Init Data for Key
#define LOAD_CX_SS_KEY							0x15								///< Load SS Init Data for Key
#define LOAD_CX_MS_FORCE						0x16								///< Load MS Init Data for Force
#define LOAD_CX_SS_FORCE						0x17								///< Load SS Init Data for Force
#define LOAD_SYNC_FRAME_RAW						0x30								///< Load a Synchronized Raw Frame
#define LOAD_SYNC_FRAME_FILTER					0x31								///< Load a Synchronized Filter Frame
#define LOAD_SYNC_FRAME_STRENGTH				0x33								///< Load a Synchronized Strength Frame
#define LOAD_SYNC_FRAME_BASELINE				0x32								///< Load a Synchronized Baseline Frame
#define LOAD_CM_CAPACITANCE						0x40
#define LOAD_CP_CAPACITANCE						0x41
#define LOAD_PANEL_CX_TOT_MS_TOUCH				0x50								///< Load TOT MS Init Data for Active Mode
#define LOAD_PANEL_CX_TOT_MS_LOW_POWER			0x51								///< Load TOT MS Init Data for Low Power Mode
#define LOAD_PANEL_CX_TOT_SS_TOUCH				0x52								///< Load TOT SS Init Data for Active Mode
#define LOAD_PANEL_CX_TOT_SS_TOUCH_IDLE			0x53								///< Load TOT SS Init Data for Low Power Mode
#define LOAD_PANEL_CX_TOT_MS_KEY				0x54								///< Load TOT MS Init Data for Key
#define LOAD_PANEL_CX_TOT_SS_KEY				0x55								///< Load TOT SS Init Data for Key
#define LOAD_PANEL_CX_TOT_MS_FORCE				0x56								///< Load TOT MS Init Data for Force
#define LOAD_PANEL_CX_TOT_SS_FORCE				0x57								///< Load TOT SS Init Data for Force
#define LOAD_LOCKDOWN_CODE_REC_CP				0x70
#define LOAD_LOCKDOWN_CODE_REC_L2				0x71
#define LOAD_LOCKDOWN_CODE_REC_DB				0x72
#define LOAD_LOCKDOWN_CODE_REC_BD				0x73
#define LOAD_LOCKDOWN_CODE_REC_FINAL			0x74
#define LOAD_LOCKDOWN_CODE_REC_OQC				0x75
#define LOAD_LOCKDOWN_CODE_REC_GIB				0x76

/**
  * @brief  Operation Setting of Save to Flash Commands (0xA4 - 0x08)
  */
#define CMD_SYS_SPECIAL_TUNE_CMD_LPTIMER_CAL	0x01
#define CMD_SYS_SPECIAL_TUNE_CMD_IOFFSET_TUNE	0x02
#define CMD_SYS_SPECIAL_TUNE_CMD_IOFFSET_DATA	0x04

/**
  * @brief  FTS Event ID definitions for Event Messages
  */
#define EVTID_NO_EVENT							0x00
#define EVTID_CONTROLLER_READY					0x03
#define EVTID_ENTER_POINTER						0x13
#define EVTID_MOTION_POINTER					0x23
#define EVTID_LEAVE_POINTER						0x33
#define EVTID_STATUS_REPORT						0x43
#define EVTID_USER_REPORT						0x53
#define EVTID_ERROR_REPORT						0xF3

/**
  * @brief  Report Type of Status Report Event (0xA4)
  */
#define EVTID_RPTTYPE_CMD_ECHO					0x01
#define	EVTID_RPTTYPE_FRAME_DROP				0x03
#define	EVTID_RPTTYPE_FCAL_TRIG					0x05

/**
  * @brief  Report Type of Status Report Event (0xF3)
  */
#define	EVTID_ERR_TYPE_SYSTEM1					0x00
#define EVTID_ERR_TYPE_SYSTEM2					0x10
#define	EVTID_ERR_TYPE_CRC						0x20
#define	EVTID_ERR_TYPE_LOCKDOWN_CODE			0x30
#define	EVTID_ERR_TYPE_FW						0x40
#define	EVTID_ERR_TYPE_MS_TUNE					0x70
#define	EVTID_ERR_TYPE_SS_TUNE					0x80
#define	EVTID_ERR_TYPE_CX						0xA0

/**
  * @brief  FTS Address
  */
#define ADDR_FRAMEBUFFER						(uint16_t) 0x0000						///< frame buffer address in memory
#define ADDR_ERROR_DUMP							(uint16_t) 0xEF80						///< start address dump error log

#define FTS_ADDR_CHIP_ID						((uint32_t) 0x20000000)
#define FTS_ADDR_SYSTEM_RESET					((uint32_t) 0x20000024)
#define ADDR_ICR								((uint32_t) 0x2000002D)
#define ADDR_GPIO_DIRECTION						((uint32_t) 0x20000032)
#define ADDR_GPIO_PULLUP						((uint32_t) 0x20000034)
#define ADDR_GPIO_CONFIG_REG0					((uint32_t) 0x2000003D)
#define ADDR_GPIO_CONFIG_REG2					((uint32_t) 0x2000003F)

#define SYSTEM_RESET_SOFT						0
#define	SYSTEM_RESET_HARD						1
#define SYSTEM_RESET_VALUE						0x80
#define SYSTEM_HOLD_M3_VALUE					0x01

#define SPI4_MASK								0x02	/* /< bit to set spi4 */

/**
  * @brief  FTS Flash definitions
  */
#define FW_MAIN_BLOCK							0x01
#define FW_INFO_BLOCK							0x02

#define WRITE_CHUNK_SIZE						32
#define FLASH_CHUNK								(32 * 1024)
#define DMA_CHUNK								32

#define FW_HEADER_SIZE							64
#define FW_HEADER_FTB_SIGNATURE					0xAA55AA55
#define FW_HEADER_TARGET_ID						0x00003936
#define FW_BYTES_ALLIGN							4

#define FLASH_ADDR_CODE							0x00000000				// starting address in the flash of the code in FTM4
#define FLASH_ADDR_CONFIG						0x00007C00				// starting address in the flash of the config in FTI
#define FLASH_ADDR_CX							0x00007000				///< starting address (words) in the flash of the Init data in FTI

#define FLASH_UNLOCK_CODE0						0x25
#define FLASH_UNLOCK_CODE1						0x20

#define FLASH_ERASE_START						0x80
#define FLASH_ERASE_CODE1                       0xC0
#define FLASH_DMA_CODE1                         0xC0
#define FLASH_ERASE_UNLOCK_CODE0				0xDE
#define FLASH_ERASE_UNLOCK_CODE1				0x03
#define FLASH_ERASE_CODE0                       0x6A
#define FLASH_DMA_CODE0                      	0x71
#define FLASH_DMA_CONFIG                        0x72
#define FLASH_NUM_PAGE							32						// number of pages in main flash
#define FLASH_CX_PAGE_START						26						// starting page which contain Panel Init data
#define FLASH_CX_PAGE_END						30

/**
  * @brief  Enumeration - Error type
  */
enum	fts_error_type
{
	FTS_ERR							= 0x80000000,
	FTS_NO_ERR						= 0x00000000,
	FTS_ERR_EVT_TIMEOVER			= 0x00000001,
	FTS_ERR_SYS_RST					= 0x00000010,
	FTS_ERR_CHIPID					= 0x00000020,
	FTS_ERR_AUTOTUNE				= 0x00000040,
	FTS_ERR_SAVE_COMP				= 0x00000080,
	FTS_ERR_HOSTDATA_ID_HD			= 0x00000100,
	FTS_ERR_ITO_TEST				= 0x00000200,
	FTS_ERR_SYSTEM					= 0x00001000,
	FTS_ERR_MISS_FINAL				= 0x00002000,
	FTS_ERR_CRC						= 0x00010000,
	FTS_ERR_CRC_CFG					= 0x00020000,
	FTS_ERR_CRC_CX					= 0x00040000,
	FTS_ERR_CRC_CORRUPT				= 0x00080000,
	FTS_ERR_BIN_TYPE				= 0x00100000,
	FTS_ERR_FLASH_BURN				= 0x00200000,
	FTS_ERR_FLASH_ERASE				= 0x00400000,
	FTS_ERR_LOCKDOWN_ERR			= 0x01000000,
	FTS_ERR_COMM					= 0x10000000,
	FTS_ERR_MEM_ALLC				= 0x20000000
};

/**
  * @brief  Enumeration - Type of Binary File
  */
enum binfile_type
{
	BIN_FTS128 = 1,
	BIN_FTS256 = 2,
	BIN_FTB = 3
};

/**
  * @brief  Type definitions - header structure of firmware file (ftb)
  */
typedef __packed struct {
	uint32_t	signature;
	uint32_t	ftb_ver;
	uint32_t	target;
	uint32_t	fw_id;
	uint32_t	fw_ver;
	uint32_t	cfg_id;
	uint32_t	cfg_ver;
	uint32_t	reserved1[2];
	uint32_t	ext_ver;
	uint32_t	reserved2[1];
	uint32_t	sec0_size;
	uint32_t	sec1_size;
	uint32_t	sec2_size;
	uint32_t	sec3_size;
	uint32_t	hdr_crc;
}	FW_FTB_HEADER;

/** @defgroup system_info	System Info
  * System Info Data collect the most important informations about hw and fw
  * @{
  */
#define SYS_INFO_SIZE							210									///< Size in bytes of System Info data
#define DIE_INFO_SIZE							16									///< num bytes of die info
#define EXTERNAL_RELEASE_INFO_SIZE				8									///< num bytes of external release in config
#define RELEASE_INFO_SIZE						(EXTERNAL_RELEASE_INFO_SIZE)		///< num bytes of release info in sys info (first bytes are external release)

#define COMP_DATA_HEADER_SIZE					16
#define COMP_DATA_HEADER						4									///< size in bytes of initialization data header
#define COMP_DATA_GLOBAL						(16 - COMP_DATA_HEADER)				///< size in bytes of initialization data general info

#define HEADER_SIGNATURE						0xA5								///< signature used as starting byte of data loaded in memory

typedef	__packed struct	{
	uint8_t		header;
	uint8_t		host_data_mem_id;
	uint16_t	cnt;
	uint8_t		force_leng;
	uint8_t		sense_leng;
	uint8_t		cx1;
	uint8_t		reserved1;
	uint32_t	reserved2;
	uint32_t	reserved3;
}	MsCompHeader;

typedef	__packed struct	{
	uint8_t		header;
	uint8_t		host_data_mem_id;
	uint16_t	cnt;
	uint8_t		force_leng;
	uint8_t		sense_leng;
	uint8_t		force_ix1;
	uint8_t		sense_ix1;
	uint8_t		force_cx1;
	uint8_t		sense_cx1;
	uint8_t		force_maxn;
	uint8_t		sense_maxn;
	uint32_t	reserved;
}	SsCompHeader;

typedef	__packed struct	{
	uint8_t		header;
	uint8_t		host_data_mem_id;
	uint16_t	cnt;
	uint8_t		force_leng;
	uint8_t		sense_leng;
	uint8_t		reserved;
	uint8_t		reserved1;
	uint32_t	reserved2;
	uint32_t	reserved3;
}	CapFormHeader;

typedef	__packed struct	{
	uint8_t		header;
	uint8_t		host_data_mem_id;
	uint16_t	cnt;
	uint8_t		dbg_frm_leng;
	uint8_t		ms_force_leng;
	uint8_t		ms_sense_leng;
	uint8_t		ss_force_leng;
	uint8_t		ss_sense_leng;
	uint8_t		key_leng;
	uint16_t	reserved1;
	uint32_t	reserved2;
}	SyncFrameHeader;

/**
 * @brief  Struct which contains fundamental informations about the chip and its configuration
 */
typedef __packed struct {
	uint8_t		header;										// 0x0000
	uint8_t		host_data_mem_id;
	uint16_t	cnt;
	uint16_t	apiVer_rev;									// API revision version
	uint8_t		apiVer_minor;								// API minor version
	uint8_t		apiVer_major;								// API major version
	uint16_t	chip0Ver;									// Dev0 version
	uint16_t	chip0Id;									// Dev0 ID
	uint16_t	chip1Ver;									// Dev1 version
	uint16_t	chip1Id;									// Dev1 ID

	uint16_t	fwVer;										// 0x0010 // Fw version
	uint16_t	svn_rev;									// Revision of svn
	uint16_t	cfgVer;										// Config Version
	uint16_t	cfgProjctId;								// Project ID
	uint16_t	cxVer;										// Cx Version
	uint16_t	cxId;										// Cx ID
	uint8_t		CfgAfeVer;									// AFE version in Config
	uint8_t		CxAfeVer;									// AFE version of Cx
	uint8_t		PanelCfgAfeVer;
	uint8_t		protocol;

	uint8_t		dieInfo[DIE_INFO_SIZE];						// 0x0020 // Die information
	uint8_t		releaseInfo[RELEASE_INFO_SIZE];				// 0x0030 // Release information
	uint32_t	fw_crc;										// crc of fw
	uint32_t	cfg_crc;									// crc of cfg

	uint32_t	reserved2[4];								// 0x0040

	uint16_t	scrResX;									// 0x0050 // X resolution on main screen
	uint16_t	scrResY;									// Y resolution on main screen
	uint8_t		scrTxLen;									// Tx length
	uint8_t		scrRxLen;									// Rx length
	uint8_t		keyLen;										// Key Len
	uint8_t		forceLen;									// Force Len
	uint32_t	reserved3[10];

	uint16_t	dbgFrameAddr;								// 0x0080 // Offset of debug Info structure
	uint16_t	reserved4[3];

	uint16_t	msTchRawAddr;								// Offset of MS touch raw frame
    uint16_t	msTchFilterAddr;							// Offset of MS touch filter frame
    uint16_t	msTchStrenAddr;								// Offset of MS touch strength frame
    uint16_t	msTchBaselineAddr;							// Offset of MS touch baseline frame

    uint16_t	ssTchTxRawAddr;								// 0x0090 // Offset of SS touch force raw frame
    uint16_t	ssTchTxFilterAddr;							// Offset of SS touch force filter frame
    uint16_t	ssTchTxStrenAddr;							// Offset of SS touch force strength frame
    uint16_t	ssTchTxBaselineAddr;						// Offset of SS touch force baseline frame

    uint16_t	ssTchRxRawAddr;								// Offset of SS touch sense raw frame
    uint16_t	ssTchRxFilterAddr;							// Offset of SS touch sense filter frame
    uint16_t	ssTchRxStrenAddr;							// Offset of SS touch sense strength frame
    uint16_t	ssTchRxBaselineAddr;						// Offset of SS touch sense baseline frame

    uint16_t	keyRawAddr;									// 0x00A0 // Offset of key raw frame
    uint16_t	keyFilterAddr;								// Offset of key filter frame
    uint16_t	keyStrenAddr;								// Offset of key strength frame
    uint16_t	keyBaselineAddr;							// Offset of key baseline frame

    uint16_t	frcRawAddr;									// Offset of force touch raw frame
    uint16_t	frcFilterAddr;								// Offset of force touch filter frame
    uint16_t	frcStrenAddr;								// Offset of force touch strength frame
    uint16_t	frcBaselineAddr;							// Offset of force touch baseline frame

    uint16_t	ssHvrTxRawAddr;								// 0x00B0 // Offset of SS hover Force raw frame
    uint16_t	ssHvrTxFilterAddr;							// Offset of SS hover Force filter frame
    uint16_t	ssHvrTxStrenAddr;							// Offset of SS hover Force strength frame
    uint16_t	ssHvrTxBaselineAddr;						// Offset of SS hover Force baseline frame

    uint16_t	ssHvrRxRawAddr;								// Offset of SS hover Sense raw frame
    uint16_t	ssHvrRxFilterAddr;							// Offset of SS hover Sense filter frame
    uint16_t	ssHvrRxStrenAddr;							// Offset of SS hover Sense strength frame
    uint16_t	ssHvrRxBaselineAddr;						// Offset of SS hover Sense baseline frame

    uint16_t	ssPrxTxRawAddr;								// 0x00C0 // Offset of SS proximity force raw frame
    uint16_t	ssPrxTxFilterAddr;							// Offset of SS proximity force filter frame
    uint16_t	ssPrxTxStrenAddr;							// Offset of SS proximity force strength frame
    uint16_t	ssPrxTxBaselineAddr;						// Offset of SS proximity force baseline frame

    uint16_t	ssPrxRxRawAddr;								// Offset of SS proximity sense raw frame
    uint16_t	ssPrxRxFilterAddr;							// Offset of SS proximity sense filter frame
    uint16_t	ssPrxRxStrenAddr;							// Offset of SS proximity sense strength frame
    uint16_t	ssPrxRxBaselineAddr;						// Offset of SS proximity sense baseline frame

    uint16_t	ssDetRawAddr;								// Offset of SS Detect raw frame
}	SysInfo;

/** @}*/

/**
* Possible types of MS frames
*/
typedef enum	{
	MS_RAW = 0,																	///< Mutual Sense Raw Frame
	MS_FILTER = 1,																///< Mutual Sense Filtered Frame
	MS_STRENGHT = 2,															///< Mutual Sense Strength Frame (Baseline-Raw)
	MS_BASELINE = 3,															///< Mutual Sense Baseline Frame
	MS_KEY_RAW = 4,																///< Mutual Sense Key Raw Frame
	MS_KEY_FILTER = 5,															///< Mutual Sense Key Filter Frame
	MS_KEY_STRENGHT = 6,														///< Mutual Sense Key Strength Frame (Baseline-Raw)
	MS_KEY_BASELINE = 7,														///< Mutual Sense Key Baseline Frame
	FRC_RAW = 8,																///< Force Raw Frame
	FRC_FILTER = 9,																///< Force Filtered Frame
	FRC_STRENGHT = 10,															///< Force Strength Frame (Baseline-Raw)
	FRC_BASELINE = 11															///< Force Baseline Frame
}	MSFrameType;


/**
* Possible types of SS frames
*/
typedef enum	{
	SS_RAW = 0,																	///< Self Sense Raw Frame
	SS_FILTER = 1,																///< Self Sense Filtered Frame
	SS_STRENGHT = 2,															///< Self Sense Strength Frame (Baseline-Raw)
	SS_BASELINE = 3,															///< Self Sense Baseline Frame
	SS_HVR_RAW = 4,																///< Self Sense Hover Raw Frame
	SS_HVR_FILTER = 5,															///< Self Sense Hover Filter Frame
	SS_HVR_STRENGHT = 6,														///< Self Sense Hover Strength Frame (Baseline-Raw)
	SS_HVR_BASELINE = 7,														///< Self Sense Hover Baseline Frame
	SS_PRX_RAW = 8,																///< Self Sense Proximity Raw Frame
	SS_PRX_FILTER = 9,															///< Self Sense Proximity Filtered Frame
	SS_PRX_STRENGHT = 10,														///< Self Sense Proximity Strength Frame (Baseline-Raw)
	SS_PRX_BASELINE = 11,														///< Self Sense Proximity Baseline Frame
	SS_DET_RAW = 12
}	SSFrameType;

/**
  * @brief  Enumeration - Address size of Register
  */
enum	Reg_Address_Size	{
 	NO_ADDR = 0,
 	BITS_8 = 1,
 	BITS_16 = 2,
 	BITS_24 = 3,
 	BITS_32 = 4,
 	BITS_40 = 5,
 	BITS_48 = 6,
 	BITS_56 = 7,
 	BITS_64 = 8
};

/**
  * @brief  Enumeration - Error type of ITO TEST
  */
enum	ito_error_type
{
	ITO_FORCE_SHRT_GND		= 0x60,
	ITO_SENSE_SHRT_GND		= 0x61,
	ITO_FORCE_SHRT_VDD		= 0x62,
	ITO_SENSE_SHRT_VDD		= 0x63,
	ITO_FORCE_SHRT_FORCE	= 0x64,
	ITO_SENSE_SHRT_SENSE	= 0x65,
	ITO_FORCE_OPEN 			= 0x66,
	ITO_SENSE_OPEN 			= 0x67,
	ITO_KEY_OPEN			= 0x68
};

/**
  * @brief  FTS general definitions
  */
#define ON					0x01
#define OFF					0x00

#define TRUE				1
#define FALSE				0

#define	ENABLE				1
#define	DISABLE				0

/** @defgroup FTS_Exported_FunctionsPrototype
  * @{
  */
int fts_event_handler(void);
int flashProcedure(int force, int keep_cx);
int fts_panel_test(void);
int fts_init(void);

/**
  * @}
  */

/**
  * @}
  */

#endif	/* __FTS_LGD_H__ */

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/
