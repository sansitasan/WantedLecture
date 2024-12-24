#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include "Creature.hpp"
#include "Monster.hpp"
#include "Player.hpp"

using namespace std;

void solutionOne();
void solutionTwo();
void solutionThree();
void swap(int&, int&);
void solutionFour();
void PrintReverse(const char*, int);
void solutionFive();
void ToLower(char&);
void ToUpper(char&);
void solutionSix();
bool HasSameCharacter(const char*, int);
//링커가 함수 정의됐는지 확인할 때 모든 파일 전수조사를 함
//파일 수가 늘어날수록 컴파일타임이 올라간다

//OS에서 폴더를 두가지로 다룬다. 하드, 소프트
//하드 방식은 실제로 존재함
//소프트 방식은 폴더가 없지만 있는 것처럼 보여주는 방식