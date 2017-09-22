/**
  ******************************************************************************
  * touch_ft5536.c by duvallee.lee 2017
  ******************************************************************************
  *
  ******************************************************************************
  */ 

#include <stdio.h>
#include "main.h"
#include "stm32f7xx_hal.h"
#include "debug_output.h"
#include "touch_ft5536.h"

#define FT5536_I2C_SLAVE_ADDRESS                         0x70

typedef struct _TOUCH_POINT_STRUCT
{
   uint8_t touch_action;

   uint16_t x_pos;
   uint16_t y_pos;

   uint8_t touch_weight;
   uint8_t touch_area;
} TOUCH_POINT_STRUCT;

typedef struct _TOUCH_EVENT_STRUCT
{
   uint8_t touch_point_num;

   TOUCH_POINT_STRUCT touch_point[FT5336_MAX_DETECTABLE_TOUCH];

   uint8_t touch_gesture;
} TOUCH_EVENT_STRUCT;


// ---------------------------------------------------------------------------
// global variable
static I2C_HandleTypeDef hi2c3;
static TOUCH_EVENT_STRUCT g_Touch_Event;

/* --------------------------------------------------------------------------
 * Name : touch_init()
 *        touch init function
 *
 * -------------------------------------------------------------------------- */
void touch_init(void)
{
   uint8_t reg_value                                     = 0;
   uint8_t reg_ex_value                                  = 0;

   HAL_Delay(1);
   hi2c3.Instance                                        = I2C3;
   hi2c3.Init.Timing                                     = 0x00303D5B;
   hi2c3.Init.OwnAddress1                                = 0;
   hi2c3.Init.AddressingMode                             = I2C_ADDRESSINGMODE_7BIT;
   hi2c3.Init.DualAddressMode                            = I2C_DUALADDRESS_DISABLE;
   hi2c3.Init.OwnAddress2                                = 0;
   hi2c3.Init.OwnAddress2Masks                           = I2C_OA2_NOMASK;
   hi2c3.Init.GeneralCallMode                            = I2C_GENERALCALL_DISABLE;
   hi2c3.Init.NoStretchMode                              = I2C_NOSTRETCH_DISABLE;
   if (HAL_I2C_Init(&hi2c3) != HAL_OK)
   {
      _Error_Handler(__FILE__, __LINE__);
      return;
   }

   /**Configure Analogue filter 
   */
   if (HAL_I2CEx_ConfigAnalogFilter(&hi2c3, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
   {
      _Error_Handler(__FILE__, __LINE__);
      return;
   }

   /**Configure Digital filter 
   */
   if (HAL_I2CEx_ConfigDigitalFilter(&hi2c3, 0) != HAL_OK)
   {
      _Error_Handler(__FILE__, __LINE__);
      return;
   }

   HAL_Delay(1);

   debug_output_dump("==================================================== \r\n");
   debug_output_dump("FocalTech FT5336GQQ - CTP Controller \r\n\r\n");
   if (touch_read_reg(FT5336_CHIP_ID_REG, &reg_value) == HAL_OK)
   {
      debug_output_dump("CHIP ID(0x%02X)        : 0x%02X \r\n", FT5336_ID_VALUE, reg_value);
   }
   if (touch_read_reg(FT5336_RELEASE_CODE_ID_REG, &reg_value) == HAL_OK)
   {
      debug_output_dump("RELEASE CODE ID      : 0x%02X \r\n", reg_value);
   }
   if (touch_read_reg(FT5336_STATE_REG, &reg_value) == HAL_OK)
   {
      debug_output_dump("CURRENT OP MODE      : 0x%02X \r\n", reg_value);
   }
   if (touch_read_reg(FT5336_FIRMID_REG, &reg_value) == HAL_OK)
   {
      debug_output_dump("F/W VER              : 0x%02X \r\n", reg_value);
   }

   if (touch_read_reg(FT5336_LIB_VER_L_REG, &reg_value) == HAL_OK)
   {
   }
   if (touch_read_reg(FT5336_LIB_VER_H_REG, &reg_ex_value) == HAL_OK)
   {
      debug_output_dump("LIB VER VER          : 0x%02X%02X \r\n", reg_ex_value, reg_value);
   }

   if (touch_read_reg(FT5336_GMODE_REG, &reg_value) == HAL_OK)
   {
      debug_output_dump("IRQ MODE             : 0x%02X \r\n", reg_value);
   }

   if (touch_read_reg(FT5336_CIPHER_REG, &reg_value) == HAL_OK)
   {
      debug_output_dump("CHIP SELECT          : 0x%02X \r\n", reg_value);
   }

   if (touch_read_reg(FT5336_PERIODMONITOR_REG, &reg_value) == HAL_OK)
   {
      debug_output_dump("rate in Mointor mode : 0x%02X \r\n", reg_value);
   }

   if (touch_read_reg(FT5336_TIMEENTERMONITOR_REG, &reg_value) == HAL_OK)
   {
      debug_output_dump("time period          : 0x%02X \r\n", reg_value);
   }

   if (touch_read_reg(FT5336_CTRL_REG, &reg_value) == HAL_OK)
   {
      debug_output_dump("time period          : 0x%02X \r\n", reg_value);
   }

   if (touch_read_reg(FT5336_DEV_MODE_REG, &reg_value) == HAL_OK)
   {
      debug_output_dump("Device Mode          : %s \r\n", ((reg_value & FT5336_DEV_MODE_MASK) == FT5336_DEV_MODE_FACTORY) ? "Factory Mode" : "Working Mode");
   }
   debug_output_dump("==================================================== \r\n");
}


/* --------------------------------------------------------------------------
 * Name : touch_start()
 *
 *
 * -------------------------------------------------------------------------- */
void touch_start(uint8_t trigger_mode)
{
   if (touch_write_reg(FT5336_GMODE_REG, trigger_mode & FT5336_G_MODE_INTERRUPT_MASK) != HAL_OK)
   {
      debug_output_error("touch_start() Failed \r\n");
      return;
   }
}

/* --------------------------------------------------------------------------
 * Name : get_touch_point()
 *
 *
 * -------------------------------------------------------------------------- */
#define XH_REG_INDEX                                     0
#define XL_REG_INDEX                                     1
#define YH_REG_INDEX                                     2
#define YL_REG_INDEX                                     3
#define WEIGHT_REG_INDEX                                 4
#define MISC_REG_INDEX                                   5
void get_touch_point(uint8_t start_reg_addr, TOUCH_POINT_STRUCT* pPoint)
{
   uint8_t reg_value                                     = 0;
   uint8_t reg_hi_value                                  = 0;
   uint8_t reg_low_value                                 = 0;

   touch_read_reg(start_reg_addr + XH_REG_INDEX, &reg_hi_value);
   touch_read_reg(start_reg_addr + XL_REG_INDEX, &reg_low_value);

   pPoint->touch_action                                  = (reg_hi_value & FT5336_TOUCH_EVT_FLAG_MASK);

#if 1
   pPoint->y_pos                                         = (((reg_hi_value & FT5336_TOUCH_POS_MSB_MASK) << 8) | reg_low_value);
#else
   pPoint->x_pos                                         = (((reg_hi_value & FT5336_TOUCH_POS_MSB_MASK) << 8) | reg_low_value);
#endif

   touch_read_reg(start_reg_addr + YH_REG_INDEX, &reg_hi_value);
   touch_read_reg(start_reg_addr + YL_REG_INDEX, &reg_low_value);

#if 1
   pPoint->x_pos                                         = (((reg_hi_value & FT5336_TOUCH_POS_MSB_MASK) << 8) | reg_low_value);
#else
   pPoint->y_pos                                         = (((reg_hi_value & FT5336_TOUCH_POS_MSB_MASK) << 8) | reg_low_value);
#endif

   touch_read_reg(start_reg_addr + WEIGHT_REG_INDEX, &reg_value);
   pPoint->touch_weight                                  = reg_value;

   touch_read_reg(start_reg_addr + MISC_REG_INDEX, &reg_value);
   pPoint->touch_area                                    = ((reg_value & FT5336_TOUCH_AREA_MASK) >> FT5336_TOUCH_AREA_SHIFT);

}

/* --------------------------------------------------------------------------
 * Name : get_touch_event()
 *
 *
 * -------------------------------------------------------------------------- */
uint8_t get_touch_event()
{
   uint8_t reg_value                                     = 0;
   uint8_t touch_pt_num                                  = 0;

   touch_read_reg(FT5336_TD_STAT_REG, &reg_value);

   touch_pt_num                                          = (reg_value & FT5336_TD_STAT_MASK);
   if (touch_pt_num == 0 || touch_pt_num > FT5336_MAX_DETECTABLE_TOUCH)
   {
      g_Touch_Event.touch_point_num                      = 0;
      return 0;
   }
   g_Touch_Event.touch_point_num                         = touch_pt_num;

   switch(g_Touch_Event.touch_point_num)
   {
      case 1 :
         get_touch_point(FT5336_P1_XH_REG, &(g_Touch_Event.touch_point[0]));
         break;

      case 2 :
         get_touch_point(FT5336_P1_XH_REG, &(g_Touch_Event.touch_point[0]));
         get_touch_point(FT5336_P2_XH_REG, &(g_Touch_Event.touch_point[1]));
         break;

      case 3 :
         get_touch_point(FT5336_P1_XH_REG, &(g_Touch_Event.touch_point[0]));
         get_touch_point(FT5336_P2_XH_REG, &(g_Touch_Event.touch_point[1]));
         get_touch_point(FT5336_P3_XH_REG, &(g_Touch_Event.touch_point[2]));
         break;

      case 4 :
         get_touch_point(FT5336_P1_XH_REG, &(g_Touch_Event.touch_point[0]));
         get_touch_point(FT5336_P2_XH_REG, &(g_Touch_Event.touch_point[1]));
         get_touch_point(FT5336_P3_XH_REG, &(g_Touch_Event.touch_point[2]));
         get_touch_point(FT5336_P4_XH_REG, &(g_Touch_Event.touch_point[3]));
         break;

      case 5 :
         get_touch_point(FT5336_P1_XH_REG, &(g_Touch_Event.touch_point[0]));
         get_touch_point(FT5336_P2_XH_REG, &(g_Touch_Event.touch_point[1]));
         get_touch_point(FT5336_P3_XH_REG, &(g_Touch_Event.touch_point[2]));
         get_touch_point(FT5336_P4_XH_REG, &(g_Touch_Event.touch_point[3]));
         get_touch_point(FT5336_P5_XH_REG, &(g_Touch_Event.touch_point[4]));
         break;
   }
   touch_read_reg(FT5336_GEST_ID_REG, &reg_value);
   g_Touch_Event.touch_gesture                           = reg_value;

   return touch_pt_num;
}


/* --------------------------------------------------------------------------
 * Name : touch_start()
 *
 *
 * -------------------------------------------------------------------------- */
void touch_polling(void* pData)
{
   uint8_t touch_pt_num                                  = 0;
   int i;
   touch_pt_num                                          = get_touch_event();
   if (touch_pt_num > 0)
   {
      debug_output_dump("pt=%d, ", touch_pt_num);
      for (i = 0; i < g_Touch_Event.touch_point_num; i++)
      {
         debug_output_dump("[x=%3d, y=%3d, ", g_Touch_Event.touch_point[i].x_pos, g_Touch_Event.touch_point[i].y_pos);
         debug_output_dump("action=");
         switch (g_Touch_Event.touch_point[i].touch_action)
         {
            case FT5336_TOUCH_EVT_FLAG_PRESS_DOWN :
               debug_output_dump("press, ");
               break;

            case FT5336_TOUCH_EVT_FLAG_LIFT_UP :
               debug_output_dump("up, ");
               break;

            case FT5336_TOUCH_EVT_FLAG_CONTACT :
               debug_output_dump("contact, ");
               break;

            case FT5336_TOUCH_EVT_FLAG_NO_EVENT :
               debug_output_dump("no_event, ");
               break;
         }
         debug_output_dump("weight=%3d, ", g_Touch_Event.touch_point[i].touch_weight);
         debug_output_dump("misc=%d] ", g_Touch_Event.touch_point[i].touch_area);
      }
      debug_output_dump("\r\n");
   }
}


/* --------------------------------------------------------------------------
 * Name : touch_read_reg()
 *
 *
 * -------------------------------------------------------------------------- */
HAL_StatusTypeDef touch_read_reg(uint8_t Reg, uint8_t* pvalue)
{
   HAL_StatusTypeDef status                              = HAL_OK;
   status                                                = HAL_I2C_Mem_Read(&hi2c3, FT5536_I2C_SLAVE_ADDRESS, (uint16_t) Reg, sizeof(uint8_t), pvalue, sizeof(uint8_t), 1000);

   /* Check the communication status */
   if (status != HAL_OK)
   {
      debug_output_error("HAL_I2C_Mem_Read Failed() : %d \r\n", status);
      _Error_Handler(__FILE__, __LINE__);
   }
   return status;
}

/* --------------------------------------------------------------------------
 * Name : touch_write_reg()
 *
 *
 * -------------------------------------------------------------------------- */
HAL_StatusTypeDef touch_write_reg(uint8_t Reg, uint8_t value)
{
   HAL_StatusTypeDef status                              = HAL_OK;
   status                                                = HAL_I2C_Mem_Write(&hi2c3, FT5536_I2C_SLAVE_ADDRESS, (uint16_t) Reg, sizeof(uint8_t), &value, sizeof(uint8_t), 1000);

   /* Check the communication status */
   if (status != HAL_OK)
   {
      debug_output_error("HAL_I2C_Mem_Write Failed() : %d \r\n", status);
      _Error_Handler(__FILE__, __LINE__);
   }
   return status;
}






