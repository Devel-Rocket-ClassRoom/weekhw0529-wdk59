#pragma once

#include <string>

enum Day0529_WeekDays
{
	None,
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday
};

struct Day0529_Date {
	int Year = 0;
	int Month = 0;
	int Day = 0;
	Day0529_WeekDays WeekDay = None;

	Day0529_Date()
	{

	}
	
	Day0529_Date(int InYear, int InMonth, int InDay, Day0529_WeekDays InWeekDay)
		: Year(InYear), Month(InMonth), Day(InDay), WeekDay(InWeekDay)
	{

	}
};

const Day0529_Date Day0529_StartDate(1, 1, 1, Monday);

void Homework01_Run();

Day0529_Date& Day0529_InputDate();

void Day0529_PrintDate(Day0529_Date& InDate, int PassedDays);

bool Day0529_CheckLeapYear(int Year);

int Day0529_GetPassedDays(int Year, int Month, int Day);

Day0529_WeekDays Day0529_GetWeekDay(int PassedDays);
