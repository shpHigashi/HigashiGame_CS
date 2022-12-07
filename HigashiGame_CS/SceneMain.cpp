#include "DxLib.h"
#include "SceneMain.h"
#include "game.h"

namespace
{
	// �G�o���p�̒x������
	constexpr int kSpawnDelay = 100;
	// �Q�[���̐�������
	constexpr int kGameMaxTime = 1800;	
	// ���S���̒x��
	constexpr int kGameOverDelay = 90;
	// �Q�[���I�[�o�[
	const char* const kGameOver = "GameOver";
	constexpr int kFontSize = 60;

	// �������ԕ\���ʒu
	constexpr int kTimerPositionX = Game::kScreenWidthHalf - 30;
	constexpr int kTimerPositionY = Game::kStageLowerLimit + 25;

	// RGB�����l�p
	constexpr int kSetColor = 255;
}

SceneMain::SceneMain()
{
	m_revSound = -1;
	m_deathSound = -1;

	m_playOnceOnly = false;
	
	m_hBackgroundGraphic = -1;
	m_hPlayerGraphic = -1;
	m_hPlayerDeadGraphic = -1;
	m_hEnemyGraphic = -1;

	m_spawnDelay = 0;
	m_fontSize = 0;

	m_gameTimeRemaining = kGameMaxTime;
	m_GameOverDelay = kGameOverDelay;

	m_isGameClear = false;
	m_isEnd = false; 
}
SceneMain::~SceneMain()
{
}

// ������
void SceneMain::init()
{
	// ���f�[�^
	m_revSound = LoadSoundMem("sounddata/blip.wav");
	m_deathSound = LoadSoundMem("sounddata/hurt.wav");

	// ��x�����Đ�
	m_playOnceOnly = false;

	// �摜�f�[�^�̓ǂݍ���
	m_hBackgroundGraphic = LoadGraph(Game::kBackgroundGraph);
	m_hPlayerGraphic = LoadGraph(Game::kPlayerGraph);

	m_hEnemyGraphic = LoadGraph("imagedata/securityEnemy.png");

	// �v���C���[�摜�Ɖ��̐ݒ�
	m_player.setHandle(m_hPlayerGraphic, m_hPlayerDeadGraphic);
	m_player.setSound(m_revSound);

	// �G�̉摜�ݒ�A������
	for (auto& EnemyLeft : m_EnemyLeft)
	{
		EnemyLeft.setHandle(m_hEnemyGraphic);
		EnemyLeft.init();
	}
	for (auto& EnemyRight : m_EnemyRight)
	{
		EnemyRight.setHandle(m_hEnemyGraphic);
		EnemyRight.init();
	}

	// �v���C���[�̏����ʒu�ݒ�
	m_player.setPos(Game::kScreenWidthHalf, Game::kScreenHeightHalf);
	// �v���C���[������ 
	m_player.init();

	// �t�H���g�T�C�Y�ݒ�
	m_fontSize = kFontSize;

	// �e���ԗp�ϐ��̏�����
	m_spawnDelay = kSpawnDelay;
	m_gameTimeRemaining = kGameMaxTime;
	m_GameOverDelay = kGameOverDelay;

	// �V�[���I���A�Q�[���N���A�� false �ɏ�����
	m_isGameClear = false;
	m_isEnd = false;
}

// �I������
void SceneMain::end()
{
	// ���y�f�[�^�̍폜
	DeleteSoundMem(m_revSound);
	DeleteSoundMem(m_deathSound);
	
	// �摜�f�[�^�̍폜
	DeleteGraph(m_hBackgroundGraphic);
	DeleteGraph(m_hPlayerGraphic);
	DeleteGraph(m_hPlayerDeadGraphic);
	DeleteGraph(m_hEnemyGraphic);
}

// ���t���[���̏���
void SceneMain::update()
{
	// �w�i�̕\��
	DrawGraph(0, 0, m_hBackgroundGraphic, true);
	
	if (!m_gameTimeRemaining)	// �Q�[���c�莞�Ԃ�0�ɂȂ����ꍇ
	{
		m_isGameClear = true;	// �Q�[���N���A�ƃV�[���I���� true �ɂ���
		m_isEnd = true;			// �N���A�p�̃V�[���ֈڍs����
	}
	else if (!m_GameOverDelay)	// �Q�[���I�[�o�[�x����0�ɂȂ����ꍇ
	{
		m_isEnd = true;			// �V�[���I���݂̂� true �ɂ���			
	}							// �^�C�g���֖߂�

	// �v���C���[�̎��S���肪 true �̏ꍇ
	if (m_player.isDead())
	{
		if (!m_playOnceOnly)
		{
			PlaySoundMem(m_deathSound, DX_PLAYTYPE_BACK);
			m_playOnceOnly = true;
		}
		// �Q�[���I�[�o�[�x����1�t���[�����ƂɌ���������
		m_GameOverDelay--;

		return;
	}

	// 1�t���[�����ƂɎc�莞�ԂƓG�̏o���x��������������
	m_gameTimeRemaining--;
	m_spawnDelay--;

	// �o���x����0�ɂȂ����ꍇ�A�G���o��������
	if (!m_spawnDelay)
	{
		// ���ꂼ��̕����̓G���쐬
		createEnemyLeft();
		createEnemyRight();

		// �o���x���ɍĂђ萔����
		m_spawnDelay = kSpawnDelay;
	}

	// �v���C���[�̍X�V����
	m_player.update();

	// �����蔻��`�F�b�N����
	checkCollision();

	// �G�̍X�V����
	for (auto& EnemyLeft : m_EnemyLeft)
	{
		EnemyLeft.update();
	}
	for (auto& EnemyRight : m_EnemyRight)
	{
		EnemyRight.update();
	}
}

// ���t���[���̕`��
void SceneMain::draw()
{
	// �v���C���[�̕`��
	m_player.draw();

	// ���݂��Ă���G�̂ݕ`��
	for (auto& EnemyLeft : m_EnemyLeft)
	{
		if (EnemyLeft.isExist()) EnemyLeft.draw();
	}
	for (auto& EnemyRight : m_EnemyRight)
	{
		if (EnemyRight.isExist()) EnemyRight.draw();
	}

	// �X�e�[�W�̐��̕\��
	DrawLine(0, Game::kStageUpperLimit, Game::kScreenWidth, Game::kStageUpperLimit, GetColor(255, 255, 255));
	DrawLine(0, Game::kStageLowerLimit, Game::kScreenWidth, Game::kStageLowerLimit, GetColor(255, 255, 255));

	// �t�H���g�T�C�Y�ݒ�
	SetFontSize(Game::kFontSize);
	
	// �Q�[���̐������ԕ\�� (�ʏ�͔������A���v���Ԃ̔������߂���Ɖ��F�����A5�b���߂���Ɛԕ����ŕ\�������)
	int red = kSetColor;
	int green = kSetColor;
	int blue = kSetColor;
	if (m_gameTimeRemaining <= 300)
	{
		green = 0;
		blue = 0;
	}
	else if (m_gameTimeRemaining <= kGameMaxTime / 2)
	{
		green = 216;
		blue = 0;
	}
	DrawFormatString(kTimerPositionX, kTimerPositionY, GetColor(red, green, blue), "%d", m_gameTimeRemaining / 60);

	// �v���C���[�̎��S���肪 true �̏ꍇ
	if (m_player.isDead())
	{
		// 1�t���[�����ƂɃt�H���g�T�C�Y�𑝉�������
		m_fontSize++;
		SetFontSize(m_fontSize);
		// �Q�[���I�[�o�[�̃e�L�X�g��\��
		DrawString(Game::kScreenWidthHalf - GetDrawStringWidth(kGameOver, 4), 210, kGameOver, GetColor(255, 0, 0));
	}
}

// �����蔻��`�F�b�N����
void SceneMain::checkCollision()
{
	for (auto& EnemyLeft : m_EnemyLeft)
	{
		// �������Ă��Ȃ��ꍇ�������X�L�b�v
		if (EnemyLeft.getRight() <= m_player.getLeft()) continue;
		if (m_player.getRight() <= EnemyLeft.getLeft()) continue;
		if (EnemyLeft.getBottom() <= m_player.getTop()) continue;
		if (m_player.getBottom() <= EnemyLeft.getTop()) continue;
		// �������Ă���ꍇ�v���C���[�����S����ɂ���
		m_player.setDead();
	}
	for (auto& EnemyRight : m_EnemyRight)
	{
		// �������Ă��Ȃ��ꍇ�������X�L�b�v
		if (EnemyRight.getRight() <= m_player.getLeft()) continue;
		if (m_player.getRight() <= EnemyRight.getLeft()) continue;
		if (EnemyRight.getBottom() <= m_player.getTop()) continue;
		if (m_player.getBottom() <= EnemyRight.getTop()) continue;
		// �������Ă���ꍇ�v���C���[�����S����ɂ���
		m_player.setDead();
	}
}

// �G�̐���(������o��)
void SceneMain::createEnemyLeft()
{
	for (auto& EnemyLeft : m_EnemyLeft)
	{
		// �G�����݂��Ă���ꍇ�X�L�b�v
		if (EnemyLeft.isExist()) continue;

		// �G�̏o������ �����Ƃ��ă����_���Ő����������W������
		EnemyLeft.start(EnemyLeft.getRandPos());
		
		return;
	}
}
// �G�̐���(�E����o��)
void SceneMain::createEnemyRight()
{
	for (auto& EnemyRight : m_EnemyRight)
	{
		// �G�����݂��Ă���ꍇ�X�L�b�v
		if (EnemyRight.isExist()) continue;

		// �G�̏o������ �����Ƃ��ă����_���Ő����������W������
		EnemyRight.start(EnemyRight.getRandPos());

		return;
	}
}