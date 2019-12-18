#ifndef _KERNEL_DATE_H
#define _KERNEL_DATE_H

typedef struct {
  int second;
  int minute;
  int hour;
  int day;
  int month;
  int year;
} datetime;

datetime get_date();

#endif
