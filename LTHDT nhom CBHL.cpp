#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
class board {
	char cell[9];
public:
	char getcell(int num) {
		return cell[num];
	}
	void display() {
		for (int i = 0; i < 3; i++) {
			cout << cell[i * 3] << " | " << cell[i * 3 + 1] << " | " << cell[i * 3 + 2] << endl;
			if (i < 2) cout << "---------" << endl;
		}
		cout << endl;
	}
	bool checkwin(char symbol) {
		for (int i = 0; i < 3; i++) {
			if (cell[i * 3] == symbol && cell[i * 3 + 1] == symbol && cell[i * 3 + 2] == symbol) return true;
			if (cell[i] == symbol && cell[i + 3] == symbol && cell[i + 6] == symbol) return true;
		}
		if ((cell[0] == symbol && cell[4] == symbol && cell[8] == symbol) || (cell[2] == symbol && cell[4] == symbol && cell[6] == symbol)) return true;
		return false;
	}
	bool full() {
		for (int i = 0; i < 9;i++)
			if (cell[i] == ' ') return false;
		return true;
	}
	void reset() {
		for (int i = 0; i < 9;i++)
			cell[i] = ' ';
	};
	void changecell(int num, char symbol) {
		cell[num] = symbol;
	}
	board() {
		reset();
	}
};


class player {
	char symbol;
public:
	player(char sym) {
		symbol = sym;
	}
	char getsymbol() {
		return symbol;
	}
	virtual int add_move() = 0;
};
class humanplayer : public player {
	board* re;
public:
	humanplayer(char sym, board* board_ref) : player(sym) { re = board_ref; }
	int add_move() {
		while (true) {
			int move;
			cout << "Nguoi choi " << getsymbol() << " hay nhap o muon chon (1-9): ";
			cin >> move;
			cout << endl;
			if (move >= 1 && move <= 9 && re->getcell(move - 1) == ' ') return move - 1;
			else cout << "Khong hop le vui long thu lai." << endl;
		}
	}
};
class computerplayer : public player {
	board* re;
public:
	computerplayer(char sym, board* board_ref) : player(sym) { re = board_ref; }
	int add_move() {
		char msymb = getsymbol();
		while (true) {
			int move = ' ';
			for (int i = 0; i < 3; i++) {
				if (re->getcell(i * 3) == msymb && re->getcell(i * 3 + 1) == msymb && re->getcell(i * 3 + 2) == ' ') move = i * 3 + 2;
				if (re->getcell(i * 3) == msymb && re->getcell(i * 3 + 2) == msymb && re->getcell(i * 3 + 1) == ' ') move = i * 3 + 1;
				if (re->getcell(i * 3 + 2) == msymb && re->getcell(i * 3 + 1) == msymb && re->getcell(i * 3) == ' ') move = i * 3;
			}
			for (int i = 1; i <= 3; i++) {
				if (move != ' ') break;
				if (re->getcell(i) == msymb && re->getcell(i + 3) == msymb && re->getcell(i + 6) == ' ') move = i + 6;
				if (re->getcell(i) == msymb && re->getcell(i + 6) == msymb && re->getcell(i + 3) == ' ') move = i + 3;
				if (re->getcell(i + 3) == msymb && re->getcell(i + 6) == msymb && re->getcell(i) == ' ') move = i;
			}
			if (re->getcell(0) == msymb && re->getcell(4) == msymb && move == ' ' && re->getcell(8) == ' ') move = 8;
			if (re->getcell(0) == msymb && re->getcell(8) == msymb && move == ' ' && re->getcell(4) == ' ') move = 4;
			if (re->getcell(4) == msymb && re->getcell(8) == msymb && move == ' ' && re->getcell(0) == ' ') move = 0;
			if (re->getcell(2) == msymb && re->getcell(4) == msymb && move == ' ' && re->getcell(6) == ' ') move = 6;
			if (re->getcell(2) == msymb && re->getcell(6) == msymb && move == ' ' && re->getcell(4) == ' ') move = 4;
			if (re->getcell(4) == msymb && re->getcell(6) == msymb && move == ' ' && re->getcell(2) == ' ') move = 2;
			if (move == ' ') move = rand() % 9;
			if (move >= 0 && move <= 8 && re->getcell(move) == ' ') return move;
		}
	}
};


class game {
	board* b;
	player* pl1;
	player* pl2;
	player* currentpl;
public:
	game(player* p1, player* p2, board* a) {
		b = a;
		pl1 = p1;
		pl2 = p2;
		currentpl = p1;
	};
	void switchp() {
		if (currentpl == pl1) currentpl = pl2;
		else currentpl = pl1;
	}
	void play() {
		while (true) {
			b->display();
			int move = currentpl->add_move();
			b->changecell(move, currentpl->getsymbol());
			if (b->checkwin(currentpl->getsymbol())) {
				cout << "Player " << currentpl->getsymbol() << " da chien thang!" << endl;
				b->display();
				break;
			}
			else if (b->full()) {
				cout << "Tran dau hoa!" << endl;
				break;
			}
			switchp();
			cout << "Den luot nguoi choi " << currentpl->getsymbol() << endl;
		}
	}
};


int main() {
	srand(time(NULL));
	char n, t, x, o;
	while (true)
	{
		cout << "Nguoi choi 1 la nguoi(N) hay may(M): ";cin >> n;cout << "X hay O: ";cin >> x;cout << endl;
		cout << "Nguoi choi 2 la nguoi(N) hay may(M): ";cin >> t;cout << "X hay O: ";cin >> o;cout << endl;
		if ((n == 'N' || n == 'M') && (t == 'N' || t == 'M') && (x == 'X' || x == 'O') && (o == 'O' || o == 'X') && x != o)
			break;
		else cout << "Cu phap khong hop le vui long nhap lai." << endl << endl;
	}
	if (n == 'N' && t == 'M') {
		board c;
		humanplayer a(x, &c);
		computerplayer b(o, &c);
		game g(&a, &b, &c);
		g.play();
	}
	else if (n == 'M' && t == 'N') {
		board c;
		humanplayer b(o, &c);
		computerplayer a(x, &c);
		game g(&a, &b, &c);
		g.play();
	}
	else if (n == 'M' && t == 'M') {
		board c;
		computerplayer a(x, &c);
		computerplayer b(o, &c);
		game g(&a, &b, &c);
		g.play();
	}
	else if (n == 'N' && t == 'N') {
		board c;
		humanplayer a(x, &c);
		humanplayer b(o, &c);
		game g(&a, &b, &c);
		g.play();
	}

	return 0;
}
