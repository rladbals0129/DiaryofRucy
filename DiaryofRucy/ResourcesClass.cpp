#include "Stdafx.h"
#include "ResourcesClass.h"

#define RESIZE      1.3


HRESULT ResourcesClass::init()
{
	//============호준============
#pragma region 호준
    // Player
    D2DMANAGER->loadImageD2D("스태프불릿", L"Resources/Images/Player/Bullets/스태프불릿.png", 32, 32);
    D2DMANAGER->loadImageD2D("애로우", L"Resources/Images/Player/Bullets/애로우.png", 50, 50);
    D2DMANAGER->loadImageD2D("검1", L"Resources/Images/Player/Bullets/검1.png", 960, 576, 5, 3);
    D2DMANAGER->loadImageD2D("검2", L"Resources/Images/Player/Bullets/검2.png", 960, 576, 5, 3);
    D2DMANAGER->loadImageD2D("검3", L"Resources/Images/Player/Bullets/검3.png", 960, 768, 5, 4);
    D2DMANAGER->loadImageD2D("그림자", L"Resources/Images/Player/그림자.png", 20, 8);

    IMAGEMANAGER->addFrameImage("루시달리기", "Resources/Images/Player/달리기.bmp", 400, 800, 4, 8, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("루시기본공격", "Resources/Images/Player/기본공격.bmp", 600, 800, 6, 8, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("루시검공격", "Resources/Images/Player/검공격.bmp", 900, 800, 9, 8, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("루시활공격", "Resources/Images/Player/활공격.bmp", 300, 800, 3, 8, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("루시차지샷", "Resources/Images/Player/차지샷.bmp", 300, 800, 3, 8, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("루시회피", "Resources/Images/Player/저스트회피.bmp", 600, 800, 6, 8, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("루시피격", "Resources/Images/Player/피격.bmp", 300, 800, 3, 8, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("루시걷기", "Resources/Images/Player/걷기.bmp", 300, 800, 3, 8, true, MAGENTA);
    IMAGEMANAGER->addImage("루시사망", "Resources/Images/Player/사망.bmp", 100, 100, true, MAGENTA);

    // Skill
    D2DMANAGER->loadImageD2D("벽력일섬아이콘", L"Resources/Images/Player/Skills/벽력일섬아이콘.png", 32, 32);
    D2DMANAGER->loadImageD2D("벽력일섬", L"Resources/Images/Player/Skills/벽력일섬.png", 960, 960, 5, 5);
    D2DMANAGER->loadImageD2D("아이시클스파크아이콘", L"Resources/Images/Player/Skills/아이시클스파크아이콘.png", 32, 32);
    D2DMANAGER->loadImageD2D("아이시클스파크2", L"Resources/Images/Player/Skills/아이시클스파크2.png", 960, 768, 5, 4);
    D2DMANAGER->loadImageD2D("아이시클스파크1", L"Resources/Images/Player/Skills/아이시클스파크1.png", 960, 576, 5, 3);
    D2DMANAGER->loadImageD2D("바람의상처아이콘", L"Resources/Images/Player/Skills/바람의상처아이콘.png", 32, 32);
    D2DMANAGER->loadImageD2D("바람의상처", L"Resources/Images/Player/Skills/바람의상처.png", 875, 350, 5, 2);
    D2DMANAGER->loadImageD2D("익스플로전아이콘", L"Resources/Images/Player/Skills/익스플로전아이콘.png", 32, 32);
    D2DMANAGER->loadImageD2D("익스플로전1", L"Resources/Images/Player/Skills/익스플로전1.png", 960, 960, 5, 5);
    D2DMANAGER->loadImageD2D("익스플로전2", L"Resources/Images/Player/Skills/익스플로전2.png", 960, 3840, 5, 20);
    D2DMANAGER->loadImageD2D("스킬캐스팅", L"Resources/Images/Player/Skills/스킬캐스팅.png", 960, 384, 5, 2);


    // UI
    IMAGEMANAGER->addImage("블랙보드", "Resources/Images/UI/블랙보드.bmp", WINSIZE_X, WINSIZE_Y);

    D2DMANAGER->loadImageD2D("스테미나UI", L"Resources/Images/UI/commonUI/스테미나UI.png", 230* RESIZE, 90* RESIZE);
    D2DMANAGER->loadImageD2D("경험치게이지UI", L"Resources/Images/UI/commonUI/경험치게이지UI.png", 126* RESIZE, 7* RESIZE);
    D2DMANAGER->loadImageD2D("스테미나게이지UI", L"Resources/Images/UI/commonUI/스테미나게이지UI.png", 166* RESIZE, 14* RESIZE);
    D2DMANAGER->loadImageD2D("레벨UI", L"Resources/Images/UI/commonUI/레벨UI.png", 320, 19,10,1);
    D2DMANAGER->loadImageD2D("골드UI", L"Resources/Images/UI/commonUI/골드UI.png", 14, 19 );
    D2DMANAGER->loadImageD2D("골드숫자UI", L"Resources/Images/UI/commonUI/골드숫자UI.png", 140, 20, 10, 1);
    D2DMANAGER->loadImageD2D("무기슬롯A", L"Resources/Images/UI/commonUI/무기슬롯A.png", 70, 68);
    D2DMANAGER->loadImageD2D("무기슬롯B", L"Resources/Images/UI/commonUI/무기슬롯B.png", 70, 68);
    D2DMANAGER->loadImageD2D("포션슬롯", L"Resources/Images/UI/commonUI/포션슬롯UI.png", 44, 44);
    D2DMANAGER->loadImageD2D("체력UI", L"Resources/Images/UI/commonUI/체력UI.png", 48, 22, 2, 1);
    D2DMANAGER->loadImageD2D("마나UI", L"Resources/Images/UI/commonUI/마나UI.png", 48, 24, 2, 1);
    D2DMANAGER->loadImageD2D("스킬슬롯UI", L"Resources/Images/UI/commonUI/스킬슬롯UI.png", 40, 40);
    D2DMANAGER->loadImageD2D("불스킬마나UI", L"Resources/Images/UI/commonUI/불스킬마나UI.png",     24, 24);
    D2DMANAGER->loadImageD2D("바람스킬마나UI", L"Resources/Images/UI/commonUI/바람스킬마나UI.png", 24, 24);
    D2DMANAGER->loadImageD2D("얼음스킬마나UI", L"Resources/Images/UI/commonUI/얼음스킬마나UI.png", 24, 24);
    D2DMANAGER->loadImageD2D("번개스킬마나UI", L"Resources/Images/UI/commonUI/번개스킬마나UI.png", 24, 24);
    D2DMANAGER->loadImageD2D("마나소모량UI", L"Resources/Images/UI/commonUI/마나소모량UI.png", 200, 29, 10, 1);
    D2DMANAGER->loadImageD2D("스킬쿨타임UI", L"Resources/Images/UI/commonUI/스킬쿨타임UI.png", 200, 29, 10, 1);
        
    D2DMANAGER->loadImageD2D("미니맵배경UI", L"Resources/Images/UI/MapUI/미니맵배경UI.png", 200, 200);
    D2DMANAGER->loadImageD2D("미니맵위치UI", L"Resources/Images/UI/MapUI/미니맵위치UI.png", 64, 8, 8, 1);

    D2DMANAGER->loadImageD2D("시작&출구", L"Resources/Images/UI/MapUI/MiniMap/시작&출구.png", 1008, 816);
    D2DMANAGER->loadImageD2D("노멀방1", L"Resources/Images/UI/MapUI/MiniMap/노멀방1.png", 1008, 768);
    D2DMANAGER->loadImageD2D("노멀방2", L"Resources/Images/UI/MapUI/MiniMap/노멀방2.png", 1008, 768);
    D2DMANAGER->loadImageD2D("노멀방3", L"Resources/Images/UI/MapUI/MiniMap/노멀방3.png", 1008, 768);
    D2DMANAGER->loadImageD2D("노멀방4", L"Resources/Images/UI/MapUI/MiniMap/노멀방4.png", 1008, 672);
    D2DMANAGER->loadImageD2D("노멀방5", L"Resources/Images/UI/MapUI/MiniMap/노멀방5.png", 1008, 768);
    D2DMANAGER->loadImageD2D("노멀방6", L"Resources/Images/UI/MapUI/MiniMap/노멀방6.png", 1008, 768);
    D2DMANAGER->loadImageD2D("노멀방7", L"Resources/Images/UI/MapUI/MiniMap/노멀방7.png", 1008, 672);
    D2DMANAGER->loadImageD2D("노멀방8", L"Resources/Images/UI/MapUI/MiniMap/노멀방8.png", 1008, 672);
    D2DMANAGER->loadImageD2D("노멀방9", L"Resources/Images/UI/MapUI/MiniMap/노멀방9.png", 1008, 672);
    D2DMANAGER->loadImageD2D("노멀방10", L"Resources/Images/UI/MapUI/MiniMap/노멀방10.png", 1008, 672);
    D2DMANAGER->loadImageD2D("노멀방11", L"Resources/Images/UI/MapUI/MiniMap/노멀방11.png", 1008, 672);
    D2DMANAGER->loadImageD2D("보스방", L"Resources/Images/UI/MapUI/MiniMap/보스방.png", 1104, 960);
    D2DMANAGER->loadImageD2D("분수&석상방", L"Resources/Images/UI/MapUI/MiniMap/분수&석상방.png",1008 , 672);
    D2DMANAGER->loadImageD2D("상자방", L"Resources/Images/UI/MapUI/MiniMap/상자방.png", 1008 , 672);
    D2DMANAGER->loadImageD2D("상점방", L"Resources/Images/UI/MapUI/MiniMap/상점방.png", 960,576 );

    D2DMANAGER->loadImageD2D("지팡이차지", L"Resources/Images/UI/PlayerUI/지팡이차지.png", 960, 384, 5, 2);
    D2DMANAGER->loadImageD2D("차지샷배경", L"Resources/Images/UI/PlayerUI/차지샷배경.png", 77, 17);
    D2DMANAGER->loadImageD2D("차지샷게이지", L"Resources/Images/UI/PlayerUI/차지샷게이지.png", 65, 5);
      
    D2DMANAGER->loadImageD2D("대미지표기넘버", L"Resources/Images/UI/commonUI/대미지표기넘버.png", 200, 29,10,1);

    D2DMANAGER->loadImageD2D("히트이펙트", L"Resources/Images/UI/commonUI/히트이펙트.png", 960, 768, 5, 4);

    D2DMANAGER->loadImageD2D("보스체력배경", L"Resources/Images/UI/BossUI/보스체력배경.png", 506, 32);
    D2DMANAGER->loadImageD2D("보스체력게이지", L"Resources/Images/UI/BossUI/보스체력게이지.png", 506, 32);

    D2DMANAGER->loadImageD2D("보스체력게이지", L"Resources/Images/UI/BossUI/보스체력게이지.png", 506, 32);


    D2DMANAGER->loadImageD2D("토글맵배경", L"Resources/Images/UI/MapUI/toggleMap/토글맵배경.png", 455, 317);
    D2DMANAGER->loadImageD2D("토글맵미확인방", L"Resources/Images/UI/MapUI/toggleMap/토글맵미확인방.png", 30, 30);
    D2DMANAGER->loadImageD2D("토글맵미확인아이콘", L"Resources/Images/UI/MapUI/toggleMap/토글맵미확인아이콘.png", 30, 30);
    D2DMANAGER->loadImageD2D("토글맵확인방", L"Resources/Images/UI/MapUI/toggleMap/토글맵확인방.png", 30, 30);
    D2DMANAGER->loadImageD2D("토글맵보스방", L"Resources/Images/UI/MapUI/toggleMap/토글맵보스방.png", 30, 30);
    D2DMANAGER->loadImageD2D("토글맵상자방", L"Resources/Images/UI/MapUI/toggleMap/토글맵상자방.png", 30, 30);
    D2DMANAGER->loadImageD2D("토글맵상점방", L"Resources/Images/UI/MapUI/toggleMap/토글맵상점방.png", 30, 30);
    D2DMANAGER->loadImageD2D("토글맵시작방", L"Resources/Images/UI/MapUI/toggleMap/토글맵시작방.png", 30, 30);
    D2DMANAGER->loadImageD2D("토글맵특수방", L"Resources/Images/UI/MapUI/toggleMap/토글맵특수방.png", 30, 30);
    D2DMANAGER->loadImageD2D("토글맵목표방", L"Resources/Images/UI/MapUI/toggleMap/토글맵목표방.png", 30, 30);
    D2DMANAGER->loadImageD2D("현재맵표시", L"Resources/Images/UI/MapUI/toggleMap/현재맵표시.png", 30, 30);
    
    
    D2DMANAGER->loadImageD2D("반딧불이숲", L"Resources/Images/UI/RoomUI/반딧불이숲.png", 300, 255);
    D2DMANAGER->loadImageD2D("1층", L"Resources/Images/UI/RoomUI/1층.png", 300, 255);
    D2DMANAGER->loadImageD2D("2층", L"Resources/Images/UI/RoomUI/2층.png", 300, 255);
    D2DMANAGER->loadImageD2D("3층", L"Resources/Images/UI/RoomUI/3층.png", 300, 255);


    D2DMANAGER->loadImageD2D("킹슬라임입장UI", L"Resources/Images/UI/BossUI/킹슬라임입장UI.png", 960, 540);
    D2DMANAGER->loadImageD2D("메가플라임입장UI", L"Resources/Images/UI/BossUI/메가플라임입장UI.png", 960, 540);
    D2DMANAGER->loadImageD2D("머쉬맘보스입장UI", L"Resources/Images/UI/BossUI/머쉬맘보스입장UI.png", 960, 540);



    D2DMANAGER->loadImageD2D("검UI", L"Resources/Images/UI/ItemUI/검UI.png", 32, 32);
    D2DMANAGER->loadImageD2D("활UI", L"Resources/Images/UI/ItemUI/활UI.png", 32, 32);
    D2DMANAGER->loadImageD2D("지팡이UI", L"Resources/Images/UI/ItemUI/지팡이UI.png", 32, 32);



    // 어빌리티
    D2DMANAGER->loadImageD2D("성물설명창", L"Resources/Images/UI/ItemUI/성물설명창.png", 200, 60);

    D2DMANAGER->loadImageD2D("냄뚜", L"Resources/Images/UI/ItemUI/냄뚜.png", 32*RESIZE, 32 * RESIZE);
    D2DMANAGER->loadImageD2D("보름달", L"Resources/Images/UI/ItemUI/보름달.png", 32 * RESIZE, 32 * RESIZE);
    D2DMANAGER->loadImageD2D("신성한유물", L"Resources/Images/UI/ItemUI/신성한유물.png", 32 * RESIZE, 32 * RESIZE);




#pragma endregion





    //============성한============
#pragma region 성한

    D2DMANAGER->loadImageD2D("시작포탈", L"Resources/Images/Object/시작포탈.png", 960, 384, 5, 2);
    D2DMANAGER->loadImageD2D("스테이지포탈", L"Resources/Images/Object/스테이지포탈.png", 960, 960, 5, 5);

    D2DMANAGER->loadImageD2D("벽-상", L"Resources/Images/Maps/Wall/벽-상.png", 288, 327);
    D2DMANAGER->loadImageD2D("벽-하", L"Resources/Images/Maps/Wall/벽-하.png", 192, 144);
    D2DMANAGER->loadImageD2D("벽-우", L"Resources/Images/Maps/Wall/벽-우.png", 269, 458);
    D2DMANAGER->loadImageD2D("벽-좌", L"Resources/Images/Maps/Wall/벽-좌.png", 271, 476);

    // 사운드 추가
    SOUNDMANAGER->addSound("걷기1", "Resources/audio/걷기1.ogg", false, false);
    SOUNDMANAGER->addSound("걷기2", "Resources/audio/걷기2.ogg", false, false);
    SOUNDMANAGER->addSound("달리기1", "Resources/audio/달리기1.wav", false, false);
    SOUNDMANAGER->addSound("달리기2", "Resources/audio/달리기2.wav", false, false);
    SOUNDMANAGER->addSound("달리기3", "Resources/audio/달리기3.wav", false, false);
    SOUNDMANAGER->addSound("달리기4", "Resources/audio/달리기4.wav", false, false);
    SOUNDMANAGER->addSound("루시피격음", "Resources/audio/루시피격음.ogg", false, false);
    SOUNDMANAGER->addSound("맵통로개방", "Resources/audio/맵통로개방.ogg", false, false);
    SOUNDMANAGER->addSound("메뉴클릭", "Resources/audio/메뉴클릭.ogg", false, false);
    SOUNDMANAGER->addSound("몬스터피격음", "Resources/audio/몬스터피격음.ogg", false, false);
    SOUNDMANAGER->addSound("벽돌위이동1", "Resources/audio/벽돌위이동1.ogg", false, false);
    SOUNDMANAGER->addSound("벽돌위이동2", "Resources/audio/벽돌위이동2.ogg", false, false);
    SOUNDMANAGER->addSound("보스사망", "Resources/audio/보스사망.ogg", false, false);
    SOUNDMANAGER->addSound("스킬바람의상처", "Resources/audio/스킬바람의상처.ogg", false, false);
    SOUNDMANAGER->addSound("스킬일섬1", "Resources/audio/스킬일섬1.ogg", false, false);
    SOUNDMANAGER->addSound("스킬일섬2", "Resources/audio/스킬일섬2.ogg", false, false);
    SOUNDMANAGER->addSound("보스클리어", "Resources/audio/보스클리어.ogg", false, false);
    SOUNDMANAGER->addSound("익스플로전", "Resources/audio/익스플로전.ogg", false, false);
    SOUNDMANAGER->addSound("지팡이기본공격", "Resources/audio/지팡이기본공격.ogg", false, false);
    SOUNDMANAGER->addSound("지팡이차지", "Resources/audio/지팡이차지.wav", false, false);
    SOUNDMANAGER->addSound("회피", "Resources/audio/회피.ogg", false, false);
    SOUNDMANAGER->addSound("회피공격", "Resources/audio/회피공격.ogg", false, false);
    SOUNDMANAGER->addSound("몬스터피격음", "Resources/audio/몬스터피격음.ogg", false, false);
    SOUNDMANAGER->addSound("스킬캐스팅", "Resources/audio/스킬캐스팅.ogg", false, false);
    SOUNDMANAGER->addSound("몬스터피격음", "Resources/audio/몬스터피격음.ogg", false, false);
    SOUNDMANAGER->addSound("검1타", "Resources/audio/검1타.ogg", false, false);
    SOUNDMANAGER->addSound("검3타", "Resources/audio/검3타.ogg", false, false);
    SOUNDMANAGER->addSound("검5타", "Resources/audio/검5타.ogg", false, false);
    SOUNDMANAGER->addSound("아이시슬스파크", "Resources/audio/아이시슬스파크.ogg", false, false);
    SOUNDMANAGER->addSound("슬라임공격", "Resources/audio/슬라임공격.ogg", false, false);
    SOUNDMANAGER->addSound("슬라임공격준비", "Resources/audio/슬라임공격준비.ogg", false, false);
    SOUNDMANAGER->addSound("상자열림", "Resources/audio/상자열림.ogg", false, false);
    SOUNDMANAGER->addSound("플라임가시생성", "Resources/audio/플라임가시생성.ogg", false, false);
    SOUNDMANAGER->addSound("활시위소리", "Resources/audio/활시위소리.ogg", false, false);
    SOUNDMANAGER->addSound("오브젝트체력", "Resources/audio/오브젝트체력.ogg", false, false);
    SOUNDMANAGER->addSound("오브젝트마나", "Resources/audio/오브젝트마나.ogg", false, false);
    SOUNDMANAGER->addSound("플라임독발사", "Resources/audio/플라임독발사.ogg", false, false);
    SOUNDMANAGER->addSound("오프닝&배경", "Resources/audio/오프닝&배경.ogg", true, true);
    SOUNDMANAGER->addSound("슬라임사망", "Resources/audio/슬라임사망.ogg", false, false);
    SOUNDMANAGER->addSound("스네이크&플라임사망", "Resources/audio/스네이크&플라임사망.ogg", false, false);
    SOUNDMANAGER->addSound("머쉬맨공격", "Resources/audio/머쉬맨공격.ogg", false, false);
    SOUNDMANAGER->addSound("머쉬맨사망", "Resources/audio/머쉬맨사망.ogg", false, false);
    SOUNDMANAGER->addSound("스네이크공격", "Resources/audio/스네이크공격.ogg", false, false);
    SOUNDMANAGER->addSound("미니버섯폭발카운트", "Resources/audio/미니버섯폭발카운트.ogg", false, false);
    SOUNDMANAGER->addSound("스테이지시작", "Resources/audio/스테이지시작.ogg", false, false);
    SOUNDMANAGER->addSound("스테이지끝", "Resources/audio/스테이지끝.ogg", false, false);
    SOUNDMANAGER->addSound("스킬바람의상처", "Resources/audio/스킬바람의상처.ogg", false, false);
    SOUNDMANAGER->addSound("번개소리", "Resources/audio/번개소리.ogg", false, false);
    SOUNDMANAGER->addSound("레벨업", "Resources/audio/레벨업.ogg", false, false);
  
    SOUNDMANAGER->addSound("보스브금", "Resources/audio/semi-boss.ogg", false, false);
 

#pragma endregion

    //============유민============
#pragma region 유민
    D2DMANAGER->loadImageD2D("보스사망이펙트", L"Resources/Images/Effect/60FPS_AC3T026_Nova_02.png",
        960, 3840, 5, 20);
	IMAGEMANAGER->addFrameImage("킹슬라임IDLE", "Resources/Images/Enemy/Boss/SlimeBoss/Page1/BossSlimeIdle.bmp",
		720, 1439,
		2, 4,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("킹슬라임MOVE", "Resources/Images/Enemy/Boss/SlimeBoss/Page1/BossSlimeMove.bmp",
		1080, 1439,
		3, 4,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("킹슬라임ATTACK", "Resources/Images/Enemy/Boss/SlimeBoss/Page1/BossSlimeAttack.bmp",
		1785, 1439,
		5, 4,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("킹슬라임DIE", "Resources/Images/Enemy/Boss/SlimeBoss/Page1/BossSlimeDie.bmp",
		221, 94,
		1, 1,
		true,
		RGB(255, 0, 255));


    IMAGEMANAGER->addFrameImage("킹슬라임분열IDLE", "Resources/Images/Enemy/Boss/SlimeBoss/Page2/BossSlimePage2Idle.bmp",
        376, 766,
        2, 4,
        true,
        RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("킹슬라임분열MOVE", "Resources/Images/Enemy/Boss/SlimeBoss/Page2/BossSlimePage2Move.bmp",
        564, 766,
        3, 4,
        true,
        RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("킹슬라임분열ATTACK", "Resources/Images/Enemy/Boss/SlimeBoss/Page2/BossSlimePage2Attack1.bmp",
        564, 766,
        3, 4,
        true,
        RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("킹슬라임분열DIE", "Resources/Images/Enemy/Boss/SlimeBoss/Page2/BossSlimePage2Die.bmp",
        124, 56,
        1, 1,
        true,
        RGB(255, 0, 255));




    IMAGEMANAGER->addFrameImage("머쉬맘보스IDLE", "Resources/Images/Enemy/Boss/MushmomBoss/BossMushmamIdle.bmp",
        287, 666,
        2, 4,
        true,
        RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("머쉬맘보스MOVE", "Resources/Images/Enemy/Boss/MushmomBoss/BossMushmamMove.bmp",
        430, 666,
        3, 4,
        true,
        RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("머쉬맘보스ATTACK1", "Resources/Images/Enemy/Boss/MushmomBoss/BossMushmamAttack1.bmp",
        861, 222,
        6, 1,
        true,
        RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("머쉬맘보스ATTACK2", "Resources/Images/Enemy/Boss/MushmomBoss/BossMushmamAttack2.bmp",
        861, 222,
        6, 1,
        true,
        RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("머쉬맘보스ATTACK3", "Resources/Images/Enemy/Boss/MushmomBoss/BossMushmamAttack3.bmp",
        861, 222,
        6, 1,
        true,
        RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("머쉬맘보스DIE", "Resources/Images/Enemy/Boss/MushmomBoss/BossMushmamDie.bmp",
        102, 108,
        1, 1,
        true,
        RGB(255, 0, 255));




    IMAGEMANAGER->addFrameImage("메가플라임IDLE", "Resources/Images/Enemy/Boss/FlimeBoss/BossFlimeIdle.bmp",
        500, 775,
        2, 4,
        true,
        RGB(255, 0, 255));

    IMAGEMANAGER->addFrameImage("메가플라임ATTACK1", "Resources/Images/Enemy/Boss/FlimeBoss/BossFlimeAttack1.bmp",
        762, 775,
        3, 4,
        true,
        RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("메가플라임ATTACK2", "Resources/Images/Enemy/Boss/FlimeBoss/BossFlimeAttack2.bmp",
        762, 775,
        3, 4,
        true,
        RGB(255, 0, 255));

    IMAGEMANAGER->addFrameImage("메가플라임ATTACK3", "Resources/Images/Enemy/Boss/FlimeBoss/BossFlimeAttack1.bmp",
        762, 775,
        3, 4,
        true,
        RGB(255, 0, 255));

    IMAGEMANAGER->addFrameImage("메가플라임DIE", "Resources/Images/Enemy/Boss/FlimeBoss/BossFlimeDie.bmp",
        245, 134,
        1, 1,
        true,
        RGB(255, 0, 255));




    IMAGEMANAGER->addFrameImage("뱀IDLE", "Resources/Images/Enemy/Common/Snake/snakeIdle.bmp",
        88, 189,
        2, 4,
        true,
        RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("뱀MOVE", "Resources/Images/Enemy/Common/Snake/snakeMove.bmp",
        140, 189,
        3, 4,
        true,
        RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("뱀ATTACK", "Resources/Images/Enemy/Common/Snake/snakeAttack.bmp",
        135, 192,
        3, 4,
        true,
        RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("뱀DIE", "Resources/Images/Enemy/Common/Snake/snakeDie.bmp",
        38, 32,
        1, 1,
        true,
        RGB(255, 0, 255));




    IMAGEMANAGER->addFrameImage("슬라임IDLE", "Resources/Images/Enemy/Common/Slime/SlimeIdle.bmp",
        76, 145,
        2, 4,
        true,
        RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("슬라임MOVE", "Resources/Images/Enemy/Common/Slime/SlimeMove.bmp",
        115, 150,
        3, 4,
        true,
        RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("슬라임ATTACK", "Resources/Images/Enemy/Common/Slime/SlimeAttack1.bmp",
        200, 160,
        5, 4,
        true,
        RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("슬라임ATTACK2", "Resources/Images/Enemy/Common/Slime/SlimeAttack2.bmp",
        140, 150,
        3, 4,
        true,
        RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("슬라임DIE", "Resources/Images/Enemy/Common/Slime/SlimeDie.bmp",
        38, 17,
        1, 1,
        true,
        RGB(255, 0, 255));





    IMAGEMANAGER->addFrameImage("머쉬맘IDLE", "Resources/Images/Enemy/Common/Mushmam/mushmamIdle.bmp",
        68, 212,
        2, 4,
        true,
        RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("머쉬맘MOVE", "Resources/Images/Enemy/Common/Mushmam/mushmamMove1.bmp",
        108, 203,
        3, 4,
        true,
        RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("머쉬맘ATTACK", "Resources/Images/Enemy/Common/Mushmam/mushmamAttack1.bmp",
        216, 50,
        6, 1,
        true,
        RGB(255, 0, 255));

    IMAGEMANAGER->addFrameImage("머쉬맘DIE", "Resources/Images/Enemy/Common/Mushmam/mushmamDie.bmp",
        34, 36,
        1, 1,
        true,
        RGB(255, 0, 255));


    IMAGEMANAGER->addFrameImage("꽃IDLE", "Resources/Images/Enemy/Common/Flime/FlimeIdle.bmp",
        161, 243,
        2, 4,
        true,
        RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("꽃ATTACK", "Resources/Images/Enemy/Common/Flime/FlimeAttack1.bmp",
        234, 230,
        3, 4,
        true,
        RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("꽃ATTACK2", "Resources/Images/Enemy/Common/Flime/FlimeAttack2.bmp",
        238, 243,
        3, 4,
        true,
        RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("꽃DIE", "Resources/Images/Enemy/Common/Flime/FlimeDie.bmp",
        79, 46,
        1, 1,
        true,
        RGB(255, 0, 255));


    D2DMANAGER->loadImageD2D("작은일반탄", L"Resources/Images/Enemy/Bullets/EnemySmallBullet.png", 32, 32);
    D2DMANAGER->loadImageD2D("큰일반탄", L"Resources/Images/Enemy/Bullets/EnemyBigBullet.png", 48, 48);
    D2DMANAGER->loadImageD2D("유도탄", L"Resources/Images/Enemy/Bullets/ESK_mushroom.png", 32, 32);
    D2DMANAGER->loadImageD2D("버블", L"Resources/Images/Enemy/Bullets/bubble.png", 99, 99);
    D2DMANAGER->loadImageD2D("독탄", L"Resources/Images/Enemy/Bullets/FlimeAttack1.png", 200, 160, 5, 4);
    D2DMANAGER->loadImageD2D("가시", L"Resources/Images/Enemy/Bullets/skill_flime2.png", 960, 576, 5, 3);
    D2DMANAGER->loadImageD2D("가시미리보기", L"Resources/Images/Enemy/Bullets/skill_flime_skillLine.png", 64, 64);
    
    
    D2DMANAGER->loadImageD2D("적사망이펙트", L"Resources/Images/Effect/EnemyDie.png", 960, 2304, 5, 12);

    D2DMANAGER->loadImageD2D("꽃뿌리탄", L"Resources/Images/Enemy/Bullets/skill_flime2.png", 960, 576, 5, 3);

   

    IMAGEMANAGER->addImage("초록포탑", "Resources/Images/Enemy/Bullets/mGreen1.bmp",
        13, 13,
        true, RGB(255, 0, 255));

    IMAGEMANAGER->addImage("큰초록포탑", "Resources/Images/Enemy/Bullets/mBossGreen1.bmp",
        43, 41,
        true, RGB(255, 0, 255));
    IMAGEMANAGER->addImage("큰보라포탑", "Resources/Images/Enemy/Bullets/mBossPurple1.bmp",
        43, 41,
        true, RGB(255, 0, 255));
    IMAGEMANAGER->addImage("큰민트포탑", "Resources/Images/Enemy/Bullets/mBossMint1.bmp",
        43, 41,
        true, RGB(255, 0, 255));




#pragma endregion






    //============혜빈============
#pragma region 혜빈







#pragma endregion






	return S_OK;
}
