#ifndef SHMUP_APP_H
#define SHMUP_APP_H

#include <Windows.h>
#include "global.h"
#include "VC_App.h"
#include "SHMUP_GameManager.h"

class SHMUP_App : public VC_App
{
public:
	SHMUP_App();
	~SHMUP_App();

	void Init() override;
	void Shutdown() override;

	void Update() override;
	void Render() override;

private:

	SHMUP_GameManager* m_pGameManager;

};

#endif
