#pragma once

#include <string>

// 블랙잭 만들기
// 게임 목표
//   두 카드의 합이 21에 가깝게 만들되, 21을 넘지 않는 것이 목표
//   21을 초과하면(버스트, Bust)  즉시 패배
// 배팅은 없음
// 카드의 값
//   2~10: 카드 숫자 그대로 점수.
//   J(잭), Q(퀸), K(킹) : 각각 10점.
//   A(에이스) : 1점 또는 11점(유리한 쪽으로 자동 선택).
// 게임 진행 절차
//   초기 배분
//     딜러와 플레이어 모두 2장씩 카드를 받음.
//     플레이어의 카드는 두 장 모두 공개.
//     딜러는 한 장은 공개(오픈 카드), 한 장은 비공개(홀 카드).
//   플레이어 턴
//     플레이어가 먼저 행동.
//     선택지:
//       Hit(히트) : 카드를 한 장 더 받음.
//       Stand(스탠드) : 더 이상 카드를 받지 않고 멈춤.
//     플레이어가 21을 초과하면(버스트) 즉시 패배.
//   딜러 턴
//     플레이어가 스탠드를 하면 딜러 차례.
//     딜러는 자신의 카드 합이 17 이상이 될 때까지 계속 히트(카드 받기)해야 함.
//       A가 포함된 "소프트 17"(A + 6 = 7 또는 17)도 멈춤.
//     17 이상이면 멈추고, 21을 넘으면 딜러 패배.
// 승패 판정
//   버스트가 아닌 경우, 점수 비교.
//     플레이어가 21에 더 가까우면 승리.
//     동점이면 무승부(Push).
//     딜러가 더 가까우면 패배.
// 블랙잭: 처음 받은 두 장이 A + 10(또는 J, Q, K)이면 블랙잭.일반적으로 블랙잭이 단순 21점보다 우선함.

const int Day0529_CARD_MAX = 13;	// 스페이드, 다이아몬드, 클로버, 하트가 각각 13장씩 존재
const int Day0529_WINNING_SCORE = 21;
const int Day0529_DEALER_SOFT_SCORE = 17;

struct CardPocket
{
	int Score_ExceptAce = 0;	// 지금까지 뽑은 카드 점수 합산 (에이스 제외)
	int AceCount = 0;	// 지금까지 뽑은 에이스 개수

	// 에이스까지 합산한 총점
	int TotalScore()
	{
		int Result = Score_ExceptAce;	// Ace 제외 카드들로 점수 초기화

		// Ace 카드들 점수 결정
		if (AceCount)
		{
			// 21점을 넘으면 바로 패배이기 때문에 Ace는 더했을 때 21점보다 작거나 같을 때만 11점을 가질 수 있다.
			const int HighAce = 11;
			const int LowAce = 1;
			for (int i = 0; i < AceCount; i++)
			{
				if (Result + HighAce > Day0529_WINNING_SCORE)
				{
					Result += LowAce;
				}
				else
				{
					Result += HighAce;
				}
			}
		}

		return Result;
	}
};

void Homework02_Run();

void Day0529_BlackJack_Play(int* CardPool);

int Day0529_GameReady(int* CardPool, CardPocket& Dealer, CardPocket& Player);

std::string Day0529_GetCardNumberName(int CardNumber);

int Day0529_DrawCard(int* CardPool);

bool Day0529_CheckCardPool(int* CardPool);

void Day0529_PrintTurnOwner(bool bIsPlayerTurn);

bool Day0529_PlayTurn(CardPocket& InCardPocket, bool bIsPlayerTurn, int* CardPool);

void Day0529_GetCard(CardPocket& InCardPocket, int CardNumber);

bool Day0529_CheckBurst(CardPocket& InCardPocket);

bool Day0529_CheckBlackJack(CardPocket& InCardPocket);

void Day0529_DetermineWinner(CardPocket& PlayerPocket, CardPocket& DealerPocket, bool bIsPlayerBlackJack, bool bIsDealerBlackJack);

void Day0529_PrintWinner(int Winner);

