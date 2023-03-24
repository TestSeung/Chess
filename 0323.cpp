#include<iostream>
#include<ctime>
#include<ostream>
namespace Color {
	enum Code {
		FG_RED = 31,
		FG_GREEN = 32,
		FG_BLUE = 34,
		FG_DEFAULT = 39,
		BG_RED = 41,
		BG_GREEN = 42,
		BG_BLUE = 44,
		BG_DEFAULT = 49
	};
	class Modifier {
		Code code;
	public:
		Modifier(Code pCode) : code(pCode) {}
		friend std::ostream&
			operator<<(std::ostream& os, const Modifier& mod) {
			return os << "\033[" << mod.code << "m";
		}
	};
}
using namespace std;

Color::Modifier Default(Color::FG_DEFAULT);
Color::Modifier Blue(Color::FG_BLUE);
Color::Modifier Green(Color::FG_GREEN);
Color::Modifier Red(Color::FG_RED);

enum class ETeam
{
	None,
	Green,
	Red,
};

class Board; // ���尡 ������ ��������. ���������ϴ°��

class Piece
{
public:
	char Id;
	Board* ChessBoard;
	int X; int Y;
	ETeam Team;
	int NextX;
	int NextY;

	Piece();
	Piece(char id);
	Piece(char id, ETeam Team, int X, int Y);
	virtual void setboard(Board*Board);
	//void Move(int x, int y, Piece* Grid[8][8]);
	virtual void Move(int NextX, int NextY); //������ //=0; �߻�Ŭ����
	void ChangePosition(int posX, int posY);
	void Display();
private:

};
class Rook : public Piece	 //���
{
public:
	Rook();
	Rook(char Id, ETeam Team, int X, int Y);
	virtual void setboard(Board* Board)override;
	virtual void Move(int NextX, int NextY)override; //������ �ϰڴ�.
	void RookMovePattern(int NextX, int NextY,int X,int Y);

private:

};



class Board
{
public:
	static const int SizeX = 8;
	static const int SizeY = 8;


	Piece* Grid[SizeX][SizeY];

	

	~Board();
	void Initialize();
	bool ISInsideBound(int X, int Y);
	void Display();
	void AddPiece(Piece* Piece);
	void DeletePiece (int x, int y);
	bool HasPiece(int NewX, int NewY);

	
private:
	
};
class Player
{
public:
	Player()
	{
	}
};

class Chess
{
public:
	Board* ptrBoard;
	Player* ptrPlayerA;
	Player* ptrPlayerB;

	Chess();
	void Run();
	void HandleInput();
	void Display();
private:

};


Piece::Piece() { //Ŭ�������� �Լ������� ȣ�Ⱑ��

};
Piece::Piece(char id)
{
	this->Id = id;
};
Piece::Piece(char id, ETeam Team, int X, int Y)
{
	this->Id = id;
	this->Team = Team;
	this->X = X;
	this->Y = Y;
};
void Piece::setboard(Board* Board) //����� ������ִ��� üũ �׷��� ���������� �ǽð����� ��ߵ�.
{
	ChessBoard = Board;
};
void Piece::Move(int NextX, int NextY)
{

	int MoveY = Team == ETeam::Green ? 1 : -1;
		if (Y + MoveY == NextY)
		{
			if (X == NextX)
			{
				if (ChessBoard->Grid[NextX][NextY] == nullptr)
				{
					ChangePosition(NextX, NextY);
				}
			}
			else if (X - 1 == NextX || X + 1 == NextX)
			{
				if (ChessBoard->HasPiece(NextX,NextY) && ChessBoard->Grid[NextX][NextY]->Team != Team) // �̵������� �����ִ�
				{
					ChessBoard->DeletePiece(NextX, NextY); // kill�Լ��� delete���
					ChangePosition(NextX, NextY);
				}

			}
		}

}
void Piece::ChangePosition(int posX, int posY)
{
	ChessBoard->Grid[posX][posY] = this;
	ChessBoard->Grid[X][Y] = nullptr;
	X = posX;
	Y = posY;
}

// ���� �̵��� �� �ִ� ���ΰ�??
//bool canMove = true;
//	if (!canMove)
//	{
//		cout << "�̵��� �� ���°��Դϴ�
// \n";
//	}
//
//	bool isDig = false;
//	if (isDig)
//	{
//
//
//	}
//	else
//	{
//
//	}
//
//
//}
void Piece::Display()
{
	if (Team == ETeam::Green)
	{
		cout << Green << Id << ' ';
		//system("Color OE");
	}
	else if (Team == ETeam::Red)
	{
		cout << Red << Id << ' ';
		//system("Color OF")
	}

}
Rook::Rook() : Piece()
{

}
Rook::Rook(char id, ETeam Team, int X, int Y) : Piece(id, Team, X, Y) //�θ� �Լ�ȣ�� �̹̼���Ǿ��⶧��
{
	this->Id = id;
	this->Team = Team;
	this->X = X;
	this->Y = Y;
}

void Rook::setboard(Board* Board)
{
	ChessBoard = Board;
};
void Rook::RookMovePattern(int NextX, int NextY,int X, int Y)
{
	
}
void Rook::Move(int NextX, int NextY)
{
	if (X == NextX)
	{
		//4���ݺ� ����ȭ
		int CheckX = X;
		int Dir = NextY > Y ? 1 : -1;
		if (Dir == 1)
		{
			for (int CheckY = Y + 1; CheckY < NextY; CheckY++)
			{
				if (ChessBoard->Grid[CheckX][CheckY] != nullptr)
				{
						return;
				}
			}
			if (ChessBoard->HasPiece(NextX, NextY) && ChessBoard->Grid[NextX][NextY]->Team == Team)
			{
					return;
			}
			else if (ChessBoard->HasPiece(NextX, NextY) && ChessBoard->Grid[NextX][NextY]->Team != Team)
			{
					ChessBoard->DeletePiece(NextX, NextY);
					ChangePosition(NextX, NextY);
			}
			
		}
		else if (Dir == -1)
		{
			for (int CheckY = Y + Dir; CheckY != NextY; CheckY += Dir)
			{
				if (ChessBoard->HasPiece(CheckX, CheckY))
				{
					return;
				}
			}
			if (ChessBoard->HasPiece(NextX, NextY))
			{
				if (ChessBoard->Grid[NextX][NextY]->Team == Team)
				{
					return;
				}
				ChessBoard->DeletePiece(NextX, NextY);

			}
		}

	}

	/*if (X == NextX)
	RookMovePattern(NextX, NextY,X,Y);
	else if(Y == NextY)
	RookMovePattern(NextY, NextX,Y,X);*/
}


Board::~Board()
	{
		for (int i = 0; i < SizeX; i++)
		{
			delete[] * Grid[i];
		}
	}


void Board::Initialize()
	{

		AddPiece(new Rook('R', ETeam::Green,0,0));
		AddPiece(new Piece('N', ETeam::Green,1,0));
		AddPiece(new Piece('B', ETeam::Green,2,0));
		AddPiece(new Piece('K', ETeam::Green,3,0));
		AddPiece(new Piece('Q', ETeam::Green,4,0));
		AddPiece(new Piece('B', ETeam::Green,5,0));
		AddPiece(new Piece('N', ETeam::Green,6,0));
		AddPiece(new Rook('R', ETeam::Green,7,0));
					  
		AddPiece(new Rook('R', ETeam::Red,0,7));  
		AddPiece(new Piece('N', ETeam::Red,1,7));  
		AddPiece(new Piece('B', ETeam::Red,2,7));  
		AddPiece(new Piece('K', ETeam::Red,3,7));  
		AddPiece(new Piece('Q', ETeam::Red,4,7));  
		AddPiece(new Piece('B', ETeam::Red,5,7));  
		AddPiece(new Piece('N', ETeam::Red,6,7));  
		AddPiece(new Rook('R', ETeam::Red,7,7)); //shift+alt ����Ű�� ���ٹٲٱⰡ��
		for (int i = 0; i < SizeX; i++)
		{
			for (int j = 0; j <= 6; j++)
			{
				if (j == 1)
				{
					AddPiece(new Piece('P', ETeam::Green, i, j));
					//Grid[i][j] = new Piece('P', ETeam::Green,i,j); //
				}
				else if (j == 6)
				{
					AddPiece(new Piece('P', ETeam::Red, i, j));
					//Grid[i][j] = new Piece('P', ETeam::Red,i,j);
				}
				else if (j >= 2 && j < 6)
				{
					
					Grid[i][j] = nullptr;
				}
			}
		}
	}

	void Board::AddPiece(Piece * Piece)
	{
	if (Piece != nullptr)
	{
		Piece->setboard(this);
		Grid[Piece->X][Piece->Y] = Piece;
	}
	}
	
	bool Board::ISInsideBound(int X, int Y)
	{
		return X >= -1 && X < SizeX && Y >= -1 && Y < SizeY;
	}
	void Board::Display()
	{
		for (int j = SizeY - 1; j >= 0; j--)
		{
		
			cout << Default<< j+1 << ' ';
			for (int i = 0; i < SizeX; i++)
			{
				
				//cout << Grid[i][j] << ' ';
				if (Grid[i][j] == nullptr)
				{
					cout << Default << '*' << ' ';
				}
				else
				{
					Grid[i][j]->Display();
				}
				
			}
			
			cout << "\n";
		}
		cout << Default<< ' ' << ' ';
		for (int i = 0; i < SizeX; i++)
			cout << Default << (char)('a' + i) << ' ';
		cout << '\n';
		
			
	}
	void Board::DeletePiece(int X, int Y)
	{
		if(Grid[X][Y]!=nullptr)
		delete Grid[X][Y];
	}

	bool Board::HasPiece(int NewX, int NewY)
	{
		return Grid[NewX][NewY] != nullptr;
	}
	Chess::Chess()
	{
		ptrBoard = new Board;
	}
	void Chess::Run()
	{
		ptrBoard->Initialize();
		while (true)
		{
			Display();
			HandleInput();
		}
	}

	void Chess::HandleInput()
	{
		char CharX0, CharY0, CharX1, CharY1;
		cin.get(CharX0);
		cin.get(CharY0);
		cin.get(CharX1);
		cin.get(CharY1);
		cin.ignore(10000, '\n');
		int X0 = CharX0 - 97; //'a' // ��ǥ�� �̵��Ұ��� ���Ե�.
		int Y0 = CharY0 - 49; //'0'
		int X1 = CharX1 - 97; //'a'
		int Y1 = CharY1 - 49; //'0'
		cout << X0 <<endl;
		cout << Y0 <<endl;
		cout << X1 <<endl;
		cout << Y1 <<endl;
		if (!ptrBoard->ISInsideBound(X0, Y0) || !ptrBoard->ISInsideBound(X1, Y1)) //�Է°��� �ٸ����� �������
		{
			cout << "���忡 ���� ��ǥ�Դϴ�. \n";
			return;
		}
		if (ptrBoard->Grid[X0][Y0] == nullptr) // �Է°��� ü������ �ƴҰ��
		{
			cout << "�ƹ��͵������ϴ�\n";
			return;
		}
		ptrBoard->Grid[X0][Y0]->Move(X1, Y1);
	}
	void Chess::Display()
	{
		 // cls �Է¹��������� ��������.
		//system("cls");
		ptrBoard->Display();
		
	};


int main()
{
	//��ũ�⼳��
	//Board Play;
	/*Piece* ptrPiece = new Piece('P', ETeam::Green, 0, 0);
	Piece* ptrRook = new Rook('R', ETeam::Green, 1, 1);*/
	//ptrPiece->Move(1,1);
	//ptrRook->Move(1,2);
	Chess*GameRunnig=new Chess;
	//�Է�
	
	//Play.Display();
	GameRunnig->Run();

	return 0;
}
