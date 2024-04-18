# LittleNihtMares 모작
> 한국 콘텐츠 진흥원 교육프로그램 중간프로젝트 과제물

## 1. 게임기획
게임 `LittleNightMares`모작 입니다  
분위기, 게임조작감을 모방하였습니다

### 게임소개 영상
[![](http://img.youtube.com/vi/uNCOKJogXKc/0.jpg)](https://www.youtube.com/watch?v=uNCOKJogXKc)

> YoutubeLink : https://www.youtube.com/watch?v=uNCOKJogXKc

> LittleNightMares의 리소스로 모작하였습니다.

## 2. 게임제작 기간및 인원
**<ins>22.10.04 ~ 22.11.07 (약 1개월)</ins>**  
하루 약3시간씩 제작

### 2인개발
- 프로그래밍 `1명`
- 아트디자인 `1명`

## 3. 담당파트
2인중 `프로그래밍` 으로 크게

- 기본이동
- Player 상호작용 (소품밀기, 클라이밍)

부분을 담당하였습니다.

### 주요코드

### 1. 클라이밍 기능

```Cpp
void UAYU_PlayerMoveComp::OnActionClimbPressed()
{
    bPressed = true;
    if(bClimbed) //상호작용 버튼시 현재 클라이밍 상태인지 확인
    {
      OutClimb();
    }
    else
    {
      // 라인트레이스를 이용해 클라이밍 할수있는 환경이지 확인
      FVector Start = me->GetMesh()->GetComponenetLocation() + FVector(0, 0, 50);
      FVector End = Start + me->GetMesh()->GetRightVector() * 40;

      FHitResult HitInfo;
      FCollisionQueryParams Params;
      Params.AddIgnored(me);

      bool bHit = GetWorld()->LineTraceSingleByChannel(HitInfo, Start, End, ECC_Visibility, Params);

      // 전방에 클라이밍할수있는 물체확인 (ComponentName으로 확인중)
      if(bHit && (HitInfo.GetComponent()->GetFName() == "Climb"))
      {
          bClimb = true;
          me->SetActorRotation(FRotator(0, (UKismetMathLibrary::Conv_VectorToRotator(HitInfo.Normal).Yaw - 180), 0)); // 벽과 수평을위해

          myMovement->Velocity = FVector::ZeroVector; // 모든 가속도 초기화
          myMovement->SetMovementMode(MOVE_Flying); // MoveMode를 Fly로 변경 
          myMovement->bOrientRotationToMovement = false;
          ClimbUp = UKismeMathLibrary::GetUpVector(Rotator(0, 0, 0)); // W키로 이동하는 벡터를 윗벡터로 변환
          InClimb(); // 클라임을 지속할수있는 상황인지 확인하는 함수
    }
```

```Cpp
void UAn_PlayerMoveComp::InClimb()
{
	if (!bClimbUp)
	{
		//정상 감지 라인트레이스
		FVector TopStart = me->GetMesh()->GetComponentLocation() + FVector(0, 0, 55);
		FVector TopEnd = TopStart + me->GetMesh()->GetRightVector() * 40;

		FHitResult HitTopInfo;
		FCollisionQueryParams TopParams;
		TopParams.AddIgnoredActor(me);
		bool bTop = GetWorld()->LineTraceSingleByChannel(HitTopInfo, TopStart, TopEnd, ECC_Visibility, TopParams);
		if (!bTop) //정상에 도달해 라인트레이스에 아무것도 감지되지않을경우
		{
			myYaw = me->GetActorRotation().Yaw;
			bClimbUp = true;
			bClimb = false;
			PlayClimbUpAnim(); //클라임 종료 애니메이션 함수 실행
		}
	}
	// 클라이밍 유지 라인트레이스
	FVector start = me->GetMesh()->GetComponentLocation() + FVector(0, 0, 50);
	FVector end = start + me->GetMesh()->GetRightVector() * 40;

	FHitResult HitInfo;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(me);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitInfo, start, end, ECC_Visibility, Params);
	if (!bHit) 클라이밍 도중 벽에서 떨어져나올경우
	{
		OutClimb();
	}
}

	//클라임을 끝내고 원래 상태로돌아오기
void UAn_PlayerMoveComp::OutClimb()
{
	//bClimb를 false로바꾸고 
	bClimb = false;
	//movemode를 walk로 변경
	myMovement->SetMovementMode(MOVE_Walking);
	myMovement->bOrientRotationToMovement = true;
}

```

## 4. 주요코드 플로우차트

![image](https://github.com/zombow/EscapeFromHorror/assets/82148187/b8c02121-1e7a-4a86-91e6-49f83f060a73)
