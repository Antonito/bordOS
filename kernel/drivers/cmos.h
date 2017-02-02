#ifndef CMOS_H_
#define CMOS_H_

#include <stdint.h>

typedef struct s_cmos_rtc cmos_rtc_t;

struct s_cmos_rtc
{
  uint8_t century;
  uint8_t seconds;
  uint8_t minuts;
  uint8_t hour;
  uint8_t day;
  uint8_t month;
  uint8_t year;
  uint8_t century;
};

void cmos_RTC(cmos_rtc_t *const data);

#endif /* !CMOS_H_ */