#include<iostream>
#include<string>
#include<vector>
#include<graphics.h>
using namespace std;

#pragma comment(lib, "MSIMG32.LIB")
#pragma comment(lib, "Winmm.lib")

bool start_game = false;
bool IsRunning = true;
int window_height = 771;
int window_width = 1800;

const int button_width = 322;
const int button_height = 107;

const int button1_width = 106;
const int button1_height = 43;

inline void putimage_a(int x, int y, IMAGE* img) {
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

class button
{
public:
	button(RECT ret, LPCTSTR path_idle, LPCTSTR path_hover, LPCTSTR path_push)
	{
		rect = ret;
		loadimage(&idle, path_idle);
		loadimage(&hover, path_hover);
	}
	~button() = default;

	void draw()
	{
		switch (status)
		{
		case Status::idle:
			putimage_a(rect.left, rect.top, &idle);
			break;
		case Status::hover:
			putimage_a(rect.left, rect.top, &hover);
			break;
		case Status::push:
			putimage_a(rect.left, rect.top, &push);
			break;
		}
	}

	void process(const ExMessage& msg)
	{
		if (msg.message == WM_MOUSEMOVE)
		{
			if (check_M(msg.x, msg.y) && status == Status::idle)
			{
				status = Status::hover;
			}
			else if (status == Status::hover && !check_M(msg.x, msg.y))
			{
				status = Status::idle;
			}
		}
		else if (msg.message == WM_LBUTTONDOWN)
		{
			if (check_M(msg.x, msg.y))
			{
				status = Status::push;
			}
		}
		else if (msg.message == WM_LBUTTONUP)
		{
			if (status == Status::push)
			{
				isClick();
			}
			else
			{
				status = Status::idle;
			}
		}
	}

protected:
	virtual void isClick() = 0;

private:
	enum class Status
	{
		idle = 0,
		hover,
		push
	};

private:
	RECT rect;
	IMAGE idle;
	IMAGE hover;
	IMAGE push;
	Status status = Status::idle;

private:
	bool check_M(int x, int y)
	{
		if (x >= rect.left && x <= rect.right && y >= rect.top && y <= rect.bottom)
		{
			return true;
		}
		return false;
	}
};

class start_button : public button
{
public:
	start_button(RECT ret, LPCTSTR path_idle, LPCTSTR path_hover, LPCTSTR path_push)
		: button(ret, path_idle, path_hover, path_push) {
	}
	~start_button() = default;
protected:
	void isClick() override
	{
		start_game = true;
		mciSendString(_T("play bgm repeat from 0"), NULL, 0, NULL);
	}
};

class exit_button : public button
{
public:
	exit_button(RECT ret, LPCTSTR path_idle, LPCTSTR path_hover, LPCTSTR path_push)
		: button(ret, path_idle, path_hover, path_push) {
	}
	~exit_button() = default;
protected:
	void isClick() override
	{
		IsRunning = false;
	}
};

class Animation
{
public:
	Animation(LPCTSTR path, int num, int interval)
	{
		ms = interval;

		TCHAR path_file[256];
		for (size_t i = 0; i < num; i++)
		{
			_stprintf_s(path_file, path, i);

			IMAGE* img = new IMAGE();
			loadimage(img, path_file);
			c_list.push_back(img);
		}

	}
	~Animation()
	{
		for (size_t i = 0; i < c_list.size(); i++)delete c_list[i];
	}

	void play(int x, int y, int delta)
	{
		timer += delta;
		if (timer >= ms)
		{
			idx = (idx + 1) % c_list.size();
			timer = 0;
		}
		putimage_a(x, y, c_list[idx]);
	}
private:

	int idx = 0;
	int ms = 0;
	int timer = 0;

	vector<IMAGE*>c_list;
};

class player {
public:
	bool shoot = false;
	DWORD last_shoot_time = 0;
	const DWORD shoot_interval = 200;
	POINT pos = { 300,300 };

	player()
	{
		player_l = new Animation(_T("player/player_l%d.png"), 4, 45);
		player_r = new Animation(_T("player/player_r%d.png"), 4, 45);
		player_dn = new Animation(_T("player/player_d%d.png"), 4, 45);
		player_up = new Animation(_T("player/player_up%d.png"), 4, 45);
	}
	~player()
	{
		delete player_l;
		delete player_r;
		delete player_dn;
		delete player_up;
	}

	//角色移动
	void process_move(const ExMessage& msg) {
		if (msg.message == WM_KEYDOWN)
		{
			switch (msg.vkcode)
			{
			case VK_UP:
				move_up = true;
				break;
			case VK_DOWN:
				move_down = true;
				break;
			case VK_LEFT:
				move_left = true;
				break;
			case VK_RIGHT:
				move_right = true;
				break;
			case 'S': // 按下“S”键
				shoot = true;
				break;
			}
		}
		else if (msg.message == WM_KEYUP)
		{
			switch (msg.vkcode)
			{
			case VK_UP:
				p1 = 1, p2 = 0, p3 = 0, p4 = 0;
				move_up = false;
				break;
			case VK_DOWN:
				p1 = 0, p2 = 1, p3 = 0, p4 = 0;
				move_down = false;
				break;
			case VK_LEFT:
				p1 = 0, p2 = 0, p3 = 1, p4 = 0;
				move_left = false;
				break;
			case VK_RIGHT:
				p1 = 0, p2 = 0, p3 = 0, p4 = 1;
				move_right = false;
				break;
			case 'S': // 释放“S”键
				shoot = false;
				break;
			}
		}
	}

	void move() {
		int x = move_right - move_left;
		int y = move_down - move_up;
		double len_xy = sqrt(x * x + y * y);
		if (len_xy > 0)
		{
			double real_x = x / len_xy;
			double real_y = y / len_xy;
			pos.x += (int)(speed * real_x);
			pos.y += (int)(speed * real_y);
		}

		if (pos.x < 0)pos.x = 0;
		if (pos.x > window_width - width)pos.x = window_width - width;
		if (pos.y < 0)pos.y = 0;
		if (pos.y > window_height - height)pos.y = window_height - height;
	}

	void draw(int delta)
	{
		if (move_up)player_up->play(pos.x, pos.y, delta);
		else if (move_down)player_dn->play(pos.x, pos.y, delta);
		else if (move_left)player_l->play(pos.x, pos.y, delta);
		else if (move_right)player_r->play(pos.x, pos.y, delta);
		else if (!move_up && p1 == 1)player_up->play(pos.x, pos.y, delta);
		else if (!move_down && p2 == 1)player_dn->play(pos.x, pos.y, delta);
		else if (!move_left && p3 == 1)player_l->play(pos.x, pos.y, delta);
		else if (!move_right && p4 == 1)player_r->play(pos.x, pos.y, delta);
	}

	const POINT& get_pos() const
	{
		return pos;
	}

private:
	Animation* player_r;
	Animation* player_l;
	Animation* player_dn;
	Animation* player_up;

public:
	bool move_up = false;
	bool move_down = false;
	bool move_left = false;
	bool move_right = false;

public:
	int speed = 7;
	int width = 30;
	int height = 30;
	int damage = 40;
	int p1 = 0, p2 = 0, p3 = 0, p4 = 1;
};

class bullet {
public:
	//Animation* bt;
	POINT pos = { 0,0 };
	int speed = 10;
	int p1 = 0, p2 = 0, p3 = 0, p4 = 0;
	bool on_x = false;
	bool on_y = false;
	bool is_fly = false;

public:
	bullet() = default;
	~bullet() = default;

	void draw(int r)  const{
		setlinecolor(RGB(255, 155, 50));
		setfillcolor(RGB(128, 0, 128));
		fillcircle(pos.x, pos.y, 10 + r / 10);	
	}

	void draw1() {
		setlinecolor(RGB(0, 0, 255));
		setfillcolor(RGB(128, 0, 128));
		fillcircle(pos.x, pos.y, 10);
	}

void bullet_shot(const player& pp) {
    POINT p = pp.get_pos();
    pos.x = p.x + pp.width / 2; // 从玩家中心发射
    pos.y = p.y + pp.height / 2;

	get_player_pos(pp);

    if (pp.move_up) {
        on_x = false;
        on_y = true;
        speed = -abs(speed); // 向上移动
		p1 = 1, p2 = 0, p3 = 0, p4 = 0;
    } else if (pp.move_down) {
        on_x = false;
        on_y = true;
        speed = abs(speed); // 向下移动
		p1 = 0, p2 = 1, p3 = 0, p4 = 0;
    } else if (pp.move_left) {
        on_x = true;
        on_y = false;
        speed = -abs(speed); // 向左移动
		p1 = 0, p2 = 0, p3 = 1, p4 = 0;
    } else if (pp.move_right) {
        on_x = true;
        on_y = false;
        speed = abs(speed); // 向右移动
		p1 = 0, p2 = 0, p3 = 0, p4 = 1;
    }
}

	void bullet_move()
	{
		if (on_x)pos.x += speed;
		else if (on_y)pos.y += speed;
		else if (!on_x && !on_y && p2 == 1)pos.y += speed;
		else if (!on_x && !on_y && p1 == 1)pos.y -= speed;
		else if (!on_x && !on_y && p3 == 1)pos.x -= speed;
		else if (!on_x && !on_y && p4 == 1)pos.x += speed;
	}

	void get_player_pos(const player& pp)
	{
		if (pp.p1 == 1)p1 = 1;
		else if (pp.p2 == 1)p2 = 1;
		else if (pp.p3 == 1)p3 = 1;
		else if (pp.p4 == 1)p4 = 1;
	}

	bool is_out_of_screen() const {
		return pos.x < 0 || pos.x > window_width || pos.y < 0 || pos.y > window_height;
	}

};

class Enemy {
public:
	Enemy()
	{
		enemy_l = new Animation(_T("enemy/e1_l%d.png"), 4, 45);
		enemy_r = new Animation(_T("enemy/e1_r%d.png"), 4, 45);
		enemy_dn = new Animation(_T("enemy/e1_d%d.png"), 4, 45);
		enemy_up = new Animation(_T("enemy/e1_up%d.png"), 4, 45);

		enum class edge
		{
			left = 0,
			right,
			up,
			down
		};

		edge e = (edge)(rand() % 4);
		switch (e)
		{
		case edge::left:
			pos.x = -width;
			pos.y = rand() % window_width;
			break;
		case edge::right:
			pos.x = width;
			pos.y = rand() % window_width;
			break;
		case edge::up:
			pos.x = rand() % window_height;
			pos.y = -height;
			break;
		case edge::down:
			pos.x = rand() % window_height;
			pos.y = height;
			break;
		default:
			break;
		}
	}
	~Enemy()
	{
		delete enemy_l;
		delete enemy_r;
		delete enemy_dn;
		delete enemy_up;
	}

	bool checkbullet(const bullet& b)
	{
		if (b.pos.x >= pos.x && b.pos.x <= pos.x + width && b.pos.y >= pos.y && b.pos.y <= pos.y + height)
		{
			return true;
		}
		return false;
	}

	bool checkplayer(const player& p)
	{
		if (p.pos.x >= pos.x && p.pos.x <= pos.x + width &&
			p.pos.y >= pos.y && p.pos.y <= pos.y + height)
		{
			return true;
		}
		return false;
	}

	void move(const player& p)
	{
		int x = p.pos.x - pos.x;
		int y = p.pos.y - pos.y;
		double len_xy = sqrt(x * x + y * y);
		if (len_xy > 0)
		{
			double real_x = x / len_xy;
			double real_y = y / len_xy;
			pos.x += (int)(speed * real_x);
			pos.y += (int)(speed * real_y);
		}

		if (x < 0) {
			move_left = true;
			move_right = false;
			move_up = false;
			move_down = false;
			p1 = 0, p2 = 0, p3 = 1, p4 = 0;
		}
		else if (x > 0) {
			move_right = true;
			move_left = false;
			move_up = false;
			move_down = false;
			p1 = 0, p2 = 0, p3 = 0, p4 = 1;
		}
		else if (y < 0) {
			move_up = true;
			move_down = false;
			move_left = false;
			move_right = false;
			p1 = 1, p2 = 0, p3 = 0, p4 = 0;
		}
		else if (y > 0) {
			move_down = true;
			move_up = false;
			move_left = false;
			move_right = false;
			p1 = 0, p2 = 1, p3 = 0, p4 = 0;
		}
	}

	void get_speed()
	{
		speed = rand() % 10;
		if (speed <= 2)speed += 4;
	}

	void draw(int delta)
	{
		if (move_up)enemy_up->play(pos.x, pos.y, delta);
		else if (move_down)enemy_dn->play(pos.x, pos.y, delta);
		else if (move_left)enemy_l->play(pos.x, pos.y, delta);
		else if (move_right)enemy_r->play(pos.x, pos.y, delta);
		else if (!move_up && p1 == 1)enemy_up->play(pos.x, pos.y, delta);
		else if (!move_down && p2 == 1)enemy_dn->play(pos.x, pos.y, delta);
		else if (!move_left && p3 == 1)enemy_l->play(pos.x, pos.y, delta);
		else if (!move_right && p4 == 1)enemy_r->play(pos.x, pos.y, delta);
	}

	void hurt(int damage)
	{
		hp -= damage;
		if (hp <= 0)alive = false;
	}

	bool is_alive() const
	{
		return alive;
	}

private:
	Animation* enemy_r;
	Animation* enemy_l;
	Animation* enemy_up;
	Animation* enemy_dn;

	POINT pos = { 0,0 };
	int speed = 4;
	int width = 50;
	int height = 50;
	int hp = 100;

	bool alive = true;
	bool move_up = false;
	bool move_down = false;
	bool move_left = false;
	bool move_right = false;
	int p1 = 0, p2 = 0, p3 = 0, p4 = 1;
};

class boss {
public:
	boss()
	{
		boss_l = new Animation(_T("boss/boss_l%d.png"), 4, 45);
		boss_r = new Animation(_T("boss/boss_r%d.png"), 4, 45);
		boss_dn = new Animation(_T("boss/boss_d%d.png"), 4, 45);
		boss_up = new Animation(_T("boss/boss_up%d.png"), 4, 45);

		enum class edge
		{
			up = 0,
			down,
			left,
			right
		};

		edge e = (edge)(rand() % 4);
		switch (e)
		{
		case edge::left:
			pos.x = -width;
			pos.y = rand() % window_width;
			break;
		case edge::right:
			pos.x = width;
			pos.y = rand() % window_width;
			break;
		case edge::up:
			pos.x = rand() % window_height;
			pos.y = -height;
			break;
		case edge::down:
			pos.x = rand() % window_height;
			pos.y = height;
			break;
		default:
			break;
		}
	}
	~boss()
	{
		delete boss_l;
		delete boss_r;
		delete boss_dn;
		delete boss_up;
	}

	bool checkbullet(const bullet& b)
	{
		if (b.pos.x >= pos.x && b.pos.x <= pos.x + width && b.pos.y >= pos.y && b.pos.y <= pos.y + height)
		{
			return true;
		}
		return false;
	}

	bool checkplayer(const player& p)
	{
		if (p.pos.x >= pos.x && p.pos.x <= pos.x + width &&
			p.pos.y >= pos.y && p.pos.y <= pos.y + height)
		{
			return true;
		}
		return false;
	}

	void move(const player& p)
	{
		int x = p.pos.x - pos.x;
		int y = p.pos.y - pos.y;
		double len_xy = sqrt(x * x + y * y);
		if (len_xy > 0)
		{
			double real_x = x / len_xy;
			double real_y = y / len_xy;
			pos.x += (int)(speed * real_x);
			pos.y += (int)(speed * real_y);
		}

		if (x < 0) {
			move_left = true;
			move_right = false;
			move_up = false;
			move_down = false;
			p1 = 0, p2 = 0, p3 = 1, p4 = 0;
		}
		else if (x > 0) {
			move_right = true;
			move_left = false;
			move_up = false;
			move_down = false;
			p1 = 0, p2 = 0, p3 = 0, p4 = 1;
		}
		else if (y < 0) {
			move_up = true;
			move_down = false;
			move_left = false;
			move_right = false;
			p1 = 1, p2 = 0, p3 = 0, p4 = 0;
		}
		else if (y > 0) {
			move_down = true;
			move_up = false;
			move_left = false;
			move_right = false;
			p1 = 0, p2 = 1, p3 = 0, p4 = 0;
		}
	}

	void get_speed()
	{
		speed = rand() % 5;
		if (speed <= 2)speed += 4;
	}

	void draw(int delta)
	{
		if (move_up)boss_up->play(pos.x, pos.y, delta);
		else if (move_down)boss_dn->play(pos.x, pos.y, delta);
		else if (move_left)boss_l->play(pos.x, pos.y, delta);
		else if (move_right)boss_r->play(pos.x, pos.y, delta);
		else if (!move_up && p1 == 1)boss_up->play(pos.x, pos.y, delta);
		else if (!move_down && p2 == 1)boss_dn->play(pos.x, pos.y, delta);
		else if (!move_left && p3 == 1)boss_l->play(pos.x, pos.y, delta);
		else if (!move_right && p4 == 1)boss_r->play(pos.x, pos.y, delta);
	}

	void hurt(int damage)
	{
		hp -= damage;
		if (hp <= 0)alive = false;
	}

	bool is_alive() const
	{
		return alive;
	}

private:
	Animation* boss_r;
	Animation* boss_l;
	Animation* boss_up;
	Animation* boss_dn;

	POINT pos = { 0,0 };
	int speed = 4;
	int width = 80;
	int height = 80;
	int hp = 100;

	bool alive = true;
	bool move_up = false;
	bool move_down = false;
	bool move_left = false;
	bool move_right = false;
	int p1 = 0, p2 = 0, p3 = 0, p4 = 1;
};

void trygenerate_enemy(vector<Enemy*>& e_list)
{
	const int interval = 100;
	static int timer = 0;
	if ((++timer) % interval == 0)
	{
		Enemy* e = new Enemy();
		e->get_speed();
		e_list.push_back(e);
	}
}

void trygenerate_boss(vector<boss*>& b_list)
{
	const int interval = 100;
	static int timer = 0;
	if ((++timer) % interval == 0)
	{
		boss* b = new boss();
		b->get_speed();
		b_list.push_back(b);
	}
}

void updatebullet(vector<bullet>& bb, const player& pp)
{
	const double R_speed = 0.005;
	const double T_speed = 0.005;

	double R_interval = 2 * 3.14159 / bb.size();

	POINT p = pp.get_pos();

	double rad = 75 + 25 * sin(GetTickCount() * R_speed);

	for (size_t i = 0; i < bb.size(); i++)
	{
		double time = i * R_interval + GetTickCount() * T_speed + 100;
		bb[i].pos.x = p.x + (int)(rad * sin(time)) + pp.width;
		bb[i].pos.y = p.y + (int)(rad * cos(time)) + pp.height;
	}

}

void draw_score(int score)
{
	TCHAR score_text[256];
	_stprintf_s(score_text, _T("Score: %d"), score);

	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 85, 255));
	outtextxy(0, 0, score_text);
}

int main()
{
	initgraph(window_width, window_height);

	mciSendString(_T("open player/bgmus.mp3 alias bgm"), NULL, 0, NULL);
	mciSendString(_T("open player/get_hit.mp3 alias hit"), NULL, 0, NULL);

	player pp;
	vector<Enemy*>e_list;
	vector<boss*>b_list;
	vector<bullet>bb(3);
	vector<bullet> bullets;
	IMAGE background;
	IMAGE menu;

	RECT start_button_rect, exit_button_rect;

	start_button_rect.left = (window_width - button_width) / 2;
	start_button_rect.top = 200;
	start_button_rect.right = start_button_rect.left + button_width;
	start_button_rect.bottom = start_button_rect.top + button_height;

	exit_button_rect.left = (window_width - button1_width) / 2;
	exit_button_rect.top = 400;
	exit_button_rect.right = exit_button_rect.left + button1_width;
	exit_button_rect.bottom = exit_button_rect.top + button1_height;

	start_button start_button_kg = start_button(start_button_rect, _T("button/start_idle.png"), _T("button/start_hover.png"), _T("button/start_push.png"));
	exit_button exit_button_kg = exit_button(exit_button_rect, _T("button/exit_idle.png"), _T("button/exit_hover.png"), _T("button/exit_push.png"));

	loadimage(&menu, _T("player/hold.jpg"));
	loadimage(&background, _T("background.jpg"));

	bool boss_apper = false;

	int s = 0;
	ExMessage msg;

	BeginBatchDraw();
	while (IsRunning)
	{
		DWORD start_time = GetTickCount();

		while (peekmessage(&msg))
		{
			if (start_game)pp.process_move(msg);
			else start_button_kg.process(msg), exit_button_kg.process(msg);
		}

		if (start_game)
		{
			pp.move();

			// 发射子弹
			if (pp.shoot && GetTickCount() - pp.last_shoot_time > pp.shoot_interval) {
				bullet new_bullet;
				new_bullet.bullet_shot(pp);
				bullets.push_back(new_bullet); // 添加新子弹
				pp.last_shoot_time = GetTickCount(); // 更新发射时间
			}

			// 更新子弹位置
			for (auto it = bullets.begin(); it != bullets.end(); ) {
				it->bullet_move();
				if (it->is_out_of_screen()) {
					it = bullets.erase(it); // 移除飞出屏幕的子弹
				}
				else {
					++it;
				}
			}

			//敌人的刷新
			trygenerate_enemy(e_list);
			//boss的刷新
			if (s >= 5)trygenerate_boss(b_list), boss_apper = true;

			//boss的移动
			if (boss_apper)for (boss* boss : b_list)boss->move(pp);
			//敌人的移动
			for (Enemy* enemy : e_list)
			{
				enemy->move(pp);
			}

			//检测碰撞
			for (Enemy* enemy : e_list)
			{
				if (enemy->checkplayer(pp))
				{
					MessageBox(GetHWnd(), _T("Game Over"), _T("Game Over"), MB_OK);
					IsRunning = false;
					break;
				}
			}
		}
		cleardevice();

		if (start_game)
		{
			putimage(0, 0, &background);
			pp.draw(1000 / 144);
			//敌人的绘制
			for (Enemy* enemy : e_list)
			{
				enemy->draw(1000 / 144);
			}
			//boss的绘制
			if (boss_apper)
			{
				for (boss* boss : b_list)boss->draw(1000 / 144);
			}
			//子弹的绘制
			for (bullet& b : bb)b.draw(s);
			for (auto b : bullets) {
				b.draw1();
			}
			updatebullet(bb, pp);

			for (Enemy* enemy : e_list) {
				if (enemy->checkplayer(pp)) {
					MessageBox(GetHWnd(), _T("Game Over"), _T("Game Over"), MB_OK);
					IsRunning = false;
					break;
				}
				for (bullet& b : bullets) { // 检测新子弹
					if (enemy->checkbullet(b)) {
						mciSendString(_T("play hit from 0"), NULL, 0, NULL);
						enemy->hurt(pp.damage);
					}
				}
				for (bullet& b : bb) { // 检测旧子弹
					if (enemy->checkbullet(b)) {
						mciSendString(_T("play hit from 0"), NULL, 0, NULL);
						enemy->hurt(pp.damage);
					}
				}
			}

			if (boss_apper) {
				for (boss* boss : b_list) {
					if (boss->checkplayer(pp)) {
						MessageBox(GetHWnd(), _T("Game Over"), _T("Game Over"), MB_OK);
						IsRunning = false;
						break;
					}
					for (bullet& b : bullets) { // 检测新子弹
						if (boss->checkbullet(b)) {
							mciSendString(_T("play hit from 0"), NULL, 0, NULL);
							boss->hurt(pp.damage);
						}
					}
					for (bullet& b : bb) { // 检测旧子弹
						if (boss->checkbullet(b)) {
							mciSendString(_T("play hit from 0"), NULL, 0, NULL);
							boss->hurt(pp.damage);
						}
					}
				}
			}

			for (size_t i = 0; i < e_list.size(); i++)
			{
				Enemy* e = e_list[i];
				if (!e->is_alive())
				{
					swap(e_list[i], e_list.back());
					e_list.pop_back();
					delete e;
					s++;
				}
			}

			for (size_t i = 0; i < b_list.size(); i++)
			{
				boss* b = b_list[i];
				if (!b->is_alive())
				{
					swap(b_list[i], b_list.back());
					b_list.pop_back();
					delete b;
					s += 5;
				}
			}

			draw_score(s);
		}
		else {
			putimage(0, 0, &menu);
			start_button_kg.draw();
			exit_button_kg.draw();
		}

		FlushBatchDraw();

		DWORD end_time = GetTickCount();

		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / 60)
		{
			Sleep(1000 / 60 - delta_time);
		}

	}
	EndBatchDraw();

	return 0;
}