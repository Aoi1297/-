#pragma once

#include "../../scene_manager.h"

class CResult : public IScene
{
public:
	CResult(IGameObject* parent);

	~CResult(void) = default;

	void Initialize(void)	override;

	void Update(void)	override;

	void Draw(void)	override;

	void Finalize(void)	override;

private:
	aqua::CLabel m_TitleText;
};