anim { "enemy.anm"; "st01enm.anm"; }
ecli { "default.ecl"; }

void Boss()
{
    setBoss(0);
    anmSelect(3);
    anmSetMain(0, 0);
    flagSet(64);
    setHurtbox(48.0f, 48.0f);
    setHitbox(48.0f, 48.0f);
    setInvuln(60);
    lifeSet(11300);
    movePosTime(60, 4, 0.0f, 128.0f);
    $CAPTURE = 1;
    wait(61);
    anmSetSprite(0, 0);
    dialogWait();
    anmSetMain(0, 0);
    moveLimit(0.0f, 128.0f, 280.0f, 64.0f);
    anmSelect(1);
    anmSetSprite(1, 53);
    anmSetSprite(2, 113);
    anmSelect(3);
    fog(160.0f, 3190703);
    unless ($SPELL_ID >= 0) goto Boss_1632 @ 0;
    unless (($SPELL_ID >= 0) && ($SPELL_ID <= 3)) goto Boss_816 @ 0;
    lifeSet(1500);
    @BossCard1();
    goto Boss_1632 @ 0;
Boss_816:
    unless (($SPELL_ID >= 4) && ($SPELL_ID <= 7)) goto Boss_1044 @ 0;
    lifeSet(3000);
    @BossCard2();
    goto Boss_1632 @ 0;
Boss_1044:
    unless (($SPELL_ID >= 8) && ($SPELL_ID <= 11)) goto Boss_1272 @ 0;
    lifeSet(3000);
    @BossCard3();
    goto Boss_1632 @ 0;
Boss_1272:
    unless (($SPELL_ID >= 12) && ($SPELL_ID <= 13)) goto Boss_1500 @ 0;
    lifeSet(2500);
    @BossCard4();
    goto Boss_1632 @ 0;
Boss_1500:
    unless ($SPELL_ID == 119) goto Boss_1632 @ 0;
    lifeSet(2500);
    @BossCard4();
Boss_1632:
    @Boss1();
    return;
}

void Boss1()
{
    var A, B, C, D;
    diffI($A, 90, 90, 40, 40);
    timerReset();
    setNext(0, 1500, 2100, "BossCard1");
    lifeMarker(0, 1500.0f, -24448);
!EN
    stars(1);
!HL
    stars(2);
!*
    anmSelect(3);
    anmSetMain(0, 0);
    anmPlay(1, 65);
    playSound(54);
    wait(60);
    anmPlay(1, 76);
    playSound(6);
    diffI($D, 2, 2, 4, 4);
    goto Boss1_708 @ 0;
Boss1_412:
    anmSelectedPlay(0);
    wait(20);
    @Boss1_at() async;
    wait(120);
    unless ($D < 4) goto Boss1_660 @ 0;
    $D = $D + 1;
Boss1_660:
    moveRand(30, 4, 2.0f);
    wait(32);
Boss1_708:
    if 1 goto Boss1_412 @ 0;
    return;
}

void Boss1_at()
{
    etNew(0);
    etSprite(0, 9, 1);
    etAim(0, 3);
    etCountD(0, 42, 46, 50, 54, 2, 3, 6, 7);
    etSpeedD(0, 3.0f, 5.0f, 7.0f, 10.0f, 3.0f, 4.0f, 5.0f, 2.0f);
    etNew(1);
    etSprite(1, 9, 9);
    etAim(1, 3);
    etCountD(1, 44, 48, 52, 56, 2, 3, 6, 7);
    etSpeedD(1, 3.0f, 5.0f, 7.0f, 10.0f, 3.0f, 4.0f, 5.0f, 2.0f);
Boss1_at_388:
    unless 1 goto Boss1_at_616 @ 0;
!EN
    etOn(0);
    wait(25);
    etOn(1);
    wait(20);
!HL
    etOn(0);
    wait(15);
    etOn(1);
    wait(10);
    goto Boss1_at_388 @ 0;
Boss1_at_616:
!*
    return;
}

void Boss2()
{
    var A, B;
    lifeSet(2500);
    lifeMarker(0, 0.0f, -24448);
    moveLimit(0.0f, 128.0f, 280.0f, 256.0f);
    timerReset();
    killAllAsync();
    enmKillAll();
    unless ($TIMEOUT == 0) goto Boss2_288 @ 0;
    etCancel(640.0f);
    goto Boss2_308 @ 0;
Boss2_288:
    etClear(640.0f);
Boss2_308:
    $MISS_COUNT = 0;
    $BOMB_COUNT = 0;
    moveVel(0.0f, 0.0f);
    moveVelTime(0, 0, 0.0f, 0.0f);
    movePosTime(0, 0, 0.0f, 0.0f);
    spellEnd();
    funcSet(0);
    reset();
    playSound(27);
!EN
    stars(0);
!HL
    stars(1);
!*
    setInvuln(160);
    unless ($TIMEOUT == 0) goto Boss2_864 @ 0;
    dropClear();
    dropExtra(10, 1);
    dropExtra(12, 1);
    dropExtra(13, 20);
    dropExtra(1, 20);
    dropExtra(2, 10);
    dropArea(64.0f, 64.0f);
    dropItems();
Boss2_864:
    playSound(27);
    wait(120);
    @BossCard2();
    return;
}

void BossCard1()
{
    var A;
    timerReset();
    killAllAsync();
    enmKillAll();
    enmCreate("Ecl_EtBreak", 0.0f, 0.0f, 9999, 10000000, 1);
    spellEnd();
    funcSet(0);
    reset();
    playSound(27);
    moveVel(0.0f, 0.0f);
    moveVelTime(0, 0, 0.0f, 0.0f);
    movePosTime(60, 0, 0.0f, 180.0f);
    $MISS_COUNT = 0;
    $BOMB_COUNT = 0;
!EN
    setNext(0, 0, 2400, "Boss2");
!HL
    setNext(0, 0, 2100, "Boss2");
!EN
    spell(0, 2400, 500000, "[9 sign] Daiyousei Return");
!HL
    spell3(2, 2100, 500000, "[9 sign] Daiyousei Ultimate Return");
!*
    movePosTime(60, 4, 0.0f, 144.0f);
    moveLimit(0.0f, 128.0f, 280.0f, 256.0f);
    @BossCard1_at() async;
    @BossCard1_at2() async;
    wait(10000);
    return;
}

void BossCard1_at()
{
    var A;
    etNew(0);
    etSprite(0, 10, 8);
    etCountD(0, 8, 10, 12, 18, 2, 4, 6, 10);
    etSpeed(0, 3.0f, 4.0f);
    etAim(0, 1);
    etAngle(0, 1.5707964f, 0.17453294f);
    goto BossCard1_at_348 @ 0;
BossCard1_at_240:
    unless 1 goto BossCard1_at_348 @ 0;
    wait(15);
    etOn(0);
    goto BossCard1_at_240 @ 0;
BossCard1_at_348:
    if 1 goto BossCard1_at_240 @ 0;
    return;
}

void BossCard1_at2()
{
    etNew(1);
    etSprite(1, 10, 2);
    etAim(1, 0);
    etSpeed(1, 3.0f, 3.0f);
BossCard1_at2_136:
    unless 1 goto BossCard1_at2_304 @ 0;
!EN
    wait(20);
    etOn(1);
!HL
    etOn(1);
    wait(5);
!*
    wait(1);
    goto BossCard1_at2_136 @ 0;
BossCard1_at2_304:
    return;
}

void BossCard2()
{
    var A;
    lifeSet(3000);
    timerReset();
    killAllAsync();
    enmKillAll();
    enmCreate("Ecl_EtBreak", 0.0f, 0.0f, 9999, 0, 0);
    spellEnd();
    funcSet(0);
    reset();
    playSound(27);
    moveVel(0.0f, 0.0f);
    moveVelTime(0, 0, 0.0f, 0.0f);
    movePosTime(0, 0, 0.0f, 0.0f);
    $MISS_COUNT = 0;
    $BOMB_COUNT = 0;
    setNext(0, 0, 3400, "BossDead");
!EN
    spell(4, 3400, 500000, "Daiyousei Revenge");
!HL
    spell3(6, 3400, 500000, "Daiyousei Ultra Revenge");
!*
    movePosTime(60, 4, 0.0f, 80.0f);
    setInvuln(60);
    wait(90);
    goto BossCard2_776 @ 0;
BossCard2_644:
    movePosTime(60, 1, 0.0f, 60.0f);
    @BossCard2_1($LIFE) async;
    @BossCard2_2($LIFE) async;
    wait(10000);
BossCard2_776:
    if 1 goto BossCard2_644 @ 0;
    return;
}

void BossCard2TachyPattern()
{
    var A, B;
!EN
    $B = $DIFF + 2;
!HL
    $B = $DIFF + 3;
!*
    etNew(0);
    etSprite(0, 9, 1);
    etAim(0, 3);
    etSpeedD(0, 3.0f, 5.0f, 7.0f, 10.0f, 3.0f, 4.0f, 5.0f, 2.0f);
    etNew(1);
    etSprite(1, 9, 9);
    etAim(1, 3);
    etSpeedD(1, 3.0f, 5.0f, 7.0f, 10.0f, 3.0f, 4.0f, 5.0f, 2.0f);
BossCard2TachyPattern_436:
    unless 1 goto BossCard2TachyPattern_1732 @ 0;
    etCountD(0, 42, 46, 50, 54, $B, $B, $B, $B);
    etCountD(1, 42, 46, 50, 54, $B, $B, $B, $B);
    unless ($LIFE >= (($A / 4) * 3)) goto BossCard2TachyPattern_816 @ 0;
    etOn(0);
    wait(40);
    etOn(1);
    wait(40);
BossCard2TachyPattern_816:
    unless (($LIFE <= (($A / 4) * 3)) && ($LIFE >= ($A / 2))) goto BossCard2TachyPattern_1156 @ 0;
    etOn(0);
    wait(20);
    etOn(1);
    wait(20);
BossCard2TachyPattern_1156:
    unless (($LIFE <= ($A / 2)) && ($LIFE >= ($A / 4))) goto BossCard2TachyPattern_1460 @ 0;
    etOn(0);
    wait(5);
    etOn(1);
    wait(5);
BossCard2TachyPattern_1460:
    unless ($LIFE <= ($A / 4)) goto BossCard2TachyPattern_1708 @ 0;
    etCountD(1, 44, 48, 52, 56, $B, $B, $B, $B);
    etOn(0);
    wait(5);
    etOn(1);
    wait(5);
BossCard2TachyPattern_1708:
    goto BossCard2TachyPattern_436 @ 0;
BossCard2TachyPattern_1732:
    return;
}

void BossCard2TachyPattern1()
{
    var A, B, C;
    $B = $DIFF + 4;
    etNew(2);
    etAim(2, 1);
    etSpeedD(2, 2.0f, 3.0f, 4.0f, 6.0f, 2.0f, 3.0f, 4.0f, 6.0f);
    etSprite(2, 10, 15);
    etAngle(2, 1.5707964f, 3.1415927f);
BossCard2TachyPattern1_264:
    unless 1 goto BossCard2TachyPattern1_3428 @ 0;
    etCountD(2, 2, 2, 2, 2, $B, $B, $B, $B);
    $B = $B + 1;
    unless ($LIFE >= (($A / 4) * 3)) goto BossCard2TachyPattern1_1152 @ 0;
    $C = 15;
BossCard2TachyPattern1_628:
    unless $C-- goto BossCard2TachyPattern1_1132 @ 0;
!EN
    etOn(2);
    wait(15);
    etExSet2(2, 0, 1, 16, 50, 1, 1, -999999, 0.0f, -999999.0f, -999999.0f, -999999.0f);
!H
    etSprite(2, 22, 1);
    etOn(2);
    wait(15);
    etSprite(2, 10, 15);
    etOn(2);
    wait(15);
    etExSet2(2, 0, 1, 16, 50, 1, 1, -999999, 0.0f, -999999.0f, -999999.0f, -999999.0f);
!L
    etSprite(2, 22, 1);
    etOn(2);
    wait(15);
    etExSet2(2, 0, 1, 16, 50, 1, 1, -999999, 0.0f, -999999.0f, -999999.0f, -999999.0f);
!*
    goto BossCard2TachyPattern1_628 @ 0;
BossCard2TachyPattern1_1132:
    wait(50);
BossCard2TachyPattern1_1152:
    unless (($LIFE <= (($A / 4) * 3)) && ($LIFE >= ($A / 2))) goto BossCard2TachyPattern1_1976 @ 0;
    $C = 20;
BossCard2TachyPattern1_1452:
    unless $C-- goto BossCard2TachyPattern1_1956 @ 0;
!EN
    etOn(2);
    wait(15);
    etExSet2(2, 0, 1, 16, 50, 1, 1, -999999, 0.0f, -999999.0f, -999999.0f, -999999.0f);
!H
    etSprite(2, 22, 1);
    etOn(2);
    wait(15);
    etSprite(2, 10, 15);
    etOn(2);
    wait(15);
    etExSet2(2, 0, 1, 16, 50, 1, 1, -999999, 0.0f, -999999.0f, -999999.0f, -999999.0f);
!L
    etSprite(2, 22, 1);
    etOn(2);
    wait(15);
    etExSet2(2, 0, 1, 16, 50, 1, 1, -999999, 0.0f, -999999.0f, -999999.0f, -999999.0f);
!*
    goto BossCard2TachyPattern1_1452 @ 0;
BossCard2TachyPattern1_1956:
    wait(40);
BossCard2TachyPattern1_1976:
    unless (($LIFE <= ($A / 2)) && ($LIFE >= ($A / 4))) goto BossCard2TachyPattern1_2744 @ 0;
    $C = 20;
BossCard2TachyPattern1_2240:
    unless $C-- goto BossCard2TachyPattern1_2724 @ 0;
!EN
    etOn(2);
    wait(10);
    etExSet2(2, 0, 1, 16, 50, 1, 1, -999999, 0.0f, -999999.0f, -999999.0f, -999999.0f);
!H
    etSprite(2, 22, 1);
    etOn(2);
    etSprite(2, 10, 15);
    etOn(2);
    wait(10);
    etExSet2(2, 0, 1, 16, 50, 1, 1, -999999, 0.0f, -999999.0f, -999999.0f, -999999.0f);
!L
    etSprite(2, 22, 1);
    etOn(2);
    wait(10);
    etExSet2(2, 0, 1, 16, 50, 1, 1, -999999, 0.0f, -999999.0f, -999999.0f, -999999.0f);
!*
    goto BossCard2TachyPattern1_2240 @ 0;
BossCard2TachyPattern1_2724:
    wait(30);
BossCard2TachyPattern1_2744:
    unless ($LIFE <= ($A / 4)) goto BossCard2TachyPattern1_3404 @ 0;
    $C = 25;
BossCard2TachyPattern1_2900:
    unless $C-- goto BossCard2TachyPattern1_3404 @ 0;
!EN
    etOn(2);
    wait(4);
    etExSet2(2, 0, 1, 16, 30, 1, 1, -999999, 0.0f, -999999.0f, -999999.0f, -999999.0f);
!H
    etSprite(2, 22, 1);
    etOn(2);
    wait(4);
    etOn(2);
    etSprite(2, 10, 15);
    wait(4);
    etExSet2(2, 0, 1, 16, 40, 1, 1, -999999, 0.0f, -999999.0f, -999999.0f, -999999.0f);
!L
    etSprite(2, 22, 1);
    etOn(2);
    wait(4);
    etExSet2(2, 0, 1, 16, 50, 1, 1, -999999, 0.0f, -999999.0f, -999999.0f, -999999.0f);
!*
    goto BossCard2TachyPattern1_2900 @ 0;
BossCard2TachyPattern1_3404:
    goto BossCard2TachyPattern1_264 @ 0;
BossCard2TachyPattern1_3428:
    return;
}

void BossCard2_1(var A)
{
    var B, C, D, E, F, G, H, I, J;
    %C = 0.0f;
    %D = 0.0f;
    %E = 0.0f;
    %F = 0.0f;
    $G = 0;
    %H = 0.0f;
    %I = 0.0f;
!E
    $B = $DIFF + 2;
    $G = -15;
    %H = 20.0f;
    %E = 0.015f;
    %I = 2.0f;
!N
    $B = $DIFF + 2;
    %C = 1.0f;
    %H = 30.0f;
    %E = 0.03f;
    %I = 5.0f;
!H
    $B = $DIFF + 3;
    %C = 1.5f;
    $G = 10;
    %H = 35.0f;
    %E = 0.05f;
!L
    $B = $DIFF + 3;
    %C = 2.0f;
    $G = 20;
    %H = 50.0f;
    %E = 0.08f;
!*
    %D = %C;
    etNew(0);
    etSprite(0, 9, 2);
    etAim(0, 1);
    etSpeed(0, 1.5f + %C, 1.0f + %C);
    etNew(1);
    etSprite(1, 9, 9);
    etAim(1, 1);
    etSpeed(1, 1.5f + %C, 1.0f + %C);
!EN
    etCount(0, 1, 1);
    etCount(1, 1, 1);
!HL
    etCount(0, 1, 2);
    etCount(1, 1, 2);
BossCard2_1_1836:
!*
    unless 1 goto BossCard2_1_3488 @ 0;
    %F = 0.0f;
    %C = %D;
    $J = _S(%H);
BossCard2_1_2000:
    unless $J-- goto BossCard2_1_2556 @ 0;
    etSpeed(0, 1.5f + %C, 1.0f + %C);
    etAngle(0, 1.5708f + (%F * 0.017453292f), 0.0f);
    etOn(0);
    %F = %F + (360.0f / %H);
    %C = %C + %E;
    wait(1);
    goto BossCard2_1_2000 @ 0;
BossCard2_1_2556:
    wait(30 - $G);
    %F = 0.0f;
    %C = %D;
    $J = _S(%H);
BossCard2_1_2752:
    unless $J-- goto BossCard2_1_3324 @ 0;
    etSpeed(1, 1.5f + %C, 1.0f + %C);
    etAngle(1, -(4.712389f + (%F * 0.017453292f)), 0.0f);
    etOn(1);
    %F = %F + (360.0f / %H);
    %C = %C + %E;
    wait(1);
    goto BossCard2_1_2752 @ 0;
BossCard2_1_3324:
    moveRand(30, 4, %I);
    wait(60 - ($G * 2));
    goto BossCard2_1_1836 @ 0;
BossCard2_1_3488:
    return;
}

void BossCard2_2(var A)
{
    var B, C, D;
    $B = 0;
!E
    $B = 87;
!N
    $B = 75;
!H
    $B = 130;
!L
    $B = 130;
!*
    $C = $DIFF + 3;
    etNew(2);
    etAim(2, 3);
    etSpeedD(2, 2.0f, 3.0f, 4.0f, 6.0f, 2.0f, 3.0f, 4.0f, 6.0f);
    etSprite(2, 10, 15);
    etAngle(2, 1.5707964f, 3.1415927f);
    etNew(3);
    etAim(3, 3);
    etSpeedD(3, 2.0f, 3.0f, 4.0f, 6.0f, 2.0f, 3.0f, 4.0f, 6.0f);
    etSprite(3, 10, 10);
    etAngle(3, 1.5707964f, 3.1415927f);
    wait($B + 20);
!N
    wait(20);
BossCard2_2_712:
!*
    unless 1 goto BossCard2_2_1484 @ 0;
    etCountD(2, 12, 24, 3, 4, $C, $C, $C, $C);
    etCountD(3, 12, 24, 3, 4, $C, $C, $C, $C);
    $D = 1;
BossCard2_2_900:
    unless $D-- goto BossCard2_2_1460 @ 0;
!EN
    etExSet2(2, 0, 1, 16, 70, 1, 1, -999999, 0.0f, -999999.0f, -999999.0f, -999999.0f);
    etOn(2);
    wait($B * 2);
!H
    etSprite(2, 22, 1);
    etOn(2);
    wait(20);
    etSprite(2, 10, 15);
    etOn(2);
    wait(15);
    etExSet2(2, 0, 1, 16, 50, 1, 1, -999999, 0.0f, -999999.0f, -999999.0f, -999999.0f);
!L
    etSprite(2, 22, 1);
    etOn(2);
    wait(20);
    etExSet2(2, 0, 1, 16, 50, 1, 1, -999999, 0.0f, -999999.0f, -999999.0f, -999999.0f);
!*
    goto BossCard2_2_900 @ 0;
BossCard2_2_1460:
    goto BossCard2_2_712 @ 0;
BossCard2_2_1484:
    return;
}

void BossCard3()
{
    var A;
    timerReset();
    killAllAsync();
    enmKillAll();
    enmCreate("Ecl_EtBreak", 0.0f, 0.0f, 9999, 0, 0);
    spellEnd();
    funcSet(0);
    reset();
    playSound(27);
    moveVel(0.0f, 0.0f);
    moveVelTime(0, 0, 0.0f, 0.0f);
    movePosTime(0, 0, 0.0f, 0.0f);
    $MISS_COUNT = 0;
    $BOMB_COUNT = 0;
    spell(8, 3000, 500000, "冥符「常夜桜」");
!EN
    setNext(0, 0, 3000, "BossDead");
!HL
    setNext(0, 0, 3000, "Boss4");
!*
    movePosTime(60, 4, 0.0f, 192.0f);
    setInvuln(60);
+60: //60
    anmSelectedPlay(0);
+30: //90
    nop();
    @BossCard3_at() async;
    goto BossCard3_692 @ 130;
BossCard3_656:
    wait(380);
+40: //130
    nop();
BossCard3_692:
    if 1 goto BossCard3_656 @ 90;
    return;
}

void BossCard3_at()
{
    var A, B;
    etNew(0);
    etAim(0, 1);
    etSprite(0, 22, 3);
    etCountD(0, 2, 4, 4, 4, 2, 2, 3, 4);
    etAngle(0, 0.0f, 0.17453292f);
    etSpeed(0, 0.4f, 0.0f);
    etDist(0, 24.0f);
    etEx(0, 1, 2, 1, -999999, -999999.0f, -999999.0f);
    etEx(0, 1, 4, 60, -999999, 0.05f, -999999.0f);
    etEx(0, 1, 64, 1, 13, -999999.0f, -999999.0f);
    etEx(0, 0, 8192, 134743048, 1, 0.1f, 0.7f);
    etEx(0, 0, 16384, 1, 0, -3.1415927f, 3.1415927f);
    etEx(0, 0, 1024, -999999, -999999, -999999.0f, -999999.0f);
    etExSet(0, 8, 0, 1048576, 1, -999999, -999999.0f, -999999.0f);
    etExSet(0, 9, 0, 4, 180, -999999, 0.0044444446f, 999.0f);
    diffI($A, 50, 50, 40, 30);
    diffI($B, 30, 30, 20, 10);
    goto BossCard3_at_1332 @ 0;
BossCard3_at_696:
    etAngle(0, -1.5707964f + (%RANDF2 * 1.0471976f), 0.2617994f);
    etOn(0);
    wait($A);
    etAngle(0, -0.19634955f + (%RANDF2 * 0.5235988f), 0.2617994f);
    etOn(0);
    wait($A);
    etAngle(0, -2.9452431f + (%RANDF2 * 0.5235988f), 0.2617994f);
    etOn(0);
    wait($A);
    unless ($A > $B) goto BossCard3_at_1332 @ 0;
    $A = $A - 1;
BossCard3_at_1332:
    if 1 goto BossCard3_at_696 @ 0;
    return;
}

void BossCard4()
{
    var A;
    timerReset();
    killAllAsync();
    enmKillAll();
    enmCreate("Ecl_EtBreak", 0.0f, 0.0f, 9999, 0, 0);
    spellEnd();
    funcSet(0);
    reset();
    playSound(27);
    moveVel(0.0f, 0.0f);
    moveVelTime(0, 0, 0.0f, 0.0f);
    movePosTime(0, 0, 0.0f, 0.0f);
    $MISS_COUNT = 0;
    $BOMB_COUNT = 0;
!HL
    spell3(12, 3000, 500000, "桜符「西行桜吹雪」");
!O67
    spellEx(119, 3000, 500000, "桜符「桜吹雪地獄」");
!*
    setNext(0, 0, 3000, "BossDead");
    movePosTime(60, 4, 0.0f, 128.0f);
    setInvuln(60);
+60: //60
    anmSelectedPlay(0);
+30: //90
    nop();
    anmPlay(1, 61);
    playSound(54);
    playSound(52);
    anmSetSprite(3, 7);
    @BossCard4_at() async;
    @BossCard4_at2() async;
    goto BossCard4_832 @ 130;
BossCard4_796:
    wait(380);
+40: //130
    nop();
BossCard4_832:
    if 1 goto BossCard4_796 @ 90;
    return;
}

void BossCard4_at()
{
    var A, B;
    etNew(0);
    etAim(0, 2);
    etSprite(0, 8, 4);
    etCountD(0, 12, 12, 12, 12, 1, 1, 1, 1);
    etAngle(0, 1.5707964f, 0.032724924f);
    etSpeedD(0, 2.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    etEx(0, 1, 2, 1, -999999, -999999.0f, -999999.0f);
    etEx(0, 0, 8, 240, -999999, 0.0125f, 0.017453292f);
    etDist(0, 8.0f);
    %A = 1.570796f;
    $B = 40000;
    goto BossCard4_at_688 @ 0;
BossCard4_at_456:
    etAngle(0, %RANDRAD, 0.0f);
!O67
    etAngle(0, %A, 0.0f);
    %A = %A - 0.087266f;
    validRad(%A);
!*
    etOn(0);
!H
    wait(40);
!L
    wait(28);
!O67
    wait(8);
BossCard4_at_688:
!*
    if $B-- goto BossCard4_at_456 @ 0;
    return;
}

void BossCard4_at2()
{
    var A, B;
    etNew(1);
    etAim(1, 2);
    etSprite(1, 8, 4);
    etCountD(1, 12, 12, 12, 12, 1, 1, 1, 1);
    etAngle(1, 1.5707964f, 0.032724924f);
    etSpeedD(1, 2.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    etEx(1, 1, 2, 1, -999999, -999999.0f, -999999.0f);
    etEx(1, 0, 8, 240, -999999, 0.0125f, -0.017453292f);
    etDist(1, 8.0f);
!H
    wait(20);
!L
    wait(14);
!*
    %A = 1.570796f;
    $B = 40000;
    goto BossCard4_at2_604 @ 0;
BossCard4_at2_496:
    etAngle(1, %RANDRAD, 0.0f);
    etOn(1);
!H
    wait(40);
!L
    wait(28);
!O67
    wait(22);
BossCard4_at2_604:
!*
    if $B-- goto BossCard4_at2_496 @ 0;
    return;
}

void BossDead()
{
    flagSet(156);
    anmPlay(1, 25);
    playSound(5);
    anmPlay(1, 96);
    moveVel(%RANDRAD, 0.4f);
    unless ($TIMEOUT == 0) goto BossDead_308 @ 0;
    enmCreate("Ecl_EtBreak2", 0.0f, 0.0f, 9999, 0, 0);
    goto BossDead_364 @ 0;
BossDead_308:
    enmCreate("Ecl_EtBreak2_ni", 0.0f, 0.0f, 9999, 0, 0);
BossDead_364:
    enmKillAll();
+60: //60
    etClearAll();
    spellEnd();
    unless ($TIMEOUT == 0) goto BossDead_596 @ 60;
    dropClear();
    dropExtra(1, 7);
    dropExtra(2, 10);
    dropArea(48.0f, 48.0f);
    dropItems();
BossDead_596:
    setScreenShake(30, 12, 0);
    anmPlay(1, 25);
    anmPlay(1, 97);
    playSound(5);
    setBoss(-1);
    delete();
    delete();
}

void BossEscape()
{
    spellEnd();
    moveLimitReset();
    enmKillAll();
    unless ($TIMEOUT == 0) goto BossEscape_208 @ 0;
    etCancel(640.0f);
    goto BossEscape_228 @ 0;
BossEscape_208:
    etClear(640.0f);
BossEscape_228:
    lifeSet(100000);
    setChapter(0);
    setBoss(-1);
    flagSet(16);
    movePosTime(60, 4, -224.0f, -16.0f);
    wait(60);
    delete();
    delete();
}

void TraceEnemyPos()
{
    var A;
    goto TraceEnemyPos_100 @ 0;
TraceEnemyPos_60:
    moveEnmRel($A);
    wait(1);
TraceEnemyPos_100:
    if 1 goto TraceEnemyPos_60 @ 0;
    return;
}
