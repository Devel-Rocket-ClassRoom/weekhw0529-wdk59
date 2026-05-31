#include "Day0529_Homework02.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void Day0529_Homework02_Run()
{
	// 랜덤 시드 설정
	srand(time(0));

	// 카드 초기화
	int CardPool[Day0529_CARD_MAX + 1] = { 0, };	// 각 카드는 4장씩 존재. 1~13번째만 사용 (0번째는 무조건 0)
	for (int i = 1; i <= Day0529_CARD_MAX; i++)
	{
		CardPool[i] = 4;
	}

	// 게임 진행
	Day0529_BlackJack_Play(CardPool);
}

// 블랙잭 게임 진행 함수
void Day0529_BlackJack_Play(int* CardPool)
{
	// 딜러 및 플레이어 입장
	CardPocket DealerCardPocket;
	CardPocket PlayerCardPocket;

	// 초기 배분: 플레이어, 딜러 각각 카드 2장씩 뽑기
	int DealerHiddenCard = Day0529_GameReady(CardPool, DealerCardPocket, PlayerCardPocket);

	bool bIsPlayerWin = false;			// 플레이어 승리 여부

	bool bIsPlayerBurst = false;		// 플레이어 버스트 여부
	bool bIsDealerBurst = false;		// 딜러 버스트 여부

	// 블랙잭 확인
	bool bIsPlayerBlackJack = false;	// 플레이어 블랙잭 여부
	bool bIsDealerBlackJack = false;	// 딜러 블랙잭 여부
	if (Day0529_CheckBlackJack(PlayerCardPocket) && Day0529_CheckBlackJack(DealerCardPocket))
	{
		bIsPlayerBlackJack = true;
		bIsDealerBlackJack = true;
	}
	else if (Day0529_CheckBlackJack(PlayerCardPocket))
	{
		bIsPlayerBlackJack = true;
		bIsPlayerWin = true;
	}
	else if (Day0529_CheckBlackJack(DealerCardPocket))
	{
		bIsDealerBlackJack = true;
		bIsPlayerWin = false;
	}
	// 버스트 확인
	bIsPlayerBurst = Day0529_CheckBurst(PlayerCardPocket);
	bIsDealerBurst = Day0529_CheckBurst(DealerCardPocket);

	bool bIsPlayerTurn = true;		// 카드 뽑기 턴 관리
	bool bIsPlayerStand = false;	// 플레이어 스탠드 여부
	// 턴 진행
	if (!bIsPlayerBlackJack && !bIsDealerBlackJack && !bIsDealerBurst && !bIsPlayerBurst)
	{
		// 플레이어 턴 진행
		bIsPlayerBurst = Day0529_PlayTurn(PlayerCardPocket, bIsPlayerTurn, CardPool);
		if (!bIsPlayerBurst)
		{
			// 플레이어 버스트 나지 않으면 딜러 턴 진행
			bIsDealerBurst = Day0529_PlayTurn(DealerCardPocket, !bIsPlayerTurn, CardPool);
		}
	}

	// 승패 판정
	printf("게임이 종료됐습니다. 승패를 가립니다.\n딜러의 다른 카드는 %s였습니다.\n\n", Day0529_GetCardNumberName(DealerHiddenCard).c_str());
	Day0529_DetermineWinner(PlayerCardPocket, DealerCardPocket, bIsPlayerBlackJack, bIsDealerBlackJack);
}

// 초기 배분. 딜러의 숨긴 카드 반환
int Day0529_GameReady(int* CardPool, CardPocket& Dealer, CardPocket& Player)
{
	string DealerDraw[2] = { "", "" };
	string PlayerDraw[2] = { "", "" };

	// 플레이어와 딜러 각각 카드 두 장씩 뽑기
	int TempCard = 0;
	for (int i = 2; i; i--)
	{
		TempCard = Day0529_DrawCard(CardPool);
		if (TempCard != 1)
		{
			Player.Score_ExceptAce += (TempCard > 9 ? 10 : TempCard);
		}
		else
		{
			Player.AceCount++;
		}
		PlayerDraw[2 - i] = Day0529_GetCardNumberName(TempCard);

		TempCard = Day0529_DrawCard(CardPool);
		if (TempCard != 1)
		{
			Dealer.Score_ExceptAce += (TempCard > 9 ? 10 : TempCard);
		}
		else
		{
			Dealer.AceCount++;
		}
		DealerDraw[2 - i] = Day0529_GetCardNumberName(TempCard);
	}

	// 플레이어: 카드 두 장 모두 공개
	printf("플레이어가 뽑은 카드 번호: %s, %s\n", PlayerDraw[0].c_str(), PlayerDraw[1].c_str());

	// 딜러: 카드 한 장만 공개
	printf("딜러 오픈 카드: %s\n", DealerDraw[0].c_str());	// 처음 뽑은 카드를 오픈하기로 개발자가 임의로 정함

	return TempCard;
}

// 카드 번호를 문자열로 변환하는 함수
string Day0529_GetCardNumberName(int CardNumber)
{
	string Result = "";

	if (CardNumber == 1)
	{
		Result = "Ace";
	}
	else if (CardNumber == 10)
	{
		Result = "10";
	}
	else if (CardNumber == 11)
	{
		Result = "Jack";
	}
	else if (CardNumber == 12)
	{
		Result = "Queen";
	}
	else if (CardNumber == 13)
	{
		Result = "King";
	}
	else
	{
		Result = '0' + CardNumber;	// 2~9
	}

	return Result;
}

// 카드 한 장 뽑기
int Day0529_DrawCard(int* CardPool)
{
	int Result = 0;	// 뽑은 카드

	if (Day0529_CheckCardPool(CardPool)) {
		while (*(CardPool + (Result = rand() % Day0529_CARD_MAX + 1)) == 0);
		(*(CardPool + Result))--;
	}

	return Result;
}

// 카드 남았는지 확인
bool Day0529_CheckCardPool(int* CardPool)
{
	bool bIsPossible = false;
	for (int i = 1; i <= Day0529_CARD_MAX; i++)
	{
		if (CardPool[i] != 0)
		{
			bIsPossible = true;
		}
	}

	return bIsPossible;
}

// 턴 주인 안내
void Day0529_PrintTurnOwner(bool bIsPlayerTurn)
{
	printf("\n지금은 %s의 턴입니다.\n", bIsPlayerTurn ? "플레이어" : "딜러");
}

// 플레이 턴: 카드 뽑고 히트, 스탠드 선택. 버스트 여부 반환
bool Day0529_PlayTurn(CardPocket& InCardPocket, bool bIsPlayerTurn, int* CardPool)
{
	bool bIsBurst = false;	// 버스트 선택
	int TempCard = 0;		// 뽑은 카드 임시 저장

	// 턴 주인 안내
	Day0529_PrintTurnOwner(bIsPlayerTurn);

	// 플레이어 턴
	int InputAction = 0;
	if (bIsPlayerTurn)
	{
		bool bIsStand = false;	// 스탠드 선택
		while (InCardPocket.TotalScore() < Day0529_WINNING_SCORE && (!bIsBurst && !bIsStand))
		{
			printf("\n1. 히트: 카드 한 장 더 뽑기\n2. 스탠드: 카드 뽑기 멈추기\n행동을 결정해주세요: ");
			cin >> InputAction;
			
			if (InputAction == 1)
			{
				TempCard = Day0529_DrawCard(CardPool);
				printf("뽑은 카드: %s\n", Day0529_GetCardNumberName(TempCard).c_str());
				Day0529_GetCard(InCardPocket, TempCard);
				bIsBurst = Day0529_CheckBurst(InCardPocket);
			}
			else if (InputAction == 2)
			{
				bIsStand = true;
				printf("플레이어 턴 종료. 딜러가 카드를 뽑습니다.\n");
			}
			else
			{
				printf("잘못된 입력입니다. 다시 입력해주세요.\n");
			}
		}
	}
	// 딜러 턴
	else
	{
		printf("Dearler: %d\n\n", InCardPocket.TotalScore());
		while (InCardPocket.TotalScore() < Day0529_DEALER_SOFT_SCORE)
		{
			TempCard = Day0529_DrawCard(CardPool);
			printf("뽑은 카드: %s\n", Day0529_GetCardNumberName(TempCard).c_str());
			Day0529_GetCard(InCardPocket, TempCard);
		}
		bIsBurst = Day0529_CheckBurst(InCardPocket);
	}

	return bIsBurst;
}

// 카드 주머니에 넣기
void Day0529_GetCard(CardPocket& InCardPocket, int CardNumber)
{
	if (CardNumber == 1)
	{
		InCardPocket.AceCount++;
	}
	else if (CardNumber == 10 || CardNumber == 11 || CardNumber == 12 || CardNumber == 13)
	{
		InCardPocket.Score_ExceptAce += 10;
	}
	else
	{
		InCardPocket.Score_ExceptAce += CardNumber;
	}
}

// 버스트 확인
bool Day0529_CheckBurst(CardPocket& InCardPocket)
{
	return InCardPocket.TotalScore() > Day0529_WINNING_SCORE;
}

// 블랙잭인지 확인 (A + 10)
bool Day0529_CheckBlackJack(CardPocket& InCardPocket)
{
	return (InCardPocket.TotalScore() == Day0529_WINNING_SCORE && InCardPocket.AceCount > 0);
}

// 승패 판정
void Day0529_DetermineWinner(CardPocket& PlayerPocket, CardPocket& DealerPocket, bool bIsPlayerBlackJack, bool bIsDealerBlackJack)
{
	int Winner = -1;	// 0: 무승부, 1: 플레이어 승, 2: 딜러 승

	int PlayerTotal = PlayerPocket.TotalScore();
	int DealerTotal = DealerPocket.TotalScore();

	// 플레이어가 블랙잭인 경우:  딜러도 블랙잭이어도 무조건 플레이어 승
	if (bIsPlayerBlackJack)
	{
		Winner = 1;
		printf("블랙잭!!!!!\n");
	}
	// 딜러만 블랙잭인 경우
	else if (bIsDealerBlackJack)
	{
		Winner = 2;
		printf("블랙잭!!!!!\n");
	}
	// 둘 다 블랙잭이 아닌 경우
	else if (!bIsPlayerBlackJack && !bIsDealerBlackJack)
	{
		// 블랙잭이 아닌 경우
		// 둘 다 버스트가 아닌 경우
		if (PlayerTotal <= Day0529_WINNING_SCORE && DealerTotal <= Day0529_WINNING_SCORE)
		{
			if (PlayerTotal > DealerTotal)
			{
				Winner = 1;
			}
			else if (PlayerTotal < DealerTotal)
			{
				Winner = 2;
			}
			else
			{
				Winner = 0;
			}
		}
		// 둘 중 하나라도 버스트인 경우
		// 플레이어가 버스트면 무조건 딜러 승 (둘 다 버스트여도 플레이어가 버스트면 딜러 승)
		// 딜러가 버스트면 무조건 플레이어 승
		// 둘 중 하나라도 버스트
		if (PlayerTotal > Day0529_WINNING_SCORE)
		{
			printf("버스트!!!!!\n");
			Winner = 2;
		}
		else if (DealerTotal > Day0529_WINNING_SCORE)
		{
			printf("버스트!!!!!\n");
			Winner = 1;
		}
		// 둘 다 버스트 안 당함
		else if (PlayerTotal == DealerTotal)
		{
			Winner = 0;
		}
		else if (PlayerTotal > DealerTotal)
		{
			Winner = 1;
		}
		else if (PlayerTotal < DealerTotal)
		{
			Winner = 2;
		}
		else
		{
			Winner = -1;	// error
		}
	}

	// 승패 결과 출력
	printf("플레이어의 총점은 %d점, 딜러의 총점은 %d점입니다.\n", PlayerTotal, DealerTotal);
	Day0529_PrintWinner(Winner);
}
void Day0529_PrintWinner(int Winner)
{
	string WinnerPhrase = "";
	if (Winner == 0)
	{
		WinnerPhrase = "무승부입니다!!";
	}
	else if (Winner == 1)
	{
		WinnerPhrase = "플레이어가 이겼습니다!!";
	}
	else if (Winner == 2)
	{
		WinnerPhrase = "딜러가 이겼습니다!!";
	}
	else
	{
		WinnerPhrase = "Error!!!!!!!!!!";
	}

	printf("게임 결과는\n.\n.\n.\n%s\n수고하셨습니다.\n\n", WinnerPhrase.c_str());
}
