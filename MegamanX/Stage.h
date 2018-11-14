#pragma once
#include "RectF.h"
#include "List.h"
#include "Megaman.h"
#include <fstream>
using namespace std;

class Stage : public RectF
{
public:
	static List<Stage*>* curStages;
	static Stage* curStage;

	int index;
	int xPre, yPre;

	static bool updating;

	void update();

	static void loadStageNext();
	static void loadStagePrev();

	Stage(fstream& fs, int index);
	~Stage();
};
