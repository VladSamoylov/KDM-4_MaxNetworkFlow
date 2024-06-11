#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <limits>

#define ANSI_COLOR_BLUE "\033[34m"
#define ANSI_COLOR_RESET "\033[0m"
#define ANSI_COLOR_GREEN "\033[32m"
#define ANSI_COLOR_RED "\033[31m"

using namespace std;

void CheckData(int&);

class Graph {
private:
	int v;
	int e;
	vector<vector<int>> matrix;
public:
	Graph();
	void SetGraph(const int&, const int&, const int&);
	void Show();
	void MaxFlow();
	void AddEdge(const int&, const int&, const int&);
};

/**
 * @brief Конструктор за замовченням
*/
Graph::Graph() {

	this->v = 13;
	this->e = 24;
	this->matrix.resize(this->v, vector<int>(this->v, 0));
	this->AddEdge(1, 2, 4);
	this->AddEdge(1, 3, 8);
	this->AddEdge(1, 4, 7);
	this->AddEdge(1, 5, 4);
	this->AddEdge(2, 6, 1);
	this->AddEdge(2, 7, 5);
	this->AddEdge(3, 7, 3);
	this->AddEdge(3, 8, 5);
	this->AddEdge(4, 6, 5);
	this->AddEdge(4, 8, 3);
	this->AddEdge(5, 6, 5);
	this->AddEdge(5, 8, 2);
	this->AddEdge(6, 9, 2);
	this->AddEdge(6, 10, 2);
	this->AddEdge(6, 12, 4);
	this->AddEdge(7, 9, 1);
	this->AddEdge(7, 10, 6);
	this->AddEdge(7, 11, 2);
	this->AddEdge(8, 11, 4);
	this->AddEdge(8, 12, 2);
	this->AddEdge(9, 13, 4);
	this->AddEdge(10, 13, 7);
	this->AddEdge(11, 13, 6);
	this->AddEdge(12, 13, 6);	
}

/**
 * @brief Метод, який додає ребро до графа
 * @param i Перша вершина
 * @param j Друга Вершина
 * @param weight Вага
*/
void Graph::AddEdge(const int& i, const int& j, const int& weight) {

	this->matrix[i - 1][j - 1] = weight;
	//this->matrix[j - 1][i - 1] = weight;
}

/**
 * @brief Метод, який створює граф
 * @param var Режим створення графа
 * @param v Кількість вершин
 * @param e Кількість ребер
*/
void Graph::SetGraph(const int& var, const int& v, const int& e) {

	this->v = v;
	this->e = e;
	this->matrix.clear();
	this->matrix.resize(this->v, vector<int>(this->v, 0));

	if (var == 16) {
		this->AddEdge(1, 2, 4);
		this->AddEdge(1, 3, 8);
		this->AddEdge(1, 4, 7);
		this->AddEdge(1, 5, 4);
		this->AddEdge(2, 6, 1);
		this->AddEdge(2, 7, 5);
		this->AddEdge(3, 7, 3);
		this->AddEdge(3, 8, 5);
		this->AddEdge(4, 6, 5);
		this->AddEdge(4, 8, 3);
		this->AddEdge(5, 6, 5);
		this->AddEdge(5, 8, 2);
		this->AddEdge(6, 9, 2);
		this->AddEdge(6, 10, 2);
		this->AddEdge(6, 12, 4);
		this->AddEdge(7, 9, 1);
		this->AddEdge(7, 10, 6);
		this->AddEdge(7, 11, 2);
		this->AddEdge(8, 11, 4);
		this->AddEdge(8, 12, 2);
		this->AddEdge(9, 13, 4);
		this->AddEdge(10, 13, 7);
		this->AddEdge(11, 13, 6);
		this->AddEdge(12, 13, 6);
	}
	if (var == 30) {
		this->AddEdge(1, 2, 13);
		this->AddEdge(1, 3, 10);
		this->AddEdge(1, 4, 13);
		this->AddEdge(2, 5, 12);
		this->AddEdge(2, 6, 10);
		this->AddEdge(3, 6, 5);
		this->AddEdge(3, 7, 5);
		this->AddEdge(4, 7, 9);
		this->AddEdge(4, 8, 4);
		this->AddEdge(5, 9, 10);
		this->AddEdge(5, 10, 4);
		this->AddEdge(6, 9, 4);
		this->AddEdge(6, 11, 11);
		this->AddEdge(7, 9, 15);
		this->AddEdge(8, 11, 5);
		this->AddEdge(8, 12, 3);
		this->AddEdge(9, 13, 17);
		this->AddEdge(10, 13, 2);
		this->AddEdge(11, 13, 14);
		this->AddEdge(12, 13, 5);
		
	}
	if (var == 0) {
		cout << "Enter relationship between vertex" << endl;
		cout << "Example: Va to Vb = weight" << endl;
		int i, j, w;
		for (int n = 0; n < e; n++) {
			do {
				cin >> i >> j >> w;
				if (matrix[i - 1][j - 1] != 0) cout << "Find Dublicate! Please Reentry: ";
			} while (matrix[i - 1][j - 1] != 0);
			this->AddEdge(i, j, w);
		}
	}
}

/**
 * @brief Метод, який знаходить повний потік, а потім його корегує до найбільшого
*/
void Graph::MaxFlow() {

	vector<vector<int>> real_flow(this->v, vector<int>(this->v, 0)); 
	vector<vector<int>> reverse_flow(this->v, vector<int>(this->v, 0));
	vector<int> way;
	vector<int> banned_flow;
	vector<int> flow;
	bool found = false, direct_direction = true, reverse_direction = true;
	int min_flow = 1000, max_flow = 0, nflow = 0;
	int tmp_i = 0;
	int ncount = 1;

	
	while (direct_direction) {
		way.push_back(0);
		while (way[way.size() - 1] != this->v - 1) {
			for (int i = 0; i < this->v; i++) {
				auto fbanned = find(banned_flow.begin(), banned_flow.end(), i);
				if (this->matrix[way[way.size() - 1]][i] != 0 && fbanned == banned_flow.end()) {
					if (max_flow < this->matrix[way[way.size() - 1]][i] - real_flow[way[way.size() - 1]][i]) {
						max_flow = this->matrix[way[way.size() - 1]][i] - real_flow[way[way.size() - 1]][i];
						tmp_i = i;
						found = true;
					}
				}
			}
			if (found) {
				if (min_flow > this->matrix[way[way.size() - 1]][tmp_i] - real_flow[way[way.size() - 1]][tmp_i]) min_flow = this->matrix[way[way.size() - 1]][tmp_i] - real_flow[way[way.size() - 1]][tmp_i];
				way.push_back(tmp_i);
			}
			else if (!found && way[way.size() - 1] == 0) { direct_direction = false; cout << "\nDidn't find any way! Direct direction is over..." << endl; break; }
			else { banned_flow.push_back(way[way.size() - 1]);  cout << "Didn't find the way in vertex: " << way[way.size() - 1] + 1 << ". Return to " << way[way.size() - 2] + 1 << endl; if (!way.empty()) way.pop_back(); }
			max_flow = 0; tmp_i = 0; found = false;
		}
		if (direct_direction) {
			cout << "\n--------------------#" << ncount << "--------------------" << endl;
			for (int i = 0; i < way.size(); i++) {
				cout << ANSI_COLOR_GREEN << way[i] + 1 << ANSI_COLOR_RESET;
				if (i != way.size() - 1) cout << "-";
			}
			cout << "  min (";
			for (int i = 0; i < way.size() - 1; i++) {
				cout << matrix[way[i]][way[i + 1]] - real_flow[way[i]][way[i + 1]];
				if (i != way.size() - 2) cout << ", ";
				else cout << ") = " << ANSI_COLOR_GREEN << min_flow << ANSI_COLOR_RESET;
			}cout << endl;
			for (int i = 0; i < way.size() - 1; i++) {
				real_flow[way[i]][way[i + 1]] += min_flow;
				if (real_flow[way[i]][way[i + 1]] > this->matrix[way[i]][way[i + 1]]) cerr << "Error flow" << endl;
				if (real_flow[way[i]][way[i + 1]] == this->matrix[way[i]][way[i + 1]]) { cout << "(" << way[i] + 1 << ", " << way[i + 1] + 1 << ") - saturated" << endl; }
			}
			flow.push_back(min_flow);
			ncount++;
		}		
		way.clear();		
		min_flow = 1000;
	}
	banned_flow.clear();
	cout << "\nV = ";
	for (int i = 0; i < flow.size(); i++) {
		nflow += flow[i];
		cout << ANSI_COLOR_GREEN << flow[i] << ANSI_COLOR_RESET;
		if (i != flow.size() - 1) cout << " + ";
	}cout << " = " << ANSI_COLOR_BLUE << nflow << ANSI_COLOR_RESET << endl;
	 
	for (int i = 0; i < this->v; i++) {
		for (int j = 0; j < this->v; j++) {
			if (real_flow[i][j] != 0) real_flow[j][i] = real_flow[i][j];
			if (this->matrix[i][j] != 0) this->matrix[j][i] = this->matrix[i][j];
		}
	}

	cout << "\nAdjust the max flow: " << endl;
	while (reverse_direction) {
		way.push_back(0);
		while (way[way.size() - 1] != this->v - 1) {
			for (int i = 0; i < this->v; i++) {
				auto fbanned = find(banned_flow.begin(), banned_flow.end(), i);
				auto fway = find(way.begin(), way.end(), i);
				if (this->matrix[way[way.size() - 1]][i] != 0 && way[way.size() - 1] < i && fway == way.end() && fbanned == banned_flow.end()) {
					if (max_flow < this->matrix[way[way.size() - 1]][i] - real_flow[way[way.size() - 1]][i]) {
						max_flow = this->matrix[way[way.size() - 1]][i] - real_flow[way[way.size() - 1]][i];
						tmp_i = i;
						found = true;
					}
				}
				else if (real_flow[way[way.size() - 1]][i] != 0 && way[way.size() - 1] > i && fway == way.end() && fbanned == banned_flow.end()) {
					reverse_flow[way[way.size() - 1]][i] = 1;
					tmp_i = i;
					found = true;
				}
			}
			if (found) {
				if (min_flow > this->matrix[way[way.size() - 1]][tmp_i] - real_flow[way[way.size() - 1]][tmp_i] && reverse_flow[way[way.size() - 1]][tmp_i] != 1) min_flow = this->matrix[way[way.size() - 1]][tmp_i] - real_flow[way[way.size() - 1]][tmp_i];
				way.push_back(tmp_i);
			}
			else if (!found && way[way.size() - 1] == 0) { reverse_direction = false; cout << "\nDidn't find any way! Direct reverse is over..." << endl; break; }
			else { banned_flow.push_back(way[way.size() - 1]);  cout << "Didn't find the way in vertex: " << way[way.size() - 1] + 1 << ". Return to " << way[way.size() - 2] + 1 << endl; if (!way.empty()) way.pop_back(); }
			max_flow = 0; tmp_i = 0; found = false;
		}
		if (reverse_direction) {
			cout << "\n--------------------#" << ncount << "--------------------" << endl;
			for (int i = 0; i < way.size() - 1; i++) {
				if (reverse_flow[way[i]][way[i + 1]] == 1) cout << ANSI_COLOR_RED << way[i] + 1 << ANSI_COLOR_RESET;
				else cout << ANSI_COLOR_GREEN << way[i] + 1 << ANSI_COLOR_RESET;
				if (i != way.size() - 1) cout << "-";
				if (i == way.size() - 2) cout << ANSI_COLOR_GREEN << way[i + 1] + 1 << ANSI_COLOR_RESET;
			}
			cout << "  min (";
			for (int i = 0; i < way.size() - 1; i++) {
				if (reverse_flow[way[i]][way[i + 1]] == 1) cout << ANSI_COLOR_RED << real_flow[way[i]][way[i + 1]] << ANSI_COLOR_RESET;
				else cout << matrix[way[i]][way[i + 1]] - real_flow[way[i]][way[i + 1]];
				if (i != way.size() - 2) cout << ", ";
				else cout << ") = " << ANSI_COLOR_GREEN << min_flow << ANSI_COLOR_RESET;
			}cout << endl;
			for (int i = 0; i < way.size() - 1; i++) {
				if (real_flow[way[i]][way[i + 1]] > this->matrix[way[i]][way[i + 1]]) cerr << "Error flow" << endl;
				if (reverse_flow[way[i]][way[i + 1]] == 1) { real_flow[way[i]][way[i + 1]] -= min_flow; real_flow[way[i + 1]][way[i]] -= min_flow; }
				else { real_flow[way[i]][way[i + 1]] += min_flow; real_flow[way[i + 1]][way[i]] += min_flow; }
			}
			cout << "\nV = " << nflow << " + " << min_flow << " = ";
			nflow += min_flow;
			cout << ANSI_COLOR_BLUE << nflow << ANSI_COLOR_RESET << endl;
			ncount++;
		}
		way.clear();
		reverse_flow.resize(this->v, vector<int>(this->v, 0));
		min_flow = 1000;
	}

	cout << "\nVmax = " << ANSI_COLOR_BLUE << nflow << ANSI_COLOR_RESET << endl;

	cout << "\n-----------Graph-----------\n";
	for (int i = 0; i < this->v; i++) {
		for (int j = 0; j < this->v; j++) {
			if (this->matrix[i][j] != 0) {
				cout << setw(1) << left << "V" << setw(2) << i + 1 << setw(5) << " to V" << setw(2) << j + 1 << setw(3) << " = " << this->matrix[i][j] << "(" << ANSI_COLOR_GREEN << real_flow[i][j] << ANSI_COLOR_RESET << ")" << endl;
			}
		}
	}
}

/**
 * @brief Метод, який відображає взаємозв'язок вершин у графі
*/
void Graph::Show() {

	cout << "-----------Graph-----------\n";
	for (int i = 0; i < this->v; i++) {
		for (int j = 0; j < this->v; j++) {
			if (this->matrix[i][j] != 0) {
				cout << setw(1) << left << "V" << setw(2) << i + 1 << setw(5) << " to V" << setw(2) << j + 1 << setw(3) << " = " << this->matrix[i][j] << endl;
			}
		}
	}
}

/**
 * @brief Функція, яка перевіряє правильність введення даних користувачем
 * @param x Данні для перевірки
*/
void CheckData(int& x) {

	cin.ignore(666, '\n');
	while (true) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(666, '\n');
			cerr << "You enter wrong data! Please enter correct data: \n";
			cin >> x;
			cin.ignore(666, '\n');
		}
		else break;
	}
}

int main() {

	int work = 1;
	int task = 0, v = 0, e = 0;
	Graph g;

	while (work != 0) {
		switch (work) {
		case 1:
			g.Show();
			g.MaxFlow();
			break;
		case 2:
			cout << "Choice Graph (var 16 or 30) or set your own graph (enter - 0): ";
			cin >> task;
			CheckData(task);
			if (task == 16) { g.SetGraph(16, 13, 24); cout << "Completed...\n"; }
			else if (task == 30) { g.SetGraph(30, 13, 20); cout << "Completed...\n"; }
			else if (task == 0) {
				cout << "Set amount of vertex: ";
				do { cin >> v; CheckData(v); if (v < 1) cout << "Error! Min amount of vertex = 1 Reentry: "; } while (v < 1);
				cout << "Set amount of faces: ";
				do { cin >> e; CheckData(e); if (e < v - 1) cout << "Error! (min e = " << v - 1 << ") Reentry: "; } while (e < v - 1);
				g.SetGraph(0, v, e);
			}
			else cout << "Nothing happened..\n";
			break;
		case 3:
			g.Show();
			break;
		}

		if (work != 0) {
			cout << "\n-----------Menu of actions-----------\n";
			cout << "Enter - 1 to run the maximum flow in the network" << endl;
			cout << "Enter - 2 to set new Graph" << endl;
			cout << "Enter - 3 to show current Graph" << endl;
			cout << "Enter - 0 for Exit" << endl;
			cin >> work;
			CheckData(work);
		}
	}

	return 0;
}
