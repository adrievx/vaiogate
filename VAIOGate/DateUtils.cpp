#include "DateUtils.h"
#include <cwchar>

COleDateTime* ParseIsoDate(COleDateTime* outDate, const CStringW& input) {
	int year = 0, month = 0, day = 0;
	int hour = 0, minute = 0, second = 0;

	swscanf_s(input.GetString(), L"%d-%d-%dT%d:%d:%d",
		&year, &month, &day,
		&hour, &minute, &second);

	COleDateTime temp(year, month, day, hour, minute, second);

	if (temp.GetStatus() == COleDateTime::invalid) {
		temp.SetDateTime(1900, 1, 1, 0, 0, 0);
	}

	*outDate = temp;
	return outDate;
}