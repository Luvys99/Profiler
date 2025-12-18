#pragma once
#include <windows.h>
#include <cstring>
#include <iostream>

struct ProfileData
{
	long _flag = 0;
	const char* _name = nullptr;
	double _totaltime = 0.0;
	double _Min = 0;
	double _Max = 0;
	long _callcount = 0;
};

class ProfileManager
{
private:
	ProfileData list[30];
	int arridx = 0;
	// 생성자를 private로 숨겨서 외부에서 마음대로 생성 못하게 막음
	ProfileManager() {}
	//복사 생성자, 대입 연산자도 삭제 ( 복제 방지 )
	ProfileManager(const ProfileManager& ref) = delete;
	ProfileManager& operator=(const ProfileManager& ref) = delete;

	// 구조체 내의 중요한 데이터기 때문에 함수 내부에서만 접근
	void UpdataTimeData(int idx, double time);
	void UpdateMinMax(int idx, double time);
	// 외부에서 접근하는 함수들
public:
	static ProfileManager& GetInstance()
	{
		static ProfileManager instance;
		return instance;
	}

	// 이름을 받아서 인덱스를 반환하는 함수
	int GetProfileID(const char* name);
	// 실행시간 측정한 데이터 저장
	void SaveData(double time, int idx);
	// 파일 오픈 함수
	FILE* OpenFile(const char* filename);
	// 리포트 타이틀그리는 함수
	void DrawProfileReportTitle(FILE* fp);
	// 리포트 그리는 함수
	void DrawProfileReport(FILE* fp);
	// 엔터누르면 한 번 호출하는 함수라 가독성 최우선
	void WriteProfile(const char* filename);
	// 초기화 함수 ( 올바른 측정을 위한 )
	void ResetProfile();

};

class Profile
{
private:
	//Freq 최초에 1회만 선언되게끔 static 선언
	static LARGE_INTEGER Freq;
	LARGE_INTEGER Start;
	LARGE_INTEGER End;
	int _profileID;
	double _time = 0;
public:
	//이름 저장하지 않고 함수 이름으로 바로 아이디 등록
	Profile(const char* myname, int& staticID)
	{
		if (Freq.QuadPart == 0)
		{
			QueryPerformanceFrequency(&Freq);
		}

		if (staticID == -1)
		{
			staticID = ProfileManager::GetInstance().GetProfileID(myname);
		}
		_profileID = staticID;
		QueryPerformanceCounter(&Start);
	}
	~Profile()
	{
		QueryPerformanceCounter(&End);
		// 마이크로세컨즈 단위로 저장
		_time = (double)((End.QuadPart - Start.QuadPart) * 1000000) / (double)Freq.QuadPart;
		// 실행 측정 함수 이름이랑, 시간 저장 함수
		ProfileManager::GetInstance().SaveData(_time, _profileID);
	}

};

// 매크로 "\"뒤에 공백들어가면 오류 바로 "\n"해야됨
#define PROFILE \
	static int _my_profile_id = -1; \
	Profile _p(__FUNCTION__, _my_profile_id)
