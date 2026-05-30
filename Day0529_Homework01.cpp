#include "Day0529_Homework01.h"

#include <iostream>
using namespace std;

void Homework01_Run()
{
	Day0529_Date Today = Day0529_InputDate();
	int PassedDays = Day0529_GetPassedDays(Today.Year, Today.Month, Today.Day);
	Today.WeekDay = Day0529_GetWeekDay(PassedDays);
	Day0529_PrintDate(Today, PassedDays);
}

// 날짜를 입력받는 함수
Day0529_Date& Day0529_InputDate()
{
	Day0529_Date Result;

	bool bIsYearValid = false, bIsMonthValid = false, bIsDayValid = false;
	while (!bIsYearValid || !bIsMonthValid || !bIsDayValid) {
		bIsYearValid = false; bIsMonthValid = false; bIsDayValid = false;
		printf("날짜를 '년 월 일' 형식으로 입력하세요: ");
		cin >> Result.Year >> Result.Month >> Result.Day;

		// 연도 유효성 검사
		if (Result.Year > 0)
		{
			bIsYearValid = true;
		}
		// 월 유효성 검사
		if (Result.Month >= 1 || Result.Month <= 12)
		{
			bIsMonthValid = true;
		}
		// 일 유효성 검사
		if (Result.Day > 0)
		{
			if (
				(Result.Month == 2 && !Day0529_CheckLeapYear(Result.Year)
					&& Result.Day < 29)
				|| (Result.Month == 2 && Day0529_CheckLeapYear(Result.Year)
					&& Result.Day <= 29)
				|| ((Result.Month == 1 || Result.Month == 3 || Result.Month == 5 || Result.Month == 7 || Result.Month == 8 || Result.Month == 10 || Result.Month == 12)
					&& Result.Day <= 31)
				|| ((Result.Month == 4 || Result.Month == 6 || Result.Month == 9 || Result.Month == 11)
					&& Result.Day < 31)
				)
			{
				bIsDayValid = true;
			}
		}

		if (!bIsYearValid || !bIsMonthValid || !bIsDayValid)
		{
			printf("잘못 입력하셨습니다. 다시 입력해주세요.\n\n");
		}
	}

	return Result;
}

// StartDate로부터 지난 날 수와 입력받은 날짜의 요일을 출력하는 함수
void Day0529_PrintDate(Day0529_Date& InDate, int PassedDays)
{
	string WeekDayName = "";
	switch (InDate.WeekDay)
	{
	case Monday:
		WeekDayName = "월";
		break;
	case Tuesday:
		WeekDayName = "화";
		break;
	case Wednesday:
		WeekDayName = "수";
		break;
	case Thursday:
		WeekDayName = "목";
		break;
	case Friday:
		WeekDayName = "금";
		break;
	case Saturday:
		WeekDayName = "토";
		break;
	case Sunday:
		WeekDayName = "일";
		break;
	default:
		WeekDayName = "[ Error ]";
		break;
	}

	printf("입력한 날짜는 %s요일이며, 1년 1월 1일 월요일로부터 %d일째 날입니다.", WeekDayName.c_str(), PassedDays);
}

// 입력된 년도가 윤년인지 확인하는 함수
bool Day0529_CheckLeapYear(int Year)
{
	return Year % 400 == 0 || (Year % 4 == 0 && Year % 100 != 0);
}

// StartDate로부터 지난 날 수를 계산하는 함수
int Day0529_GetPassedDays(int Year, int Month, int Day)
{
	int PassedDays = 0;

	// StartDate부터 작년까지의 날 수 계산
	for (int i = Day0529_StartDate.Year; i < Year; i++)
	{
		PassedDays += (!Day0529_CheckLeapYear(i) ? 365 : 366);
	}

	// 올해 연초부터 작월까지의 날 수 계산
	for (int i = 1; i < Month && i <= 12; i++)
	{
		// 한 달이 31일
		if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
		{
			PassedDays += 31;
		}
		// 한 달이 30일
		else if (i == 4 || i == 6 || i == 9 || i == 11)
		{
			PassedDays += 30;
		}
		// 2월
		else
		{
			PassedDays += (!Day0529_CheckLeapYear(Year) ? 28 : 29);
		}
	}

	// 이번달에서 지난 날 수 계산
	PassedDays += Day;

	return PassedDays;
}

// 요일을 계산하는 함수
Day0529_WeekDays Day0529_GetWeekDay(int PassedDays)
{
	return Day0529_WeekDays((PassedDays + (Day0529_StartDate.WeekDay - 1)) % 7);
}
