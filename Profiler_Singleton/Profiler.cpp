#include "Profile.h"

LARGE_INTEGER Profile::Freq = { 0 };

//private
void ProfileManager::UpdataTimeData(int idx, double time)
{
	list[idx]._totaltime += time;
	list[idx]._callcount++;
}

void ProfileManager::UpdateMinMax(int idx, double time)
{
	if (time < list[idx]._Min)
	{
		list[idx]._Min = time;
	}
	if (time > list[idx]._Max)
	{
		list[idx]._Max = time;
	}
}

//public
int ProfileManager::GetProfileID(const char* name)
{
	//이미 등록된 이름이면 인덱스 반환
	for (int idx = 0; idx < arridx; idx++)
	{
		//strcpy_s 같은 복사비용 늘어나는 함수 금지, if문으로 묶을 수 있으면 한번에 묶어서 cmp명령어 줄이기
		if (list[idx]._flag == 1 && list[idx]._name == name)
		{
			return idx;
		}
	}

	// 30개 이상 측정 안할꺼라서 배열 갯수 확인하는 비교문 제거
	// 프로파일 배열 등록
	list[arridx]._flag = 1;
	list[arridx]._name = name;
	list[arridx]._Max = 0;
	list[arridx]._Min = 999999.0;
	list[arridx]._totaltime = 0.0;
	list[arridx]._callcount = 0;

	// 등록했으면 갯수 증가
	return arridx++;
}

void ProfileManager::SaveData(double time, int idx)
{
	if (idx < 0 || idx > 30) return;

	// 시간 업데이트, Min, Max 업데이트 함수 분리
	UpdataTimeData(idx, time);
	UpdateMinMax(idx, time);
}

FILE* ProfileManager::OpenFile(const char* filename)
{
	FILE* fp = nullptr;
	//fopen_s 반환값은 성공하면 0, 에러가 발생하면 에러코드(errno_t)
	errno_t err = fopen_s(&fp, filename, "w");
	if (err == 0)
	{
		printf("파일 열기 성공\n");
		return fp;
	}
	else
	{
		printf("파일 열기 실패. 에러 코드 : %d", err);
		return nullptr;
	}

}

void ProfileManager::DrawProfileReportTitle(FILE* fp)
{
	fprintf(fp, "\t----------------------------------------------------------------------------------------------\n\n");
	fprintf(fp, "\tName\t|\tAverage\t|\tMin\t|\tMax\t|\tCall\t|\n");
	fprintf(fp, "\t----------------------------------------------------------------------------------------------\n");
}

void ProfileManager::DrawProfileReport(FILE* fp)
{
	for (int idx = 0; idx < arridx; idx++)
	{
		fprintf(fp, "\t%s  |  %lfus\t|  %lfus\t|  %lfus\t|\t%d\n", list[idx]._name, list[idx]._totaltime / list[idx]._callcount,
			list[idx]._Min, list[idx]._Max, list[idx]._callcount);
	}
	fprintf(fp, "\t---------------------------------------------------------------------------------------------\n");
}

void ProfileManager::WriteProfile(const char* filename)
{
	FILE* fp = OpenFile(filename);

	DrawProfileReportTitle(fp);
	DrawProfileReport(fp);
	fclose(fp);
}

void ProfileManager::ResetProfile()
{
	for (int idx = 0; idx < arridx; idx++)
	{
		//전체를 초기화 할 필요 없이 등록했던 것만 초기화
		list[idx]._callcount = 0;
		list[idx]._Max = 0.0;;
		list[idx]._Min = 999999.0;
		list[idx]._totaltime = 0.0;
	}
}
