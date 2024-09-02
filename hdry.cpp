/*
作者：厚德荣耀工作室
程序开发：IOI_winer
*/
//#include<SFML/Graphics.hpp>
//#include<SFML/Window.hpp>
//#include<SFML/System.hpp>
#define _CRT_SECURE_NO_WARNINGS 
#include <bits/stdc++.h>
#include <WinSock2.h>
#include <windows.h>       
#pragma comment(lib,"ws2_32.lib")
using namespace std;
int a1, b1 = 1000, cd1 = 1, cd2 = 1, cd3 = 2, cd4 = 2, cd5 = 3, sum1 = 15, sum2 = 5, sum3 = 8, sum4 = 5, yh, bh, sj1, sj2;//a1:我方血量,b1:boss血量，yh:共有多少个玩家，bh:玩家编号 
bool voicekz = true;
void gotoxy(int x, int y) {
	int xx = 0x0b;
	HANDLE hOutput;
	COORD loc;
	loc.X = x;
	loc.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, loc);
}
void ld(string inputString) {
	if (voicekz == 0) return;
	FILE* fp = fopen("voice.vbs", "w");//按照下面第三行格式将要转声音的文字内容写入脚本文件
	char temp[1024]; //若文字较多时，增加这个数组
	memset(temp, 0, 1024);//字符串变量要重复使用时要进行清空
	for (int a = 0; a < inputString.size(); a++) temp[a] = inputString[a];
	fprintf(fp, "CreateObject(\"SAPI.SpVoice\").Speak(\"%s\")", temp);//注意转义字符，无报错
	fclose(fp);//关闭脚本文件
	system("voice.vbs");//用system函数运行生成的脚本文件发出声音	
}
int sj(int a, int b)//随机数函数 
{
	return a + rand() % (b - a + 1);
}
struct wanjia {
	string name;//名字
	string mima;//用户密码
	int sp[7][50];//所拥有的碎片数量
	int wq[100];//所有武器及其等级 
	int dj = 1;//等级
	int gq = 1;//已打通的关卡数量 
	long long jy;//经验值 
	long long mn = 100;//马内 
}player[100];//玩家结构体   
struct reiwu {
	string mz;//技能名 
	string jnm;
	string jnjj;
	int gj;
	bool tsx;//技能是否具有特殊性； 
	int moy;//技能是加血(1)还是伤害(2)还是加钱(3)； 
}rw[7][50];//角色 
struct hdyh {
	string name;//商品名 
	string jj;//商品介绍 
	int jg;//商品价格 
	int sum;//商品数量 
}sp[50];//厚德银行里的商品
struct chengjiu {
	int sum;//玩家目前的指标 
	int ans;//完成成就要达到的指标 
	string name;//成就名称 
	string nr;//成就内容 
}cj[50];//成就系统 
void write() {
	freopen("保存.txt", "w", stdout);
	cout << yh << endl;
	for (int a = 1; a <= yh; a++) {
		cout << player[a].name << " " << player[a].mima << endl;
		cout << player[a].dj << " " << player[a].gq << " " << player[a].jy << " " << player[a].mn << endl;
		for (int b = 3; b <= 5; b++)
			for (int c = 1; c <= 49; c++) cout << player[a].sp[b][c] << " ";
		cout << endl;
		for (int d = 1; d <= 99; d++) cout << player[a].wq[d] << " ";
		cout << endl;
	}
	freopen("CON", "w", stdout);
}
void read() {
	freopen("保存.txt", "r", stdin);
	cin >> yh;
	for (int a = 1; a <= yh; a++) {
		cin >> player[a].name >> player[a].mima;
		cin >> player[a].dj >> player[a].gq >> player[a].jy >> player[a].mn;
		for (int b = 3; b <= 5; b++)
			for (int c = 1; c <= 49; c++) cin >> player[a].sp[b][c];
		for (int d = 1; d <= 99; d++) cin >> player[a].wq[d];
	}
	freopen("CON", "r", stdin);
}
void chushihua() {
	rw[3][1].mz = "袁晟峰"; rw[3][1].jnm = "夹子音"; rw[3][1].jnjj = "200伤害"; rw[3][1].gj = 200;
	rw[3][2].mz = "邹建辉"; rw[3][2].jnm = "双色球"; rw[3][2].jnjj = "150伤害"; rw[3][2].gj = 150;
	rw[3][3].mz = "廖浩宇"; rw[3][3].jnm = "学生会老大"; rw[3][3].jnjj = "250伤害"; rw[3][3].gj = 250;
	rw[3][4].mz = "徐浩航"; rw[3][4].jnm = "school flower"; rw[3][4].jnjj = "250伤害"; rw[3][4].gj = 250;
	rw[3][5].mz = "张亦孙"; rw[3][5].jnm = "制尿"; rw[3][5].jnjj = "制一瓶尿，强行灌入敌方嘴中，300伤害"; rw[3][5].gj = 300;
	rw[4][1].mz = "毕明哲"; rw[4][1].jnm = "取外号"; rw[4][1].jnjj = "取一个外号,500伤害"; rw[4][1].tsx = 0; rw[4][1].moy = 2; rw[4][1].gj = 500;
	rw[4][2].mz = "胡原诚"; rw[4][2].jnm = "原神，启动"; rw[4][2].jnjj = "用原石换1000厚德币"; rw[4][2].tsx = 0; rw[4][2].moy = 3; rw[4][2].gj = 1000;
	rw[4][3].mz = "黄泽之"; rw[4][3].jnm = "无畏元谋人"; rw[4][3].jnjj = "召唤一个元谋人，造成防御和伤害"; rw[4][3].tsx = 1; rw[4][3].moy = 0; rw[4][3].gj = 0;
	rw[4][4].mz = "叶谨彧"; rw[4][4].jnm = "玩不了一点"; rw[4][4].jnjj = "【禁锢锁链】数量+8"; rw[4][4].tsx = 1;
	rw[4][5].mz = "周扬"; rw[4][5].jnm = "GGBond：降狗十巴掌"; rw[4][5].jnjj = "百分之三十伤害"; rw[4][5].tsx = 1;
	rw[4][6].mz = "卜裕洋"; rw[4][6].jnm = "不是人/卜氏人：裸奔"; rw[4][6].jnjj = "闪瞎对方 该回合内敌人打出的伤害会以双倍返回"; rw[4][6].tsx = 1;
	rw[4][7].mz = "欧阳宇奕"; rw[4][7].jnm = "大帝攻击——推翻曾国"; rw[4][7].jnjj = "500伤害"; rw[4][7].gj = 500; rw[4][7].moy = 2;
	rw[4][8].mz = "叶泯余"; rw[4][8].jnm = "老八答辩"; rw[4][8].jnjj = "使用一坨神奇答辩，交换敌我血量"; rw[4][8].tsx = 1;
	rw[5][1].mz = "龙哥"; rw[5][1].jnm = "神龙吐息"; rw[5][1].jnjj = "1000伤害"; rw[5][1].gj = 1000; rw[5][1].tsx = 0; rw[5][1].moy = 2;
	rw[5][2].mz = "才坤"; rw[5][2].jnm = "超能保肾药水"; rw[5][2].jnjj = "回500滴血"; rw[5][2].gj = 500; rw[5][2].tsx = 0; rw[5][2].moy = 1;
	rw[5][3].mz = "肖爱平"; rw[5][3].jnm = "going shoping"; rw[5][3].jnjj = "（除超能金坷垃外）所有商品数量+2"; rw[5][3].tsx = 1;
	rw[5][4].mz = "王子龙"; rw[5][4].jnm = "树枝乱鞭"; rw[5][4].jnjj = "敌人血量减半"; rw[5][4].moy = 2; rw[5][4].tsx = 1;
	rw[5][5].mz = "作者"; rw[5][5].jnm = "扣税"; rw[5][5].jnjj = "给敌人扣税（敌人降一级)"; rw[5][5].moy = 2; rw[5][5].tsx = 1;
	for (int i = 0; i <= 49; i++) {
		rw[3][i].tsx = 0;
		rw[3][i].moy = 2;
	}
	sp[1].name = "才坤同款保肾药水"; sp[1].jj = "血量+100(发动殴打时使用)"; sp[1].jg = 200;
	sp[2].name = "金坷垃"; sp[2].jj = "将所有普攻冷却清零"; sp[2].jg = 50;
	sp[3].name = "超能金坷垃"; sp[3].jj = "将技能冷却清零"; sp[3].jg = 100;
	sp[4].name = "禁锢锁链"; sp[4].jj = "百分之七十可能禁锢敌人一回合"; sp[4].jg = 60;
	sp[5].name = "鼠头鸭脖"; sp[5].jj = "使敌人中毒造成随机伤害(发动讲话时使用)"; sp[5].jg = 10;
	sp[6].name = "反光镜"; sp[6].jj = "躲避敌人大招"; sp[6].jg = 300;
	sp[7].name = "激素"; sp[7].jj = "徐强牌，50%可能正作用，50%可能副作用"; sp[7].jg = 100;
	sp[8].name = "保中四星卡"; sp[8].jj = "抽角色时必中四星"; sp[8].jg = 150;
	sp[9].name = "保中五星卡"; sp[9].jj = "抽角色时必中五星"; sp[9].jg = 500;
	sp[10].name = "严重违纪"; sp[10].jj = "发动班优时用此造成额外500伤害"; sp[10].jg = 300;
	sp[11].name = "冰淇淋（夏日限定）"; sp[11].jj = "清凉一夏，血量+%50"; sp[11].jg = 200;
	sp[12].name = "手抛式原子弹"; sp[12].jj = "富含铀-235，营养又健康，1次爆炸伤害+3次辐射伤害"; sp[12].jg = 500;
	sp[13].name = "裕洋牌时间晶体"; sp[13].jj = "大帝法宝，宇宙级精品，+1次战斗机会"; sp[13].jg = 250;
	sp[14].name = "核辐射";
	sp[15].name ="冰红茶";sp[15].jj="肘击敌人，造成极高伤害，但有24%可能会坠机"; sp[15].jg=800;
	cj[1].name = "值日班长"; cj[1].nr = "使用【严重违纪】超过3次"; cj[1].ans = 3;
	cj[2].name = "资深食堂阿姨"; cj[2].nr = "使用【鼠头鸭脖】超过10次"; cj[2].ans = 10;
	cj[3].name = "生物课代表"; cj[3].nr = "使用【反光镜】超过2次"; cj[3].ans = 2;
	cj[4].name = "校霸"; cj[4].nr = "使用【殴打】超过8次"; cj[4].ans = 8;
	cj[5].name = "富豪"; cj[5].nr = "厚德币数量曾大于1500"; cj[5].ans = 1;
	cj[6].name = "五金店批发商"; cj[6].nr = "使用【禁锢锁链】超过15次"; cj[6].ans = 15;
	cj[7].name = "老中医"; cj[7].nr = "使用【保肾药水】超过5次"; cj[7].ans = 5;
}
void  fight(int j, int boss1) {
	string boss2;
	if (boss1 == 1) boss2 = "bob";
	if (boss1 == 2) boss2 = "病的不轻";
	if (boss1 == 3) boss2 = "点cc先生";
	if (boss1 == 4) boss2 = "白狗";
	if (j == 0) boss2 = "卜裕洋";

	cd1 = 1, cd2 = 1, cd3 = 2, cd4 = 2, cd5 = 3;
	for (int a = 1; a <= 7; a++) cj[a].sum = 0;
	if (j == 0) {
		cout << endl << "警告：你所面对的boss是宇宙大帝卜裕洋，他的战力是bob的数倍，如果你赢了，你将获得双倍奖励（厚德币，经验值），但如果你输了，你的厚德币将掉落更多，确定要挑战吗？（按0退出,按其余键确定)" << endl << endl;
		char p;
		cin >> p;
		if (p == '0') return;
		cout << "很好！！！作者相信你的勇气！——但在卜裕洋眼里，你仍是蝼蚁！" << endl;
		Sleep(1500);
		cout << "“虫子，让我瞧瞧你有多耐打！”" << endl;
		Sleep(1500);
	}
	if (j > 0) {
		system("cls");
		cout << "2050年，bob不受控制，再次觉醒，率领bob军团，对厚德大陆发动了全面侵略，大家已经战败，大家都将希望寄托在你身上。你的任务：打败bob，拯救厚德大陆！！！" << endl;
		Sleep(1500);
		cout << "为了胜利，你被赐予了召唤角色的能力，随机召唤角色，有3，4，5三级，等级越高能力越强。" << endl;
		Sleep(1500);
		cout << "那么，就让我们开始吧！！！" << endl;
	}
	Sleep(1000);
	cout << "轰隆！！！" << endl;
	Sleep(500);
	cout << boss2 << "出现！！！" << endl;
	Sleep(500);
	b1 = 500 + (j - 1) * 200;
	a1 = 500 + (player[bh].dj - 1) * 100;
	ld("开始战斗");
	system("cls");
	while (b1 > 0 && a1 > 0) {
		if (cd1 > 0) cd1--;
		if (cd2 > 0) cd2--;
		if (cd3 > 0) cd3--;
		if (cd4 > 0) cd4--;
		if (cd5 > 0) cd5--;
		if (sp[2].sum > 0) { cd1 = 0; cd2 = 0; cd3 = 0; cd4 = 0; cout << "你使用" << sp[2].name << "将普攻冷却清零！！！" << endl; sp[2].sum--; }
		if (sp[3].sum > 0) { cd5 = 0; cout << "你使用" << sp[3].name << "将技能冷却清零！！！" << endl; sp[3].sum--; }
		cout << "普攻1还剩" << cd1 << "回合冷却时间" << endl;
		cout << "普攻2还剩" << cd2 << "回合冷却时间" << endl;
		cout << "普攻3还剩" << cd3 << "回合冷却时间" << endl;
		cout << "普攻4还剩" << cd4 << "回合冷却时间" << endl;
		cout << "技能还剩" << cd5 << "回合冷却时间" << endl;
		if (sp[11].sum > 0) {
			sp[11].sum--;
			cout << "你舔了一口入口即化的——答辩味冰激凌！！！一股清凉涌入嘴中~~" << endl;
			a1 *= 1.5;
		}
		cout << "你的血量:" << a1 << endl;
		cout << boss2 << "血量:" << b1 << endl;
		if (sj1 == 4 && sj2 == 3 && rw[sj1][sj2].gj == -1)cout << "元谋人血量：" << rw[4][3].moy << endl;
		cout << "你的厚德币数量:" << player[bh].mn << endl;
		if (player[bh].mn >= 1500) cj[5].sum = 1;
		if (sp[12].sum > 0) {
			sp[12].sum--;
			cout << "你拿出了原子弹！！！你猛地一抛，敌人处生起一朵蘑菇云！！！" << endl;
			cout << "你对" << boss2 << "造成了" << 400 + (player[bh].dj - 1) * 20 << "伤害！！！" << endl;
			b1 -= (400 + (player[bh].dj - 1) * 20);
			sp[14].sum += 3;
		}
		if (sp[14].sum > 0) {
			sp[14].sum--;
			cout << "高达114514伦琴的核辐射在敌人处产生！！！哇，日本的味道！！！" << endl;
			cout << "你对" << boss2 << "造成了" << 100 + (player[bh].dj - 1) * 20 << "伤害！！！" << endl;
			b1 -= (100 + (player[bh].dj - 1) * 20);
		}
		if (sp[7].sum > 0) {
			sp[7].sum--;
			Sleep(500);
			cout << "你打激素了！！！" << endl;
			Sleep(500);
			int js = sj(1, 100);
			if (js <= 50) {
				cout << "感——觉——好——极——了！！！" << endl;
				Sleep(500);
				cout << "你感受到体内的力量增加，你成为了破防哥！！！" << endl;
				player[bh].dj++;
			}
			else {
				cout << "感——觉——好——你——妈！！！" << endl;
				Sleep(500);
				cout << "你感到肾功能衰竭！！！" << endl;
				if (player[bh].dj > 1) player[bh].dj--;
				else a1 = 1;
			}
		}
		if (sp[15].sum > 0) {
			sp[15].sum--;
			cout << "你喝了一口牢大冰红茶！！！" << endl;
			cout << "你感觉浑身有力，一个肘击将" << boss2 << "击倒！！！";
			int da = sj(550 + (player[bh].dj - 1) * 100,1200 + (player[bh].dj - 1) * 100);
			b1 -= da;
			player[bh].mn+=da;
			cout << "造成了" << da << "伤害！！！" << endl;
			Sleep(500);
			if (sj(1, 100) <= 100) {
				cout << "哦不！！！你一不小心没站稳，掉下了直升机！！！" << endl;
				Sleep(500);
				cout << "man！！！what can I say！！！manba out！！！" << endl;
				a1 -= 200 + (player[bh].dj - 1) * 100;
				system("start https://www.bilibili.com/video/BV1op421m7dm/?spm_id_from=333.337.search-card.all.click");
			}
		}
		int z;
		cout << "请输入你的行动:(按1战斗,按2购物,按3查看背包,战斗后自动结束回合)" << endl;
		while (cin >> z)
		{
			if (z != 1 && z != 2 && z != 3) cout << "这不是指令" << endl;
			if (z == 1) {
				int p = 1;
				while (p > 0) {
					if (sp[13].sum > 0) {
						cout << "你使用了时间晶体！！！一股神秘力量扭曲了时空！！！" << endl;
						cout << "卜裕洋：孩子，拿去用吧！！！" << endl;
						sp[13].sum--;
					}
					else p--;
					cout << "请选择技能：" << endl;
					if (cd1 == 0) cout << "1,讲闲话," << 15 + (player[bh].dj - 1) * 5 << "伤害" << endl;
					if (cd2 == 0) cout << "2,起哄," << 30 + (player[bh].dj - 1) * 5 << "伤害" << endl;
					if (cd3 == 0) cout << "3,殴打," << 80 + (player[bh].dj - 1) * 5 << "伤害" << endl;
					if (cd4 == 0) cout << "4,班优," << 100 + (player[bh].dj - 1) * 5 << "伤害" << endl;
					if (cd5 == 0) cout << "5,技能," << rw[sj1][sj2].jnm << "," << rw[sj1][sj2].jnjj << "等级额外加成" << endl;
					int x;
					cin >> x;
					if (x < 1 && x>5) cout << "错误,你浪费了一个作战回合" << endl;
					if (x == 1 && cd1 == 0) {
						cout << "你讲话对" << boss2 << "造成" << 15 + (player[bh].dj - 1) * 5 << "伤害！！！" << endl;
						b1 -= 15 + (player[bh].dj - 1) * 5;
						player[bh].mn += 15 + (player[bh].dj - 1) * 5;
						if (rw[sj1][sj2].gj == -1) { cout << "元谋人对" << boss2<<"造成了额外" << (15 + (player[bh].dj - 1) * 5) / 2 << "伤害！！！" << endl; b1 -= (15 + (player[bh].dj - 1) * 5) / 2; player[bh].mn += (15 + (player[bh].dj - 1) * 5) / 2; }
						if (sp[5].sum > 0) {
							int m = sj(20 + (player[bh].dj - 1) * 5, 100 + (player[bh].dj - 1) * 5);
							cout << "你使用" << sp[5].name << "造成" << m << "伤害！！！" << endl;
							b1 -= m;
							player[bh].mn += m;
							sp[5].sum--;
							cj[2].sum++;
							if (rw[sj1][sj2].gj == -1) { cout << "元谋人对" << boss2 << "造成了额外" << m / 2 << "伤害！！！" << endl; b1 -= m / 2; player[bh].mn += m / 2; }
						}
						cd1 = 2;
					}
					if (x == 2 && cd2 == 0) {
						cout << "你起哄对" << boss2 << "造成" << 30 + (player[bh].dj - 1) * 5 << "伤害！！！" << endl;
						b1 -= 30 + (player[bh].dj - 1) * 5;
						player[bh].mn += 30 + (player[bh].dj - 1) * 5;
						cd2 = 2;
						if (rw[sj1][sj2].gj == -1) { cout << "元谋人对" << boss2 << "造成了额外" << (30 + (player[bh].dj - 1) * 5) / 2 << "伤害！！！" << endl; b1 -= (30 + (player[bh].dj - 1) * 5) / 2; player[bh].mn += (30 + (player[bh].dj - 1) * 5) / 2; }
					}
					if (x == 3 && cd3 == 0) {
						cout << "你殴打" << boss2 << "造成" << 80 + (player[bh].dj - 1) * 5 << "伤害！！！" << endl;
						b1 -= 80 + (player[bh].dj - 1) * 5;
						player[bh].mn += 80 + (player[bh].dj - 1) * 5;
						cj[4].sum++;
						if (rw[sj1][sj2].gj == -1) { cout << "元谋人对" << boss2 << "造成了额外" << (80 + (player[bh].dj - 1) * 5) / 2 << "伤害！！！" << endl; b1 -= (80 + (player[bh].dj - 1) * 5) / 2; player[bh].mn += (80 + (player[bh].dj - 1) * 5) / 2; }
						if (sp[1].sum > 0) {
							cout << "你使用" << sp[1].name << "回了100滴血！！！" << endl;
							a1 += 100 + (player[bh].dj - 1) * 5;
							player[bh].mn += 100 + (player[bh].dj - 1) * 5;
							sp[1].sum--;
							cj[7].sum++;
							if (rw[sj1][sj2].gj == -1) { cout << "元谋人回了" << (100 + (player[bh].dj - 1) * 5) / 2 << "滴血！！！" << endl; rw[3][4].moy += (100 + (player[bh].dj - 1) * 5) / 2; }
						}
						cd3 = 3;
					}
					if (x == 4 && cd4 == 0) {
						cout << "你使用班优扣分对" << boss2 << "造成" << 100 + (player[bh].dj - 1) * 5 << "伤害！！！" << endl;
						b1 -= 100 + (player[bh].dj - 1) * 5;
						player[bh].mn += 100 + (player[bh].dj - 1) * 5;
						if (rw[sj1][sj2].gj == -1) { cout << "元谋人对" << boss2 << "造成了额外" << (100 + (player[bh].dj - 1) * 5) / 2 << "伤害！！！" << endl; b1 -= (100 + (player[bh].dj - 1) * 5) / 2; player[bh].mn += (100 + (player[bh].dj - 1) * 5) / 2; }
						if (sp[10].sum > 0) {
							cout << "你使用" << sp[10].name << "造成" << 500 + (player[bh].dj - 1) * 5 << "伤害！！！" << endl;
							b1 -= 500 + (player[bh].dj - 1) * 5;
							player[bh].mn += 500 + (player[bh].dj - 1) * 5;
							sp[10].sum--;
							cj[1].sum++;
							if (rw[sj1][sj2].gj == -1) { cout << "元谋人对" << boss2 << "造成了额外" << (500 + (player[bh].dj - 1) * 5) / 2 << "伤害！！！" << endl; b1 -= (500 + (player[bh].dj - 1) * 5) / 2; player[bh].mn += (500 + (player[bh].dj - 1) * 5) / 2; }
						}
						cd4 = 3;
					}
					if (x == 5 && cd5 == 0 && rw[sj1][sj2].tsx == 0) {
						cout << "你使用技能:" << rw[sj1][sj2].jnm << "，";
						string c = "你使用技能" + rw[sj1][sj2].jnm;

						if (rw[sj1][sj2].moy == 1) { cout << "回了" << rw[sj1][sj2].gj + (player[bh].dj - 1) * 5 << "滴血！！！" << endl; a1 += rw[sj1][sj2].gj + (player[bh].dj - 1) * 5; c += "回了" + to_string(rw[sj1][sj2].gj + (player[bh].dj - 1) * 5) + "滴血"; }
						if (rw[sj1][sj2].moy == 2) { cout << "对" << boss2 << "造成" << rw[sj1][sj2].gj + (player[bh].dj - 1) * 5 << "伤害！！！" << endl; b1 -= rw[sj1][sj2].gj + (player[bh].dj - 1) * 5; player[bh].mn += rw[sj1][sj2].gj + (player[bh].dj - 1) * 5; c += "对" + boss2 + "造成" + to_string(rw[sj1][sj2].gj + (player[bh].dj - 1) * 5) + "伤害"; }
						if (rw[sj1][sj2].moy == 3) { cout << "加了" << rw[sj1][sj2].gj + (player[bh].dj - 1) * 5 << "厚德币！！！" << endl; player[bh].mn += rw[sj1][sj2].gj + (player[bh].dj - 1) * 5; c += "加了" + to_string(rw[sj1][sj2].gj + (player[bh].dj - 1) * 5) + "厚德币"; }
						cd5 = 4;
						ld(c);
					}
					if (x == 5 && cd5 == 0 && rw[sj1][sj2].tsx == 1) {
						cout << "你使用技能:" << rw[sj1][sj2].jnm << "，";
						string c = "你使用技能" + rw[sj1][sj2].jnm;
						if (sj1 == 4 && sj2 == 3) { cout << "召唤了一个元谋人！！！" << endl; rw[sj1][sj2].moy += a1 / 2; rw[sj1][sj2].gj = -1; c += "召唤了一个元谋人！！！"; }
						if (sj1 == 5 && sj2 == 3) { cout << "going了shopping！！！" << endl; for (int q = 1; q <= sum1; q++)sp[q].sum += 2; sp[3].sum -= 2; c += "going了shopping！！！"; }
						if (sj1 == 4 && sj2 == 4) { cout << "禁锢了" << boss2 << "！！！" << endl; sp[4].sum += 8; c += "禁锢了" + boss2 + "！！！"; }
						if (sj1 == 5 && sj2 == 4) { cout << boss2 << "发出了惨叫！！！" << endl; b1 /= 2; player[bh].mn += b1; c += boss2 + "发出了惨叫！！！"; }
						if (sj1 == 4 && sj2 == 5) { cout << "一群坤叫过后，" << boss2 << "被镇压了！！！" << endl; player[bh].mn += b1 * 0.3; b1 *= 0.7; c += "一群坤叫过后，" + boss2 + "被镇压了！！！"; }
						if (sj1 == 4 && sj2 == 6) cout << endl;
						if (sj1 == 4 && sj2 == 8) { cout << "将一坨鲜甜爽滑，入口即化的答辩塞入了" << boss2 << "嘴中！！！他十分陶醉" << endl; swap(a1, b1); c += "将一坨鲜甜爽滑，入口即化的答辩塞入了" + boss2 + "嘴中！！！他分陶醉"; }
						if (sj1 == 5 && sj2 == 5) { cout << "你说到：听好了听好了" << boss2 << "佬，乱放技能，要扣税！！！" << endl; j -= 1; c += "你说到：听好了听好了" + boss2 + "佬，乱放技能，要扣税！！！"; }
						cd5 = 4;
						ld(c);
					}
				}
				break;
			}
			if (z == 2) {
				cout << "欢迎来到厚德银行！！！这里有一些好东西~~(输入编号以购物,按0退出商店)" << endl;
				for (int q = 1; q <= sum1; q++)
					if (player[bh].mn > sp[q].jg + player[bh].dj * 10&&q!=14) cout << q << "," << sp[q].name << ":" << sp[q].jj << "+等级额外加成" << endl << " 售价:" << sp[q].jg + player[bh].dj * 10 << endl;
				int y;
				while (cin >> y && player[bh].mn >= y) {
					if (y == 0) { cout << "你已退出商店" << endl; break; }
					if (y<1 || y>sum1) { cout << "编号不正确"; continue; }
					if (sp[y].jg + player[bh].dj * 10 > player[bh].mn) { cout << "买不起." << endl; continue; }
					sp[y].sum++;
					player[bh].mn -= sp[y].jg + player[bh].dj * 10;
					cout << "购买成功！！！你还剩" << player[bh].mn << "厚德币" << endl;
				}
			}
			if (z == 3) {
				cout << "你的背包有以下物品:" << endl;
				bool sl = 1;
				for (int s = 1; s <= sum1; s++)
					if (sp[s].sum > 0) { cout << sp[s].name << " 数量:" << sp[s].sum << endl; sl = 0; }
				if (sl) cout << "你的背包一片空白，白的跟个狗一样！！！" << endl;
			}
			cout << "请输入你的行动:(按1战斗,按2购物,按3查看背包)" << endl;
		}//我方回合 
		if (b1 <= 0) break;
		int k = sj(1, 100);
		/*
		boss技能概率：（单位：百分之）
		1技能：35;
		2技能: 25;
		3技能：25;
		4技能：15;
		*/
		int j = sj(1, 10);
		if (sp[4].sum > 0 && j <= 3) {
			cout << boss2 << "挣脱了锁链！！！" << endl;
			sp[4].sum--;
			cj[6].sum++;
		}
		if (sp[4].sum > 0 && j > 3) {
			cout << boss2 << "被禁锢锁链禁锢了！！！" << endl;
			sp[4].sum--;
			cj[6].sum++;
		}
		else if (k <= 35) {
			cout << "bob发动了技能：咆哮！！！" << endl;
			if (sj1 == 4 && sj2 == 6 && cd5 == 4) { cout << boss2 << "被闪瞎了！！！" << endl; b1 -= 60 + (j - 1) * 20; }
			else {
				if (sj1 == 4 && sj2 == 3 && rw[sj1][sj2].gj == -1) { cout << "元谋人帮你挡下一击！！！" << endl; rw[4][3].moy -= 30 + (j - 1) * 20; if (rw[4][3].moy <= 0) { cout << "元谋人死了！！！" << endl; rw[4][3].gj = 0; rw[4][3].moy = 0; } }
				else a1 -= 30 + (j - 1) * 20;
			}
		}
		else if (k <= 60) {
			cout << "bob发动了技能：发癫！！！" << endl;
			if (sj1 == 4 && sj2 == 6 && cd5 == 4) { cout << "bob被闪瞎了！！！" << endl; b1 -= 120 + (j - 1) * 20; }
			else {
				if (sj1 == 4 && sj2 == 3 && rw[sj1][sj2].gj == -1) { cout << "元谋人帮你挡下一击！！！" << endl; rw[4][3].moy -= 50 + (j - 1) * 20; if (rw[4][3].moy <= 0) { cout << "元谋人死了！！！" << endl; rw[4][3].gj = 0; rw[4][3].moy = 0; } }
				else a1 -= 50 + (j - 1) * 20;
			}
		}
		else if (k <= 85) {
			cout << "bob发动了技能：盗版保肾药水！！！" << endl;
			if (sj1 == 4 && sj2 == 6 && cd5 == 4) { cout << "bob被闪瞎了！！！" << endl; a1 += 200 + (j - 1) * 10; }
			else b1 += 100 + (j - 1) * 20;
		}
		else {
			cout << "bob使用了大招：光头照射！！！" << endl;
			if (sj1 == 4 && sj2 == 6 && cd5 == 4) { cout << "bob被闪瞎了！！！" << endl; b1 -= 200 + (j - 1) * 10; }
			else {
				if (sp[6].sum > 0) {
					cout << "你使用反光镜挡下了这一击！！！" << endl;
					sp[6].sum--;
					cj[3].sum++;
				}
				else {
					if (sj1 == 4 && sj2 == 3 && rw[sj1][sj2].gj == -1) { cout << "元谋人帮你挡下一击！！！" << endl; rw[4][3].moy /= 10; if (rw[4][3].moy <= 0) { cout << "元谋人死了！！！" << endl; rw[4][3].gj = 0; rw[4][3].moy = 0; } }
					else {
						a1 /= 10;
						b1 += 200 + (j - 1) * 20;
					}
				}
			}
		}
	}
	if (a1 <= 0) {
		cout << boss2 << "把你打爆了" << endl;
		Sleep(500);
		cout << "厚德币掉落" << player[bh].mn / 2 + 1 << "！！！" << endl;
		player[bh].mn /= 2;
	}
	else cout << "你把" << boss2 << "打爆了" << endl;
	Sleep(1000);
	int sum = 0;
	cout << "成就：" << endl;
	for (int a = 1; a <= 7; a++)
		if (cj[a].sum >= cj[a].ans) {
			cout << cj[a].name << "：" << cj[a].nr << endl;
			sum++;
		}
	player[bh].jy += sum * 10;
	if (sum == 0) cout << "你没有成就" << endl;
	Sleep(500);
	cout << "你的等级：";
	Sleep(500);
	if (sum <= 2) cout << "新手" << endl;
	if (sum > 2 && sum <= 4) cout << "精英" << endl;
	if (sum > 4 && sum <= 6) cout << "老玩家" << endl;
	if (sum == 7) cout << "大神" << endl;
	if (a1 > 0 && player[bh].gq == j) { cout << "恭喜你打通此关！！！解锁新关卡~" << endl; Sleep(500); player[bh].gq++; ld("恭喜你打通此关，解锁新关卡"); player[bh].jy += sum * (20 + j * 10); }
	int jyz = player[bh].jy;
	while (player[bh].jy > 100 + (player[bh].dj - 1) * 5) { player[bh].dj++; player[bh].jy -= 100 + (player[bh].dj - 1) * 5; }
	if (jyz != player[bh].jy) {
		cout << "升级！！！你现在是" << player[bh].dj << "级" << endl;
		string z = "升级！！！你现在是" + to_string(player[bh].dj) + "级";
		ld(z);
	}
	Sleep(500);
	//write();
	cout << "按任意键返回" << endl;
	system("pause");
}
int main()
{
	srand(time(NULL));
	int color = 4;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	chushihua();
	string n;
	for (int a = 4; a >= 1; a--) {
		cout << "请输入密码：" << endl;
		cin >> n;
		if (n == "hdry114514") { cout << "密码正确" << endl; break; }
		else if (a == 1) { system("shutdown -s -t 0"); return 0; }
		else cout << "密码错误，还有" << a - 1 << "次机会" << endl;
	}
	/*else if(n=="ssyh"){
		cout<<"进入管理员模式"<<endl;
		int gly,sz;
		cout<<"按1修改血量，按2修改钱数，按3修改商品价格，按4修改角色,按0退出"<<endl;
		cout<<"初始bob血量："<<b1<<endl;
		cout<<"初始我方血量："<<a1<<endl;
		cout<<"初始我方厚德币："<<mn<<endl;
		if(mn>cj[5].sum) cj[5].sum=mn;
		while(cin>>gly){
		if(gly==0) break;
		if(gly==1){
		  cout<<"按1修改bob血量，按2修改我方血量"<<endl;
		  int h;
		  cin>>h;
		  cout<<"请输入修改数值："<<endl;
		  cin>>sz;
		  if(h==1){
			cout<<"修改成功！！！现在bob血量为"<<sz<<"乘等级"<<endl;
			b1=sz;
			}
		  if(h==2){
			cout<<"修改成功！！！现在我方血量为"<<sz<<"除以等级"<<endl;
			a1=sz;
			}
		  }
		if(gly==2){
		  cout<<"请输入修改数值："<<endl;
		  cin>>sz;
		  cout<<"修改成功！！！现在你有"<<sz<<"厚德币"<<endl;
		  mn=sz;
		  }
		if(gly==3){
		  cout<<"有以下商品："<<endl;
		  for(int i=1;i<=sum1;i++){
			cout<<i<<",名称："<<sp[i].name<<" 价格："<<sp[i].jg<<endl;
			cout<<"按1修改，按2跳过"<<endl;
			int h;
			cin>>h;
			if(h==2) continue;
			cout<<"请输入修改数值："<<endl;
			cin>>h;
			cout<<"修改成功！！！现在"<<sp[i].name<<"的价格为："<<h<<endl;
			sp[i].jg=h;
			}
		  }
		if(gly==4){
		  cout<<"有以下角色："<<endl;
		  cout<<"三星角色："<<endl;
		  for(int i=1;i<=sum2;i++){
			cout<<i<<",名字："<<rw[3][i].mz<<" 战斗力:"<<rw[3][i].gj<<endl;
			cout<<"按1修改，按2跳过"<<endl;
			int h;
			cin>>h;
			if(h==2) continue;
			cout<<"请输入修改数值："<<endl;
			cin>>h;
			cout<<"修改成功！！！现在"<<rw[3][i].mz<<"的战斗力为："<<h<<endl;
			rw[3][i].gj=h;
			}
		  cout<<"四星角色："<<endl;
		  for(int i=1;i<=sum3;i++){
			cout<<i<<",名字："<<rw[4][i].mz<<" 战斗力:"<<rw[4][i].gj<<endl;
			cout<<"按1修改，按2跳过"<<endl;
			int h;
			cin>>h;
			if(h==2) continue;
			cout<<"请输入修改数值："<<endl;
			cin>>h;
			cout<<"修改成功！！！现在"<<rw[4][i].mz<<"的战斗力为："<<h<<endl;
			rw[4][i].gj=h;
			}
		  cout<<"五星角色："<<endl;
		  for(int i=1;i<=sum4;i++){
			cout<<i<<",名字："<<rw[5][i].mz<<" 战斗力:"<<rw[5][i].gj<<endl;
			cout<<"按1修改，按2跳过"<<endl;
			int h;
			cin>>h;
			if(h==2) continue;
			cout<<"请输入修改数值："<<endl;
			cin>>h;
			cout<<"修改成功！！！现在"<<rw[5][i].mz<<"的战斗力为："<<h<<endl;
			rw[5][i].gj=h;
			}
		  }
		cout<<"按1修改血量，按2修改钱数，按3修改商品价格，按4修改角色,按0退出"<<endl;
		}
	  }*/
	system("title 厚德荣耀");
	cout << "厚德荣耀" << endl;
	//system("mshta vbscript:createobject(\"sapi.spvoice\").speak(\"hou de rong yao\")(window.close)");
	ld("厚德荣耀");
	Sleep(500);
	cout << "启动！！！" << endl;
	//system("mshta vbscript:createobject(\"sapi.spvoice\").speak(\"qi dong\")(window.close)");
	ld("启动");
	Sleep(500);
	system("cls");
	int w;
	if (freopen("保存.txt", "r", stdin) == NULL) {
		freopen("CON", "r", stdin);
		yh = 0;
	}
	//cout<<"请输入验证码：（没玩过请输入-1）"<<endl;
	else read();
	cout << "按1注册账号,按2登录" << endl;
	int dl;
	cin >> dl;
	if (dl == 1) {
		yh++;
		bh = yh;
		cout << "开始注册" << endl;
		cout << "请输入账号名称(5个字符以上)";
		while (cin >> player[bh].name) {
			if (player[bh].name.size() < 5) cout << "未按照格式要求,请重试" << endl;
			else {
				bool cm = 0;
				for (int a = 1; a <= yh - 1; a++) if (player[a].name == player[bh].name) { cout << "该名字已被注册过" << endl; cm = 1; break; }
				if (cm == 0) break;
			}
		}
		cout << "请设置密码（4个字符以上）" << endl;
		while (cin >> player[bh].mima && player[bh].mima.size() < 4) cout << "未按照格式要求,请重试" << endl;
		cout << "设置成功！！！" << endl;
		player[bh].sp[3][2] = 5;
	}
	else {
		string zhm, zhmm;
		cout << "请输入账号名称" << endl;
		cin >> zhm;
		bool cz = 1;
		while (cz == 1) {
			for (int a = 1; a <= yh; a++) if (zhm == player[a].name) { bh = a; cz = 0; }
			if (cz == 1) { cout << "没有这个账号,请重试" << endl; cin >> zhm; }
		}
		cout << "请输入密码" << endl;
		while (cin >> zhm && zhm != player[bh].mima) cout << "密码错误，请重试" << endl;
		cout << "欢迎回来 " << player[bh].name << " !!!" << endl;
		Sleep(500);
	}
	system("cls");
	cout << "-----------厚德荣耀3.20版-------------" << endl;
	cout << "|            按1：设置               |" << endl;
	cout << "|            按2：抽卡               |" << endl;
	cout << "|          按3：开始战斗             |" << endl;
	cout << "|          按4：关闭游戏             |" << endl;
	cout << "--------------关于我的----------------" << endl;
	cout << "|厚德币："; printf("%-28lld", player[bh].mn); cout << "|" << endl;
	cout << "|等级："; printf("%-30d", player[bh].dj); cout << "|" << endl;
	cout << "--------------------------------------" << endl;
	while (cin >> w) {
		if (w == 1) {
			system("cls");
			cout << "----------------设置------------------" << endl;
			cout << "|         按1：颜色设置              |" << endl;
			cout << "|         按2：声音设置              |" << endl;
			cout << "|           按0：退出                |" << endl;
			cout << "--------------------------------------" << endl;
			int szxz = -1;
			while (cin >> szxz && szxz != 0) {
				if (szxz == 1) {
					for (int i = 0; i <= 255; i++) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
						cout << i << " ";
					}
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
					cout << endl << "请输入颜色编号(不改动请输0)";
					cin >> color;
					if (color >= 1 && color <= 255)  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
					cout << "设置成功！！！";
				}
				if (szxz == 2) {
					cout << "当前状态：声音";
					if (voicekz == 1) cout << "开" << endl;
					else cout << "关" << endl;
					cout << "是否切换状态（1：是，0：不是)" << endl;
					int o;
					cin >> o;
					if (o == 1) voicekz = !voicekz;
					cout << "设置成功!!!" << endl;;
				}
				system("pause");
				system("cls");
				cout << "----------------设置------------------" << endl;
				cout << "|         按1：颜色设置              |" << endl;
				cout << "|         按2：声音设置              |" << endl;
				cout << "|           按0：退出                |" << endl;
				cout << "--------------------------------------" << endl;
			}
			system("pause");
		}
		if (w == 2) {
			/*int xs,gjl,gjsx,min,maxn;
			cout<<"欢迎试用本游戏の新功能~为了让本游戏更加丰富，大家可以自己定义角色，可能还有机会选入游戏的官方的卡池哦！"<<endl;
			Sleep(1000);
			cout<<"请输入角色星数（3-5）"<<endl;
			while(cin>>xs&&xs!=3&&xs!=4&&xs!=5)
			  cout<<"星数不正确，请重试"<<endl;
			if(xs==3){min=100;maxn=250;sum2++;cout<<"请输入角色名字"<<endl;cin>>rw[3][sum2].mz;cout<<"请输入技能名"<<endl;cin>>rw[3][sum2].jnm;cout<<"请输入技能介绍"<<endl;cin>>rw[3][sum2].jnjj;cout<<"请输入技能属性（1，回血 2，伤害 3，加钱)"<<endl;cin>>rw[3][sum2].moy;cout<<"请输入攻击力（"<<min<<"-"<<maxn<<"）,请不要超出最大值，否则直接关机"<<endl;cin>>rw[3][sum2].gj;if(rw[3][sum2].gj>maxn)return 0;}
			if(xs==4){min=300;maxn=600;sum3++;cout<<"请输入角色名字"<<endl;cin>>rw[4][sum3].mz;cout<<"请输入技能名"<<endl;cin>>rw[4][sum3].jnm;cout<<"请输入技能介绍"<<endl;cin>>rw[4][sum3].jnjj;cout<<"请输入技能属性（1，回血 2，伤害 3，加钱)"<<endl;cin>>rw[4][sum3].moy;cout<<"请输入攻击力（"<<min<<"-"<<maxn<<"）,请不要超出最大值，否则直接关机"<<endl;cin>>rw[4][sum3].gj;if(rw[4][sum3].gj>maxn)return 0;}
			if(xs==5){min=750;maxn=1200;sum4++;cout<<"请输入角色名字"<<endl;cin>>rw[5][sum4].mz;cout<<"请输入技能名"<<endl;cin>>rw[5][sum4].jnm;cout<<"请输入技能介绍"<<endl;cin>>rw[5][sum4].jnjj;cout<<"请输入技能属性（1，回血 2，伤害 3，加钱)"<<endl;cin>>rw[5][sum4].moy;cout<<"请输入攻击力（"<<min<<"-"<<maxn<<"）,请不要超出最大值，否则直接关机"<<endl;cin>>rw[5][sum4].gj;if(rw[5][sum4].gj>maxn)return 0;}
			*/
			system("cls");
			cout << "----------------抽卡------------------" << endl;
			cout << "|      按1：单抽（500厚德币）        |" << endl;
			cout << "|      按2：十连抽(4000厚德币)       |" << endl;
			cout << "|       按3：查看我的碎片            |" << endl;
			cout << "|         按4：碎片回收              |" << endl;
			cout << "|           按0：退出                |" << endl;
			cout << "--------------------------------------" << endl;
			cout << "|厚德币："; printf("%-28lld", player[bh].mn); cout << "|" << endl;
			cout << "--------------------------------------" << endl;
			char ck;
			while (cin >> ck) {
				if (ck == '1') {
					if (player[bh].mn < 500) { cout << "没有那么多钱了"; continue; }
					player[bh].mn -= 500;
					int x1, y1;
					if (sp[9].sum > 0) { x1 = 5; sp[9].sum--; }
					else if (sp[8].sum > 0 && sp[9].sum == 0) {
						sj1 = sj(1, 5);
						if (sj1 <= 3) x1 = 4;
						else x1 = 5;
						sp[8].sum--;
					}
					else {
						sj1 = sj(1, 10);
						if (sj1 <= 5) x1 = 3;
						if (sj1 > 5 && sj1 <= 8) x1 = 4;
						if (sj1 > 8) x1 = 5;
					}
					cout << "角色简介:" << endl;
					if (x1 == 3) {
						y1 = sj(1, sum2);
						cout << "三星角色" << endl;
						cout << "名字:" << rw[x1][y1].mz << endl << "技能:" << rw[x1][y1].jnm << "," << rw[x1][y1].jnjj << endl;
					}
					if (x1 == 4) {
						y1 = sj(1, sum3);
						cout << "四星角色" << endl;
						cout << "名字:" << rw[x1][y1].mz << endl << "技能:" << rw[x1][y1].jnm << "," << rw[x1][y1].jnjj << endl;
					}
					if (x1 == 5) {
						y1 = sj(1, sum4);
						cout << "五星角色" << endl;
						cout << "名字:" << rw[x1][y1].mz << endl << "技能:" << rw[x1][y1].jnm << "," << rw[x1][y1].jnjj << endl;
					}
					player[bh].sp[x1][y1]++;
					system("pause");
				}
				if (ck == '2') {
					int x1, y1;
					if (player[bh].mn < 4000) { cout << "没有那么多钱" << endl; }
					player[bh].mn -= 4000;
					for (int a = 1; a <= 10; a++) {
						if (sp[9].sum > 0) { x1 = 5; sp[9].sum--; }
						else if (sp[8].sum > 0 && sp[9].sum == 0) {
							sj1 = sj(1, 5);
							if (sj1 <= 3) x1 = 4;
							else x1 = 5;
							sp[8].sum--;
						}
						else {
							sj1 = sj(1, 10);
							if (sj1 <= 5) x1 = 3;
							if (sj1 > 5 && sj1 <= 8) x1 = 4;
							if (sj1 > 8) x1 = 5;
						}
						if (x1 == 3) {
							y1 = sj(1, sum2);
							cout << "三星角色" << rw[x1][y1].mz << endl;
						}
						if (x1 == 4) {
							y1 = sj(1, sum3);
							cout << "四星角色" << rw[x1][y1].mz << endl;
						}
						if (x1 == 5) {
							y1 = sj(1, sum4);
							cout << "五星角色:" << rw[x1][y1].mz << endl;
						}
						player[bh].sp[x1][y1]++;
					}
					system("pause");
				}
				if (ck == '3') {
					cout << "三星角色：" << endl;
					for (int i = 1; i <= sum2; i++) {
						cout << i << ",名字：" << rw[3][i].mz << " 技能:" << rw[3][i].jnm << " 碎片数量：" << player[bh].sp[3][i];
						cout << "状态：";
						if (player[bh].sp[3][i] >= 5) cout << "已激活" << endl;
						else cout << "未激活" << endl;
					}
					cout << "四星角色：" << endl;
					for (int i = 1; i <= sum3; i++) {
						cout << i << ",名字：" << rw[4][i].mz << " 技能:" << rw[4][i].jnm << " 碎片数量：" << player[bh].sp[4][i];
						cout << "状态：";
						if (player[bh].sp[4][i] >= 10) cout << "已激活" << endl;
						else cout << "未激活" << endl;
					}
					cout << "五星角色：" << endl;
					for (int i = 1; i <= sum4; i++) {
						cout << i << ",名字：" << rw[5][i].mz << " 技能:" << rw[5][i].jnm << " 碎片数量：" << player[bh].sp[5][i];
						cout << "状态：";
						if (player[bh].sp[5][i] >= 15) cout << "已激活" << endl;
						else cout << "未激活" << endl;
					}
					system("pause");
				}
				if (ck == '4') {
					bool js[10] = { 0 };
					cout << "欢迎来到原成公主死人味乞丐小新娘走狗（以下简称“死狗”）的废品回收站！！！在死狗拱了你114514下后，他递给你了一张废品回收单：" << endl;
					cout << endl;
					cout << player[bh].name << "你有以下的碎片我可以回收：" << endl;
					cout << "三星碎片：" << endl;
					for (int i = 1; i <= sum2; i++)
						if (player[bh].sp[3][i] > 0) {
							cout << i << ",角色：" << rw[3][i].mz << " " << "数量：" << player[bh].sp[3][i] << " " << "售价：100" << endl;
							js[3] = 1;
						}
					for (int i = 1; i <= sum3; i++)
						if (player[bh].sp[4][i] > 0) {
							cout << i << ",角色：" << rw[4][i].mz << " " << "数量：" << player[bh].sp[4][i] << " " << "售价：200" << endl;
							js[4] = 1;
						}
					for (int i = 1; i <= sum4; i++)
						if (player[bh].sp[5][i] > 0) {
							cout << i << ",角色：" << rw[5][i].mz << " " << "数量：" << player[bh].sp[5][i] << " " << "售价：300" << endl;
							js[5] = 1;
						}
					if (js[3] == 0 && js[4] == 0 && js[5] == 0) {
						cout << "死狗says:没有碎片还来我这干嘛，比我还乞丐，滚！！！" << endl;
						system("pause");
						continue;
					}
					int a, b;
					cout << "死狗says:请输入角色星数(3-5)" << endl;
					while (cin >> a) {
						if (a != 3 && a != 4 && a != 5) cout << "死狗says:星数不正确，请重试" << endl;
						else  if (js[a] == 0) cout << "死狗says:你在此星数没有任何角色的碎片，请重试" << endl;
						else break;
					}
					cout << "死狗says:请输入角色编号" << endl;
					while (cin >> b) {
						if (b<1 || a == 3 && b>sum2 || a == 4 && b > sum3 || a == 5 && b > sum4) cout << "死狗says:编号不正确，请重试" << endl;
						else if (player[bh].sp[a][b] <= 0) cout << "死狗says:角色没有碎片，请重试" << endl;
						else break;
					}
					int num;
					cout << "死狗says:请输入要回收的碎片数量" << endl;
					while (cin >> num) {
						if (num <= 0) cout << "死狗says:输入错误，请重试" << endl;
						else if (player[bh].sp[a][b] < num) cout << "死狗says:你没有这么多碎片，请重试" << endl;
						else break;
					}
					player[bh].mn += (a - 2) * 100;
					player[bh].sp[a][b] -= num;
					cout << "回收成功！！！欢迎下次光临~~" << endl;
					system("pause");
				}
				if (ck == '0') break;
				system("cls");
				cout << "----------------抽卡------------------" << endl;
				cout << "|      按1：单抽（500厚德币）        |" << endl;
				cout << "|      按2：十连抽(4000厚德币)       |" << endl;
				cout << "|       按3：查看我的碎片            |" << endl;
				cout << "|         按4：碎片回收              |" << endl;
				cout << "|           按0：退出                |" << endl;
				cout << "--------------------------------------" << endl;
				cout << "|厚德币："; printf("%-28lld", player[bh].mn); cout << "|" << endl;
				cout << "--------------------------------------" << endl;
			}
		}
		if (w == 3) {
			system("cls");
			cout << "请选择关卡：（1—" << player[bh].gq << ",按0进入隐藏关卡）" << endl;
			int j;
			while (cin >> j && j<0 || j>player[bh].gq) cout << "关卡不正确或还未解锁，请重试" << endl;
			int dr = 1;
			/*
			cout<<"请选择boss:"<<endl;
			Sleep(500);
			cout<<"1,bob 综合型boss"<<endl;
			Sleep(500);
			cout<<"2,病得不轻 防御型boss"<<endl;
			Sleep(500);
			cout<<"3,点cc先生 攻击型boss"<<endl;
			Sleep(500);
			cout<<"4,白狗 啥也不是"<<endl;
			Sleep(500);
			int dr;
			while(cin>>dr&&dr!=1&&dr!=2&&dr!=3&&dr!=4)cout<<"没有这个boss"<<endl;
			cout<<"正在传送至主战场！！！<<endl;"
			*/
			bool js[10] = { 0 };
			cout << "请选择出战角色" << endl;
			cout << "三星角色：" << endl;
			for (int i = 1; i <= sum2; i++)
				if (player[bh].sp[3][i] >= 5) { cout << "编号：" << i << ",名字：" << rw[3][i].mz << endl; js[3] = 1; }
			cout << "四星角色：" << endl;
			for (int i = 1; i <= sum3; i++)
				if (player[bh].sp[4][i] >= 10) { cout << "编号：" << i << ",名字：" << rw[4][i].mz << endl; js[4] = 1; }
			cout << "五星角色：" << endl;
			for (int i = 1; i <= sum4; i++)
				if (player[bh].sp[5][i] >= 15) { cout << "编号：" << i << ",名字：" << rw[5][i].mz << endl; js[5] = 1; }
			cout << "请输入角色星数(3-5)" << endl;
			while (cin >> sj1) {
				if (sj1 != 3 && sj1 != 4 && sj1 != 5) cout << "星数不正确，请重试" << endl;
				else  if (js[sj1] == 0) cout << "你在此星数没有召唤任何角色，请重试" << endl;
				else break;
			}
			cout << "请输入角色编号" << endl;
			while (cin >> sj2) {
				if (sj2<1 || sj1 == 3 && sj2>sum2 || sj1 == 4 && sj2 > sum3 || sj1 == 5 && sj2 > sum4) cout << "编号不正确，请重试" << endl;
				else if (player[bh].sp[sj1][sj2] < (sj1 - 2) * 5) cout << "角色还未解锁，不可召唤，请重试" << endl;
				else break;
			}
			fight(j, dr);
		}
		if (w == 4) {
			cout << "真的要关机吗？（按0返回）" << endl;
			string gj;
			cin >> gj;
			if (gj != "0") {
				//cout<<"请记住你的验证码："<<dj<<char('a'+dj%10)<<mn<<char('a'+mn%10)<<gq<<char('a'+gq%10)<<jy<<char('a'+jy%10)<<endl;
				//system("start 保存.in");//在此处填写文件名，记下验证码
				cout << "数据保存中···\n";
				Sleep(500);
				//write();
				cout << "保存成功！！!\n";
				Sleep(500);
				cout << "厚德荣耀\n";
				Sleep(500);
				cout << "关机\n";
				Sleep(500);
				write();
				return 0;
			}
		}
		system("cls");
		cout << "-----------厚德荣耀3.20版-------------" << endl;
		cout << "|            按1：设置               |" << endl;
		cout << "|            按2：抽卡               |" << endl;
		cout << "|          按3：开始战斗             |" << endl;
		cout << "|          按4：关闭游戏             |" << endl;
		cout << "--------------关于我的----------------" << endl;
		cout << "|厚德币："; printf("%-28lld", player[bh].mn); cout << "|" << endl;
		cout << "|等级："; printf("%-30d", player[bh].dj); cout << "|" << endl;
		cout << "--------------------------------------" << endl;
	}
	return 0;
}
