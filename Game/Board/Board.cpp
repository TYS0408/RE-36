#include "stdafx.h"
#include "Board.h"
#include"GameScene/GameClear.h"
#include"GameScene/GameOver.h"
#include"OseroAI/OseroAI.h"
#include"ScalePopupAnimation/ScalePopupAnimation.h"
namespace
{
	//オセロの盤面
	const char* FILEPATHBOARD = "Assets/Sprite/Osero/Board.dds";
	const int WIDTHBOARD = 1000.0f;
	const int HIGHTBOARD = 1000.0f;

	/** 置ける場所ヒント画像のファイルパス*/
	const char* FILEPATH = "Assets/Sprite/Osero/OseroCanPut.dds";

	/** 手番を表示するUIファイルパス*/
	const char* FILEPATH_BLACKTURN = "Assets/Sprite/OseroTurn/Black_Turn.dds";
	const char* FILEPATH_WHITETURN = "Assets/Sprite/OseroTurn/White_Turn.dds";

	/** 手番表示UIの幅と高さ*/
	const float TURNUI_WIDTH = 800.0f;
	const float TURNUI_HEIGHT = 200.0f;

	/** 「FINISH！」の画像ファイルパス*/
	const char* FILEPATH_FINISH = "Assets/Sprite/Finish/Finish.dds";

	/** 「FINISH！」の画像の幅と高さ*/
	const float FINISH_WIDTH = 1400.0f;
	const float FINISH_HEIGHT = 800.0f;

	/** 手番UIアニメーション用の座標 ・時間定数*/
	/** 画面右外側の開始位置*/
	const float TURNUI_START_X = 1000.0f;
	/** 中央で一旦停止する位置*/
	const float TURNUI_CENTER_X = 0.0f;
	/**画面左外側の消える位置 */
	const float TURNUI_END_X= -1300.0f;
	/** Y座標は固定*/
	float TURNUI_POS_Y = 0.0f;

	/** 右→中央にかかる時間*/
	const float TURNUI_SLIDEIN_TIME = 0.30f;
	/** 中央で止まっている秒数*/
	const float TURNUI_HOLD_TIME = 2.0f;
	/** 中央→画面外にかかる秒数*/
	const float TURNUI_SLIDEOUT_TIME = 0.30f;


	/** 8方向(左上から時計回り)*/
	const int DX[8] = { -1,0,1,-1,1,-1,0,1 };
	const int DY[8] = { -1,-1,-1,0,0,1,1,1 };
}
Board::Board()
{
	m_ai = new OseroAI(); // ★コンストラクタで生成
}
Board::~Board()
{
	delete m_ai;
}


bool Board::IsInside(int x, int y)const
{

	return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}

bool Board::CanPut(int x, int y, Stone turn)const
{
	/** 盤面外の場合は駒を置けない*/
	if (!IsInside(x, y)) return false;
	/** 既に駒が置いてある場合も置けない*/
	if (m_board[y][x] != EMPTY)return false;
	/**今の手番が黒なら白に白なら黒に変える */
	/** 条件 ? 条件がtrueのときの値 : 条件がfalseのときの値*/
	Stone opponent = (turn == BLACK) ? WHITE : BLACK;

	/** 8方向全てチェックする*/
	for (int dir = 0; dir < 8; dir++)
	{
		int nx = x + DX[dir];
		int ny = y + DY[dir];
		/**相手の石があるかどうか */
		bool hasOpponentBetween = false;

		/** 相手の石が連続している間、進み続ける*/
		while (IsInside(nx, ny) && m_board[ny][nx] == opponent)
		{
			nx += DX[dir];
			ny += DY[dir];
			hasOpponentBetween = true;
		}

		/** 相手の石を一つ以上挟んだ先に自分の石があれば置ける*/
		if (hasOpponentBetween && IsInside(nx, ny) && m_board[ny][nx] == turn)
		{
			return true;
		}
	}
	return false;
}

void Board::Reverse(int x, int y, Stone turn)
{
	Stone opponent = (turn == BLACK) ? WHITE : BLACK;

	for (int dir = 0; dir < 8; dir++)
	{
		int nx = x + DX[dir];
		int ny = y + DY[dir];
		/**相手の石が一個以上あるかどうか */
		bool hasOpponentBetween = false;

		/** 指定した方向に「挟めるかどうか」をもう一度確認*/

		/** cx,cyの値はどんどん動かして使うので
		「ひっくり返す開始位置」として記録しておきたいので保存しておく。*/

		/**例えるなら、nx, ny は「スタート地点のメモ」、
		cx, cy は「今どこまで調べたかを進めていく作業用の変数」*/
		int cx = nx, cy = ny;
		/** 相手の石がどこまで連続しているか*/
		while (IsInside(cx, cy) && m_board[cy][cx] == opponent)
		{
			cx += DX[dir];
			cy += DY[dir];
			hasOpponentBetween = true;
		}

		/** 挟めるなら挟んだ石を全てひっくり返してTurn色にする*/
		if (hasOpponentBetween &&
			IsInside(cx, cy) &&
			m_board[cy][cx] == turn)
		{
			/** 保存しておいた変数を呼び出す*/
			int fx = nx, fy = ny;
			/**fx,fyを自分の石があったcx,cyに到達するまで繰り返す */
			while (fx != cx || fy != cy)
			{
				m_board[fy][fx] = turn;
				fx += DX[dir];
				fy += DY[dir];
			}
		}
	}
}



void Board::UpdateAI()
{
	/** ターン交代のスライドアニメ―ション中は操作できない*/
	if (m_isPlayTurnAnimation)
	{
		return;
	}
	if (m_gameState != GameState::Playing) return;
	if (m_isPlayTurnAnimation) return;
	if (m_turn != WHITE) return;

	int x, y;
	if (!m_ai->DecideMove(*this, WHITE, x, y)) return;

	PutStone(x, y, WHITE);

	Stone next = BLACK;
	if (HasValidMove(next))
	{
		m_turn = next;
		StartTurnAnimation();
	}
	
	else if (!HasValidMove(m_turn)) CheckGameEnd();
}
void Board::PutStone(int x, int y, Stone turn)
{
	/** 置けない場所なら何もしない(念のための安全策)*/
	if (!CanPut(x, y, turn))
	{
		return;
	}

	/** まず石を置く*/
	m_board[y][x] = turn;

	/** 挟んだ石をひっくり返す*/
	Reverse(x, y, turn);
}


bool Board::HasValidMove(Stone turn)const
{
	/** 盤面全マスをチェックして、1つでも置ける場所があればtrue*/
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			if (CanPut(x, y, turn))
			{
				return true;
			}
		}
	}
	return false;
}

bool Board::WorldPosToBoardIndex(float worldX, float worldY, int& outX, int& outY)const
{
	/** 盤面の左端、下端の座標を計算*/
	const float startX = -WIDTHBOARD * 0.5f;
	const float startY = -HIGHTBOARD * 0.5f;
	/** 1マスのサイズを計算*/
	/** 盤面の全体をSIZE(6)で割って求めている*/
	const float cellSize = WIDTHBOARD / (float)SIZE;

	/** 盤面の範囲外なら無効*/
	if (worldX <startX || worldX > startX + WIDTHBOARD)return false;
	if (worldY < startY || worldY > startY + HIGHTBOARD)return false;
	/** WorldX - startX = 盤面の左端からの距離*/
	int col = (int)((worldX - startX) / cellSize);
	/** WorldY - startY = 盤面の下端からの距離*/
	int rowFromBottom = (int)((worldY - startY) / cellSize);

	/** RenderでY方向を反転させているのでこちらも同様に反転させる*/
	int row = (SIZE - 1) - rowFromBottom;

	if (!IsInside(col, row))return false;

	outX = col;
	outY = row;
	return true;
}




bool Board::Start()
{
	m_spriteRender.Init(FILEPATHBOARD, WIDTHBOARD, HIGHTBOARD);
	m_spriteRender.SetPosition({ 0.0f,0.0f,0.0f });

	m_finishSprite.Init(FILEPATH_FINISH, FINISH_WIDTH, FINISH_HEIGHT);

	m_scalePopupAnimation.Init(1.0f, 1.5f, 0.1f);
	/** ヒント画像の初期化*/
	const float cellSize = WIDTHBOARD / (float)SIZE;
	const float hintSize = cellSize * 0.6f;

	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			m_hintSprite[y][x].Init(FILEPATH, hintSize, hintSize);
		}
	}

	First();

	m_turn = BLACK;
	///** 先手をランダムで決める*/
	//std::random_device rd;
	//std::mt19937 gen(rd());
	//std::uniform_int_distribution<int> dist(0, 1);
	//m_turn = (dist(gen) == 0) ? BLACK : WHITE;

	/** 手番表示UIの初期化*/
	m_blackTurnSprite.Init(FILEPATH_BLACKTURN, TURNUI_WIDTH, TURNUI_HEIGHT);
	m_WhiteTurnSprite.Init(FILEPATH_WHITETURN, TURNUI_WIDTH, TURNUI_HEIGHT);
	
	/** アニメーションを開始させる*/
	m_lastTurn = m_turn;
	m_turnUIState = TurnUIState::SlideIn;
	m_turnUITimer = 0.0f;
	m_turnUIPosX = TURNUI_START_X;
	m_isPlayTurnAnimation = true;

	/** 全マス分のインスタンスを初期化*/
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			m_piece_White[y][x].Start();
			m_piece_Black[y][x].Start();
		}
	}
	return true;
}

void Board::Update()
{
	/** 手番表示用アニメーションを更新*/
	UpdateTurnUI();

	/** Finish絵演出中なら更新して、終わったら勝敗を確定*/
	if (m_scalePopupAnimation.IsPlaying())
	{
		bool finished = m_scalePopupAnimation.Update(g_gameTime->GetFrameDeltaTime());
		if (finished)
		{
			FinalizeGameEnd();
		}
	}
	
	/** マウス操作をできるようにする*/
	HandleMouseInput();
	/** 白の番になったらAIに考えて置いてもらう*/
	UpdateAI();
	
}

void Board::HandleMouseInput()
{

	/** ゲームが終了していたら操作できない*/
	if (m_gameState != GameState::Playing)
	{
		return;
	}
	/** ターン交代のスライドアニメ―ション中は操作できない*/
	if (m_isPlayTurnAnimation)
	{
		return;
	}
	/** どのウィンドウを基準にするかを知るためにhwndの識別番号を取得する*/
	/** アクティブウィンドウのハンドルを取得*/
	/** GetActiveは「現在、キーボードフォーカスが当たっている(操作対象になっている)ウィンドウ*/
	HWND hwnd = GetActiveWindow();
	if (hwnd == nullptr)
	{
		return; // ウィンドウが取得できなければ何もしない
	}

	/** 左クリックのエッジ検知*/
	/**VK_LBUTTONは「マウスの左ボタン」を表す定数*/
	bool leftButtonIsPressed = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
	/** クリックした瞬間を検知する*/
	bool leftButtonTriggerd = leftButtonIsPressed && !m_leftButtonWasPressed;
	/** 次のフレームのために、今の状態を保存しておく*/
	m_leftButtonWasPressed = leftButtonIsPressed;

	/** クリックされた瞬間は何もしない*/
	if (!leftButtonTriggerd)
	{
		return;
	}


	/** マウス座標の取得*/
	POINT pt;
	/** 現在のマウスカーソル位置を取得*/
	GetCursorPos(&pt);
	/** 取得したスクリーン座標をクライアント座標に変換*/
	ScreenToClient(hwnd, &pt);

	/** クライアントサイズの取得*/
	RECT rect;
	/** クライアント領域の短径情報を取得*/
	GetClientRect(hwnd, &rect);
	/** right - leftで幅、bottom - topで高さを計算してfloat型に変換*/
	float clientWidth = static_cast<float>(rect.right - rect.left);
	float clientHeight = static_cast<float>(rect.bottom - rect.top);

	/** クライアント座標　→　ワールド座標に取得*/
	float worldX = static_cast<float>(pt.x) - clientWidth * 0.5f;
	/** Y軸はスクリーン座標系とワールド座標系でY軸の向きが逆なので
		 「-」をつける*/
	float worldY = -(static_cast<float>(pt.y) - clientHeight * 0.5f);

	/** ワールド座標→盤面のマス目に変換*/
	int bx, by;
	if (!WorldPosToBoardIndex(worldX, worldY, bx, by))
	{
		return;
	}

	/** 石を置く*/
	if (CanPut(bx, by, m_turn))
	{
		PutStone(bx, by, m_turn);
		/** 駒を置いたらターンを交代する*/
		Stone next = (m_turn == BLACK) ? WHITE : BLACK;
		if (HasValidMove(next))
		{
			StartTurnAnimation();
			m_turn = next;
		}
		/** 次の手番が置けない場合、現在の手番も置けなければ終了*/
		else if (!HasValidMove(m_turn))
		{
			CheckGameEnd();
		}
	}
}
void Board::StartTurnAnimation()
{
	m_lastTurn = m_turn;
	m_turnUIState = TurnUIState::SlideIn;
	m_turnUITimer = 0.0f;
	m_turnUIPosX = TURNUI_START_X;
	m_isPlayTurnAnimation = true;
}

void Board::UpdateTurnUI()
{


	float deltaTime = g_gameTime->GetFrameDeltaTime();

	switch (m_turnUIState)
	{
	/** 画面外から中央へ、時間経過(t)に応じて線形補完しながら移動*/
	case TurnUIState::SlideIn:
		{
			m_turnUITimer += deltaTime;
		float t = m_turnUITimer / TURNUI_SLIDEIN_TIME;
		/** ここで次のHold状態に遷移*/
		if (t >= 1.0f)
		{
			m_turnUIPosX = TURNUI_CENTER_X;
			m_turnUIState = TurnUIState::Hold;
			m_turnUITimer = 0.0f;
		}
		else
		{
			/** 右から中央へ線形補完*/
			m_turnUIPosX = TURNUI_START_X + (TURNUI_CENTER_X - TURNUI_START_X) * t;
		}
		break;
		}
		/**中央位置で静止したまま、TURNUI_HOLD_TIMEだけ待機。時間が経過したらSlideOutへ遷移*/
		case TurnUIState::Hold:
		{
			m_turnUITimer += deltaTime;
			m_turnUIPosX = TURNUI_CENTER_X;
			if (m_turnUITimer >= TURNUI_HOLD_TIME)
			{
				m_turnUIState = TurnUIState::SlideOut;
				m_turnUITimer = 0.0f;
			}
			break;
		}
		case TurnUIState::SlideOut:
		{
			/** 中央から画面外へ*/
			m_turnUITimer += deltaTime;
			float t = m_turnUITimer / TURNUI_SLIDEOUT_TIME;
			if (t >= 1.0f)
			{
				m_turnUIPosX = TURNUI_END_X;
				m_turnUIState = TurnUIState::Idle;
				m_turnUITimer = 0.0f;
				m_isPlayTurnAnimation = false;
			}
			else
			{
				/** 中央から画面外へ線形補完*/
				m_turnUIPosX = TURNUI_CENTER_X + (TURNUI_END_X - TURNUI_CENTER_X) * t;
			}
			break;
		}

		case TurnUIState::Idle:
		default:
			/** 画面外で待機*/
			m_turnUIPosX = TURNUI_END_X;
			
			break;
	}
}


//初期化
void Board::First()
{

	//盤面を全てEMPTY（何も置かれていない状態)にしている
	for (int y = 0; y < SIZE; y++)
		for (int x = 0; x < SIZE; x++)
			m_board[y][x] = EMPTY;

	//6×6の盤面の中央は(2,2)(3,3)だから
	// 盤面から0,1,2,……と数える
		  //行//列
	m_board[2][2] = WHITE;
	m_board[3][3] = WHITE;
	m_board[2][3] = BLACK;
	m_board[3][2] = BLACK;

}

Board::Stone Board::GetStone(int x, int y)const
{
	return m_board[y][x];
}

void Board::CountStone(int& black, int& white)const
{
	/** 初期化しておく*/
	black = 0;
	white = 0;
	/** 盤面を全て見て黒と白の駒を数える*/
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			if (m_board[y][x] == BLACK)
			{
				black++;
			}
			else if(m_board[y][x] ==WHITE)
			{
				white++;
			}
		}
	}


}


void Board::CheckGameEnd()
{
	if (!HasValidMove(BLACK) && !HasValidMove(WHITE))
	{
		/** ここでは勝敗を決めず、FINISH演出を開始するだけ*/
		m_gameState = GameState::Finishing;
		m_scalePopupAnimation.Start();
	}
}

void Board::FinalizeGameEnd()
{
	int blackCount = 0;
	int whiteCount = 0;
	CountStone(blackCount, whiteCount);
	/** 黒が白より多い場合はクリアにする*/
	if (blackCount > whiteCount)
	{
		/** すでに生成していたら生成しない*/
		if (m_GameClear == nullptr)
		{
			m_GameClear = NewGO<GameClear>(0, "gameclear");
		}
		/** ピースカウントを設定 */
		m_GameClear->SetPieceCount(blackCount, whiteCount);
		m_gameState = GameState::GameClear;
	}
	else
	{
		if (m_GameOver == nullptr)
		{
			m_GameOver = NewGO<GameOver>(0, "gameover");
		}
		/** ここで駒数を渡す*/
		m_GameOver->SetPieceCount(blackCount, whiteCount);
		m_gameState = GameState::GameOver;
	}
}

void Board::Render(RenderContext& rc)
{
	//盤面の表示
	m_spriteRender.Update();
	m_spriteRender.Draw(rc);

	/** 盤面の中心が(0,0)なので
	石の盤面を左上端(WIDTHBORAD/2,-HIGHTBOARD/2)を基準にする*/
	const float startX = -WIDTHBOARD * 0.5f;
	const float startY = -HIGHTBOARD * 0.5f;
	const float cellSize = WIDTHBOARD / (float)SIZE;

	/** 盤面に駒を置ける場所にヒントを描画*/
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			if (CanPut(x, y, m_turn))
			{
				float drawX = startX + x * cellSize + cellSize * 0.5f;
				float drawY = startY + (SIZE - 1 - y) * cellSize + cellSize * 0.5f;

				m_hintSprite[y][x].SetPosition({ drawX,drawY,0.0f });
				m_hintSprite[y][x].Update();
				m_hintSprite[y][x].Draw(rc);
			}
		}
	}



	//ここで盤面のデータをみて初期位置の石を配置
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			//石の描画位置の計算
			float drawX = startX + x * cellSize + cellSize * 0.5f;
			/**ワールド座標(Y+が上)に変換するため上下を反転させる */
			float drawY = startY + (SIZE - 1 - y) * cellSize + cellSize * 0.5f;

			if (m_board[y][x] == BLACK)
			{
				m_piece_Black[y][x].SetPosition(drawX, drawY);
				m_piece_Black[y][x].Render(rc,m_turn ==BLACK);
			}
			else if (m_board[y][x] == WHITE)
			{
				m_piece_White[y][x].SetPosition(drawX, drawY);
				m_piece_White[y][x].Render(rc,m_turn ==WHITE);
			}
		}
	}


	/** FINISH演出中ならスケールを適用して描画*/
	if (m_scalePopupAnimation.IsPlaying())
	{
		float s = m_scalePopupAnimation.GetScale();
		m_finishSprite.SetPosition({ 0.0f, 0.0f, 0.0f });
		m_finishSprite.SetScale(Vector3(s, s, 1.0f)); 
		m_finishSprite.Update();
		m_finishSprite.Draw(rc);
	}


	/** 現在の手番に応じて手番表示UIを切り替えて描画させる*/
	if (m_turn == BLACK)
	{
		m_blackTurnSprite.SetPosition({ m_turnUIPosX,TURNUI_POS_Y,0.0f });
		m_blackTurnSprite.Update();
		m_blackTurnSprite.Draw(rc);
	}

	else if (m_turn == WHITE)
	{
		m_WhiteTurnSprite.SetPosition({ m_turnUIPosX, TURNUI_POS_Y, 0.0f });
		m_WhiteTurnSprite.Update();
		m_WhiteTurnSprite.Draw(rc);
	}

}